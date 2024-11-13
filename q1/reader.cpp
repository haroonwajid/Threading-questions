#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    // Open the named pipe for reading
    int f1 = open("pipe", O_RDONLY);

    if (f1 < 0) {
        cerr << "Error opening pipe for reading." << endl;
        return 1;
    }

    char message[100];
    read(f1, message, sizeof(message));  // Read the message from the pipe
    cout << "Reader received: " << message << endl;

    close(f1);  

    return 0;
}
