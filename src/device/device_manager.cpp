#include "device/device_manager.hpp"
#include "irq/irq_controller.hpp"
#include "dma/dma_engine.hpp"
#include "core/event_queue.hpp"
#include "device/device.hpp"

// Register device
void DeviceManager::register_device(Device* dev) {

    // Store device pointer in internal list
    devices.push_back(dev);
}

// Wire IRQ controller into system
void DeviceManager::set_irq_controller(IRQController* controller) {

    // Store IRQ controller reference
    irq = controller;
}

// Wire DMA engine into system
void DeviceManager::set_dma_engine(DMAEngine* engine) {

    // Store DMA engine reference
    dma = engine;
}

// Wire global event queue into system
void DeviceManager::set_event_queue(EventQueue* q) {

    // Store event queue reference
    event_queue = q;
}

// Initialize all registered devices
void DeviceManager::init_all() {

    // Iterate through all devices and initialize them
    for (auto* d : devices) {

        // Call device-specific initialization logic
        d->init();
    }
}

// Shutdown all registered devices
void DeviceManager::shutdown_all() {

    // Iterate through all devices and shutdown cleanly
    for (auto* d : devices) {

        // Call device-specific shutdown logic
        d->shutdown();
    }
}