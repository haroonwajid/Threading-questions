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

        // Read the sum from the previous process
        int sum = 355; 

        // Calculate the 8% tax
        double tax = sum * 0.08;
        double taxed_sum = tax + sum;

        string output = to_string(sum) + " " + to_string(taxed_sum);
        write(fd[1], output.c_str(), output.size() + 1);
        close(fd[1]);

        execl("./process3", "./process3", NULL); // Execute next process
    } else {
        wait(NULL); // Wait for child process
    }

    return 0;
}
