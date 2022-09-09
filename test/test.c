#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>


void prev() {
    char test[64];

    test[5] = 253;
    test[6] = 53;
    test[7] = 0;
}

void test() {
    void* val = alloca(128);
}

int main(int argc, char* argv[]) {
    prev();
    test();
}