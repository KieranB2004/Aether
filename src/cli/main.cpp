#include "device/device_manager.hpp"
#include "device/device.hpp"
#include "mmio/mmio.hpp"
#include "irq/irq_controller.hpp"
#include "dma/dma_engine.hpp"
#include "core/event_queue.hpp"
#include "core/scheduler.hpp"
#include <iostream>
#include <cstring>

// Fake device used only to verify the framework works
// This simulates a real hardware device (GPU / storage / etc.)
class FakeDevice : public Device {
public:
    FakeDevice() {

        // Allocate 64 bytes of MMIO registers for this device
        registers = std::make_unique<MMIORegion>(64);
    }

    void init() override {

        // Called when DeviceManager initializes this device
        std::cout << "[FakeDevice] init()\n";

        // Write to CONTROL register (offset 0x00)
        mmio().write32(0x00, 0x1);
    }

    void shutdown() override {

        // Called when DeviceManager shuts down this device
        std::cout << "[FakeDevice] shutdown()\n";

        // Clear CONTROL register (stop device)
        mmio().write32(0x00, 0x0);
    }

    const char* name() const override {

        // Used for logging and debugging inside DeviceManager
        return "FakeDevice";
    }
};

int main() {

    // Create central device manager (owns all devices)
    DeviceManager mgr;

    // Create global event queue (system bus for IRQ + DMA + device events)
    EventQueue event_queue;

    // Create scheduler (single execution loop for all system events)
    Scheduler scheduler(event_queue);

    // Create interrupt controller (hardware IRQ simulation layer)
    IRQController irq;

    // Create DMA engine (hardware DMA simulation layer)
    DMAEngine dma;

    // Start DMA engine worker thread
    dma.start();

    // Create test device
    FakeDevice* dev = new FakeDevice();

    // Register device with system
    mgr.register_device(dev);

    // Connect DeviceManager to event system (IMPORTANT for Step 5 consistency)
    mgr.set_event_queue(&event_queue);

    // Connect IRQ controller to event system
    irq.set_event_queue(&event_queue);

    // Connect DMA engine to event system
    dma.set_event_queue(&event_queue);

    // Wire DeviceManager with subsystems (for future extensibility)
    mgr.set_irq_controller(&irq);
    mgr.set_dma_engine(&dma);

    // Register IRQ handler in scheduler
    scheduler.on_event(EventType::IRQ, [](int device_id, int line) {

        // Handles hardware interrupt events
        std::cout << "[Scheduler] IRQ device=" << device_id
                  << " line=" << line << "\n";
    });

    // Register DMA completion handler in scheduler
    scheduler.on_event(EventType::DMA_COMPLETE, [](int device_id, int line) {

        // Handles DMA completion events
        std::cout << "[Scheduler] DMA complete device=" << device_id
                  << " line=" << line << "\n";
    });

    // Register device lifecycle events (optional but consistent system model)
    scheduler.on_event(EventType::DEVICE_INIT, [](int device_id, int) {

        // Device initialization event
        std::cout << "[Scheduler] DEVICE INIT device=" << device_id << "\n";
    });

    scheduler.on_event(EventType::DEVICE_SHUTDOWN, [](int device_id, int) {

        // Device shutdown event
        std::cout << "[Scheduler] DEVICE SHUTDOWN device=" << device_id << "\n";
    });

    // Boot system (initialize all devices)
    mgr.init_all();

    // Process all startup events
    scheduler.run();

    // Shutdown system (shutdown all devices)
    mgr.shutdown_all();

    // Process shutdown events
    scheduler.run();

    // Stop DMA engine cleanly
    dma.stop();

    // Cleanup device memory
    delete dev;

    return 0;
}