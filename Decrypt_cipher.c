#include <stdio.h>
#include <string.h>

#define NUM_BIT 16
unsigned short int key = 0b00101101; // The key value is set to 45 in binary
unsigned short int plainText; // Variable to store the result of XOR operation

// Function to set the kth index bit of input
int setBit(unsigned short int input, int k)
{
	return (input | (1 << (k))); // Bitwise OR operation to set the kth bit to 1
}

// Function to get the kth bit of input
int getBit(unsigned short int input, int k)
{
	return (unsigned short int)((input >> k) & 1); // Bitwise right shift and AND operation to get the kth bit
}

// Function to perform manual XOR operation between input and key
unsigned short int manualXOR(unsigned short int input, unsigned short int key)
{
    unsigned short int output = 0;
    for(int i=0; i<NUM_BIT; i++)
    {
        // If the i-th bit of input is 1
        if(getBit(input, i))
        {
            // If the i-th bit of key is 0, set the i-th bit of output to 1
            if(!getBit(key, i))
                output = setBit(output, i);
        }
        else
        {
            // If the i-th bit of input is 0
            // If the i-th bit of key is 1, set the i-th bit of output to 1
            if(getBit(key, i))
                output = setBit(output, i);
        }
    }
    return output; // Return the result of XOR operation
}

// Function to print the bits of the input and the result of XOR operation
void printBits(unsigned short int input)
{
	printf("%d\t\t",input); // Print the decimal value of input
    for(int i=NUM_BIT-1; i>=0; i--)
    {
        printf("%hu", getBit(input, i)); // Print each bit of input from MSB to LSB
    }
    printf("\t\t");

    plainText = manualXOR(input,key); // Perform XOR operation

    printf("%u\t\t",plainText); // Print the decimal value of the result
    
    for(int i=NUM_BIT-1; i>=0; i--)
    {
        printf("%hu", getBit(plainText, i)); // Print each bit of the result from MSB to LSB
    }
    printf("\t\t%c\n",plainText); // Print the character representation of the result
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

    // Read cipher text from the file and perform XOR operation
    while (fscanf(file, "%hu", &cipherText) == 1) {
        manualXOR(cipherText,key); // Perform XOR operation
        printBits(cipherText); // Print the bits of cipher text and the result
    }

    fclose(file); // Close the file
    return 0;
}
