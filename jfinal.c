#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

void encrypt(char nextCharacter) {
    int currentCharacter = nextCharacter;
    int outCharValue = currentCharacter - 16;
    if (outCharValue < 32){
        outCharValue = (outCharValue - 32) + 144;
    }
    // Convert to 2 digit hexidecimal & upload into encrypted
    fputc("%02x", outCharValue); // THIS IS WRONG, FIGURE OUT HOW TO UPLOAD THE NUMBER VALUE AS A TWO DIGIT HEXADECIMAL VALUE TO THE ENCRYPT FILE LOCATION PATH
}

void decrypt(char pair1, char pair2) {
   int asciiPairOne = pair1;
   int asciiPairTwo = pair2;
   int outCharValue = ((asciiPairOne * 16) + asciiPairTwo) + 16;
   if (outCharValue >= 127){
    outCharValue = (outCharValue - 144) + 32;
   }
   char outChar = outCharValue;
   fputc(outChar, )// THIS IS WRONG, FIGURE OUT HOW TO UPLOAD THE CHARACTER TO THE .TXT FILE PATH. MIGHT REQUIRE FILE PATH IN FUNCTION? UNSURE.
}

int main() {
   
    //File Name to Encrypt
    char fTextNameOfFile[SIZE_MAX];
    char fEncryptNameOfFile[SIZE_MAX];
    printf("Input a File Name (DO NOT ADD .txt OR .crp):");
    scanf("%s.txt", fTextNameOfFile);  
    scanf("%s.crp", fEncryptNameOfFile);

    char selection;
    printf("Select -E for Encrypt, or -D for Decrypt");
    scanf("-%s", selection);

    FILE *fFileStream;
    FILE *fEncryptorDecryptFileStream;

    if (selection == "E")
    {
        fFileStream = fopen(fTextNameOfFile, "r"); // Stream = the Text file, and 'r' signifies that the file is meant to be written in read only mode.
        fEncryptorDecryptFileStream = fopen(fEncryptNameOfFile, "w"); // 'w' signifies will write data onto encrypted file --> .crp file.
        if (fFileStream == NULL){
        printf("WARNING! File cannot be opened/read or is not present in explorer!");
        return 0;
        }

        char buffer[120];
        while (fgets(buffer, 120, fFileStream) != NULL)
        {
            char nextCharacter = fgetc(buffer); // collect character
            //upload
            if (nextCharacter == '\r')
            { // If the character is a carriage return or NULL value (Whitespace Does Not Count as Null Value)
                fputc('\r', fEncryptorDecryptFileStream);
                continue;
            }
            if (nextCharacter == NULL)
            {
                continue;
            }
            if (nextCharacter == '\t')
            {
                fputc('T', fEncryptorDecryptFileStream);
                fputc('T', fEncryptorDecryptFileStream); // Changes tab to output sequence TT onto new .crp file.
            }
            if (nextCharacter != '\t')
            {
                encrypt(nextCharacter);
            }
        }
    }
    if (selection == "D")
    {
        fFileStream = fopen(fEncryptNameOfFile, "r"); // Stream becomes .crp file
        fEncryptorDecryptFileStream = fopen(fTextNameOfFile, "w"); // Writer becomes .txt file
        if (fFileStream == NULL){
        printf("WARNING! File cannot be opened/read or is not present in explorer!");
        return 0;
        }

        char buffer[255];
        while (fgets(buffer, 255, fFileStream) != NULL)
        {
            char pairCharacter[2] = {fgetc(buffer), fgetc(buffer)}; // Collect the character
            if (pairCharacter[0] == 'T' && pairCharacter[1] == 'T'){ // Check for T Sequence in the character after first T
                fputc('\t', fEncryptorDecryptFileStream);
            }
            if (pairCharacter[0] == '\r' || pairCharacter[1] == '\r'){
                continue;
            }
            if (pairCharacter[0] != 'T' && pairCharacter[1] != 'T'){
                decrypt(pairCharacter[0], pairCharacter[1]);
            }
        }
    }

    /*char input[SIZE];
    char choice;

    printf("Enter a string : ");
    fgets(input, sizeof(input), stdin);
    printf("Choose an option (-E for encryption, -D for decryption): ");
    scanf("-%c", &choice);
    if (choice == 'E' || choice == 'e') {
        encrypt(input);
    } else if (choice == 'D' || choice == 'd') {
        decrypt(input);
    } else {
        encrypt(input);
    }
    return 0;*/
}
