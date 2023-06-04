#include <bits/stdc++.h>
using namespace std;

int main() {
    int given[50] = {230,356,149,278,278,92,344,152,227,323,152,137,290,212,335,341,284,284,224,221,287,149,158,341,296,149,197,239,278,302,140,323,245,137,278,290,137,362,143,299,158,341,149,290,149,284,158,290,368,287};
    string scrambled = "";
    for (int num : given) {
        // *3+5-24/2
        scrambled.push_back(char((num+7)/3));
    }
    string flag = "";
    int count = 1;
    while (scrambled.size() > 0) {
        if (count % 2 == 1) {
            flag.push_back(scrambled.at(0));
        }else {
            flag = scrambled.at(0) + flag;
        }
        scrambled.erase(0,1);
        count++;
    }
    std::cout << flag;
}