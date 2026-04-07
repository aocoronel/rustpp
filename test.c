#include <stdio.h>
int add_int(int x, int y);

int main(int argc, char *argv[]) {
        printf("%d\n", add_int(20, 30));
        return 0;
}

// rustc -O --crate-type staticlib add.rs
// cc test.c libadd.a
//
// or
//
// clang++ hello.cpp -fno-exceptions -fno-rtti -nostdlib++ -c
// cc test.c hello.o
