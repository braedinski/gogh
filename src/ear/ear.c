/*
 * ear
 * A utility which *listens* for connections and then relays the current instruction to the
 * `gogh` client.
 * 
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <asm/ptrace.h>

struct process_s {
    pid_t pid;

    bool is_attached;

    struct pt_regs registers;
};

bool process_trace(struct process_s *process)
{
    ptrace(PTRACE_CONT, process->pid, NULL, NULL);

    int status;
    if (wait(&status) < 0) {
        perror("waitpid");
        return false;
    }

    // The attached process exited, so we exit.
    if (WIFEXITED(status)) {
        return false;
    }

    while (WIFSTOPPED(status)) {
        printf("Test 3");
    

        if (ptrace(PTRACE_GETREGS, process->pid, NULL, &process->registers) < 0) {
            perror("ptrace");
            break;
        }

        printf("0x%08x\n", process->registers.cp0_epc);

        if (ptrace(PTRACE_SINGLESTEP, process->pid, NULL, NULL) < 0) {
            perror("ptrace");
            return false;
        }
        
        if (wait(&status) < 0) {
            perror("waitpid");
            return false;
        }
    }

    return false;
}


bool process_attach(struct process_s *process)
{
    assert(process != NULL);

    if (ptrace(PTRACE_ATTACH, process->pid, NULL, NULL) < 0) {
        perror("ptrace");
        return false;
    }

    return true;
}


int main(int argc, char * const *argv)
{
    fprintf(stdout, "ear\n" "Braeden Lynden, @braedinski, 2019\n");

    struct process_s process;
    memset(&process, 0, sizeof(struct process_s));

    while (true)
    {
        static struct option options[] = {
            {"pid", required_argument, 0, 'p'},
            {0, 0, 0, 0}
        };

        int index = 0;
        int c = getopt_long(argc, argv, "p:", options, &index);
        if (c == -1) {
            break;
        }

        switch (c)
        {
            case 'p': {
                // What's the process ID we want to attach to?
                process.pid = atoi(optarg);
                fprintf(stdout, "Attaching %d ...", process.pid);

                break;
            }
            default: {
                return 1;
            }
        }
    }


    if (process_attach(&process)) {
        while (process_trace(&process)) {
            /* */
        }
    }

    return 0;
}
