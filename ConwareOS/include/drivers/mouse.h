#ifndef __CONWAREOS_DRIVERS_MOUSE_H
#define __CONWAREOS_DRIVERS_MOUSE_H

#include <common/types.h>
#include <HWcommunication/port.h>
#include <drivers/driver.h>
#include <HWcommunication/interrupts.h>

namespace ConwareOS
{
    namespace drivers
    {
        class MouseEventHandler
        {
        public:
            MouseEventHandler();
            
            virtual void OnActivate();
            virtual void OnMouseDown(ConwareOS::common::uint8_t button);
            virtual void OnMouseUp(ConwareOS::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
            
        class MouseDriver : public ConwareOS::HWcommunication::InterruptHandler, public Driver
        {
            ConwareOS::HWcommunication::Port8Bit dataport;
            ConwareOS::HWcommunication::Port8Bit commandport;
            
            ConwareOS::common::uint8_t buffer[3];
            ConwareOS::common::uint8_t offset;
            ConwareOS::common::uint8_t buttons;
            
            MouseEventHandler* handler;
            

        public:
            MouseDriver(ConwareOS::HWcommunication::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual ConwareOS::common::uint32_t HandleInterrupt(ConwareOS::common::uint32_t esp);
            virtual void Activate();
        };
    }
}

#endif 
