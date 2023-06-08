#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

void load_flag(char* flag, size_t size) {
    FILE *fp = NULL;

    fp = fopen("./flag.txt", "r");
    if (fp == NULL) {
        puts("flag.txt could not be loaded; if you see this, please contact admin.");
        return;
    }

    fgets(flag, size, fp);
}

typedef struct {
    size_t size;
    size_t __;
    char text[];
} note_t;

note_t* note_alloc(size_t size) {
    note_t* this = malloc(size + sizeof(note_t) + 1);
    this->size = size;

    return this;
}

void note_write(note_t* this, char* str) {
    if (strlen(str) >= this->size) return;

    strcpy(this->text, str);
}

char* note_read(note_t* this) {
    return this->text;
}

void note_free(note_t* this) {
    free(this);
}

#define NOTE_COUNT 5
#define MAX_NOTE_SIZE 128

note_t* notes[NOTE_COUNT + 12];


int readInteger() {
    // Regarding this code, thank CHAT-GPT 3.5
    char input[20]; // Assuming the input will be within 20 characters

    fgets(input, sizeof(input), stdin); // Read input from the user

    int number = atoi(input); // Convert input to an integer

    return number;
}

int readNoteIndex() {
    int idx = 0;
    printf("Please choose a note (1 to %d inclusive)\n", NOTE_COUNT);
    idx = readInteger();

    while (idx <= 0 || idx > NOTE_COUNT) {
        printf("Invalid note index! Index must be from 1 to %d (inclusive)\n> ", NOTE_COUNT);
        idx = readInteger();
    }

    return idx - 1; 
}

size_t readNoteSize() {
    int size = 0;
    printf("Please choose a size (1 to %d inclusive)\n> ", MAX_NOTE_SIZE);
    size = readInteger();

    while (size <= 0 || size >= MAX_NOTE_SIZE) {
        printf("Invalid note size! Size must be from 1 to %d (inclusive)\n> ", MAX_NOTE_SIZE);
        size = readInteger();
    }

    return size;
}

void handleCreate() {
    int idx = readNoteIndex();
    int size = readNoteSize();
    notes[idx] = note_alloc(size);
}

void handleWrite() {
    note_t* note = notes[readNoteIndex()];
    if (note == NULL) {
        puts("ERROR. Unexistant note!");
        return;
    }
    printf("Please enter content; With a maximum length of %zu\n: ", note->size);
    fgets(note->text, note->size, stdin);
}

void handleRead() {
    note_t* note = notes[readNoteIndex()];
    if (note == NULL) {
        puts("ERROR. Unexistant note!");
        return;
    }
    puts(note->text);
}

void handleDelete() {
    int idx = readNoteIndex();
    note_t* note = notes[idx];
    if (note == NULL) {
        puts("ERROR. Unexistant note!");
        return;
    }
    note_free(note);
    notes[idx] = NULL;
}

void handleExit() {
    puts("Bye bye");
    exit(0);
}

void thoughts() {
    notes[0] = note_alloc(100);
    for (int i = 1; i < 7; ++i) {
        notes[i] = note_alloc(100);
    }
    strcpy(notes[0]->text, "Da flag iss:");
    load_flag(notes[0]->text + strlen(notes[0]->text), 80);
    for (int i = 0; i < 7; i ++) {
        free(notes[i]);
        notes[i] = NULL;
    }
}

int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);

    thoughts();

    puts("====[NOTETAKER++]====");
    while (1) {
        int action;
        puts("actions)");
        puts("      1) create");
        puts("      2) write");
        puts("      3) read");
        puts("      4) delete");
        puts("      5) exit");
        puts("What do you want to do?");
        printf("> ");

        action = readInteger();

        switch (action) {
            case 1: handleCreate(); break;
            case 2: handleWrite(); break;
            case 3: handleRead(); break;
            case 4: handleDelete(); break;
            default:
            case 5: handleExit(); break;
        }
    }
}