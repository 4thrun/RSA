#include "./utils.h"


int commandTokens() {
    char *token; int i = 0;
    token = strtok(command, "-");
    strcpy(argc[i++], token);
    while(token!=NULL) {
        token = strtok(NULL, "-");
        if(token!=NULL) {
            strcpy(argc[i++], token);
        }
    }
    return i;
}


void readToMemory() {
    // Read N
    FILE *fp_n = fopen("./file/N.txt", "r");
    if(NULL==fp_n) {
        printf("[-] Failed to open N file\n");
        exit(-1);
    } else {
        mpz_inp_str(n, fp_n, 16);
        printf("\n[+] N: ");
        mpz_out_str(stdout, 16, n);
        fclose(fp_n);
    }

    // Read E
    FILE *fp_e = fopen("./file/E.txt", "r");
    if(fp_e==NULL) {
        printf("[-] Failed to open E file\n");
        exit(-1);
    } else {
        mpz_inp_str(e, fp_e, 16);
        printf("\n[+] E: ");
        mpz_out_str(stdout, 16, e);
        fclose(fp_e);
    }

    // Read D
    FILE *fp_d = fopen("./file/D.txt", "r");
    if(fp_d==NULL) {
        printf("[-] Failed to open D file\n");
        exit(-1);
    } else {
        mpz_inp_str(d, fp_d, 16);
        printf("\n[+] D: ");
        mpz_out_str(stdout, 16, d);
        fclose(fp_d);
    }

    // Read plain text
    FILE *fp_plain = fopen("./file/RSA_plain.txt", "r");
    if(NULL==fp_plain) {
        printf("[-] Failed to open plain text file\n");
        exit(-1);
    } else {
        mpz_inp_str(plain, fp_plain, 16);
        printf("\n[+] Plain text: ");
        mpz_out_str(stdout, 16, plain);
        fclose(fp_plain);
    }
}


void RSAProcess() {
    mpz_t rop; // Result of the process
    mpz_init(rop);

    // Signature
    mpz_powm(rop, plain, d, n);
    FILE *fp = fopen("./file/RSA_signature.txt", "w");
    // Save to file
    if (fp==NULL) {
        printf("[-] Failed to create the signature file\n");
        exit(-1);
    }
    mpz_out_str(fp, 16, rop);
    fclose(fp);
    // Print
    printf("\n[*] Result after signature: ");
    mpz_out_str(stdout, 16, rop);
    printf("\n");
    // Inverse signature
    mpz_powm(rop, rop, e, n);
    printf("Result after inverse signature: ");
    mpz_out_str(stdout, 16, rop);
    printf("\n");

    // Encrypt
    mpz_powm(rop, plain, e, n);
    FILE *fp_cipher = fopen("./file/RSA_cipher.txt", "w");
    // Save to file
    if(NULL==fp_cipher) {
        printf("[-] Failed to create the cipher file \n");
        exit(-1);
    }
    mpz_out_str(fp_cipher, 16, rop);
    fclose(fp_cipher);
    // Print
    printf("\n[*] Result after encryption: ");
    mpz_out_str(stdout, 16, rop);
    printf("\n");

    // Decryption
    mpz_powm(rop, rop, d, n);
    printf("\n[*] Result after decryption: ");
    mpz_out_str(stdout, 16, rop);
    printf("\n");
}


void createKeys() {
    mpz_t p, q;
    mpz_init(p); mpz_init(q);
    // Seed
    gmp_randstate_t rand;
    gmp_randinit_default(rand);
    gmp_randseed_ui(rand, time(NULL));
    mpz_urandomb(p, rand, 256); mpz_urandomb(q, rand, 256);
    mpz_t tmp;
    mpz_init_set_str(tmp, "10000000000", 10);
    mpz_add(p, p, tmp);
    mpz_add(q, p, tmp);
    // Generate prime numbers
    mpz_nextprime(p, p);
    mpz_nextprime(q, q);
    // mpz_t n;
    mpz_init(n);
    mpz_mul(n, p, q);
    // Euler function
    mpz_t Euler;
    mpz_init(Euler);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(Euler, p, q);
    mpz_add_ui(p, p, 1);
    mpz_add_ui(q, q, 1);
    // E
    // mpz_t e;
    mpz_init(e);
    mpz_t rop;
    mpz_init(rop);
    mpz_t one;
    mpz_init_set_ui(one, 1);
    gmp_randstate_t randD;
    gmp_randinit_default(randD);
    gmp_randseed_ui(randD, time(NULL));
    mpz_urandomb(e, randD , 1000);
    while(1){
        mpz_gcd(rop, e, Euler);
        if(!mpz_cmp(rop, one)){
            mpz_clear(rop);
            mpz_clear(one);
            break;
        }
        else{
            mpz_add_ui(e, e, 1);
        }
    }
    // D
    // mpz_t d;
    mpz_init(d);
    mpz_invert(d, e, Euler);
    // Save p
    FILE *fp;
    fp = fopen("./file/P.txt","w");
    if(NULL==fp) exit(-1);
    mpz_out_str(fp, 16, p);
    fclose(fp);
    // Save q
    fp = fopen("./file/Q.txt","w");
    if(NULL==fp) exit(-1);
    mpz_out_str(fp, 16, q);
    fclose(fp);
    // save N
    fp = fopen("./file/N.txt","w");
    if(NULL==fp) exit(-1);
    mpz_out_str(fp, 16, n);
    fclose(fp);
    // Save public key
    fp = fopen("./file/E.txt","w");
    if(NULL==fp) exit(-1);
    mpz_out_str(fp, 16, e);
    fclose(fp);
    // Save private key
    fp = fopen("./file/D.txt","w");
    if(NULL==fp) exit(-1);
    mpz_out_str(fp, 16, d);
    fclose(fp);
}
