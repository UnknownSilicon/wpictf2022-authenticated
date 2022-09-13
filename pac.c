#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void is_auth(int* out) {
    // Do some thing
    *out = 1;
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
    }
}

int try() {
    char buf[50];

    while(1) {
        printf("Select Option: ");

        scanf("%2s", buf);

        if (strncmp(buf, "1", 1) == 0) {

        } else if (strncmp(buf, "2", 1) == 0) {

        }
    }
    return 1;
}


int main(int argc, char* argv[]) {
    printf("Welcome to the Automated Archive Authenticator (AAA) v0.152\n\n");

    return try();

    //auth->verify = 0;

    //verify(auth, 123);

    //return 0;
}