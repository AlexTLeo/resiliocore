#include "include/core/hsm.hpp"

namespace Engine::States {

using namespace Engine::Core;

// Parent State: Operational Domain
StateResult State_Operational(StateMachine& sm, const Event& evt) {
    switch (evt.id) {
        case EventId::CRITICAL_FAULT:
            sm.TransitionTo(State_SafeFailRecovery);
            return StateResult::TRAN_TARGET;
        default:
            return StateResult::IGNORED;
    }
}

// Child State: Active Execution Loop
StateResult State_Execute(StateMachine& sm, const Event& evt) {
    switch (evt.id) {
        case EventId::POWER_LOW:
            sm.TransitionTo(State_SleepHarvest);
            return StateResult::TRAN_TARGET;
        default:
            // Delegate unhandled events to the parent (Operational)
            return State_Operational(sm, evt); 
    }
}

// Fault Recovery State
StateResult State_SafeFailRecovery(StateMachine& sm, const Event& evt) {
    // Actuators are locked out at entry
    return StateResult::HANDLED;
}

} // namespace Engine::States