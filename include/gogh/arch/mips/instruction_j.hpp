/*
 * gogh::instruction_j
 * 
*/

#include "../../instruction.hpp"

namespace gogh::arch::mips {

    class instruction_j : public gogh::instruction {
        public:
            instruction_j(
                std::uint32_t opcode,
                std::uint32_t immediate) :
                    _opcode(opcode),
                    _immediate(immediate) {
                
            }

            void print() override {
                /*
                std::cout
                        << "opcode = " << _opcode << ", "
                        << "immediate = 0x" << std::hex << _immediate << '\n';
                */
            }

            void print_instruction() override {
            }

        private:
            std::uint32_t _opcode,
                          _immediate;
    };
}