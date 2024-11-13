#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

const int BUFFER_SIZE = 256;

// Function declarations
void child1(int read_fd, int write_fd);
void child2(int read_fd1, int write_fd1, int read_fd2, int write_fd2);
void child3(int read_fd, int write_fd);

int main() {
    int pipe1[2], pipe2[2], pipe3[2];
    
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        cerr << "Pipe creation failed" << endl;
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // Child 1
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe3[0]);
        close(pipe3[1]);
        child1(pipe1[0], pipe2[1]);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Child 2
        close(pipe1[0]);
        close(pipe2[1]);
        close(pipe3[0]);
        child2(pipe2[0], pipe3[1], pipe3[0], pipe1[1]);
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        // Child 3
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        close(pipe3[1]);
        child3(pipe3[0], pipe3[1]);
        exit(0);
    }

    // Parent process
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
    close(pipe3[0]);
    close(pipe3[1]);

    // Wait for all child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}

void child1(int read_fd, int write_fd) {
    char message[] = "Hello, this is a test message!";
    cout << "Child 1: Sending message: " << message << endl;
    write(write_fd, message, strlen(message) + 1);

    char buffer[BUFFER_SIZE];
    read(read_fd, buffer, BUFFER_SIZE);
    cout << "Child 1: Received capitalized message: " << buffer << endl;

    close(read_fd);
    close(write_fd);
}

void child2(int read_fd1, int write_fd1, int read_fd2, int write_fd2) {
    char buffer[BUFFER_SIZE];
    
    // Read from Child 1
    read(read_fd1, buffer, BUFFER_SIZE);
    cout << "Child 2: Received message: " << buffer << endl;

    // Reverse the message
    reverse(buffer, buffer + strlen(buffer));
    cout << "Child 2: Reversed message: " << buffer << endl;

    // Send to Child 3
    write(write_fd1, buffer, strlen(buffer) + 1);

    // Read from Child 3
    read(read_fd2, buffer, BUFFER_SIZE);
    cout << "Child 2: Received reversed message from Child 3: " << buffer << endl;

    // Capitalize the message
    for (int i = 0; buffer[i]; i++) {
        buffer[i] = toupper(buffer[i]);
    }
    cout << "Child 2: Capitalized message: " << buffer << endl;

    // Send to Child 1
    write(write_fd2, buffer, strlen(buffer) + 1);

    close(read_fd1);
    close(write_fd1);
    close(read_fd2);
    close(write_fd2);
}

void child3(int read_fd, int write_fd) {
    char buffer[BUFFER_SIZE];
    
    // Read from Child 2
    read(read_fd, buffer, BUFFER_SIZE);
    cout << "Child 3: Received reversed message: " << buffer << endl;

    // Send back to Child 2
    write(write_fd, buffer, strlen(buffer) + 1);

    close(read_fd);
    close(write_fd);
}
