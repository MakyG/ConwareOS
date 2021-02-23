#ifndef __CONWAREOS__GDT_H
#define __CONWAREOS__GDT_H

#include <common/types.h>

namespace ConwareOS
{
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    ConwareOS::common::uint16_t limit_lo;
                    ConwareOS::common::uint16_t base_lo;
                    ConwareOS::common::uint8_t base_hi;
                    ConwareOS::common::uint8_t type;
                    ConwareOS::common::uint8_t limit_hi;
                    ConwareOS::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(ConwareOS::common::uint32_t base, ConwareOS::common::uint32_t limit, ConwareOS::common::uint8_t type);
                    ConwareOS::common::uint32_t Base();
                    ConwareOS::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            ConwareOS::common::uint16_t CodeSegmentSelector();
            ConwareOS::common::uint16_t DataSegmentSelector();
    };
}

#endif 
