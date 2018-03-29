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

void genPrimeV2(BIGD p, size_t keySize,size_t w, size_t z ){
    bdRandomBits(p,2* (keySize + 1) * (w + z));
    while(bdBitLength(p) < (keySize + 1) *(w + z)){
        bdRandomBits(p,2* (keySize + 1) * (w + z));
    }
    //bdPrint(p, 0x1);
    //printf("The size of p is:%ld\n",bdBitLength(p) );
    while(!bdIsEven(p)){
        bdSetZero(p);
        bdRandomBits(p,2* (keySize + 1) * (w + z));
    }

    size_t ntests = 80; //The count of Rabin-miller primality tests to carry out 
    while(!bdIsPrime(p, ntests)){
        bdSetZero(p);
        bdRandomBits(p, 2* (keySize + 1) * (w + z));
    }
}
/**
 * write the prime number to a file
 * @param p: prime number
 * @param file: keyfile
 */ 
void writePrimeHexStringToFile(BIGD p, FILE* file){
    char* primeString;
   // printf("inside write to file\n");
  //  bdPrint(p, 0x1);
    size_t nChars = bdConvToHex(p,NULL, 0);
    primeString = malloc(nChars + 1);
    bdConvToHex(p, primeString,nChars + 1);
    //printf("write to file %s\n", primeString);
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

    /* bdPrint(p1, 0x1);
    bdPrint(p2, 0x1);
    bdPrint(p3, 0x1); */
    
    
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
/**
 * Encrypt the message by using pregenerated key
 * @param message: plaintext which should be smaller than p1
 * @param keyFile: keyFile pointer
 * @return cipher text
 */ 
char* encryption(char* message, FILE* keyFile){
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
    char* cipher = NULL;
    size_t len = 0;
    getline(&keySizeLine, &len, keyFile); 
    getline(&p1Line, &len, keyFile);
    size_t keySize = atoi(keySizeLine);
    bdConvFromHex(p1, p1Line);
    if(bdCompare(m,p1) > 0){
        printf("Message must be less than the decrytion key p1\n");
        return NULL;
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
    size_t nchars = bdConvToDecimal(c, NULL, 0);
    cipher = malloc(nchars+1); 
    bdConvToDecimal(c,cipher, nchars+1);

   
    free(tempLine);
    free(p1Line);
    free(nLine);
    rewind(keyFile);
    bdFree(&r);
    bdFree(&temp);
    bdFree(&m);
    bdFree(&c);
    bdFree(&n);
    bdFree(&p1);
    return cipher;
}

/**
 * Decrypte the cipher text
 * @param cipherText
 * @param keyFile: key file pointer
 */ 
char* decryption(char* cipherText,FILE* keyFile){
    BIGD c, p1;
    c = bdNew();
    p1 = bdNew();
    bdConvFromDecimal(c, cipherText);
    char* p1Line =NULL;
    char* tempLine = NULL;
    size_t len = 0;

    getline(&tempLine, &len, keyFile); 
    getline(&p1Line, &len, keyFile);
    bdConvFromHex(p1,p1Line);

    BIGD m;
    m = bdNew();
    bdModulo_s(m, c, p1);

    char* message = NULL;
    size_t nchars = bdConvToDecimal(m, NULL, 0);
    message = malloc(nchars+1); 
    bdConvToDecimal(m,message, nchars+1);

    //printf("Plaintext = %s\n",message);
    rewind(keyFile);
//    free(message);
    free(tempLine);
    free(p1Line);
    bdFree(&c);
    bdFree(&p1);
    bdFree(&m);
    return message;

}

/**
 * Read key from key file and then do encryption, decryption
 * @param message: plaintext
 * @param file: key file pointer
 */ 
void encrDecryption(char* message,FILE* file){
    printf("Cipher Text = %s\n", encryption(message, file));
    printf("Plaintext = %s\n",decryption(encryption(message, file), file));
}

void cipherAddition(char* cipher1, char* cipher2, FILE* keyFile){
    BIGD c1,c2, n;
    c1 = bdNew();
    c2 = bdNew();
    n = bdNew();
    bdConvFromDecimal(c1, cipher1);
    bdConvFromDecimal(c2, cipher2);
    
    char* nLine =NULL;
    char* tempLine = NULL;
    size_t len = 0;

    for(int i= 0; i < 7; i++){ //jump to the N number line, N is at the 8th line of the keyFile
        getline(&tempLine, &len, keyFile);
    }
    getline(&nLine, &len, keyFile);
    bdConvFromHex(n, nLine);
    //bdPrint(n, 0x1);

    BIGD temp, addition;
    temp = bdNew();
    addition = bdNew();
    bdAdd_s(temp, c1, c2);
    bdModulo_s(addition, temp, n);
    char* cipherAddition = NULL;
    size_t nchars = bdConvToDecimal(addition, NULL, 0);
    cipherAddition = malloc(nchars+1); 
    bdConvToDecimal(addition,cipherAddition, nchars+1);

    printf("cipher addition = %s\n",cipherAddition);
    rewind(keyFile);
    bdFree(&temp);
    bdFree(&addition);
    bdFree(&c1);
    bdFree(&c2);
    bdFree(&n);
    free(cipherAddition);
    free(nLine);
    free(tempLine);
}

void messageAddition(char* message1, char* message2, FILE* keyFile ){
    char* cipher1;
    char* cipher2;
    cipher1 = encryption(message1, keyFile);
    cipher2 = encryption(message2, keyFile);
    cipherAddition(cipher1, cipher2, keyFile);
    free(cipher1);
    free(cipher2);

}
//
void cipherMultiplication(char* cipher1, char* cipher2, FILE* keyFile){
    BIGD c1,c2, n;
    c1 = bdNew();
    c2 = bdNew();
    n = bdNew();
    bdConvFromDecimal(c1, cipher1);
    bdConvFromDecimal(c2, cipher2);
    
    char* nLine =NULL;
    char* tempLine = NULL;
    size_t len = 0;

    for(int i= 0; i < 7; i++){ //jump to the N number line, N is at the 8th line of the keyFile
        getline(&tempLine, &len, keyFile);
    }
    getline(&nLine, &len, keyFile);
    bdConvFromHex(n, nLine);
    //bdPrint(n, 0x1);

    BIGD temp, mul;
    temp = bdNew();
    mul = bdNew();
    bdMultiply_s(temp, c1, c2);
    bdModulo_s(mul, temp, n);
    char* cipherMul = NULL;
    size_t nchars = bdConvToDecimal(mul, NULL, 0);
    cipherMul = malloc(nchars+1); 
    bdConvToDecimal(mul,cipherMul, nchars+1);

    printf("cipher Muliplication = %s\n",cipherMul);
    rewind(keyFile);
    bdFree(&temp);
    bdFree(&mul);
    bdFree(&c1);
    bdFree(&c2);
    bdFree(&n);
    free(cipherMul);
    free(nLine);
    free(tempLine);
}

void messageMultiplication(char* message1, char* message2, FILE* keyFile ){
    char* cipher1;
    char* cipher2;
    cipher1 = encryption(message1, keyFile);
    cipher2 = encryption(message2, keyFile);
    cipherMultiplication(cipher1, cipher2, keyFile);
    free(cipher1);
    free(cipher2);

}

int cipherEqualityTest(char* cipher1, char* cipher2, FILE* keyFile){
    BIGD c1,c2, t, g1, g2;
    c1 = bdNew();
    c2 = bdNew();
    t = bdNew();
    g1 = bdNew();
    g2 = bdNew();
    bdConvFromDecimal(c1, cipher1);
    bdConvFromDecimal(c2, cipher2);
    
    char* tLine =NULL;
    char* tempLine = NULL;
    size_t len = 0;

    for(int i= 0; i < 7; i++){ //jump to the t number line, t is at the 8th line of the keyFile
        getline(&tempLine, &len, keyFile);
    }
    getline(&tLine, &len, keyFile);
    bdConvFromHex(t, tLine);
    rewind(keyFile);

    char* g1Line = NULL;
    char* g2Line = NULL;
    tempLine = NULL;
    len = 0;

    for(int i= 0; i < 5; i++){ //jump to the g1 number line, N is at the 8th line of the keyFile
        getline(&tempLine, &len, keyFile);
    }
    getline(&g1Line, &len, keyFile);
    getline(&g2Line, &len, keyFile);
    bdConvFromHex(g1, g1Line);
    bdConvFromHex(g2, g2Line);
   
   BIGD exp = bdNew();
   if(bdCompare(c1, c2) >= 0){
       bdSubtract_s(exp, c1, c2);
   }
   else {
       bdSubtract_s(exp, c2, c1);
   }
   //bdPrint(exp, 0x1);
   BIGD result1, result2, bigOne;
   result1 = bdNew();
   result2 = bdNew();
   bigOne = bdNew();
   bdSetShort(bigOne, 1);
  // bdPrint(bigOne, 0x1);

   bdModExp(result1, g1, exp, t);
   bdModExp(result2, g2, exp, t);
   
   //bdPrint(result1, 0x1);
   //bdPrint(result2, 0x1);
   if(bdIsEqual(result1, bigOne) && bdIsEqual(result2, bigOne)){
       return 1;
   }
   else{
       return 0;
   }
   rewind(keyFile);
   bdFree(&result1);
   bdFree(&result2);
   bdFree(&t);
   bdFree(&c1);
   bdFree(&c2);
   bdFree(&bigOne);
   bdFree(&g1);
   bdFree(&g2);
   bdFree(&exp);
   free(tLine);
   free(tempLine);
   free(g1Line);
   free(g2Line);
}

int messageEqualityTest(char* message1, char* message2, FILE* keyFile){
    char* cipher1;
    char* cipher2;
    cipher1 = encryption(message1, keyFile);
    cipher2 = encryption(message2, keyFile);
    int result =  cipherEqualityTest(cipher1, cipher2, keyFile);
    free(cipher1);
    free(cipher2);
    return result;
}

char* messagePadding(char* message, FILE* keyFile){
    BIGD m, r, rShift, m1;
    m = bdNew();
    m1 = bdNew();
    r = bdNew();
    rShift = bdNew();
    char* wLine = NULL;
    char* zLine = NULL;
    char* tempLine = NULL;
    size_t len = 0;

    for(int i= 0; i < 9; i++){ //jump to the w number line, t is at the 8th line of the keyFile
        getline(&tempLine, &len, keyFile);
    }
    getline(&wLine, &len, keyFile);
    getline(&zLine, &len, keyFile);
    size_t w = atoi(wLine);
    size_t z = atoi(zLine);
    //printf("w=%ld, z=%ld\n",w, z);
    bdRandomBits(r, z );
    char* paddedMessage;
    bdConvFromDecimal(m, message);
    bdShiftLeft(rShift, r, w);
    bdOrBits(m1, r, m);
    size_t nchars = bdConvToDecimal(m1, NULL, 0);
    paddedMessage = malloc(nchars+1); 
    bdConvToDecimal(m1,paddedMessage, nchars+1);
    rewind(keyFile);
    return paddedMessage;
}

void keyGenV2(size_t keySize, size_t w, size_t z, char* keyFile){
    BIGD p1, p2, p3, q, bigTwo;
    p1 = bdNew();
    p2 = bdNew();
    p3 = bdNew();
    q = bdNew();
    bigTwo = bdNew();
    size_t ntests = 80; //The count of Rabin-miller primality tests to carry out
    bdSetShort(bigTwo, 2);
    
    genPrimeV2(p1,keySize, w, z);
    //bdPrint(p1, 0x1);
    bdMultiply_s(q, p1, bigTwo);
    bdIncrement(q);
    
    while(!bdIsPrime(q, ntests)){
        genPrimeV2(p1,keySize, w, z);
        bdMultiply_s(q, p1, bigTwo);
        bdIncrement(q);
    }
    genPrimeV2(p2,keySize, w, z);
    genPrimeV2(p3,keySize, w, z);
    /* bdPrint(p1, 0x1);
    bdPrint(p2, 0x1);
    bdPrint(p3, 0x1);  */
    
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
    fprintf(file, "%zu\n", w); //save w
    fprintf(file, "%zu\n", z); //save z

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
char* decryptionV2(char* cipher, FILE* keyFile){
    char* paddedMessage = decryption(cipher, keyFile);
    BIGD pm = bdNew();
    bdConvFromDecimal(pm, paddedMessage);
    
    BIGD m = bdNew();

    char* wLine = NULL;
    char* tempLine = NULL;
    size_t len = 0;

    for(int i= 0; i < 9; i++){ //jump to the w number line, t is at the 8th line of the keyFile
        getline(&tempLine, &len, keyFile);
    }
    getline(&wLine, &len, keyFile);
    size_t w = atoi(wLine);

    BIGD w2 = bdNew();
    BIGD bigOne = bdNew();
    bdSetShort(bigOne, 1);
    bdShiftLeft(w2, bigOne, w);
    bdModulo_s(m, pm, w2);

    char* message = NULL;
    size_t nchars = bdConvToDecimal(m, NULL, 0);
    message = malloc(nchars+1); 
    bdConvToDecimal(m,message, nchars+1);

    //printf("Plaintext = %s\n",message);
    rewind(keyFile);
    free(tempLine);
    free(wLine);
    free(paddedMessage);
    bdFree(&m);
    bdFree(&pm);
    bdFree(&w2);
    bdFree(&bigOne);
    return message;
}