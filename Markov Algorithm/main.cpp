#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    string data;
    Node* next;
};

map<string, Node*> markovChain;

void generateMarkovChain(const string& filename, int order) {
    ifstream file(filename);
    string word;
    Node* head = nullptr;
    Node* tail = nullptr;

    while (file >> word) {
        Node* newNode = new Node{ word, nullptr };
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    Node* current = head;
    while (current && current->next) {
        string prefix = "";
        for (int i = 0; i < order; ++i) {
            prefix += current->data + " ";
            current = current->next;
        }
        string nextWord = current->data;
        if (markovChain.find(prefix) == markovChain.end()) {
            markovChain[prefix] = new Node{ nextWord, nullptr };
        }
        else {
            Node* newNode = new Node{ nextWord, markovChain[prefix] };
            markovChain[prefix] = newNode;
        }
        current = current->next;
    }

    // Free memory
    current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

string generateText(int order, int length) {
    srand(time(0));
    string result;

    // Choose a random starting prefix
    int chainSize = markovChain.size();
    if (chainSize == 0) {
        return result; // Return empty string if the markovChain is empty
    }
    int index = rand() % chainSize;
    auto it = markovChain.begin();
    advance(it, index);
    string currentPrefix = it->first;

    result += currentPrefix;

    for (int i = 0; i < length; ++i) {
        Node* currentSuffix = markovChain[currentPrefix];
        int numSuffixes = 0;
        Node* temp = currentSuffix;
        while (temp) {
            ++numSuffixes;
            temp = temp->next;
        }

        if (numSuffixes == 0) {
            break; // Avoid division by zero
        }

        int randomIndex = (numSuffixes > 1) ? rand() % numSuffixes : 0; // Check if numSuffixes is greater than 1 to avoid division by zero
        temp = currentSuffix;
        for (int j = 0; j < randomIndex; ++j) {
            temp = temp->next;
        }
        string nextWord = temp->data;
        result += nextWord + " ";
        currentPrefix = currentPrefix.substr(nextWord.size() + 1) + nextWord + " ";
    }

    return result;
}

int main() {
    string filename = "input.txt"; // Replace with your text file name
    int order = 2; // Markov chain order
    int length = 100; // Length of generated text

    generateMarkovChain(filename, order);
    string newText = generateText(order, length);

    cout << "Input Text:\n";
    ifstream inputFile(filename);
    cout << inputFile.rdbuf() << endl; // Output the content of the file

    cout << "\nGenerated Text:\n" << newText << endl;

    // Free memory
    for (auto& pair : markovChain) {
        Node* current = pair.second;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    return 0;
}
