#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

class HashTable {
private:
    // Structure to hold key-value pairs
    struct HashNode {
        string key;
        int value;
    };

    int buckets; // Total number of slots/buckets
    vector<list<HashNode>> table; // Vector of linked lists

    // Basic hash function
    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % buckets;
    }

public:
    HashTable(int capacity) {
        this->buckets = capacity;
        table.resize(capacity);
    }

    // Insert or update a key-value pair
    void insert(const string& key, int value) {
        int index = hashFunction(key);
        
        // Check if key already exists, if so, update its value
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        // If key doesn't exist, push new node to the bucket's list
        table[index].push_back({key, value});
    }

    // Search for a value by key
    bool search(const string& key, int& valueResult) {
        int index = hashFunction(key);
        for (const auto& node : table[index]) {
            if (node.key == key) {
                valueResult = node.value;
                return true; // Found
            }
        }
        return false; // Not found
    }

    // Delete a key-value pair
    void remove(const string& key) {
        int index = hashFunction(key);
        auto& cell = table[index];
        for (auto it = cell.begin(); it != cell.end(); ++it) {
            if (it->key == key) {
                cell.erase(it);
                return;
            }
        }
    }
};

// int main() {
//     HashTable ht(7); // Create table with 7 buckets

//     ht.insert("Apple", 100);
//     ht.insert("Banana", 200);

//     int price;
//     if (ht.search("Apple", price)) {
//         std::cout << "Apple price: " << price << std::endl;
//     }

//     ht.remove("Apple");
//     return 0;
// }
