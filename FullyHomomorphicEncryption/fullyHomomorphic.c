#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigdtypes.h"
#include "bigd.h"
#include "bigdRand.h"
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
 * Generating the encryption/decription keys(P,N)
 * the operational keys(N, g1, g2, T) and write them to a key file.
 * @param keysize: keysize
 * @param keyFile: keyfile name;
**/
void keyGen(size_t keySize, char* keyFile){
    BIGD p1, p2, p3, q, bigTwo;
    p1 = bdNew();
    p2 = bdNew();
    p3 = bdNew();
    q = bdNew();
    bigTwo = bdNew();
    size_t ntests = 80;
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

    printf("The prime number p1 = ");
    bdPrint(p1, 0x1);
    printf("The size of p1 is:%ld\n",bdSizeof(p1) );

    printf("The prime number p2 = ");
    bdPrint(p2, 0x1);
    printf("The size of p2 is:%ld\n",bdSizeof(p2) );

    printf("The prime number p3 = ");
    bdPrint(p3, 0x1);
    printf("The size of p3 is:%ld\n",bdSizeof(p3) );
    printf("The prime number q = ");
    bdPrint(q, 0x1);
    printf("The size of q is:%ld\n",bdSizeof(q) );

    printf("The number n = ");
    bdPrint(n, 0x1);

    printf("The number t = ");
    bdPrint(t, 0x1);
    

    bdFree(&p1);
    bdFree(&p2);
    bdFree(&p3);
    bdFree(&q);
    bdFree(&bigTwo);
    bdFree(&n);
    bdFree(&t);
    
    
    return;
}