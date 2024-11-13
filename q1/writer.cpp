#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
   
    int f1 = open("pipe", O_WRONLY);

    if (f1 < 0) {
        cerr << "Error opening pipe for writing." << endl;
        return 1;
    }

    const char* message = "OS is very easy";
    write(f1, message, strlen(message) + 1);

    close(f1);

    return 0;
}
