#include <cstdio>
#include <cstring>

#define MAX_NAME_SIZE 0xf0

class Pet {
 private:
    char name_[MAX_NAME_SIZE];
 public:
    void setName(std::string& name) {
        int i;
        for (i = 0; i < name.length()
            // haha no overflow 4 u
            && i < MAX_NAME_SIZE; ++i) {
            name_[i] = name[i];
        }
        name_[i] = 0;
    }
    virtual void talk() = 0;
    virtual void goTowards(const char* location) = 0;
};

class Dog : public Pet {
 public:
    void talk() override {
        puts("Bark! Bark!");
    }

    void goTowards(const char* location) override {
        printf("I am running towards %s\n", location);
    }
};

class Frog : public Pet {
 public:
    void talk() override {
        puts("Ribbit. Ribbit!");
    }

    void goTowards(const char* location) override {
        printf("I am jumping towards %s\n", location);
    }
};

class Fish : public Pet {
 public:
    void talk() override {
        puts("Bloop");
    }

    void goTowards(const char* location) override {
        printf("I am swimming towards %s\n", location);
    }
};

class Doge : public Dog {
    void talk() override {
        puts("Much doge");
    }

    void goTowards(const char* location) override {
        printf("Very doge. Much %s\n", location);
    }
};