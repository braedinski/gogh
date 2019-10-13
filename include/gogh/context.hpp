/*
 * gogh::context
 * 
 * A context is responsible for managing 
*/

#include <gogh/stab.hpp>
#include <gogh/decoder.hpp>
#include <gogh/cpu_register.hpp>

namespace gogh {
    class context {
        public:
            /*
             * A context requires a decoder to decode instructions as they come in,
             * as well as a `stab` which is the segment translation table.
            */
            context(gogh::decoder &decoder, gogh::stab &stab) :
                _decoder(decoder),
                _stab(stab)
            {

            }

            ~context() = default;

            /*
            gogh::cpu_register &get_register(std::uint32_t num) {
                
            }
            */

            gogh::instruction *decode(const std::uint32_t &instruction) {
                return _decoder.decode(instruction);
            }

        protected:
            gogh::decoder   &_decoder;
            gogh::stab      &_stab;
    };
}