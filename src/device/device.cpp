#include "device/device.hpp"
#include "mmio/mmio.hpp"
#include "irq/irq_controller.hpp"

// Return reference to MMIO register space
MMIORegion& Device::mmio() {
    return *registers;
}

// Store IRQ controller pointer (used by devices to raise interrupts)
void Device::set_irq_controller(IRQController* ctrl) {
    irq = ctrl;
}