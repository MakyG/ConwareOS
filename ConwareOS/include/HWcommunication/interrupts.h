#ifndef __CONWAREOS__HWCOMMUNICATION__INTERRUPTMANAGER_H
#define __CONWAREOS__HWCOMMUNICATION__INTERRUPTMANAGER_H
#include <gdt.h>
#include <common/types.h>
#include <HWcommunication/port.h>

namespace ConwareOS
{
    namespace HWcommunication
    {
                

        class InterruptManager;

        class InterruptHandler
        {
        protected:
            ConwareOS::common::uint8_t InterruptNumber;
            InterruptManager* interruptManager;
            InterruptHandler(InterruptManager* interruptManager, ConwareOS::common::uint8_t InterruptNumber);
            ~InterruptHandler();
        public:
            virtual ConwareOS::common::uint32_t HandleInterrupt(ConwareOS::common::uint32_t esp);
        };


        class InterruptManager
        {
        friend class InterruptHandler;
        public:

            static InterruptManager* ActiveInterruptManager;
            InterruptHandler* handlers[256];

            struct GateDescriptor
            {
                ConwareOS::common::uint16_t handlerAddressLowBits;
                ConwareOS::common::uint16_t gdt_codeSegmentSelector;
                ConwareOS::common::uint8_t reserved;
                ConwareOS::common::uint8_t access;
                ConwareOS::common::uint16_t handlerAddressHighBits;
            } __attribute__((packed));
            
            static GateDescriptor interruptDescriptorTable[256];
            
            struct InterruptDescriptorTablePointer
            {
                ConwareOS::common::uint16_t size;
                ConwareOS::common::uint32_t base;
            } __attribute__((packed));

            ConwareOS::common::uint16_t hardwareInterruptOffset;
            static void SetInterruptDescriptorTableEntry(ConwareOS::common::uint8_t interrupt,
            ConwareOS::common::uint16_t codeSegmentSelectorOffset, void (*handler)(),
            ConwareOS::common::uint8_t DescriptorPrivilegeLevel, ConwareOS::common::uint8_t DescriptorType);
            
            static void InterruptIgnore();
            static void HandleInterruptRequest0x00();
            static void HandleInterruptRequest0x01();
            static void HandleInterruptRequest0x02();
            static void HandleInterruptRequest0x03();
            static void HandleInterruptRequest0x04();
            static void HandleInterruptRequest0x05();
            static void HandleInterruptRequest0x06();
            static void HandleInterruptRequest0x07();
            static void HandleInterruptRequest0x08();
            static void HandleInterruptRequest0x09();
            static void HandleInterruptRequest0x0A();
            static void HandleInterruptRequest0x0B();
            static void HandleInterruptRequest0x0C();
            static void HandleInterruptRequest0x0D();
            static void HandleInterruptRequest0x0E();
            static void HandleInterruptRequest0x0F();
            static void HandleInterruptRequest0x31();
            static void HandleException0x00();
            static void HandleException0x01();
            static void HandleException0x02();
            static void HandleException0x03();
            static void HandleException0x04();
            static void HandleException0x05();
            static void HandleException0x06();
            static void HandleException0x07();
            static void HandleException0x08();
            static void HandleException0x09();
            static void HandleException0x0A();
            static void HandleException0x0B();
            static void HandleException0x0C();
            static void HandleException0x0D();
            static void HandleException0x0E();
            static void HandleException0x0F();
            static void HandleException0x10();
            static void HandleException0x11();
            static void HandleException0x12();
            static void HandleException0x13();

            static ConwareOS::common::uint32_t HandleInterrupt(ConwareOS::common::uint8_t interrupt, ConwareOS::common::uint32_t esp);
            ConwareOS::common::uint32_t DoHandleInterrupt(ConwareOS::common::uint8_t interrupt, ConwareOS::common::uint32_t esp);

            Port8BitSlow programmableInterruptControllerMasterCommandPort;
            Port8BitSlow programmableInterruptControllerMasterDataPort;
            Port8BitSlow programmableInterruptControllerSlaveCommandPort;
            Port8BitSlow programmableInterruptControllerSlaveDataPort;
        public:
            InterruptManager(ConwareOS::common::uint16_t hardwareInterruptOffset, ConwareOS::GlobalDescriptorTable* globalDescriptorTable);
            ~InterruptManager();
            ConwareOS::common::uint16_t HardwareInterruptOffset();
            void Activate();
            void Deactivate();
        };
    }
}
#endif
