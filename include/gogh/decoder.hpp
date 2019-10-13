/*
    * gogh::decoder
*/

#include <iostream>
#include "instruction.hpp"
#include "arch/mips/instruction_i.hpp"
#include "arch/mips/instruction_j.hpp"
#include "arch/mips/instruction_r.hpp"

namespace gogh {
    class decoder {
        public:
            decoder() = default;
        
        public:
            gogh::instruction *decode(const std::uint32_t &instruction) {
                std::uint32_t opcode = (instruction & 0xfc000000) >> 26;
                switch (opcode) {
                    case 0: {
                        // instruction_r
                        return new gogh::arch::mips::instruction_r(
                            (instruction & 0x03e00000) >> 21, // rs
                            (instruction & 0x001f0000) >> 16, // rt
                            (instruction & 0x0000f800) >> 11, // rd
                            (instruction & 0x000007c0) >> 6,  // shift
                            (instruction & 0x000000ff) >> 0   // function
                        );
                    }
                    case 2:
                    case 3: {
                        // instruction_j
                        return new gogh::arch::mips::instruction_j(
                            opcode,
                            (instruction & 0x03ffffff)        // rs
                        );
                    }
                    default: {
                        // instruction_i
                        return new gogh::arch::mips::instruction_i(
                            opcode,
                            (instruction & 0x03e00000) >> 21, // rs
                            (instruction & 0x001f0000) >> 16, // rt
                            (instruction & 0x0000ffff)        // immediate
                        );
                    }
                }
            }
    };
}