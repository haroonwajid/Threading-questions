#include <iostream>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <cctype>

using namespace std;

extern const int BUFFER_SIZE;

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
