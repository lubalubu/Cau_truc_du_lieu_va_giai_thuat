#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void createKeyTable(string key, char keyTable[5][5]) {
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; 
    string keyString = "";

    for (char &c : key) {
        c = toupper(c);
        if (keyString.find(c) == string::npos && c != 'J') {
            keyString += c;
        }
    }

    for (char c : alphabet) {
        if (keyString.find(c) == string::npos) {
            keyString += c;
        }
    }

    
    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            keyTable[i][j] = keyString[k++];
        }
    }
}

void preprocessText(string &text) {
    text.erase(remove_if(text.begin(), text.end(), [](char c) { return !isalpha(c); }), text.end());
    transform(text.begin(), text.end(), text.begin(), ::toupper);

    replace(text.begin(), text.end(), 'J', 'I');

    for (size_t i = 0; i < text.length(); i += 2) {
        if (i + 1 == text.length()) {
            text += 'X';
        } else if (text[i] == text[i + 1]) {
            text.insert(i + 1, 1, 'X');
        }
    }
}

string playfairEncrypt(string text, char keyTable[5][5]) {
    string cipherText = "";

    for (size_t i = 0; i < text.length(); i += 2) {
        char a = text[i];
        char b = text[i + 1];
        int row1, col1, row2, col2;

        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (keyTable[r][c] == a) {
                    row1 = r;
                    col1 = c;
                }
                if (keyTable[r][c] == b) {
                    row2 = r;
                    col2 = c;
                }
            }
        }

        if (row1 == row2) {
            cipherText += keyTable[row1][(col1 + 1) % 5];
            cipherText += keyTable[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            cipherText += keyTable[(row1 + 1) % 5][col1];
            cipherText += keyTable[(row2 + 1) % 5][col2];
        } else {
            cipherText += keyTable[row1][col2];
            cipherText += keyTable[row2][col1];
        }
    }

    return cipherText;
}

int main() {
    string key = "KEYWORD";
    string plainText = "HELLO WORLD";

    char keyTable[5][5];
    createKeyTable(key, keyTable);

    preprocessText(plainText);

    string cipherText = playfairEncrypt(plainText, keyTable);

    cout << "Plain Text: " << plainText << endl;
    cout << "Cipher Text: " << cipherText << endl;

    return 0;
}