#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define NUM_ITERATIONS 10
#define SLEEP_TICKS 10
#define NUM_PROCESSES 10
// #define ITERATIONS 600000000
#define ITERATIONS 300000000

int main() {
    // Open the file for writing (create if it doesn't exist)
    int pid = fork();
    if(pid == 0){
        setlog(0);
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
        setlog(0);
        printf(1,"interactive end\n");
        exit();
        
    }
    printf(1,"pid\n: %d", pid);
    pid = fork();
    if(pid == 0){
        for(int i = 0; i < ITERATIONS; i++){
            i++;
            i--;
        }
        printf(1,"cpu heavy end\n");
        exit();
        
    }
    wait();
    wait();
    // Exit the program successfully
    exit();
}






