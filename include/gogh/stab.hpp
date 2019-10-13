/*
 * gogh::memory
 *
 * This class manages pages of memory. It'll automatically create a bitmap for unaccessed
 * memory addresses. For example, if 0x1000 doesn't exist in the map, it creates a bitmap for
 * it of size 1024. Any subsequent access to 0x1000 < x < 0x1400 will return the same bitmap.
 * 
*/

#include <map>
#include <memory>
#include "tagmap.hpp"

namespace gogh {
    // Each entry in the segment translation table can store taint on 1024 bytes of actual memory.
    // The size required for such a table is (n / 8) = (1024 / 8) = 128 bytes.
    const std::uintptr_t tagmap_size = 1024;

    struct stab_entry {
        std::uintptr_t segment;
        std::uintptr_t offset;
    };

    class stab {
        public:
            stab() = default;

        public:
            const struct gogh::stab_entry get_stab_entry(const std::uintptr_t &address) {
                return {
                    .segment = address &  0xfffffc00,
                    .offset  = address & ~0xfffffc00
                };
            }

            /*
             * taint()
             * 
            */
            void taint(std::uintptr_t address) {
                auto [segment, offset] = get_stab_entry(address);

                // If the bitmap already exists for this address, taint the byte in the bitmap.
                // Otherwise, create a new bitmap for this address and store it in the table.
                auto itr = _stab.find(segment);
                if (itr != _stab.end()) {
                    itr->second->set(offset, true);

                    return;
                }
                else {
                    // The entry wasn't found in the map just yet, create it.
                    auto tagmap = std::make_unique<gogh::tagmap>(gogh::tagmap_size);
                    tagmap->set(offset, true);

                    _stab.insert(
                        std::make_pair(segment, std::move(tagmap))
                    );
                }
            }

            void taint_n(std::uintptr_t address, std::size_t n) {
                // There's a more efficient implementation for this, but it'll do for now.
                for (std::size_t i = 0; i < n; ++i) {
                    taint(address + i);
                }
            }

            /*
             * is_tainted()
            */
            bool is_tainted(const std::uintptr_t &address) {
                auto [segment, offset] = get_stab_entry(address);

                auto itr = _stab.find(segment);
                if (itr != _stab.end()) {
                    return itr->second->get(offset);
                }

                return false;
            }

            /*
             * loop()
            */
            void print_all() {
                for (const auto &[segment, tagmap] : _stab) {
                    // std::cout << std::hex << page << std::endl;
                    // bitmap->print();
                }
            }

            /*
             * print()
            */
            void print(std::uintptr_t address) {
                auto [segment, _] = get_stab_entry(address);

                auto itr = _stab.find(segment);
                if (itr != _stab.end()) {
                    // std::cout << "Range [0x" << std::hex << page << ", 0x" << std::hex << page + 1023 << "]" << std::endl;
                    // itr->second->print();
                }
            }

        private:
            std::map<std::uintptr_t, std::unique_ptr<gogh::tagmap>> _stab; 
    };
}