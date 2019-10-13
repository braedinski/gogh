/*
 * gogh::arch::mips::cpu_register
 * 
*/

#include "../../cpu_register.hpp"

namespace gogh::arch::mips {
    /* MIPS has 32 registers */
    const int num_registers = 32;

    class cpu_register : public gogh::cpu_register {
    };
}