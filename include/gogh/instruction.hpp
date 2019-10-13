/*
 * gogh::instruction
 * 
 * A base class for any instruction type. As an example, for `arch/mips`, the instruction types
 * R, I and J descend from this class.
 * 
*/

#pragma once

namespace gogh {
    class instruction {
        public:
            instruction() = default;
            virtual ~instruction() = default;

        public:
            virtual void print() = 0;
    };
}