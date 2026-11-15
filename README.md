# resiliocore

Embedded real-time control and automated Hardware-in-the-Loop (HiL) validation framework for a legged robotic actuator testbed.

## Overview

A two-tier embedded robotics architecture separating hard real-time control from high-level telemetry, simulation, and automated testing:

* **Real-Time Edge (Dual-Core MCU / RTOS):** Dedicates one core to deterministic actuator control loops, bus communication, jitter profiling, and fault watchdogs, while isolating asynchronous telemetry and host messaging on the second core.
* **Host Compute (Linux / ROS 2):** Handles high-level orchestration, live telemetry visualisation, data logging, and automated CI/CD hardware verification.

## Planned Features & Roadmap

- [ ] **Repository & Build Setup:** Project scaffold, RTOS workspace manifest, and cross-compilation pipeline.
- [ ] **Dual-Core RTOS Spine:** Core-pinned real-time control thread decoupled from asynchronous host communications via lock-free queues.
- [ ] **Actuator Bus & Control Loop:** Closed-loop motor communication and impedance control with gravity compensation.
- [ ] **Safety & Observability:** Watchdog fault handling, safe fallback states, and cycle-accurate loop jitter telemetry.
- [ ] **ROS 2 & Visualisation Bridge:** Embedded-to-host messaging for real-time state plotting and parameter tuning.
- [ ] **Physical Testbed Assembly:** Linear-constrained single-leg rig and power distribution.
- [ ] **CI & Hardware-in-the-Loop (HiL):** Cloud static analysis/unit tests paired with an automated self-hosted runner for hardware flashing, step-response verification, and fault-injection testing.

### In Progress / Next Steps
- [ ] **Basic PWM:** Write a basic PWM driver
- [ ] **Test PWM:** Test PWM driver outputs with logic analyser 

## Planned Directory Structure
```text
.
├── boards/                 # Hardware-specific overlays and board configurations
├── include/
│   ├── control/            # Control laws, kinematics, and state estimation headers
│   ├── core/               # Dual-core scheduling, IPC queues, and timing utilities
│   ├── drivers/            # Peripheral driver interfaces, hardware abstraction, protocols, etc.
│   └── safety/             # Watchdogs, fault handling, and limit enforcement
├── src/
│   ├── control/            
│   ├── core/               
│   ├── drivers/            
│   └── safety/             
├── ros2_ws/                # Host-side ROS 2 packages, launch files, and visualisation configs
├── tests/
│   ├── unit/               # Host-compiled unit tests for control and state logic
│   └── hil/                # Automated Hardware-in-the-Loop test suites
├── .github/workflows/      # Cloud CI and self-hosted HiL pipeline definitions
├── CMakeLists.txt
├── prj.conf
└── west.yml
```

## Instructions
Remember to activate the zepyhr venv. For example:
```bash
source ~/zephyrproject/.venv/bin/activate
```