/*
 * gogh::bitmap
 * 
 * Each page of memory has its own `bitmap`. A page is 4096 bytes. For a page of 4096 bytes,
 * we need (4096/8) bits for our bitmap, this is assuming we're tainting bytes only.
 * 
 * The implementation might not be very efficient, but it'll do for now.
 * 
*/

#include <bitset>
#include <vector>
#include <ostream>

namespace gogh {
    class bitmap {
        public:
            bitmap() = delete;
            bitmap(const std::size_t &size) {
                _bitmap.resize(size / 8);

                /*
                std::cout << "Creating gogh::bitmap of size = " << size << std::endl;
                std::cout << "gogh::bitmap is " << _bitmap.size() << " bytes" << std::endl;
                */
            }

            ~bitmap() {
                /*
                std::cout << "Destroying bitmap" << std::endl;
                */
            }

        public:
            /*
             * set
            */
            void set(const std::size_t &byte, bool on) {
                std::size_t column = byte % _bitmap[0].size();
                std::size_t row = byte / _bitmap[0].size();
                _bitmap[row].set(column, on);
            }

            /*
             * get
            */
            bool get(const std::size_t &byte) const {
                std::size_t column = byte % _bitmap[0].size();
                std::size_t row = byte / _bitmap[0].size();
                return _bitmap[row].test(column);
            }

            /*
             * pretty_print()
            */
            std::ostream & operator << (std::ostream &os) {
                size_t prints = 0;
                for (const auto &bits : _bitmap) {
                    os << bits << ' ';
                    if (++prints % 8 == 0) {
                        os << '\n';
                        prints = 0;
                    }
                }

                return os;
            }

        private:
            std::vector<std::bitset<8>> _bitmap;
    };
}