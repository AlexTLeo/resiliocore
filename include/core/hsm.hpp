/**
 * @file hsm.hpp
 * @brief Hierarchical State Machine (HSM) implementation for event-driven state management.
 */

#pragma once
#include <cstdint>

namespace Engine::Core {

enum class EventId : uint16_t {
    NONE = 0,
};

struct Event {
    EventId id;
    uint32_t payload;
};

enum class StateResult {
    HANDLED,
    IGNORED,
    TRAN_SUPER, // Handled, but defer to parent/super state
    TRAN_TARGET // Transition to a new target state
};

class HierarchicalStateMachine ; // Forward declaration

// State handler function pointer type
using StateHandler = StateResult (*)(HierarchicalStateMachine & sm, const Event& evt);

class HierarchicalStateMachine  {
public:
    explicit HierarchicalStateMachine (StateHandler initial_state) 
        : current_state_(initial_state), target_state_(nullptr) {}

    void init() {
        Event entry_evt{EventId::NONE, 0};
        if (current_state_) {
            current_state_(*this, entry_evt);
        }
    }

    void dispatch(const Event& evt) {
        if (!current_state_) return;

        StateResult res = current_state_(*this, evt);

        // Handle State Transition
        if (res == StateResult::TRAN_TARGET && target_state_ != nullptr) {
            // 1. Execute Exit Action on Current State
            Event exit_evt{EventId::NONE, 0}; // Use reserved ID for exit if expanded
            current_state_(*this, exit_evt);

            // 2. Update State Pointer
            current_state_ = target_state_;
            target_state_ = nullptr;

            // 3. Execute Entry Action on New State
            Event entry_evt{EventId::NONE, 0};
            current_state_(*this, entry_evt);
        }
    }

    StateHandler getCurrentState() const { return current_state_; }

private:
    StateHandler current_state_;
    StateHandler target_state_;

    void transitionTo(StateHandler target) {
        target_state_ = target;
    }
};

} // namespace Engine::Core