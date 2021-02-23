#include <HWcommunication/pci.h>
using namespace ConwareOS::common;
using namespace ConwareOS::drivers;
using namespace ConwareOS::HWcommunication;

 
PeripheralComponentInterconnectDeviceDescriptor::PeripheralComponentInterconnectDeviceDescriptor(){}
PeripheralComponentInterconnectDeviceDescriptor::~PeripheralComponentInterconnectDeviceDescriptor(){}

PeripheralComponentInterconnectController::PeripheralComponentInterconnectController() : dataPort(0xCFC), commandPort(0xCF8)
{
    
}
PeripheralComponentInterconnectController::~PeripheralComponentInterconnectController(){}

uint32_t PeripheralComponentInterconnectController::Read(uint16_t bus, uint16_t device, uint16_t function, uint32_t registerOffset)
{
uint32_t id =
    0x1 << 31
    | ((bus & 0xFF) << 16)
    | ((device & 0x1F) << 11)
    | ((function & 0x07) << 8)
    | (registerOffset & 0xFC);
commandPort.Write(id);
uint32_t result = dataPort.Read();
return result >> (8 * (registerOffset % 4));
}

void PeripheralComponentInterconnectController::Write(uint16_t bus, uint16_t device, uint16_t function, uint32_t registerOffset, uint32_t value)
{
    uint32_t id =
    0x1 << 31
    | ((bus & 0xFF) << 16)
    | ((device & 0x1F) << 11)
    | ((function & 0x07) << 8)
    | (registerOffset & 0xFC);
commandPort.Write(id);
dataPort.Write(value);
}

bool PeripheralComponentInterconnectController:: DeviceHasFunctions(common::uint16_t bus, common::uint16_t device)
{
    return Read(bus, device, 0, 0x0E) & (1 << 7);
}

void print(char* str);
void printHex(uint8_t);

void PeripheralComponentInterconnectController::SelectDrivers(DriverManager* driverManager)
{
    for(int bus = 0; bus < 8; bus++)
    {
        for(int device = 0; device < 32; device++)
        {
            int numFunctions = DeviceHasFunctions(bus, device) ? 8 : 1;
            for(int function = 0; function < numFunctions; function++)
            {
                PeripheralComponentInterconnectDeviceDescriptor dev = GetDeviceDescriptor(bus, device, function);
                
                if(dev.vendor_id == 0x0000 || dev.vendor_id == 0xFFFF)
                    continue;
                
                print("PCI BUS ");
                printHex(bus & 0xFF);
                
                print(", DEVICE ");
                printHex(device & 0xFF);
                
                print(", FUNCTION ");
                printHex(function & 0xFF);
                
                print(", = VENDOR ");
                printHex((dev.vendor_id & 0xFF00) >> 8);
                printHex(dev.vendor_id & 0xFF);

                print(", DEVICE ");
                printHex((dev.device_id & 0xFF00) >> 8);
                printHex(dev.device_id & 0xFF);
                
                print("\n");
            }
        }
    }
}

PeripheralComponentInterconnectDeviceDescriptor PeripheralComponentInterconnectController:: GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function)
{
PeripheralComponentInterconnectDeviceDescriptor result;
    
result.bus = bus;
result.device = device;
result.function = function;
    
result.vendor_id = Read(bus, device, function, 0x00);
result.device_id = Read(bus, device, function, 0x02);

result.class_id = Read(bus, device, function, 0x0B);
result.subclass_id = Read(bus, device, function, 0x0A);
result.interface_id = Read(bus, device, function, 0x09);

result.revision = Read(bus, device, function, 0x08);
result.interrupt = Read(bus, device, function, 0x3D);

return result;
}

