#ifndef __CONWAREOS__HARDWARECOMMUNICATION__PCI_H
#define __CONWAREOS__HARDWARECOMMUNICATION__PCI_H

#include <HWcommunication/port.h>
#include <drivers/driver.h>
#include <common/types.h>
#include <HWcommunication/interrupts.h>

namespace ConwareOS
{
    namespace HWcommunication
    {

        class PeripheralComponentInterconnectDeviceDescriptor
        {
        public:
            ConwareOS::common::uint32_t portBase;
            ConwareOS::common::uint32_t interrupt;

            ConwareOS::common::uint16_t bus;
            ConwareOS::common::uint16_t device;
            ConwareOS::common::uint16_t function;

            ConwareOS::common::uint16_t vendor_id;
            ConwareOS::common::uint16_t device_id;

            ConwareOS::common::uint8_t class_id;
            ConwareOS::common::uint8_t subclass_id;
            ConwareOS::common::uint8_t interface_id;

            ConwareOS::common::uint8_t revision;

            PeripheralComponentInterconnectDeviceDescriptor();
            ~PeripheralComponentInterconnectDeviceDescriptor();

        };


        class PeripheralComponentInterconnectController
        {
            Port32Bit dataPort;
            Port32Bit commandPort;

        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();

            ConwareOS::common::uint32_t Read(ConwareOS::common::uint16_t bus, ConwareOS::common::uint16_t device, ConwareOS::common::uint16_t function, ConwareOS::common::uint32_t registeroffset);
            void Write(ConwareOS::common::uint16_t bus, ConwareOS::common::uint16_t device, ConwareOS::common::uint16_t function, ConwareOS::common::uint32_t registeroffset, ConwareOS::common::uint32_t value);
            bool DeviceHasFunctions(ConwareOS::common::uint16_t bus, ConwareOS::common::uint16_t device);

            void SelectDrivers(ConwareOS::drivers::DriverManager* driverManager);
            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(ConwareOS::common::uint16_t bus, ConwareOS::common::uint16_t device, ConwareOS::common::uint16_t function);
        };
    }
}

#endif 
