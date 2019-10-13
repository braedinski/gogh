/*
 * gogh::arch::mips::context
 * 
 * A `context` represents the state of the process.
 * It holds the CPU register file, (i.e. array of `gogh::cpu_register`),
 * it also contains the process's tainted memory tables (`gogh::memory`).
 * 
*/

#include "cpu_register.hpp"
#include "../../context.hpp"

namespace gogh::arch::mips {
    using namespace gogh::arch;

    class context : public gogh::context {
        public:
            context() {
            }

            void print_registers() {
                for (const auto &cpu_register : _cpu_registers) {
                    std::cout << cpu_register.get_name() << " 0x" << std::hex << cpu_register.get_value() << '\n';
                }
            }

        private:
            gogh::memory _memory;

            std::array<mips::cpu_register, 31> _cpu_registers {{
                "zero",
                "v0", "v1",
                "a0", "a1", "a2", "a3",
                "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
                "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
                "t8", "t9",
                "k0", "k1",
                "gp",
                "sp",
                "fp",
                "ra"
            }};
    };
}