/*
 * gogh::instruction_r
 * 
 * The R instruction type always has a zero opcode. `function` determines the operation, e.g.
 * `add`, `sub`, `xor`, etc.
 * 
*/

#include <gogh/context.hpp>
#include <gogh/instruction.hpp>


namespace gogh::arch::mips {
    enum function_r {
        ADD  = 0b100000, // rd = rs + rt
        ADDU = 0b100001, // rd = rs + rt
        AND  = 0b100100, // rd = rs & rt
        NOR  = 0b100111,
        OR   = 0b100101,
        SLT  = 0b101010,
        SLTU = 0b101011,
        SUB  = 0b100010,
        SUBU = 0b100011,
        XOR  = 0b100110, // rd = rs ^ rt
        SLL  = 0b000000, // rd = rt << shift
        SLLV = 0b000100, // rd = rt << rs
        SRA  = 0b000011, 
        SRAV = 0b000111,
        SRL  = 0b000010,
        SRLV = 0b000110,
        DIV  = 0b011010,
        DIVU = 0b011011,
        MFHI = 0b010000,
        MFLO = 0b010010,
        MTHI = 0b010001,
        MTLO = 0b010011,
        MULT = 0b011000,
        MULTU = 0b011001
    };

    class instruction_r : public gogh::instruction {
        public:
            /* instruction_r doesn't take an `opcode` value because it's always zero */
            instruction_r(
                std::uint32_t rs,
                std::uint32_t rt,
                std::uint32_t rd,
                std::uint32_t shift,
                std::uint32_t function) :
                _rs(rs),
                _rt(rt),
                _rd(rd),
                _shift(shift),
                _function(function)
            {

            }


            /*
            void propagate(gogh::context &context) {
                using namespace gogh::arch::mips;

                auto rd = context.get_register(_rd);
                auto rt = context.get_register(_rt);
                auto rs = context.get_register(_rs);

                switch (_function) {
                    case function_r::ADD: {
                        std::cout << "ADD" << '\n';
                        break;
                    }
                }
            }
            */

            void print() override {
                std::cout
                        << "opcode = 0" << ", "
                        << "rs = " << _rs << ", "
                        << "rt = " << _rt << ", "
                        << "rd = " << _rd << ", "
                        << "shift = " << _shift << ", "
                        << "function = " << _function << '\n';
            }

        private:
            std::uint32_t _rs,
                          _rt,
                          _rd,
                          _shift,
                          _function;
    };
}