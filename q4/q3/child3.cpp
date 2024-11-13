#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

extern const int BUFFER_SIZE;

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
