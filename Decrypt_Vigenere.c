#include <stdio.h>  
#include <string.h>  

unsigned char key[] = "KEY"; // The key value is set to "KEY"

unsigned char plainText;  // Variable to store the result of Vigenere operation 

/* 
this functions is used to do the vigenere decyption task
input: unsigned short int input, unsigned char* key
output: unsigned short int output
*/
unsigned short int decrypt_Vigenere(unsigned short int input, unsigned char* key)
{

   unsigned short int output;  /* Initialize output to 0*/
   printf("%c\t\t",input);
   static int i=0;  /* Initialize i to 0 */

   /* If the current key character is the last character in the key string, reset i to 0 */
   if (key[i]==strlen(key))
   {
       i=0;
   }

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

/* 
main function
input: int argc, char const *argv[]
output: int
*/
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

   /* Read cipher text from the file and perform Vigenere operation */
   while (fscanf(file, "%c", &cipherText) == 1)
   {

       plainText = decrypt_Vigenere(cipherText,key);
       printf("%c\n",plainText);
   }

   fclose(file); /* Close the file */
   return 0;
}