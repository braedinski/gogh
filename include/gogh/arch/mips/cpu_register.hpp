/*
 * gogh::arch::mips::cpu_register
 * 
*/

#pragma once

#include <string>
#include <iostream>
#include "../../cpu_register.hpp"

namespace gogh::arch::mips {
    /* MIPS has 32 registers */
    const int num_registers = 32;

    class cpu_register : public gogh::cpu_register {
        public:
            cpu_register(const char *name) : _name(name) {
            }

            const std::string &get_name(void) const {
                return _name;
            }

            std::uint32_t get_value(void) const {
                return _value;
            }

        private:
            std::string _name;
            std::uint32_t _value = 0;
    };
}