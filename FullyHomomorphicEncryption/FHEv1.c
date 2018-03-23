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
    else if (argc == 4 && strcmp(argv[1],"-e")== 0){
        FILE* file = fopen(argv[3], "r");
        if(file != NULL){
            encryption(argv[2],file);
            fclose(file);
        }
        else{
            printf("Opening key file fails! User may need generate key file first.\n");
            return EXIT_FAILURE;
        }
    }
    else if(argc == 4 && strcmp(argv[1], "-d") == 0){
        FILE* file = fopen(argv[3], "r");
        if(file != NULL){
            decryption(argv[2],file);
            fclose(file);
        }
        else{
            printf("Opening key file fails! User may need generate key file first.\n");
            return EXIT_FAILURE;
        }
    }
    else {
        printf("Usge: FHEv1 -k <key size> <KeyFileName>\n");
        printf("Usge: FHEv1 -e <m> <KeyFileName>\n");
        printf("Usge: FHEv1 -d <Cm> <KeyFileName>\n");
        
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
