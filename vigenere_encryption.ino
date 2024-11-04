char Key[] = "KEY";  // Define the encryption key
char c[] = "AZHELLO WORLD!";  // Define the character array to be encrypted

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  
  // Encrypt and print the ciphertext
  Serial.println();
  vigenere_cipher(c,Key);  // Call the vigenere_cipher function with the character array and key
}

void loop() {
  // No code here because the encryption is done only once in the setup function
}

// Function to perform Vigenere cipher encryption
unsigned short int vigenere_cipher(unsigned char *input, unsigned char* Key ) {
  int output = 0;

  // Loop through each character in the input string
  for (int i = 0,j=0; i<strlen(input); i++,j++) {
    // If the end of the key is reached, reset the key index
    if (j == strlen(Key)) {
      j = 0;
    }
  
    // Convert lowercase letters to uppercase
    if (input[i] >= 'a' && input[i] <= 'z') {
      input[i] -= 32;  // Subtract the ASCII difference to convert to uppercase
    }

    // Encrypt uppercase letters using the Caesar cipher technique
    if(input[i] >= 'A' && input[i] <= 'Z') {
      // Shift the character by the key value
      output = ((input[i] + Key[j]) % 26) + 'A';  // Apply the Vigenere cipher formula
    } else {
      output = input[i];  // If the character is not a letter, leave it unchanged
    }

    Serial.print((char)output);  // Print the encrypted character
  }  

  // Return the last encrypted character
  return (char)output;
}
