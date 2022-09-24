#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void check_pass(char* pass) {
    return;
}

void is_auth(int* out) {
    char buf2[4055];
    buf2[0] = 0;
    buf2[4054] = 1;
    buf2[1] = buf2[0];
    // Do some thing
    check_pass("no");
    printf("%p\n",  (void*)*((long long unsigned int*)((void*)&buf2 - 32))); // Print signed return address of is_auth
    *out = 0;
}

void print_flag() {
    //char buf2[1024];
    //buf2[0] = 0;
    //buf2[1023] = 5;
    //buf2[1] = buf2[0];

    int auth = 0;
    is_auth(&auth);

    if (auth) {
        FILE* fp = fopen("./flag.txt", "r");

        char buf[256];

        fgets(buf, 50, fp);

        fclose(fp);

        printf("%s", buf);
    } else {
        printf("Authentication Failed!\n");
    }
}

void read_buf() {
    char auth[10];

    gets(auth); // hack
    gets(auth);

    sleep(5);

}

void test() {
    read_buf();
    // The stack pointer at the end of this function is what is used to verify
    return;
}

void big_stack() {
    char buf[8];

    test();
}

int looping() {
    char input[64];

    char* stack;

    while(1) {
        printf("Select Option: Download More RAM (1), Print Flag (2), Print Info (3), System Test (4), Reset (5), Exit (6): ");

        scanf("%2s", input);

        if (strncmp(input, "1", 1) == 0) {
            stack = alloca(64);
            stack = stack-0x10;
        } else if (strncmp(input, "2", 1) == 0) {
            print_flag();
        } else if (strncmp(input, "3", 1) == 0) {
            //printf("----\n");
            //printf("%08llx\n", (long long unsigned int)(stack)); // print the address of stack
            //printf("%08llx\n", (long long unsigned int)(stack-776)); // print the address of stack+24
            printf("%08llx\n", *(long long unsigned int *)(0x55007fe8f8)); // print value at 0x55007fe8f8
            //printf("%08llx\n", *(long long unsigned int *)(stack-776)); // Value at stack+24
            //printf("%08llx\n", *(long long unsigned int *)(0x55007fe8f8)); // print value at 0x55007fe8f8
            //printf("----\n");
        } else if (strncmp(input, "4", 1) == 0) {
            big_stack();
        } else if (strncmp(input, "5", 1) == 0) {
            return 0;
        } else if (strncmp(input, "6", 1) == 0) {
            return 1;
        }
    }
    return 1;
}


int main(int argc, char* argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Welcome to the Automated Archive Authenticator (AAA) v0.152\n\n");

    while (looping() == 0);
    return 0;
}