#include <common/types.h>
#include <gdt.h>
#include <HWcommunication/interrupts.h>
#include <HWcommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>

using namespace ConwareOS;
using namespace ConwareOS::common;
using namespace ConwareOS::drivers;
using namespace ConwareOS::HWcommunication;

void print(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    static uint8_t x = 0,y = 0;
    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void printHex(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    print(foo);
}

class PrintKeyboardEventHandler : public KeyboardEventHandler
{
public:
    void OnKeyDown(char c)
    {
        char* foo = " ";
        foo[0] = c;
        print(foo);
    }
};

class MouseToConsole : public MouseEventHandler
{
    int8_t x, y;
public:
    MouseToConsole(){}
    virtual void OnActive()
    {
        uint16_t* VideoMemory = (uint16_t*)0xb8000;
        
        x = 40;
        y = 12;

        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);  
    }
    void OnMouseMove(int x_offset, int y_offset)
    {
        static uint16_t* VideoMemory = (uint16_t*)0xb8000;
                
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);
        
        x += x_offset;
        
        if(x >= 80) x = 79;
        if(x < 0) x = 0;

        y += y_offset;
        
        if(y >= 25) y = 24;
        if(y < 0) y = 0;
        
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);
    }
};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
    {
        (*i)();
    }
}


extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    print("################################################################################");
    print("#______________________________Conware_OS_limited______________________________#\n");
    print("Default keyboard layout: US\n");
    GlobalDescriptorTable gdt;
    InterruptManager interrupts(0x20, &gdt);
    
    print("Hardware initialization: Stage 1...\n");
    
    DriverManager drvManager;
    
    PrintKeyboardEventHandler kbhandler;
    
    KeyboardDriver keyboard(&interrupts, &kbhandler);
    drvManager.AddDriver(&keyboard);
    
    MouseToConsole mousehandler;
    MouseDriver mouse(&interrupts, &mousehandler);
    drvManager.AddDriver(&mouse);
    
    PeripheralComponentInterconnectController PCIcontroller;
    PCIcontroller.SelectDrivers(&drvManager);
    print("Hardware initialization: Stage 2...\n");
    
    drvManager.ActivateAll();
    print("Hardware initialization: Stage 3...\n");
    
    interrupts.Activate();
    print("Conware ready.\n");
    
    while(1);
}
