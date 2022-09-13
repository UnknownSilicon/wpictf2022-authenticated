#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void is_auth(int* out) {
    // Do some thing
    *out = 0;
}

void print_flag() {
    int auth = 0;
    is_auth(&auth);

    if (auth) {
        FILE* fp = fopen("./flag.txt", "r");

        char buf[255];

        fgets(buf, 50, fp);

        fclose(fp);

        printf("%s", buf);
    } else {
        printf("Authentication Failed!\n");
    }
}

void test() {
    char auth[10];

    gets(auth); // hack
    gets(auth);

    return;
}

void big_stack() {
    char large[2048];

    large[0] = 1; // This is literally just to force the compiler not to optimize the array out

    test();
}

int looping() {
    char input[50];

    void** stack;

    while(1) {
        printf("Select Option: Download More RAM (1), Print Flag (2), Print Info (3), System Test (4), Exit (5): ");

        scanf("%40s", input);

        if (strncmp(input, "1", 1) == 0) {
            stack = alloca(64);
        } else if (strncmp(input, "2", 1) == 0) {
            print_flag();
        } else if (strncmp(input, "3", 1) == 0) {
            printf("%p\n", *(stack+64));
        } else if (strncmp(input, "4", 1) == 0) {
            big_stack();
        } else if (strncmp(input, "5", 1) == 0) {
            break;
        }
    }
    return 0;
}


int main(int argc, char* argv[]) {
    printf("Welcome to the Automated Archive Authenticator (AAA) v0.152\n\n");

    return looping();
}