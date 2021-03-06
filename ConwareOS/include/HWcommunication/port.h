//copied
#ifndef __CONWAREOS__HWCOMMUNICATION__PORT_H
#define __CONWAREOS__HWCOMMUNICATION__PORT_H

#include <common/types.h>

namespace ConwareOS
{
    namespace HWcommunication
    {
            class Port
        {
            protected:
                Port(ConwareOS::common::uint16_t portnumber);
                ~Port();
                ConwareOS::common::uint16_t portnumber;
        };


        class Port8Bit : public Port
        {
            public:
                Port8Bit(ConwareOS::common::uint16_t portnumber);
                ~Port8Bit();

                virtual ConwareOS::common::uint8_t Read();
                virtual void Write(ConwareOS::common::uint8_t data);

            protected:
                static inline ConwareOS::common::uint8_t Read8(ConwareOS::common::uint16_t _port)
                {
                    ConwareOS::common::uint8_t result;
                    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write8(ConwareOS::common::uint16_t _port, ConwareOS::common::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };



        class Port8BitSlow : public Port8Bit
        {
            public:
                Port8BitSlow(ConwareOS::common::uint16_t portnumber);
                ~Port8BitSlow();

                virtual void Write(ConwareOS::common::uint8_t data);
            protected:
                static inline void Write8Slow(ConwareOS::common::uint16_t _port, ConwareOS::common::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
                }

        };



        class Port16Bit : public Port
        {
            public:
                Port16Bit(ConwareOS::common::uint16_t portnumber);
                ~Port16Bit();

                virtual ConwareOS::common::uint16_t Read();
                virtual void Write(ConwareOS::common::uint16_t data);

            protected:
                static inline ConwareOS::common::uint16_t Read16(ConwareOS::common::uint16_t _port)
                {
                    ConwareOS::common::uint16_t result;
                    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write16(ConwareOS::common::uint16_t _port, ConwareOS::common::uint16_t _data)
                {
                    __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };



        class Port32Bit : public Port
        {
            public:
                Port32Bit(ConwareOS::common::uint16_t portnumber);
                ~Port32Bit();

                virtual ConwareOS::common::uint32_t Read();
                virtual void Write(ConwareOS::common::uint32_t data);

            protected:
                static inline ConwareOS::common::uint32_t Read32(ConwareOS::common::uint16_t _port)
                {
                    ConwareOS::common::uint32_t result;
                    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write32(ConwareOS::common::uint16_t _port, ConwareOS::common::uint32_t _data)
                {
                    __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
                }
        };
    }
}

#endif
