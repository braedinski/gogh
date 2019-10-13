/*
 * gogh::arch::mips::decoder
*/

#include <gogh/decoder.hpp>

#define IJR_MASK_OPCODE  0xfc000000

#define R_MASK_RS        0x03e00000
#define R_MASK_RT        0x001f0000
#define R_MASK_RD        0x0000f800
#define R_MASK_SHIFT     0x000007c0
#define R_MASK_FUNCTION  0x000000ff

#define J_MASK_RS        0x03ffffff

#define I_MASK_RS        0x03e00000
#define I_MASK_RT        0x001f0000
#define I_MASK_IMM       0x0000ffff

namespace gogh::arch::mips {
    class decoder : public gogh::decoder {
        public:
            decoder() = default;
        
        public:
            gogh::instruction *decode(const std::uint32_t &instruction) override;
    };
}