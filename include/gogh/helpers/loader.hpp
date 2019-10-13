/*
 * gogh::loader
*/

#include <vector>
#include <string>
#include <fstream>

/* These headers shouldn't be in here, get them outta here ASAP! */
#include <iomanip>
#include <iostream>

#include "../decoder.hpp"
#include "../instruction.hpp"

namespace gogh::helpers {
    class loader {
        public:
            loader() = delete;
            loader(const std::string &filename) : _filename(filename) {
                std::cout << filename << '\n';
            }

            /*
             * The whole function is a fucking mess, it's just for testing anyways.
            */
            std::vector<gogh::instruction *> get_instructions(size_t count) {
                std::vector<gogh::instruction *> poop;

                gogh::decoder decoder;

                std::ifstream binary(_filename, std::ios::binary);
                if (binary.good()) {
                    binary.seekg(0x4c);

                    while (poop.size() < count) {
                        std::uint32_t inst;
                        binary.read(reinterpret_cast<char*>(&inst), sizeof(std::uint32_t));

                        std::cout << std::setfill('0') << std::setw(8) << std::hex << inst << '\n';

                        gogh::instruction *instr = decoder.decode(inst);
                        instr->print();
                        
                        poop.push_back(nullptr);
                        
                    }
                }

                return poop;
            }

        private:
            std::string _filename;
    };
}