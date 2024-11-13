#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    int fd[2];
    pipe(fd); // Creating a pipe for communication

    if (fork() == 0) {
        close(fd[0]); // Child process, close read end

        // Items with quantities and prices
        string items[] = {"eggs", "bread", "chocolate"};
        int qty[] = {3, 1, 5}; // Quantity
        int price[] = {15, 60, 50}; // Price per item
        int sum = 0;

        // Calculate the total
        for (int i = 0; i < 3; i++) {
            sum += qty[i] * price[i];
        }

        // Sending sum and items through pipe
        string output = "355 eggs=45 bread=60 chocolate=250";
        write(fd[1], output.c_str(), output.size() + 1);
        close(fd[1]); // Close write end after sending data

        execl("./process2", "./process2", NULL); // Execute next process
    } else {
        wait(NULL); // Wait for child process
    }

    return 0;
}
