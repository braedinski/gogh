/*
 * gogh::instruction_i
*/

#pragma once

#include <map>
#include <iomanip>
#include <iostream>
#include "../../instruction.hpp"

namespace gogh::arch::mips {
    class instruction_i : public gogh::instruction {
        public:
            instruction_i(
                std::uint32_t opcode,
                std::uint32_t rs,
                std::uint32_t rt,
                std::uint32_t immediate) :
                _opcode(opcode),
                _rs(rs),
                _rt(rt),
                _immediate(immediate) {
                    
            }

            void print() override {
                std::cout
                        << "opcode = 0" << ", "
                        << "rs = " << _rs << ", "
                        << "rt = " << _rt << ", "
                        << "immediate = " << _immediate << '\n';
            }

            /*
            void print_instruction() override {
                auto itr = mnemonics.find(_opcode);
                if (itr != mnemonics.end()) {
                    std::cout << itr->second << '\t'
                        << '$' << std::dec << std::setw(2) << _rt << ", "
                        << '$' << std::dec << std::setw(2) << _rs << ", "
                        << std::hex << "0x" << _immediate << '\n';
                } else {
                    print();
                }
            }

            std::uint32_t get_source() override {
                return _rs;
            }

            std::uint32_t get_destination() override {
                return _rt;
            }
            */

        private:
            std::uint32_t _opcode,
                            _rs,
                            _rt,
                            _immediate;

            enum function : std::uint32_t {
                ADDI    = 0b001000,
                ADDIU   = 0b001001,
                ANDI    = 0b001100,
                LUI     = 0b001111,
                ORI     = 0b001101,
                SLTI    = 0b001010,
                SLTIU   = 0b001011,
                XORI    = 0b001110,
                LW      = 0b100011,
                LB      = 0b100000,
                LBU     = 0b100100,
                LH      = 0b100001,
                LHU     = 0b100101,
                SB      = 0b101000,
                SH      = 0b101001,
                SW      = 0b101011
            };

            std::map<std::uint32_t, std::string> mnemonics = {
                {ADDI,  "addi"},
                {ADDIU, "addiu"},
                {ANDI,  "andi"},
                {LUI,   "lui"},
                {ORI,   "ori"},
                {SLTI,  "slti"},
                {SLTIU, "sltiu"},
                {XORI,  "xori"},
                {LW,    "lw"},
                {LB,    "lb"},
                {LBU,   "lbu"},
                {LH,    "lh"},
                {LHU,   "lhu"},
                {SB,    "sb"},
                {SH,    "sh"},
                {SW,    "sw"}
            };
    };
}
