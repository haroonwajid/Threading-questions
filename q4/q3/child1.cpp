#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

extern const int BUFFER_SIZE;

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
