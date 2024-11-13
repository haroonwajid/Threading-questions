#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    // P1 process will take the total and obtained marks of 5 different subjects from user and send this data to P2.
   
    mkfifo("pipe1", 0666);  // Create a named pipe
    int f1 = open("pipe1", O_WRONLY);  // Open pipe1 for writing

    if (f1 < 0) {
        cout << "Error opening pipe1." << endl;
        return 1;
    }

    while (true) {
        int totalMarks[5];  // Array to store total marks for 5 subjects
        int obtainedMarks[5];  // Array to store obtained marks for 5 subjects

        // Take total marks from user
        cout << "Enter Total Marks for 5 subjects: ";
        for (int i = 0; i < 5; i++) {
            cin >> totalMarks[i];
        }
        
        // Take obtained marks from user
        cout << "Enter Obtained Marks for 5 subjects: ";
        for (int i = 0; i < 5; i++) {
            cin >> obtainedMarks[i];
        }

        // Send totalMarks and obtainedMarks arrays to P2
        write(f1, totalMarks, sizeof(totalMarks));
        write(f1, obtainedMarks, sizeof(obtainedMarks));

        cout << "Data sent to P2 via pipe1!" << endl;

        break;
    }

    close(f1);  // Close the pipe after use

    return 0;
}
