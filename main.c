#include "./src/utils.h"
#include <conio.h>


int main(void) {
    for(int k=0; k<30; k++) {
        plainFile[k] = 0;
        nFile[k] = 0;
        dFile[k] = 0;
        eFile[k] = 0;
        cipherFile[k] = 0;
    }
    mpz_init(n);
    mpz_init(e);
    mpz_init(d);
    mpz_init(plain);
    mpz_init(cipher);
    int tokenNumber;
    while(1) {
        printf("[*] Enter command: ");
        getchar();
        fgets(command, 200, stdin);
        tokenNumber = commandTokens();
        // Parse command
        for(int i=1; i<tokenNumber; i++) {
            printf("[*] Command No.%d: %s\n", i, argc[i]);
            switch(argc[i][0]) {
                case 'p': {
                    for(int j=2; argc[i][j]!=0; j++) {
                        plainFile[j-2] = argc[i][j];
                    }
                    printf("[+] Plain text file: %s\n", plainFile);
                    break;
                }
                case 'n': {
                    for(int j=2; argc[i][j]!=0; j++) {
                        nFile[j-2] = argc[i][j];
                    }
                    printf("[+] N file: %s\n", nFile);
                    break;
                }
                case 'd': {
                    for(int j=2; argc[i][j]!=0; j++) {
                        dFile[j-2] = argc[i][j];
                    }
                    printf("[+] D file: %s\n", dFile);
                    break;
                }
                case 'e': {
                    for(int j=2; argc[i][j]!=0; j++) {
                        eFile[j-2] = argc[i][j];
                    }
                    printf("[+] E file: %s\n", eFile);
                    break;
                }
                case 'c': {
                    for(int j=2; argc[i][j]!=0; j++) {
                        cipherFile[j-2] = argc[i][j];
                    }
                    printf("[+] Cipher file: %s\n", cipherFile);
                    break;
                }
                default:
                    break;
            }
        }
        char choice;
        printf("[*] Choose whether to create key[y/n]: ");
        scanf("%c", &choice);
        if(choice=='y' || choice=='Y'){
            createKeys();
        }
        readToMemory();
        RSAProcess();
        // Exit the loop
        if(_kbhit() && _getch()==0x1b){
            break;
        }
    }
    return 0;
}
