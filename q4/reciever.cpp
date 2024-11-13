#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main() {
    int f1 = open("mypipe", O_RDONLY); // Open the named pipe for reading
    if (f1 < 0) {
        cerr << "Error opening pipe for reading." << endl;
        return 1;
    }

    char buffer[100]; // Buffer to hold the incoming message

    while (true) {
        read(f1, buffer, sizeof(buffer)); // Read from P1

        if (buffer[0] == '#') {
            cout << "P2: Incomplete sentence received. Exiting...\n";
            break; // Termination condition
        }

        cout << "P2: Received sentence: " << buffer << endl; // Display the received message
    }

    close(f1); // Close the pipe after use
    return 0;
}
