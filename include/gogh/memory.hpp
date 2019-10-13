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
#include "bitmap.hpp"

namespace gogh {
    const std::uintptr_t bitmap_size = 1024;

    struct masked {
        std::uintptr_t page;
        std::uintptr_t offset;
    };

    class memory {
        public:
            memory() = default;

        public:
            const struct gogh::masked mask(const std::uintptr_t &address) {
                return {
                    .page   = address &  0xfffffc00,
                    .offset = address & ~0xfffffc00
                };
            }

            /*
             * taint()
             * 
            */
            void taint(std::uintptr_t address) {
                auto [page, offset] = mask(address);

                // If the bitmap already exists for this address, taint the byte in the bitmap.
                // Otherwise, create a new bitmap for this address and store it in the table.
                auto itr = _page_table.find(page);
                if (itr != _page_table.end()) {
                    itr->second->set(offset, true);

                    return;
                }
                else {
                    // The entry wasn't found in the map just yet, create it.
                    std::unique_ptr<gogh::bitmap> bitmap = std::make_unique<gogh::bitmap>(1024);
                    bitmap->set(offset, true);

                    _page_table.insert(
                        std::make_pair(
                            page,
                            std::move(bitmap)
                        )
                    );
                }
            }

            void taint_n(std::uintptr_t address, std::size_t n) {
                for (std::size_t i = 0; i < n; ++i) {
                    taint(address + i);
                }
            }

            /*
             * is_tainted()
            */
            bool is_tainted(const std::uintptr_t &address) {
                auto [page, offset] = mask(address);
                auto itr = _page_table.find(page);
                if (itr != _page_table.end()) {
                    return itr->second->get(offset);
                }

                return false;
            }

            /*
             * loop()
            */
            void print_all() {
                for (const auto &[page, bitmap] : _page_table) {
                    // std::cout << std::hex << page << std::endl;
                    // bitmap->print();
                }
            }

            /*
             * print()
            */
            void print(std::uintptr_t address) {
                auto [page, _] =  mask(address);

                auto itr = _page_table.find(page);
                if (itr != _page_table.end()) {
                    // std::cout << "Range [0x" << std::hex << page << ", 0x" << std::hex << page + 1023 << "]" << std::endl;
                    // itr->second->print();
                }
            }

        private:
            std::map<std::uintptr_t, std::unique_ptr<gogh::bitmap>> _page_table; 
    };
}