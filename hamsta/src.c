#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void sleepms(long ms) {
    // https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void load_flag(char* flag, size_t size) {
    FILE *fp = NULL;

    fp = fopen("./flag.txt", "r");
    if (fp == NULL) {
        puts("flag.txt could not be loaded; if you see this, please contact admin.");
        return;
    }

    fgets(flag, size, fp);
}

void hamster_logo() {
    system("clear");
    puts("                                                                                ");
    puts("                  .&*,,%(#,#%               .(*                                 ");
    puts("                  %@@#*,,,*,,,,*,,*&@    &//*%**/(                              ");
    puts("                  .@*,,,,,,,,,,,,,,,,,*/#//@**,,,*#                             ");
    puts("                %/,,*,,,,,,,,,,,,,,,,,,**/%**,,,,,%                             ");
    puts("              .&*,,,,,,,,, .,,,,,,,,,,,,,,,*,,,,,,@                             ");
    puts("       @/(&//(#**,,,,,,,..   ,,,,,,,,,,,,,,,,/#&(                               ");
    puts("       ***//(@***,,,,,,,      .,,,,,*@,,,,,,,,**&.                              ");
    puts("        @,**/(***,,,,,,,        ,,,@@@@,,,,,,,,,,*/                             ");
    puts("         #**/****,,,@@,,          .,@@*,,         ,/,,%@.                       ");
    puts("            .(***,,@@@@,.                          &,,,,,,,@.                   ");
    puts("            ./**,,,*@@,,     /*                   .#,,,,,,,,,,&                 ");
    puts("            ,**.              &    _.             %,,,,,,,,,,,,,#,              ");
    puts("             &              .  @(&'^            (,,,,,,,,,,,,,,,,,@             ");
    puts("              #              ^''              ,*,,,,,,,,,,,,,,,,,,,%            ");
    puts("               %, .                       ,****,,,,,,,,,,,,,,,,,,,,,@           ");
    puts("                  #&#,.                   ,,,,,,,,,,,,,,,,,,,,      *.          ");
    puts("                  %*...  .                    .,,,,,,,,.            /.          ");
    puts("                  #. .                                              @           ");
    puts("                  &  ..                                            &            ");
    puts("                  (  ..... .         (                           &              ");
    puts("                   & ......##     ..,%         (         (/..(@(**%             ");
    puts("                 (#//#&&@*       */#@       *@#((#%@%*     %&*&&.               ");
    puts("                  .%#.&&         //*,*#%%,                                      ");
    puts("                                    %,.%#                                       ");
    puts("                                                                                ");
    puts("            888                                  888                            ");
    puts("            888                                  888                            ");
    puts("            888                                  888                            ");
    puts("            88888b.  8888b. 88888b.d88b. .d8888b 888888 .d88b. 888d888          ");
    puts("            888  88b     88b888  888  88b88K     888   d8P  Y8b888P             ");
    puts("            888  888.d888888888  888  888 Y8888b.888   88888888888              ");
    puts("            888  888888  888888  888  888     X88Y88b. Y8b.    888              ");
    puts("            888  888 Y888888888  888  888 88888P   Y888  Y8888 888              ");                                   
    putchar('\n');
}
                   
void hamster_frame1() {
    system("clear");
    puts("                                                                              ");                              
    puts("                          ░░  ▓▓████▓▓██▓▓▓▓▓▓░░░░░░                          ");
    puts("                    ██████░░  ████████████████▒▒  ░░████░░                    ");
    puts("                  ▒▒    ░░████                ██████▒▒  ▓▓                    ");
    puts("                ▓▓▓▓████▓▓                        ░░████▒▒████                ");
    puts("              ▒▒░░▒▒                                    ▒▒░░░░██              ");
    puts("            ▓▓▒▒                                              ██░░▒▒          ");
    puts("          ░░░░▒▒                                                ▓▓▒▒          ");
    puts("          ▓▓▓▓                                                    ▓▓▓▓        ");
    puts("        ▒▒▒▒                                                      ▒▒░░▓▓      ");
    puts("      ░░▓▓▒▒                                                        ██▒▒██    ");
    puts("      ▓▓▓▓                                                            ██  ▒▒  ");
    puts("      ▓▓▓▓                                                            ██░░▒▒  ");
    puts("    ▒▒░░░░                                                            ░░██▒▒░░");
    puts("    ▒▒▒▒░░                  ▒▒▒▒▒▒▒▒                                    ██▒▒░░");
    puts("  ░░▒▒▓▓                  ▒▒░░░░░░░░██                                    ▒▒▓▓");
    puts("    ██▓▓                ░░▒▒░░    ░░░░██                                  ▒▒▓▓");
    puts("    ██▓▓              ░░░░▒▒        ░░██      ░░                          ██▓▓");
    puts("  ░░▒▒▓▓            ▒▒▒▒▒▒▒▒        ░░██▒▒▒▒▒▒▒▒▒▒▒▒▒▒                    ██▓▓");
    puts("    ▓▓▓▓          ▒▒░░░░░░░░░░    ░░██░░░░░░░░░░░░░░░░██░░██████▓▓        ▓▓▓▓");
    puts("    ▒▒▓▓        ▓▓░░░░▓▓░░░░░░░░░░▓▓░░░░░░░░░░░░░░░░░░░░▒▒░░░░░░▓▓        ▒▒▓▓");
    puts("  ░░▓▓▓▓    ██▓▓  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░████            ▓▓▓▓");
    puts("    ██▓▓    ████  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██              ▒▒▓▓");
    puts("    ▒▒░░░░  ▓▓        ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██        ░░██▒▒░░");
    puts("    ▒▒░░░░  ░░▒▒            ░░░░░░░░░░░░░░░░░░██░░░░░░░░░░░░██        ░░██▒▒░░");
    puts("      ██▓▓    ░░██▓▓░░      ░░░░░░░░░░░░░░░░██░░░░░░░░░░░░░░██        ▓▓░░▒▒  ");
    puts("      ▓▓▓▓      ▒▒▓▓░░      ▓▓░░░░░░░░░░░░░░██░░░░░░░░░░░░░░██        ▓▓░░▒▒  ");
    puts("      ░░▒▒▒▒      ████████  ██░░░░██        ██░░░░░░░░░░░░██        ██░░██    ");
    puts("        ▒▒▒▒              ▓▓██░░░░██░░░░░░░░██░░░░░░░░░░░░▓▓        ▒▒▓▓      ");
    puts("        ░░▒▒▒▒              ██░░▒▒░░░░  ░░░░░░▓▓▓▓░░░░░░▓▓        ▒▒▒▒░░      ");
    puts("      ████▒▒▒▒▒▒            ██░░▒▒                ████░░▓▓      ██▓▓          ");
    puts("      ▓▓▓▓  ▒▒▒▒░░          ██░░▒▒                ░░██▒▒░░░░░░▓▓░░░░          ");
    puts("    ▒▒▒▒░░▒▒  ▒▒▒▒▒▒        ██▒▒░░                  ██▒▒▒▒▒▒▓▓▓▓░░            ");
    puts("    ▒▒░░░░▒▒    ██░░████▓▓                          ████░░████                ");
    puts("    ▒▒░░░░▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░░░▒▒░░░░░░░░░░▒▒▒▒▓▓▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒");
    puts("    ██░░░░▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░▒▒▒▒░░▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓");
    puts("    ▒▒██████████████████████████████████████████████████████████████████████░░");
    putchar('\n');
}

void hamster_frame2() {
    system("clear");
    puts("                                                                          ");
    puts("                            ░░░░▓▓▓▓▓▓▓▓██▓▓▓▓░░░░                         ");
    puts("                      ░░██▒▒░░  ██████████████░░░░████▒▒                   ");
    puts("                     ▓▓░░▒▒████              ████░░▒▒▒▒                    ");
    puts("                 ▒▒██░░██▒▒                      ▓▓██▒▒▓▓▓▓                ");
    puts("               ░░▓▓░░▒▒                              ░░▒▒░░▓▓              ");
    puts("             ██░░░░                                        ██▓▓░░          ");
    puts("           ▒▒▒▒▓▓                                            ▒▒▓▓          ");
    puts("         ░░▒▒▓▓                                              ░░░░██░░      ");
    puts("         ▓▓▓▓                                                  ▓▓░░██      ");
    puts("       ██░░░░                                                    ██░░▓▓    ");
    puts("     ██  ▓▓                    ░░                                  ██▒▒░░  ");
    puts("     ██░░▓▓              ▒▒▒▒▒▒▒▒▒▒                                ██░░░░  ");
    puts("   ▓▓░░██              ▒▒░░      ░░██                                ▓▓▓▓  ");
    puts("   ▓▓░░██            ▒▒▓▓░░      ░░████▒▒░░██▒▒░░                    ▓▓▒▒  ");
    puts("   ░░██            ██░░▒▒░░      ░░██░░░░░░░░░░▒▒██      ████        ░░▒▒██");
    puts("   ▒▒██          ▒▒░░░░░░░░      ▓▓░░░░░░░░░░░░░░░░▓▓▒▒██░░██        ░░▒▒██");
    puts("   ░░██        ▓▓▒▒░░▓▓░░░░░░░░▒▒░░░░░░░░░░░░░░░░░░░░▒▒░░░░▓▓        ░░▒▒██");
    puts("   ▒▒██    ▒▒██  ░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒          ░░▒▒██");
    puts("   ░░██  ░░████  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██            ░░  ██");
    puts("   ░░██  ░░░░        ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓░░          ░░▒▒██");
    puts("   ░░██    ▒▒████░░      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓          ░░▒▒██");
    puts("   ░░██      ██▓▓▓▓      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓          ░░▒▒██");
    puts("   ▓▓▒▒██      ▓▓▓▓██      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓          ▓▓▒▒  ");
    puts("   ▓▓  ██        ▒▒████░░▒▒░░░░▒▒░░            ▒▒░░░░░░░░░░██        ▓▓▓▓  ");
    puts("     ██▒▒▓▓            ▒▒▓▓░░░░▒▒░░░░░░░░░░░░▓▓▓▓░░░░░░░░░░▓▓░░    ██░░░░  ");
    puts("     ██  ▓▓            ░░░░░░▓▓░░░░░░░░░░  ░░    ░░░░▓▓██▒▒░░▒▒░░  ██▒▒░░  ");
    puts("       ██▒▒░░        ░░░░▒▒██                            ░░████░░██  ██    ");
    puts("         ▓▓▒▒        ░░██▒▒                                    ▓▓░░██      ");
    puts("         ░░▓▓▒▒                                                ▒▒▓▓░░      ");
    puts("     ████▓▓▒▒  ▓▓                                            ▒▒▓▓          ");
    puts("     ██░░▓▓  ▓▓░░▒▒░░                                  ░░░░▓▓▒▒            ");
    puts("   ▒▒░░▒▒▒▒▒▒  ▒▒▒▒░░▒▒                              ░░▓▓▒▒▒▒░░            ");
    puts("   ░░░░░░░░▒▒    ▒▒██▒▒██▒▒                      ████▒▒██▓▓                ");
    puts("  ░░  ░░  ▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▓▓░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░");
    puts("  ░░░░░░  ▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒░░▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██");
    puts("  ▓▓████████████████████████████████████████████████████████████████████  ");
    putchar('\n');
}

void hamster_frame3() { 
    system("clear");                                                                                                                                               
    puts("                                                                          ");
    puts("                              ▒▒▒▒▒▒▒▒▒▒▒▒▒▒                              ");
    puts("                        ▒▒████░░░░▒▒  ▒▒  ▒▒████                          ");
    puts("                    ▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒                    ");
    puts("                ░░▒▒▒▒▒▒▒▒░░░░              ░░░░▒▒▓▓▒▒▒▒▒▒                ");
    puts("              ░░░░▒▒▓▓                              ▒▒░░▒▒██              ");
    puts("            ░░▒▒▒▒▒▒                                  ▒▒▒▒▒▒▒▒            ");
    puts("          ░░░░▓▓                                          ░░▒▒▒▒          ");
    puts("        ░░▒▒██                                              ▒▒░░██        ");
    puts("        ▓▓▓▓                                                  ▓▓░░██      ");
    puts("      ▒▒▒▒▒▒                                                  ░░▓▓▒▒▒▒    ");
    puts("    ██▒▒▓▓                                                        ██░░░░  ");
    puts("    ██  ██                                                        ██▒▒    ");
    puts("  ▓▓  ██                                                            ▓▓▓▓  ");
    puts("  ██  ██                                                            ▓▓▒▒  ");
    puts("  ▒▒██                                                              ░░▒▒██");
    puts("  ░░██                        ██████▒▒                              ░░░░██");
    puts("  ▒▒██                      ██░░░░░░▒▒                              ░░▒▒██");
    puts("  ░░██                    ▓▓░░░░    ░░▓▓                            ░░▒▒██");
    puts("  ▒▒██                  ████░░      ░░████████▒▒                    ░░▒▒██");
    puts("  ░░██                ▒▒░░▓▓░░        ▓▓░░░░░░▒▒██▓▓                ░░▒▒██");
    puts("  ░░██              ░░▒▒░░░░░░░░    ▒▒░░░░░░░░░░░░░░▒▒░░            ░░▒▒██");
    puts("  ▓▓  ██      ░░██  ░░▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒░░██████░░    ▓▓▓▓  ");
    puts("  ▓▓░░██      ▓▓██  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██░░░░▒▒░░    ▓▓▓▓  ");
    puts("    ██  ▓▓    ▓▓        ░░░░░░░░░░░░░░░░░░░░██▒▒░░░░░░██▓▓        ██▒▒░░  ");
    puts("    ██  ▓▓    ░░░░        ░░░░░░░░░░░░░░████░░░░░░░░░░██          ██░░    ");
    puts("    ▓▓▒▒▒▒    ░░▓▓          ░░░░░░░░░░▒▒▒▒░░░░░░░░░░░░▓▓        ░░▓▓░░░░  ");
    puts("      ░░▒▒▒▒    ░░▒▒▒▒▒▒      ░░░░░░░░▓▓░░░░░░░░░░░░▒▒        ▒▒░░▓▓░░    ");
    puts("        ▓▓▓▓        ▓▓        ░░░░██░░▓▓░░░░░░░░░░░░▒▒        ▓▓  ██      ");
    puts("        ░░▒▒██      ░░████░░  ▒▒░░██  ▓▓░░░░░░░░░░░░▒▒      ░░▒▒▓▓        ");
    puts("    ██▓▓▓▓▒▒░░▓▓          ▒▒▓▓▒▒░░░░▒▒██░░░░░░░░░░▓▓        ▒▒▓▓          ");
    puts("  ▓▓██████░░  ▓▓▒▒██          ▒▒░░░░▒▒░░▒▒░░░░▒▒      ████▒▒▒▒            ");
    puts("  ░░░░░░  ▒▒  ░░▒▒▒▒▒▒░░        ▒▒░░▒▒▓▓░░░░▒▒  ░░░░▒▒░░░░▓▓              ");
    puts("  ░░  ░░░░▒▒▒▒▒▒▓▓██▒▒▒▒▒▒▒▒▒▒    ░░▓▓▓▓▒▒░░▒▒▒▒▓▓▒▒▒▒████▒▒▒▒▒▒▒▒▒▒▒▒██  ");
    puts("  ░░░░    ██▒▒▒▒▒▒▒▒▓▓██▒▒▒▒  ██████████████▒▒  ████▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██");
    puts("  ░░░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████▒▒░░░░▒▒░░▒▒░░████▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓");
    putchar('\n');
}

void wait_for(int nseconds) {
    for (int i = 0; i < nseconds; ++i) {
        printf(" .");
        sleep(1);
    }
    printf("\n");
}

void print_sliced_string(char* string, int count) {
    for (int i = 0; i < count && string[i] != '\0'; i++) {
        putchar(string[i]);
    }

    putchar('\n');
}


int readInteger() {
    // Regarding this code, thank CHAT-GPT 3.5
    char input[20]; // Assuming the input will be within 20 characters

    fgets(input, sizeof(input), stdin); // Read input from the user

    int number = atoi(input); // Convert input to an integer

    return number;
}

#define MAX_DISTANCE 11

int main() {
    char flag[100];
    load_flag(flag, 100);
    int flag_len = strlen(flag);

    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);

    puts("Warning: You may need to zoom out your window for the best hamster experience");
    wait_for(3);
    hamster_logo();
    wait_for(3);

    int distance = 0;
    bool has_moved = false;
    
    hamster_frame1();
    puts("Hi there. This is my my hamster. He LOVES to run.");
    puts("The further he runs, the more of the flag you get");
    do {
        printf("How many miles do you want him to run? ");
        distance = readInteger();

        if (distance > MAX_DISTANCE) {
            puts("HEY! My hamster is not a MACHINE");
            puts("He does NOT want to run that far");
            printf("He likes to run up to %d miles\n", MAX_DISTANCE);
            continue;
        }

        printf("Awesome, (%d <= %d) is true, so my hamster's ready to run!\n", distance, MAX_DISTANCE);
        sleep(1);
        int i;
        for (i = 0; i != distance && i < flag_len; ++i) {
            hamster_frame2();
            printf("Flag is: ");
            print_sliced_string(flag, i + 1);
            sleepms(250);
            hamster_frame3();
            printf("Flag is: ");
            print_sliced_string(flag, i + 1);
            sleepms(250);
            hamster_frame1();
            printf("Flag is: ");
            print_sliced_string(flag, i + 1);
            sleepms(250);
        }

        if (i == flag_len) return 0;

        wait_for(3);
        printf("Welp! That was %d miles, time to stop\n", distance);
        puts("But let's do it again!");
    } while (1);

    puts("Unknown option. Goodbye");
    return 1;
}