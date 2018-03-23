#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FHEv1.h"

int main(int argc, char* argv[]){
    if (argc == 4 && strcmp(argv[1], "-k") == 0){
        size_t keySize = 0;
        keySize = atoi(argv[2]);
        keyGen(keySize, argv[3]);
    }
    else {
        printf("Usge: FHEv1 -k <key size> <KeyFileName>\n");
    }
    return EXIT_SUCCESS;
}
