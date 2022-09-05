#include "pac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void sign(struct authenticate* auth, int context) {
    __asm__(
        "LDR x9, [x0, #0xA]\r\n"
        "PACGA x10, x9, x1\r\n"
        "STR x10, [x0, #0x12]\r\n"
    );
}

struct authenticate* initialize(int context) {
    struct authenticate* auth = malloc(sizeof(struct authenticate));
    strcpy(auth->name, "default");
    strcpy(auth->password, "default");
    auth->isAdmin = 0;

    sign(auth, context);

    return auth;
}

int verify(struct authenticate* auth, int context) {
    __asm__(
        "LDR x9, [x0, #0xA]\r\n"    // Load `isAdmin` into x7
        "PACGA x10, x9, x1\r\n"     // Compute the PAC for x7 using `context`
        "LDR x11, [x0, #0x12]\r\n"  // Load the previous PAC into x8
        "CMP x10, x11\r\n"          // Compare the two PACs
        "BEQ end\r\n"               // If they are equal, jump
        "MOV x9, #0x0\r\n"          // Jump to 0x0
        "BR x9\r\n"
        "end:\r\n"                  // All good
    );
    return 1;
}

int try(struct authenticate* auth) {
    char buf[50];

    printf("Enter Name: ");
    scanf("%50s", buf);
    strncpy(auth->name, buf, 50);

    printf("\nEnter password: ");
    scanf("%50s", buf);
    strncpy(auth->password, buf, 20);

    printf("\n");

    if (strncmp(auth->password, "thisisareallygoodpassword", 25) == 0) {
        printf("Authenticated\n");

        if (verify(auth, 123)) {
            printf("Verified\n");
            if (auth->isAdmin != 0) {
                printf("Flag: \n");

                FILE* fp;

                fp = fopen("./flag.txt", "rb");

                fscanf(fp, "%s", buf);

                printf("%s", buf);

                return 0;
            }
        }
        printf("Intrusion detected!\n");
    } else {
        printf("Failed\n");

    }
    return 1;
}


int main(int argc, char* argv[]) {
    struct authenticate* auth = initialize(123);

    printf("Welcome to the Automated Archive Authenticator (AAA) v0.152\n\n");

    return try(auth);

    //auth->verify = 0;

    //verify(auth, 123);

    //return 0;
}