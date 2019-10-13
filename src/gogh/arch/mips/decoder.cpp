/*
 * gogh::arch::mips::decoder
*/

#include <gogh/instruction.hpp>
#include <gogh/arch/mips/decoder.hpp>
#include <gogh/arch/mips/instruction_i.hpp>
#include <gogh/arch/mips/instruction_j.hpp>
#include <gogh/arch/mips/instruction_r.hpp>

using namespace gogh::arch::mips;


gogh::instruction *decoder::decode(const std::uint32_t &instruction) {
    std::uint32_t opcode = (instruction & IJR_MASK_OPCODE) >> 26;
    switch (opcode) {
        case 0: {
            return new gogh::arch::mips::instruction_r(
                (instruction & R_MASK_RS) >> 21,
                (instruction & R_MASK_RT) >> 16,
                (instruction & R_MASK_RD) >> 11,
                (instruction & R_MASK_SHIFT) >> 6,
                (instruction & R_MASK_FUNCTION)
            );
        }
        case 2:
        case 3: {
            return new gogh::arch::mips::instruction_j(
                opcode,
                (instruction & J_MASK_RS)
            );
        }
        default: {
            return new gogh::arch::mips::instruction_i(
                opcode,
                (instruction & I_MASK_RS) >> 21,
                (instruction & I_MASK_RT) >> 16,
                (instruction & I_MASK_IMM)
            );
        }
    }
}
