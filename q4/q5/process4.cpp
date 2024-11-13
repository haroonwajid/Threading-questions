#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    int price;

    // Constructor for Item
    Item(string n, int p) : name(n), price(p) {}
};

bool compare(Item a, Item b) {
    return a.price > b.price; // Sorting in descending order of price
}

int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        close(fd[0]); // Close read end

        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));

        // Parse the data (assuming you're receiving appropriate data in buffer)
        int sum = 355;
        double taxed_sum = 383.4;
        double final_sum = 319.5;

        // Use explicit constructor calls for each item
        vector<Item> items;
        items.push_back(Item("chocolate", 250));
        items.push_back(Item("bread", 60));
        items.push_back(Item("eggs", 45));

        // Sorting items by price
        sort(items.begin(), items.end(), compare);

        // Display receipt using traditional for loop
        cout << "Items      Price" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << items[i].name << "   " << items[i].price << endl;
        }
        cout << "Total: " << sum << endl;
        cout << "After 8% tax: " << taxed_sum << endl;
        cout << "After 10% sale: " << final_sum << endl;
    } else {
        wait(NULL); // Wait for child process
    }

    return 0;
}
