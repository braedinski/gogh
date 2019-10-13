/*
    * gogh::decoder
*/

#pragma once

#include <cstdint>
#include <gogh/instruction.hpp>

namespace gogh {
    class decoder {
        public:
            decoder() = default;
            virtual ~decoder() = default;

        public:
            virtual gogh::instruction *decode(const std::uint32_t &instruction) = 0;
    };
}