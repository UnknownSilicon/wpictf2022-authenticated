#include "pac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void sign(struct authenticate* auth, int context) {
    __asm__(
        "LDR x7, [x1, #0xA]\r\n"
        "PACGA x4, x7, x2\r\n"
        "STR x4, [x7, #0x12]\r\n"
    );
}

struct authenticate* initialize(int context) {
    struct authenticate* auth = malloc(sizeof(struct authenticate));
    strcpy(auth->name, "default");
    auth->isAdmin = 0;

    sign(auth, context);

    return auth;
}

int verify(struct authenticate* auth, int context) {
    __asm__(
        "LDR x7, [x1, #0xA]\r\n"  // Load `isAdmin` into x7
        "PACGA x4, x7, x2\r\n"    // Compute the PAC for x7 using `context`
        "LDR x8, [x1, #0x12]\r\n" // Load the previous PAC into x8
        "CMP x4, x8\r\n"          // Compare the two PACs
        "BEQ end\r\n"             // If they are equal, jump
        "MOV x9, #0x0\r\n"        // Jump to 0x0
        "BR x9\r\n"
        "end:\r\n"                // All good
    );
    return 1;
}


int main(int argc, char* argv[]) {
    struct authenticate* auth = initialize(123);

    

    return 0;
}