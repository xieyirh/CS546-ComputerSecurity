#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigdtypes.h"
#include "bigd.h"
#include "bigdRand.h"

/**
 * Generating the encryption/decription keys(P,N)
 * the operational keys(N, g1, g2, T) and write them to a key file.
 * @param keysize: keysize
 * @param keyFile: keyfile name;
**/
void keyGen(size_t keySize, char* keyFile);
char* encryption(char* message, FILE* keyFile);
char* decryption(char* cipherText,FILE* keyFile);
void encrDecryption(char* message,FILE* file);
void messageAddition(char*, char*, FILE* );
void cipherAddition(char*,  char*, FILE*);
void messageMultiplication(char*, char*, FILE* );
void cipherMultiplication(char*,  char*, FILE*);
int messageEqualityTest(char*, char*, FILE*);
int cipherEqualityTest(char*, char*, FILE*);
char* messagePadding(char*, FILE*);
void keyGenV2(size_t, size_t, size_t, char*);
char* decryptionV2(char*, FILE*);
