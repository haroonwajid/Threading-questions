#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[]) {
    // Check if proper arguments are provided
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " ./writer ./reader" << endl;
        return 1;
    }

    mkfifo("pipe", 0666);

    // Fork process for writer
    pid_t pid_writer = fork();
    if (pid_writer == 0) {
        // Child process for writer
        execl(argv[1], argv[1], NULL);  // Execute writer program
    }

    pid_t pid_reader = fork();
    if (pid_reader == 0) {
        
        execl(argv[2], argv[2], NULL);  // Execute reader program
    }

    wait(NULL);
    wait(NULL);
   
    unlink("pipe");  // Clean up the pipe

    return 0;
}
