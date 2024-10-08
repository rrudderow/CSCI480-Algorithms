#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <chrono>

using namespace std;

/*
int hash_function(string word, int M) {
    int h = 0, a = 127;
    for (char ch : word) {
        h = (a * h + ch) % M;
    }
    return h;
}*/

int hash_function(string word, int M) {
    int h = 3, a = 293;
    for (char ch : word) {
        h = (h * a + ch) % M;
    }
    return h;
}

void separate_chaining(vector<list<string>>& table, string word, int size) {
    int hash_code = hash_function(word, size);
    table[hash_code].push_back(word);
}

void linear_probing(string table[], string word, int size) {
    int hash_code = hash_function(word, size);
    int original_hash = hash_code;
    while (!table[hash_code].empty()) {
        hash_code = hash_code + 1; // Move to next slot
        if (hash_code == original_hash){
            cout << "Error: Table is full, cannot insert " << word << endl;
            return;
        }
    }
    table[hash_code] = word;
}

// Retrieve data from Separate Chaining hash function
bool retrieve_from_separate_chaining(const vector<list<string>>& table, string word, int size) {
    int hash_code = hash_function(word, size);
    for (const auto& w : table[hash_code]) {
        if (w == word) return true;
    }
    return false;
}

// Retrieve data from Linear Probing hash function
bool retrieve_from_linear_probing(const string table[], string word, int size) {
    int hash_code = hash_function(word, size);
    int original_hash = hash_code;
    while (!table[hash_code].empty()) {
        if (table[hash_code] == word) return true;
        hash_code = hash_code + 1;
        if (hash_code == original_hash) break; // We've looped around
    }
    return false;
}

// Print Separate Chaining Table
void printSeparateChainingTable(const vector<list<string>>& table) {
    cout << "Printing Separate Chaining table:" << endl;
    for (int i = 0; i < table.size(); i++) {
        cout << i << ": ";
        if (table[i].empty()) {
            cout << "empty" << endl;
        } else {
            for (const auto& word : table[i]) {
                cout << word << " -> ";
            }
            cout << "NULL" << endl;
        }
    }
}

// Print Linear Probing Table
void printLinearProbingTable(string table[], int size) {
    cout << "Printing Linear Probing table:" << endl;
    for (int i = 0; i < size; i++) {
        if (table[i].empty())
            cout << i << ": empty" << endl;
        else
            cout << i << ": " << table[i] << endl;
    }
}

string words[] = {
        "false", "his", "nature", "adjusted", "seldom", "in", "him", "seen",
        "from", "drawing", "mention", "upon", "other", "any", "eclipses", "be",
        "predominates", "All", "eyes", "Irene", "one", "yet", "reasoning", "which",
        "would", "has", "was", "the", "and", "intrusions", "observing",
        "disturbing", "questionable", "factor", "felt", "Sherlock", "Holmes",
        "woman", "abhorrent", "heard", "reasoner", "most", "he", "that", "into",
        "strong", "I", "late", "her", "is", "such", "crack", "a",
        "admirably", "mental", "spoke", "than", "admit", "should", "distracting",
        "never", "temperament", "love", "whole", "balanced", "always", "under",
        "for", "Adler.", "trained", "veil", "there", "were", "emotion", "might",
        "himself", "Bohemia", "gigantic", "perfect", "lover", "softer", "sensitive",
        "own", "Scandal", "save", "gibe", "have", "world", "with", "more",
        "but", "simplicity", "dubious", "take", "introduce", "admirable", "old",
        "little", "precise", "name"
    };

int main() {
    ifstream InFile("text.txt");
    if (!InFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }
    int size = 4044;

    vector<list<string>> chainingTable(size);
    string linearProbingTable[size];
    string word;

    //auto start = std::chrono::high_resolution_clock::now();
    while (InFile >> word) {
        separate_chaining(chainingTable, word, size);
        linear_probing(linearProbingTable, word, size);
    }
    //auto end = std::chrono::high_resolution_clock::now();

    cout << "Finished hashing the input" << endl;

    //auto start = std::chrono::high_resolution_clock::now();
    for (auto &word : words) {
        if(!retrieve_from_separate_chaining(chainingTable, word, size))
            cout << "error:" << word << endl;
        if(!retrieve_from_linear_probing(linearProbingTable, word, size))
            cout << "error:" << word << endl;
    }
    //auto end = std::chrono::high_resolution_clock::now();

    //std::chrono::duration<double, std::micro> duration = end - start;
    //std::cout << "Function executed in: " << duration.count() << " microseconds" << std::endl;

    cout << "Finished retrieving data" << endl;

    return 0;
}
