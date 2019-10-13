/*
 * gogh::instruction_r
 * 
*/

#include "../../instruction.hpp"

namespace gogh::arch::mips {
    class instruction_r : public gogh::instruction {
        public:
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
                    _function(function) {

                
            }

            void print() override {
                /*
                std::cout
                        << "opcode = 0" << ", "
                        << "rs = " << _rs << ", "
                        << "rt = " << _rt << ", "
                        << "rd = " << _rd << ", "
                        << "shift = " << _shift << ", "
                        << "function = " << _function << '\n';
                */
            }

            void print_instruction() override {
            }

        private:
            std::uint32_t _rs,
                          _rt,
                          _rd,
                          _shift,
                          _function;
            
            enum functions {
                ADD  = 0b100000,
                ADDU = 0b100001,
                AND  = 0b100100,
                NOR  = 0b100111,
                OR   = 0b100101,
                SLT  = 0b101010,
                SLTU = 0b101011,
                SUB  = 0b100010,
                SUBU = 0b100011,
                XOR  = 0b100110,  /* rd = rs ^ rt */
                SLL  = 0b000000,  /* rd = rt << shift */
                SLLV = 0b000100,
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
    };
}