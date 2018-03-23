#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigdtypes.h"
#include "bigd.h"
#include "bigdRand.h"

/**
 * Check Random number if it is a prime number, if not, regenerate another random number
 * @param p: random number, if it is not a prime, regenerate one until it is a prime
 * @param keySize:
 */
void genPrime(BIGD p, size_t keySize){
    bdRandomBits(p,keySize);
    while(!bdIsEven(p)){
        bdSetZero(p);
        bdRandomBits(p,keySize);
    }

    size_t ntests = 80; //The count of Rabin-miller primality tests to carry out 
    while(!bdIsPrime(p, ntests)){
        bdSetZero(p);
        bdRandomBits(p, keySize);
    }
}
/**
 * write the prime number to a file
 * @param p: prime number
 * @param file: keyfile
 */ 
void writePrimeHexStringToFile(BIGD p, FILE* file){
    char* primeString;
    size_t nChars = bdConvToHex(p,NULL, 0);
    primeString = malloc(nChars + 1);
    bdConvToHex(p, primeString,nChars + 1);
    fputs(primeString,file);
    fputs("\n", file);
    free(primeString);
}

/**
 * Generate equality test key
 * @param g: equality test key
 * @param p3
 * @param t: t = q x p3
 * @param keysize
 */ 
void genEqualityTestKey(BIGD g, BIGD p3, BIGD t, size_t keySize){
    BIGD expo, h, p3Decrement, bigTwo, bigOne;
    expo = bdNew();
    h = bdNew();
    p3Decrement = bdNew();
    bigTwo = bdNew();
    bigOne = bdNew();
    
    bdSetShort(bigOne, 1);
    bdSetShort(bigTwo, 2);

    bdMultiply_s(p3Decrement, p3, bigOne);
    bdDecrement(p3Decrement);
    bdMultiply_s(expo, p3Decrement, bigTwo);
    bdRandomBits(h, 2*keySize);

    //printf("The random number h = ");
    //bdPrint(h, 0x1);


    bdModExp(g, h, expo,t);
}

/**
 * Generating the encryption/decription keys(P,N)
 * the operational keys(N, g1, g2, T) and write them to a key file.
 * @param keysize: keysize
 * @param keyFile: keyfile name;
 */
void keyGen(size_t keySize, char* keyFile){
    BIGD p1, p2, p3, q, bigTwo;
    p1 = bdNew();
    p2 = bdNew();
    p3 = bdNew();
    q = bdNew();
    bigTwo = bdNew();
    size_t ntests = 80; //The count of Rabin-miller primality tests to carry out
    bdSetShort(bigTwo, 2);
    
    genPrime(p1,keySize);
    bdMultiply_s(q, p1, bigTwo);
    bdIncrement(q);
    
    while(!bdIsPrime(q, ntests)){
        genPrime(p1,keySize);
        bdMultiply_s(q, p1, bigTwo);
        bdIncrement(q);
    }
    genPrime(p2,keySize);
    genPrime(p3,keySize);
    
    BIGD n, t;
    n = bdNew();
    t = bdNew();
    bdMultiply_s(n, p1,p2);
    bdMultiply_s(t, q, p3);

    BIGD g1, g2;
    g1 = bdNew();
    g2 = bdNew();
    genEqualityTestKey(g1, p3, t, keySize);
    genEqualityTestKey(g2, p3, t, keySize);
    

    FILE* file = fopen(keyFile, "w+");
    if (file == NULL){
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%zu\n", keySize); //save keysize
    writePrimeHexStringToFile(p1, file);
    writePrimeHexStringToFile(p2, file);
    writePrimeHexStringToFile(p3, file);
    writePrimeHexStringToFile(q, file);
    writePrimeHexStringToFile(g1, file);
    writePrimeHexStringToFile(g2, file);
    writePrimeHexStringToFile(n, file);
    writePrimeHexStringToFile(t, file);


    fclose(file);
/*
    printf("The prime number p1 = ");
    bdPrint(p1, 0x1);
    //printf("The size of p1 is:%ld\n",bdBitLength(p1) );

    printf("The prime number p2 = ");
    bdPrint(p2, 0x1);
    //printf("The size of p2 is:%ld\n",bdBitLength(p2) );

    printf("The prime number p3 = ");
    bdPrint(p3, 0x1);
    //printf("The size of p3 is:%ld\n",bdBitLength(p3) );
    printf("The prime number q = ");
    bdPrint(q, 0x1);
    //printf("The size of q is:%ld\n",bdBitLength(q) );

    printf("The prime number g1 = ");
    bdPrint(g1, 0x1);
    //printf("The size of g1 is:%ld\n",bdBitLength(g1) );

    printf("The prime number g2 = ");
    bdPrint(g2, 0x1);
    //printf("The size of g2 is:%ld\n",bdBitLength(g2) );

    printf("The number n = ");
    bdPrint(n, 0x1);
    //printf("The size of n is:%ld\n",bdBitLength(n) );

    printf("The number t = ");
    bdPrint(t, 0x1);
    //printf("The size of t is:%ld\n",bdBitLength(t) ); 
*/
    bdFree(&p1);
    bdFree(&p2);
    bdFree(&p3);
    bdFree(&q);
    bdFree(&bigTwo);
    bdFree(&n);
    bdFree(&t);
    
    return;
}

void encryption(char* message, FILE* keyFile){
    BIGD m, c, p1, n;
    m = bdNew();
    c = bdNew();
    p1 = bdNew();
    n = bdNew();
    bdConvFromDecimal(m, message);

    char* keySizeLine = NULL;
    char* p1Line = NULL;
    char* tempLine = NULL;
    char* nLine = NULL;
    size_t len = 0;
    getline(&keySizeLine, &len, keyFile); 
    getline(&p1Line, &len, keyFile);
    size_t keySize = atoi(keySizeLine);
    bdConvFromHex(p1, p1Line);
    if(bdCompare(m,p1) > 0){
        printf("Message must be less than the decrytion key p1\n");
        return ;
    }

    for(int i= 0; i < 5; i++){ //jump to the N number line, N is at the 8th line of the keyFile
        getline(&tempLine, &len, keyFile);
    }
    getline(&nLine, &len, keyFile);
    bdConvFromHex(n, nLine);

    BIGD r = bdNew();
    bdRandomBits(r,keySize);
    
    BIGD temp = bdNew();
    bdMultiply_s(temp, r, p1);
    bdAdd_s(temp,temp, m);
    bdModulo_s(c, temp,n);
    char* cypher = NULL;
    size_t nchars = bdConvToDecimal(c, NULL, 0);
    cypher = malloc(nchars+1); 
    bdConvToDecimal(c,cypher, nchars+1);
    /* printf("keySize=%zu\n",keySize);
    bdPrint(p1, 0x1);
    bdPrint(n, 0x1);
    bdPrint(c, 0x1); */
    printf("Plaintext = %s\n",message);
    printf("Cyphertext = %s\n",cypher);
    

    
}