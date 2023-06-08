#include <bits/stdc++.h>
using namespace std;

int main() {
    FILE *flagFile = fopen("flag.txt","r");
    char flag[50];
    fgets(flag, 50, flagFile);
    string baseFlag = "";
    for (char c : flag) {
        baseFlag += c;
    }
    int encryptedFlag[50] = {};
    int count = 0;
    while (baseFlag.size() > 0) {
        char c = baseFlag.at(baseFlag.size()/2);
        encryptedFlag[count] =  c*3+5-24/2;
        count++;
        baseFlag.erase(baseFlag.size()/2,1);
    }

    fclose(flagFile);

    int userInput[50] = {};
    for (int i = 0; i < 50; i++) {
        int input;
        std::cin >> input;
        userInput[i] = input;
    }

    bool correct = true;
    for (int i = 0; i < 50; i++) {
        if (userInput[i] != encryptedFlag[i]) {
            correct = false;
        }
    }
    if (correct) {std::cout << "Correct!";}
    else {std::cout << "Incorrect.";}
}