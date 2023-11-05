//Hello There how are you?<CR>
//My name is Sean Clarke.<tab>I like software!<CR>
#include <stdio.h>
#include <string.h>

// Utility function to convert a character to hex and write to file
void charToHex(FILE *outputFile, unsigned char c) {
    fprintf(outputFile, "%02X", c);  // Use uppercase X for uppercase hex letters as per project description
}

// Encrypt function



void encrypt(const char *inputFilename, const char *outputFilename) {
    FILE *inputFile = fopen(inputFilename, "r");
    FILE *outputFile = fopen(outputFilename, "w");

    if (!inputFile || !outputFile) {
        perror("Error opening files");
        if (inputFile) fclose(inputFile);
        if (outputFile) fclose(outputFile);
        return;
    }

    char c;
    while ((c = fgetc(inputFile)) != EOF) {
        if (c == '\t') {  // Tab character
            fputs("TT", outputFile);
        } else if (c == '\n') {  // Newline (carriage return)
            fputc(c, outputFile);  // Write newline to output as is
        } else {
            int outChar = c - 16;
            if (outChar < 32) {
                outChar = (outChar - 32) + 144;
            }
            charToHex(outputFile, outChar);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}




// Utility function to convert a two-character hex string to a char value
int hexToChar(const char *hex) {
    int value;
    sscanf(hex, "%2x", &value);
    return value;
}

// Decrypt function
void decrypt(const char *inputFilename, const char *outputFilename) {
    FILE *inputFile = fopen(inputFilename, "r");
    FILE *outputFile = fopen(outputFilename, "w");

    if (!inputFile || !outputFile) {
        perror("Error opening files");
        if (inputFile) fclose(inputFile);
        if (outputFile) fclose(outputFile);
        return;
    }

    char hex[3] = {0};  // Buffer for two hex digits and a null terminator
    int i = 0;
    char c;
    while ((c = fgetc(inputFile)) != EOF) {
        if (i < 2) {
            hex[i++] = c;
        }
        if (i == 2 || c == '\n') {
            if (strcmp(hex, "TT") == 0) {
                fputc('\t', outputFile);
            } else if (c == '\n') {
                fputc(c, outputFile);
            } else {
                int outChar = hexToChar(hex);
                outChar += 16;
                if (outChar > 127) {
                    outChar = (outChar - 144) + 32;
                }
                fputc(outChar, outputFile);
            }
            i = 0;
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}


#include <stdlib.h>
#include <string.h>

// Add previous encrypt and decrypt function definitions here

// Function to derive the output file name based on input file and mode
void getOutputFilename(const char *inputFilename, char *outputFilename, int mode) {
    strcpy(outputFilename, inputFilename);
    char *lastDot = strrchr(outputFilename, '.');
    if (lastDot != NULL) *lastDot = '\0';  // Remove the extension if it exists

    // Append the new extension based on mode
    strcat(outputFilename, mode == 'E' ? ".crp" : ".txt");
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage: %s [-E|-D] <filename>\n", argv[0]);
        return 1;
    }

    int mode = 'E';  // Default mode is Encrypt
    char *inputFilename;
    char outputFilename[FILENAME_MAX];

    if (argc == 3) {
        if (strcmp(argv[1], "-E") == 0) {
            mode = 'E';
        } else if (strcmp(argv[1], "-D") == 0) {
            mode = 'D';
        } else {
            fprintf(stderr, "Invalid option '%s'. Use -E for encryption or -D for decryption.\n", argv[1]);
            return 1;
        }
        inputFilename = argv[2];
    } else {
        inputFilename = argv[1];
    }

    getOutputFilename(inputFilename,outputFilename,mode);

    if (mode == 'E') {
    encrypt(inputFilename, outputFilename);
    } else {
    decrypt(inputFilename, outputFilename);
    }

    return 0;
}
