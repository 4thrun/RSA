#ifndef RSA_UTILS_H
#define RSA_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gmp.h>


// Global
char command[150];
char argc[6][30];
char plainFile[30];
char nFile[30];
char dFile[30];
char eFile[30];
char cipherFile[30];
// int flag = 0; // 0: sign; 1: encrypt
mpz_t n, e, d, plain, cipher;


int commandTokens();
void readToMemory();
void RSAProcess();
void createKeys();

#endif
