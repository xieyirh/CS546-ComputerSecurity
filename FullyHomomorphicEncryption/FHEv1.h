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
