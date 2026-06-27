#include "irq/irq_controller.hpp"

// Raise interrupt → convert to event
void IRQController::raise(int device_id, int irq_line) {
    if (event_queue) {
        event_queue->push({
            EventType::IRQ,
            device_id,
            irq_line
        });
    }
}

// Connect IRQ controller to system event bus
void IRQController::set_event_queue(EventQueue* q) {
    event_queue = q;
}