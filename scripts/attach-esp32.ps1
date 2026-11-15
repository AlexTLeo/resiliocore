# attach-esp32.ps1
# Keeps ESP32 (CP2102: 10c4:ea60) attached to WSL2 Ubuntu across replugs and WSL restarts.

$HardwareId = "10c4:ea60"
$Distro = "Ubuntu"

Write-Host "Starting ESP32 WSL2 auto-attach watcher for $HardwareId..." -ForegroundColor Cyan

while ($true) {
    # 1. Verify WSL2 kernel is booted before calling usbipd (prevents 'not USBIP capable' exit)
    wsl -d $Distro -e true 2>$null
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Waiting for WSL ($Distro) to start..." -ForegroundColor Yellow
        Start-Sleep -Seconds 3
        continue
    }

    # 2. Ensure device is bound/shared (silent no-op if already bound)
    usbipd bind --hardware-id $HardwareId 2>$null

    # 3. Start blocking auto-attach loop; respawns automatically if WSL restarts or usbipd exits
    Write-Host "WSL active. Watching for ESP32 ($HardwareId)..." -ForegroundColor Green
    usbipd attach --wsl --auto-attach --hardware-id $HardwareId

    Write-Host "usbipd watcher exited. Retrying in 2 seconds..." -ForegroundColor Yellow
    Start-Sleep -Seconds 2
}
