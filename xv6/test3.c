#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define NUM_ITERATIONS 1
#define SLEEP_TICKS 5
#define NUM_PROCESSES 20
// #define ITERATIONS 600000000
#define ITERATIONS 100000000
//test2 start NUM_PROCESSES of CPU heavy processes and 1 interactive process, check the finish time of each process

int main(void) {
    int i;
    int pid;

    // setlog(0);
    

    
    // Start 5 CPU-heavy processes
    for (i = 0; i < NUM_PROCESSES; i++) {
        pid = fork();
        if (pid == 0) {
            // printtime(0);
            // Child process
            // Run a CPU-heavy task (e.g., loop)
            volatile int sum = 0;
            int j;
            for (j = 0; j < ITERATIONS; j++) {
                sum += j;
            }
            // Exit the child process when done
            // printf(1, "cpu heavy done\n");
            exit();
        } else if (pid < 0) {
            // Fork failed
            printf(1, "Failed to fork process %d\n", i);
            exit();
        }
        // Parent process continues
    }

        pid = fork();
    
    if(pid == 0){
    // Open the file for writing (create if it doesn't exist)
        // printtime(0);
        int fd = open("output.txt", O_WRONLY | O_CREATE);
        if (fd < 0) {
            // Handle error using printf with file descriptor `1` (stdout)
            printf(1, "Failed to open file for writing.\n");
            exit();
        }

        // The string "hello" and its length
        char *str = "hello\n";
        int len = strlen(str);

        // For loop to iterate NUM_ITERATIONS times
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            // Write the string "hello" to the file
            // printf(1, "----------------before write----------------\n");
            if (write(fd, str, len) != len) {
                // Handle write error using printf with file descriptor `1` (stdout)
                printf(1, "Failed to write to file.\n");
                close(fd);
                exit();
            }
            // printf(1, "----------------after write----------------\n");

            // Sleep for SLEEP_TICKS
            // printf(1,"before sleep\n");
            sleep(SLEEP_TICKS);
        }

        // Close the file
        close(fd);
        // printf(1,"interactive end\n");
        exit();
    }
    printf(1,"interactive process: %d\n", pid);
    
    // Wait for all child processes to complete
    for (i = 0; i < NUM_PROCESSES + 1; i++) {
        wait();
    }

    // setlog(0);
    printf(1, "All %d CPU-heavy processes have completed.\n", NUM_PROCESSES);

    // Exit the main process
    exit();
}
