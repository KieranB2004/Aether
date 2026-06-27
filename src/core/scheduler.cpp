#include "core/scheduler.hpp"

// Convert enum to index
static int idx(EventType t) {
    return static_cast<int>(t);
}

// Constructor
Scheduler::Scheduler(EventQueue& q) : queue(q) {}

// Main system execution loop
void Scheduler::run() {

    Event e;

    // Process all events in priority order
    while (queue.pop(e)) {

        // Dispatch based on event type
        auto& fn = handlers[idx(e.type)];

        if (fn) {
            fn(e.device_id, e.code);
        }
    }
}

// Register handler for event type
void Scheduler::on_event(EventType type, std::function<void(int,int)> fn) {

    handlers[idx(type)] = fn;
}