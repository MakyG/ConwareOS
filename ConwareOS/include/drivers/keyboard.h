#ifndef __CONWAREOS_DRIVERS_KEYBOARD_H
#define __CONWAREOS_DRIVERS_KEYBOARD_H

#include <common/types.h>
#include <HWcommunication/interrupts.h>
#include <drivers/driver.h>
#include <HWcommunication/port.h>

namespace ConwareOS
{
    namespace drivers
    {
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();
            
            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
            
        };

        class KeyboardDriver : public ConwareOS::HWcommunication::InterruptHandler, public Driver
        {
            ConwareOS::HWcommunication::Port8Bit dataport;
            ConwareOS::HWcommunication::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(ConwareOS::HWcommunication::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual ConwareOS::common::uint32_t HandleInterrupt(ConwareOS::common::uint32_t esp);
            virtual void Activate();
        };
    }
}

#endif 
