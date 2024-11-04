#include <stdio.h>
#include <string.h>

unsigned short int key = 3; // The key value is set to 3

unsigned short int plainText;  // Variable to store the result of XOR operation


unsigned short int decrypt_Caesar(unsigned short int input, unsigned short int key)
{
    unsigned short int output = 0;  // Initialize output to 0

    // Check if the input is an uppercase alphabet character
    if(input >=65 && input <=90)
    {
        output = input - key;  // Subtract the key value from the input

        // If the result is less than 65 (ASCII value of 'A'), add 26 to wrap around to the correct range
        if(output <65)
        {
            output +=26;
        }
    }

    // Check if the input is a lowercase alphabet character
    else if (input >=97 && input <= 122)
    {
        output = input - key;  // Subtract the key value from the input

        // If the result is less than 97 (ASCII value of 'a'), add 26 to wrap around to the correct range
        if(output < 97)
        {
            output+=26;
        }
    }

    // If the input is not an alphabet character, leave it unchanged
    else
    {
        output = input;
    }

    return output;  // Return the decrypted value
}

// Function to print the bits of the input and the result of XOR operation
void printBits(unsigned short int input)
{
	
	printf("%d\t\t%c\t\t",input,input); // Print the decimal value of input

    plainText = decrypt_Caesar(input,key); // Perform XOR operation

    printf("%u\t\t\t%c\n",plainText,plainText); // Print the decimal value and character representation of the result
}

int main(int argc, char const *argv[])
{
    // Open the file for reading
    FILE *file = fopen("CipherText.txt", "r");
    
    // Check if the file is opened successfully
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    unsigned short int cipherText = 0;
    
	printf("Encrpted ASCII\t");
    printf("Cipher Text\t");
	printf("Decimal Value\t\t");
	printf("characters\n");
	
    // Read cipher text from the file and perform XOR operation
    while (fscanf(file, "%hu", &cipherText) == 1) {
        decrypt_Caesar(cipherText,key);
        printBits(cipherText); // Print the bits of cipher text and the result
    }

    fclose(file); // Close the file
    return 0;
}
