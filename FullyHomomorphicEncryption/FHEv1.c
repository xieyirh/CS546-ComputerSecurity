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
            char* cipherText = NULL;
            cipherText = encryption(argv[2],file);
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
    else if(argc == 4 && strcmp(argv[1],"-b") == 0 ){
        FILE* file = fopen(argv[3], "r");
        if(file != NULL){
            printf("Input message = %s\n", argv[2]);
            encrDecryption(argv[2],file);
            fclose(file);
        }
        else{
            printf("Opening key file fails! User may need generate key file first.\n");
            return EXIT_FAILURE;
        }
    }
    else if(argc == 5 && strcmp(argv[1],"-a") == 0){
        FILE * file = fopen(argv[4], "r");
        if(file != NULL){
            cipherAddition(argv[2], argv[3], file);
            fclose(file);
        }
        else {
            printf("Opening key file fails! User may need generate key file first.\n");
            return EXIT_FAILURE;
        }
    }
     else if(argc == 7 && strcmp(argv[1],"-a") == 0 && strcmp(argv[2],"-e")== 0 && strcmp(argv[4], "-e")== 0 ){
        FILE * file = fopen(argv[6], "r");
        if(file != NULL){
            messageAddition(argv[3], argv[5], file);
            fclose(file);
        }
        else {
            printf("Opening key file fails! User may need generate key file first.\n");
            return EXIT_FAILURE;
        }
    }
    else if(argc == 5 && strcmp(argv[1],"-m") == 0){
        FILE * file = fopen(argv[4], "r");
        if(file != NULL){
            cipherMultiplication(argv[2], argv[3], file);
            fclose(file);
        }
        else {
            printf("Opening key file fails! User may need generate key file first.\n");
            return EXIT_FAILURE;
        }
    }
     else if(argc == 7 && strcmp(argv[1],"-m") == 0 && strcmp(argv[2],"-e")== 0 && strcmp(argv[4], "-e")== 0 ){
        FILE * file = fopen(argv[6], "r");
        if(file != NULL){
            messageMultiplication(argv[3], argv[5], file);
            fclose(file);
        }
        else {
            printf("Opening key file fails! User may need generate key file first.\n");
            return EXIT_FAILURE;
        }
    }
    else if(argc == 5 && strcmp(argv[1],"-t") == 0){
        FILE * file = fopen(argv[4], "r");
        if(file != NULL){
            if((cipherEqualityTest(argv[2], argv[3], file) == 1)){
                printf("Two cipher texts are equal!\n");
            }
            else {
                printf("Two cipher texts are not equal!\n");
            }
            fclose(file);
        }
        else {
            printf("Opening key file fails! User may need generate key file first.\n");
            return EXIT_FAILURE;
        }
    }
    else if(argc == 7 && strcmp(argv[1],"-t") == 0 && strcmp(argv[2],"-e")== 0 && strcmp(argv[4], "-e")== 0 ){
        FILE * file = fopen(argv[6], "r");
        if(file != NULL){
            if(messageEqualityTest(argv[3], argv[5], file) == 1){
                printf("Two messages are equal!\n");
            }
            else{
                printf("Two mesages are not equal!\n");
            }
            fclose(file);
        }
        else {
            printf("Opening key file fails! User may need generate key file first.\n");
            return EXIT_FAILURE;
        }
    }
    else {
        printf("Usage: FHEv1 -k <key size> <KeyFileName>\n");
        printf("Usage: FHEv1 -e <m> <KeyFileName>\n");
        printf("Usage: FHEv1 -d <Cm> <KeyFileName>\n");
        printf("Usage: FHEv1 -b <m> <KeyFileName>\n");
        printf("Usage: FHEV1 -a <-e <m1> | <Cm1>,<-e <m2> | <Cm2> <keyFileName>");
        printf("Usage: FHEV1 -m <-e <m1> | <Cm1>,<-e <m2> | <Cm2> <keyFileName>");
        printf("Usage: FHEV1 -t <-e <m1> | <Cm1>,<-e <m2> | <Cm2> <keyFileName>");
        
        
        
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
