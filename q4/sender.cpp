#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main() {
    // Create a named pipe if it doesn't already exist
    mkfifo("mypipe", 0666); // Create a named pipe with read and write permissions

    int f1 = open("mypipe", O_WRONLY);  // Open the pipe for writing
    if (f1 < 0) {
        cerr << "Error opening pipe for writing." << endl;
        return 1;
    }

    string input; // Use a string to accumulate input characters
    char inputChar;

    cout << "P1: Type characters (end with '#'):\n";
    while (true) {
        cin >> inputChar; // Read one character

        if (inputChar == '#') {
            // Send termination signal
            write(f1, &inputChar, sizeof(inputChar));
            break; // Exit loop on termination
        }

        // Accumulate input until punctuation is found
        input += inputChar;

        if (inputChar == '.' || inputChar == '?') {
            // Send the complete sentence
            write(f1, input.c_str(), input.size() + 1); // +1 to include null terminator
            input.clear(); // Clear the buffer for the next sentence
        }
    }

    close(f1); // Close the pipe after use
    return 0;
}
