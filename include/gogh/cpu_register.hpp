/*
 * gogh::cpu_register
 *
 * `register` is a keyword in C, kms.
 * 
*/

#include <string>
#include <bitset>


namespace gogh {
    class cpu_register {
        public:
            cpu_register(const char *name) :
                _name(name) {
            }

        public:
            /*
             * get_name
            */
            const std::string &get_name(void) const {
                return _name;
            }
            
            void taint() {
                _taint.flip();
            }

            bool is_tainted() {
                return _taint.any();
            }

            void print() {
                // std::cout << _name << " = " << _taint << '\n';
            }

        private:
            std::string _name;
            std::bitset<4> _taint;
    };
}