#include <stdio.h>  
#include <string.h>

#define NUM_BIT 16

char Key_Vigenere[] = "KEY";  // Define the encryption key

const int Key_Caesar = 3;  // Replace with your desired key

const int key_XOR = 0b00101101; // The key value is set to 45 in binary, which corresponds to decimal 45

unsigned char plainText_Vigenere;  // Variable to store the result of Vigenere operation

unsigned char plainText_Caesar;  // Variable to store the result of Vigenere operation

unsigned short int plainText_XOR; // Variable to store the result of XOR operation

unsigned short int decrypt_Vigenere(unsigned short int input, unsigned char* key)
{

   unsigned short int output;  /* Initialize output to 0*/
   printf("%c\t\t",input);
   static int i=0;  /* Initialize i to 0 */

   unsigned char key_char = key[i%strlen(key)]; /* Get the key character */
   printf("%c\t\t",key_char);

   /* If the input character is an uppercase letter, perform the Vigenere decryption */
   if(input >= 'A' && input <= 'Z')
   {

       /* Shift the character by the key value for decryption */
       output =((input-key_char+26)%26) + 'A' ;

       /* Handle wrap-around if the resulting character goes beyond 'Z' */

   }
   else output = input;

   /* Increment i for the next iteration */
   i++;
   return output;    /* Return the decrypted character */
}

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

    printf( "%c\t\t%d\t\t",input,key);

    return output;  // Return the decrypted value
}


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
unsigned short int decrypt_XOR(unsigned short int input, unsigned short int key)
{
    unsigned short int output = 0;                        // Initialize output to 0
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
    printf( "%hu\t\t%hu\t\t",input,key);
    return output; // Return the result of XOR operation
}


int main(int argc, char const *argv[])
{
   /* Open the file for reading */
   FILE *file = fopen("CipherText.txt", "r");

   /* Check if the file is opened successfully */
   if (file == NULL)
   {
       printf("Error: Unable to open file.\n");
       return 1;
   }

   unsigned short int cipherText = 0;

   /* Print the headers for the output */
   printf("Cipher Text\t");
   printf("Key\t");
   printf("Plain Text\n");

    int line_number = 0;    //  Line number in the file
    char line[256]; // Buffer to store each line read from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;  //  Increment the line number count
        if (line_number==1){
            printf("\nVigenere Cipher:-\n");
        }   else if (line_number==2 || line_number == 4){
            printf("Caesar Cipher:-\n");
            }   else if (line_number==3 || line_number == 5){ 
                printf("XOR Cipher:-\n");
                }
        char *token = strtok(line, " "); // Tokenize the line
        while (token != NULL) {
            sscanf(token, "%hu", &cipherText); // Convert token to integer
            switch (line_number) {

                case 1: // Decrypt Vigenere Cipher
                cipherText = (int)*token;
                    plainText_Vigenere = decrypt_Vigenere(cipherText, Key_Vigenere);
                    printf("%c\n", plainText_Vigenere);
                    break;

                case 2: case 4: // Decrypt Caesar Cipher
                    plainText_Caesar = decrypt_Caesar(cipherText, Key_Caesar);
                    printf("%c\n", plainText_Caesar);
                    break;

                case 3: case 5: // Decrypt XOR Function
                    plainText_XOR = decrypt_XOR(cipherText, key_XOR);
                    printf("%hu\n", plainText_XOR);
                    break;

                default:
                    printf("Invalid line number\n");
            }
            token = strtok(NULL, " "); // Move to next token
        }
        printf("\n");
        
        
    }

   fclose(file); /* Close the file */
   return 0;
}