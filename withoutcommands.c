#include <stdio.h>
#include <string.h>

#define SIZE 100

void encrypt(char *input) {
    int i;
    for (i = 0; input[i] != '\0'; ++i) {
        printf("%02x", input[i]);
    }
    printf("\n");
}

void decrypt(char *input) {
    int i;
    for (i = 0; input[i] != '\0'; i += 2) {
        char hex[3];
        hex[0] = input[i];
        hex[1] = input[i + 1];
        hex[2] = '\0';

        int value;
        sscanf(hex, "%x", &value);
        printf("%c", (char)value);
    }
    printf("\n");
}

int main() {
    char input[SIZE];
    char choice;

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    printf("Choose an option (-E for encryption, -D for decryption): ");
    scanf(" %c", &choice);

    if (choice == 'E' || choice == 'e') {
        encrypt(input);
    } else if (choice == 'D' || choice == 'd') {
        decrypt(input);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
