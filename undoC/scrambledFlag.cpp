#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("flag.txt","r",stdin);
    string flag;
    std::cin >> flag;
    string scrambled = "";
    while (flag.size() > 0) {
        char c = flag.at(flag.size()/2);
        scrambled.push_back(c);
        std::cout << scrambled << endl;
        flag.erase(flag.size()/2,1);
    }
    for (int i = 0; i < scrambled.size(); i++) {
        std::cout << scrambled.at(i)*3+5-24/2;
        std::cout << "  ";
    }
    return 0;
}