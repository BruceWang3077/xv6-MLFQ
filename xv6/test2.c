#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define NUM_ITERATIONS 20
#define SLEEP_TICKS 5
// #define NUM_PROCESSES 20
// #define ITERATIONS 600000000
#define ITERATIONS 200000000
#define EPOCH 20
//test2 start NUM_PROCESSES of CPU heavy processes and 1 interactive process, check the finish time of each process

int interactive_num_proc[20] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
int cpu_heavy_num_proc[20] ={2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40};

void run_cpu_intense(int num_processes){
    int pid;
    int i;
    // Start 5 CPU-heavy processes
    for (i = 0; i < num_processes; i++) {
        pid = fork();
        if (pid == 0) {
            printtime(0);
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

}

void run_interactive(int num_processes){
    int i;
    int pid;
    for (i = 0; i < num_processes; i++){
        pid = fork();
    
        if(pid == 0){
        // Open the file for writing (create if it doesn't exist)
            printtime(0);
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
    }
    
}

int main(void) {
    int i, j;
    int num_interactive;
    int num_cpu_intense;

    setlog(0);
    for(i = 0; i < EPOCH; i++){
        num_interactive = interactive_num_proc[i];
        num_cpu_intense = cpu_heavy_num_proc[i];
        printf(1,"EPOCH %d\n", num_cpu_intense );
        run_interactive(num_interactive);
        run_cpu_intense(num_cpu_intense);
            // Wait for all child processes to complete
        
        for (j = 0; j < num_cpu_intense + num_interactive; j++) {
            wait();
        }
        printf(1,"EPOCH %d DONE\n\n", i);     
    }
    setlog(0);
    
    // Exit the main process
    exit();
}
