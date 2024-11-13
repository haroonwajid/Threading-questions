#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    // P2 Process will calculate the percentage and display the grade
    mkfifo("pipe1", 0666);  // Create a named pipe for reading
    int f1 = open("pipe1", O_RDONLY);  // Open pipe1 for reading

    if (f1 < 0) {
        cerr << "Error opening pipe1." << endl;
        return 1;
    }

    while (true) {
        int totalMarks[5];  // Array to store total marks
        int obtainedMarks[5];  // Array to store obtained marks
        float percentage[5];  // Array to store percentage for each subject

        // Read total marks and obtained marks from P1
        read(f1, totalMarks, sizeof(totalMarks));
        read(f1, obtainedMarks, sizeof(obtainedMarks));

        // Calculate and display percentage and grade for each subject
        for (int i = 0; i < 5; i++) {
            percentage[i] = (obtainedMarks[i] * 100.0) / totalMarks[i];
            cout << "Subject " << i + 1 << " - Percentage: " << percentage[i] << "%" << endl;

            // Display grade based on percentage
            cout << "Grade: ";
            if (percentage[i] < 50) {
                cout << "F" << endl;
            } else if (percentage[i] >= 50 && percentage[i] < 60) {
                cout << "D" << endl;
            } else if (percentage[i] >= 60 && percentage[i] < 70) {
                cout << "C" << endl;
            } else if (percentage[i] >= 70 && percentage[i] < 80) {
                cout << "B" << endl;
            } else if (percentage[i] >= 80 && percentage[i] <= 100) {
                cout << "A" << endl;
            }
        }

        break;  // Exit after one iteration
    }

    close(f1);  // Close the pipe after use
    unlink("pipe1");  // Unlink the pipe

    return 0;
}
