/*
 * gogh::disassembler
 * 
 * The class is just a wrapper for capstone disassembler.
 * `gogh` will use its own instruction decoder/disassembler.
 * 
*/

#include <capstone/capstone.h>

namespace gogh {
    class disassembler {
        public: 
            disassembler() {
                if (cs_open(
                    CS_ARCH_MIPS,
                    (cs_mode)(CS_MODE_MIPS32 + CS_MODE_BIG_ENDIAN),
                    &_handle) != CS_ERR_OK) {
                }
            }

            ~disassembler() {
                if (_handle) {
                    cs_close(&_handle);
                }
            }

            bool disassemble(const uint8_t *code, const size_t length) {
                std::size_t count = cs_disasm(
                    _handle,
                    code,
                    length,
                    0x1000,
                    0,
                    &_instruction
                );

                if (count > 0) {
                    for (std::size_t j = 0; j < count; j++) {
                        /*
                        std::cout
                            << "0x" << std::hex << _instruction[j].address << ' '
                            << _instruction[j].mnemonic << ' '
                            << _instruction[j].op_str << '\n';
                        */
                    }

                    cs_free(_instruction, count);
                }

                return true;
            }

        protected:
            cs_insn *_instruction;
            csh      _handle;
    };
}