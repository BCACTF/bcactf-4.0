#include <iostream>
#include <cstdio>
#include "pets.hh"
// #include <cstring>
// #include <cstdint>
// #include <sys/mman.h>
// #include <unistd.h>

// -Wl,-z,norelro

#define PET_COUNT (12)

int readInteger() {
    // Regarding this code, thank CHAT-GPT 3.5
    char input[20]; // Assuming the input will be within 20 characters

    fgets(input, sizeof(input), stdin); // Read input from the user

    int number = atoi(input); // Convert input to an integer

    return number;
}

int readIndex() {
    int idx = 0;
    std::cout << "Please choose a pet index (1 to " << PET_COUNT << " inclusive)\n> ";
    idx = readInteger();

    while (idx <= 0 || idx > PET_COUNT) {
        std::cout << "Invalid pet index! Index must be from 1 to " << PET_COUNT << " (inclusive)\n> ";
        idx = readInteger();
    }

    return idx - 1; 
}

typedef struct {
    void (**vtable)(const char*);
    char name[];
}* WINNER;
void win(WINNER raw) {
    ((raw->vtable)[1])(raw->name);
}


int getInput(char* input) {
    int i;
    for (i = 0; i < 511; ++i) {
        char c = getchar();
        if (c == '\n') {
            input[i] = '\0';
            return i;
        } else {
            input[i] = c;
        }
    }
    return i;
}


bool DEBUG = true;

int main() {
    setbuf(stdout, nullptr);
    setbuf(stdin, nullptr);
    setbuf(stderr, nullptr);

    Pet* pets[PET_COUNT];
    char input[512];
    size_t s;

    std::cout << "~~~~~[pet zoo]~~~~~\n";
    while (1) {
        int action = 0;
        std::cout << "actions)\n";
        std::cout << "      1) adopt pet\n";
        std::cout << "      2) change pet name\n";
        std::cout << "      3) walk with pet\n";
        std::cout << "      4) free pet\n";
        std::cout << "      5) exit\n";
        std::cout << "What do you want to do?\n";
        std::cout << "> ";
        action = readInteger();

        switch (action) {
            // new
            case 1: {
                int idx = readIndex();
                std::cout << "Pick a name for your pet!\n> ";

                s = getInput(input);
                std::string name(input, s);

                int type = 0;
                std::cout << "decide pet type\n";
                std::cout << "      1) dog\n";
                std::cout << "      2) frog\n";
                std::cout << "      3) fish\n";
                std::cout << "      4) doge\n";
                std::cout << "What do you say?\n";
                std::cout << "> ";
                type = readInteger();


                Pet*& a = pets[idx];
                switch (type) {
                    case 1: {
                        a = new Dog();
                        a->setName(name);
                        std::cout << name << " says: ";
                        a->talk();
                    } break;
                    case 2: {
                        a = new Frog();
                        a->setName(name);
                        std::cout << name << " says: ";
                        a->talk();
                    } break;
                    case 3: {
                        a = new Fish();
                        a->setName(name);
                        std::cout << name << " says: ";
                        a->talk();
                    } break;
                    case 4: {
                        a = new Doge();
                        a->setName(name);
                        std::cout << name << " says: ";
                        a->talk();
                    } break;
                    default: {
                        if (DEBUG) printf("pet type unfound; %p\n", a);
                        break;
                    }
                }
            } break;
            // name
            case 2: {
                int idx = readIndex();
                std::cout << "Pick a name for your pet!\n> ";
                s = getInput(input);
                std::string name(input, s);

                Pet* a = pets[idx];
                if (a == nullptr) {
                    std::cout << "Unexistant pet!\n";
                    break;
                }

                std::cout << name << " says: ";
                a->talk();

                a->setName(name);
            } break;
            // location
            case 3: {
                int idx = readIndex();
                std::cout << "Where do you want to go?\n> ";
                s = getInput(input);
                std::string location(input, s);

                Pet* a = pets[idx];
                if (a == nullptr) {
                    std::cout << "Unexistant pet!\n";
                    break;
                }

                a->goTowards(location.c_str());
            } break;
            // free
            case 4: {
                int idx = readIndex();

                Pet* a = pets[idx];
                if (a == nullptr) {
                    std::cout << "Unexistant pet!\n";
                    break;
                }

                delete pets[idx];
                pets[idx] = nullptr;
            } break;
            default: exit(0); break;
        }

    }
}