
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct test{
    void* a;
    int b;
    long c;
    double adf;
    float adsf;
};

size_t isLittle(void){
    unsigned int x = 1;
    return (int) (((char *)&x)[0]);
}

size_t max(size_t a, size_t b){
    if(a>b) return a;
    return b;
}
/* This implementation will work for x86 32 bit and 64 bit computers, but will need 8 bytes alignment on 32 bit SPARC. */

/* SPARCen fuckar bara om den har en strukt med doubles. Annars funkar den här implementationen bra.

   Vi skulle kunna göra ett specialfall för double isåfall så att strukten då läggs på 8 byte alignat minne. */

/* Den här funktionen löser padding mellan objekt och efter objekt, men den antar att det är alignat innan. */
size_t structSizeFromString(char *layout) {
    size_t res = 0;
    size_t align = 1; //Largest alignment.
    int i = 0;
    char c = *layout;
    while (c) {
        c = *(layout + i);
        switch (c) {
        case 'c':
            res += sizeof(char);
            break;
        case '*':
            if(res % sizeof(void*) != 0){
                res += sizeof(void*) - res % sizeof(void*);
            }
            align = max(align, sizeof(void*));
            res += sizeof(void*);
            break;
        case 'i':
            if(res % sizeof(int) != 0){
                res += sizeof(int) - res % sizeof(int);
            }
            align = max(align, sizeof(int));
            res += sizeof(int);
            break;
        case 'f':
            if(res % sizeof(float) != 0){
                res += sizeof(float) - res % sizeof(float);
            }
            align = max(align, sizeof(float));
            res += sizeof(float);
            break;
        case 'd':
            if(isLittle() && res % sizeof(void*) != 0){
                res += sizeof(void*) - res % sizeof(void*);
                align = max(align, sizeof(void*));
            }else if(res % sizeof(double) != 0){
                res += sizeof(double) - res % sizeof(double);
                align = max(align, sizeof(double));
            }
            res += sizeof(double);
            break;
        case 'l':
            if(res % sizeof(long) != 0){
                res += sizeof(long) - res % sizeof(long);
            }
            align = max(align, sizeof(long));
            res += sizeof(long);
            break;
        }
        i++;
    }
    printf("Res: %d \n", (int)align);
    if(res % align != 0){
        res += align - res % align;
        puts("THIS RUNS");
    }
    return res;
}

int main(int argc, char *argv[])
{
    char *string = malloc(10);
    string = "cli";
    size_t test = structSizeFromString(string);
    
    printf("Size is: %d \n", (int)sizeof(struct test));

    string = "*cildf";
    test = structSizeFromString(string);
    printf("Size is: %d \n", (int)test);
    return 0;
}
