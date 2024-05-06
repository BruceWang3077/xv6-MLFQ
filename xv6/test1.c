#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_PROCESSES 3
// #define ITERATIONS 600000000
#define ITERATIONS 1000000000

int main(void) {
    int i;
    int pid;

    setlog(0);
    // Start 5 CPU-heavy processes
    for (i = 0; i < NUM_PROCESSES; i++) {
        pid = fork();
        if (pid == 0) {
            // Child process
            // Run a CPU-heavy task (e.g., loop)
            volatile int sum = 0;
            int j;
            for (j = 0; j < ITERATIONS; j++) {
                sum += j;
            }
            // Exit the child process when done
            exit();
        } else if (pid < 0) {
            // Fork failed
            printf(1, "Failed to fork process %d\n", i);
            exit();
        }
        // Parent process continues
    }

    // Wait for all child processes to complete
    for (i = 0; i < NUM_PROCESSES; i++) {
        wait();
    }

    setlog(0);
    printf(1, "All %d CPU-heavy processes have completed.\n", NUM_PROCESSES);

    // Exit the main process
    exit();
}
