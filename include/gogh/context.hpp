/*
 * gogh::context
 * 
*/

#include "memory.hpp"

namespace gogh {
    class context {
        public:
            context() = default;
            ~context() = default;

        public:

        private:
            gogh::memory _memory;
    };
}