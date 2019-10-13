/*
 * gogh::tagmap
 * 
 * Each page of memory has its own `tagmap`. A page is 4096 bytes. For a page of 4096 bytes,
 * we need (4096/8) bits for our tagmap, this is assuming we're tainting bytes only.
 * 
 * The implementation might not be very efficient, but it'll do for now.
 * 
*/

#include <bitset>
#include <vector>
#include <ostream>

namespace gogh {
    class tagmap {
        public:
            tagmap() = delete;
            tagmap(const std::size_t &size) {
                _tagmap.resize(size / 8);
            }

        public:
            /*
             * set
            */
            void set(const std::size_t &byte, bool on) {
                std::size_t column = byte % _tagmap[0].size();
                std::size_t row = byte / _tagmap[0].size();

                _tagmap[row].set(column, on);
            }

            /*
             * get
            */
            bool get(const std::size_t &byte) const {
                std::size_t column = byte % _tagmap[0].size();
                std::size_t row = byte / _tagmap[0].size();
                
                return _tagmap[row].test(column);
            }

            /*
             * pretty_print()
            */
            std::ostream & operator << (std::ostream &os) {
                size_t prints = 0;
                for (const auto &bits : _tagmap) {
                    os << bits << ' ';
                    if (++prints % 8 == 0) {
                        os << '\n';
                        prints = 0;
                    }
                }

                return os;
            }

        private:
            std::vector<std::bitset<8>> _tagmap;
    };
}