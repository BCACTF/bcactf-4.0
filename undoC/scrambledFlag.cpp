#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    cout << "Flag checker :o\n";
    cout << "Enter flag\n? ";
    char flag[50];
    fgets(flag, 50, stdin);
    string baseFlag = "";
    for (char c : flag) {
        baseFlag += c;
    }
    int encryptedInput[50] = {};
    int count = 0;
    while (baseFlag.size() > 0) {
        char c = baseFlag.at(baseFlag.size()/2);
        encryptedInput[count] =  c*3+5-24/2;
        count++;
        baseFlag.erase(baseFlag.size()/2,1);
    }

    int encryptedFlag[50] = {230, 356, 149, 278, 278, 92, 344, 152, 227, 323, 152, 137, 290, 212, 335, 341, 284, 284, 224, 221, 287, 149, 158, 341, 296, 149, 197, 239, 278, 302, 140, 323, 245, 137, 278, 290, 137, 362, 143, 299, 158, 341, 149, 290, 149, 284, 158, 290, -7, 287};

    bool correct = true;
    for (int i = 0; i < 50; i++) {
        if (encryptedFlag[i] != encryptedInput[i]) {
            correct = false;
        }
    }
    if (correct) {cout << "Correct!";}
    else {cout << "Incorrect.";}
}