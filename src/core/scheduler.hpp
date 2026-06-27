#pragma once

#include "core/event_queue.hpp"
#include <functional>

// Central event dispatcher for entire system
class Scheduler {
public:
    Scheduler(EventQueue& q);

    // Run until no events remain
    void run();

    // Register handlers for different event types
    void on_irq(std::function<void(int, int)> fn);
    void on_dma_complete(std::function<void(int, int)> fn);

private:
    EventQueue& queue;

    std::function<void(int, int)> irq_handler;
    std::function<void(int, int)> dma_handler;
};