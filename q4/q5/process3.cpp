#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        close(fd[0]); // Close read end

        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));

        // Read the sum and taxed sum from previous process
        double sum = 355; // Modify as necessary
        double taxed_sum = 383.4;

        // Calculate the 10% discount if applicable
        double discount = 0;
        if (sum > 250) {
            discount = sum * 0.1;
        }
        double final_sum = sum - discount;

        string output = to_string(sum) + " " + to_string(final_sum);
        write(fd[1], output.c_str(), output.size() + 1);
        close(fd[1]);

        execl("./process4", "./process4", NULL); // Execute next process
    } else {
        wait(NULL); // Wait for child process
    }

    return 0;
}
