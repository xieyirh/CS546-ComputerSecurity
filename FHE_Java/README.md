#FHE Project
* Author: YI XIE
* Class: CS546 [Computer Security]

##Overview

In this project, we test a homomorphic encrytion algorithm over integers. Two variants of this
algorithm are under our investigation. 

##Manifest

[README.md](./README.md)   -- **This file**
[Makefile](./Makefile)    -- **build file for two variant algorithms**
[Key.java](./Key.java)   -- **key generation class**
[FHE.java](./FHE.java) --  **algorithm implementation**
[FHEv1.java](./FHEv1.java) --   **Variant 1 test driver**
[FHEv2.java](./FHEv2.java)    --**Variant 2 test driver**

##Building and usage

User could use **make** to build java class files.

To run the program FHEv1:
*java FHEv1 -k < keysize > < KeyFileName >*
*java FHEv1 -e < m > < keyFileName>*
*java FHEv1 -d < Cm > < keyFileName>*
*java FHEv1 -b < m > < keyFileName>*
*java FHEv1 -a < - e < m1 > | Cm1 > < -e < m2 >|Cm2 > < keyFileName >*
*java FHEv1 -m < -e < m1 > | Cm1 > < -e < m2 >|Cm2 > < keyFileName >*
*java FHEv1 -t < -e < m1 > | Cm1 > < -e < m2 >|Cm2 > < keyFileName >*

To Run the program FHEv2:
*java FHEv2 -k < keysize > < KeyFileName >*
*java FHEv2 -e < m > < keyFileName >*
*java FHEv2 -d < Cm > < keyFileName >*
*java FHEv2 -b < m > < keyFileName >*
*java FHEv2 -a < -e < m1 > | Cm1 > < -e < m2 >|Cm2 > < keyFileName >*
*java FHEv2 -m < -e < m1 > | Cm1 > < -e < m2 >|Cm2 > < keyFileName >*


##Features and usage

Both algorithm support:
1. Generate key file. Note: if keysize is big, such as 1000, it will take 3-5 minutes to generate the key file on onyx. For the variant 2, user has to make sure w is big enough, and I suggest keysize is 1000 and w = 100, t = 60 since max message should be less than 2^w.  Again this will take 3-5 minutes to generate key file.
2. My implementation on the FHEv2 works for 5 consecutive homomorphic Multiplications by using keysize = 1000,  w = 100, t = 60;
3. All required implementations have been tested on onyx.

## Tested case

1. Different key size generation.
2. if m > p1, generate error message.
3. if keysize < (k+1)(w+z), generate error message. Here k =5;
4. if m < 2^w, generate error message.

## known Bugs

Do not find yet.

##Discussion
1. I first implement this algorithm by C by using provided Library. key file generation, encryption, decryption all work in my C version. But I could not get it work on equality test. It seems there is some issue with multiplication feature of the library. I don't have enough time to debug the problem since due date is coming. So I implement them with java, which works now.
2. To be done.

##Source used
[Java API](https://docs.oracle.com/javase/8/docs/api/)

