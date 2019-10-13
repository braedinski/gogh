/*
 * gogh
 * Braeden Lynden, @braedinski, 2019
 * 
 * `gogh` is a taint-analysis framework. It aims to simplify the process of building tools for
 * dynamic-taint analysis (DTA). The goal of the project is to create a fast, lightweight,
 * library.
 * 
*/

#include <gogh/gogh.hpp>

#include <iostream>
#include <getopt.h>

int main(int argc, char * const *argv)
{
    std::cout << "gogh .1" << '\n'
              << "Braeden Lynden, @braedinski, 2019" << '\n'
              << std::endl;

    while (true)
    {
        static struct option options[] = {
            {"remote", required_argument, 0, 'r'},
            {0, 0, 0, 0}
        };

        int index = 0;
        int c = getopt_long(argc, argv, "r:", options, &index);
        if (c == -1) {
            break;
        }

        switch (c)
        {
            case 'r': {
                // Set the remote host here, the format is <ip:port>
                break;
            }
            default: {
                std::cerr << "Error parsing arguments, exiting" << std::endl;
                return EXIT_FAILURE;
            }
        }
    }

    gogh::arch::mips::context context;
    context.print_registers();
    
    return EXIT_SUCCESS;
}
