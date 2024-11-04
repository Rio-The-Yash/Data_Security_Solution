#define sensorPin A0
#define countADC 5.0
#define countMAX 1023.0
#define NUM_BIT 16

char Key_Vigenere[] = "KEY";  // Define the encryption key
char msg_Vigenere[] = "AZHELLO,,WORLD!";  // Define the character array to be encrypted

const int Key_Caesar = 3;  // Replace with your desired key
char msg_Caesar[] = "Cyber Security";  // Replace with your character array

const int Key_XOR = 45;  // Replace with your desired key

void setup() {
  pinMode(sensorPin, INPUT);  // sets the pin as input
  Serial.begin(9600);  // Initialize serial communication
  
  // Encrypt and print the ciphertext
  Serial.println();
  vigenere_cipher(msg_Vigenere,Key_Vigenere);  // Call the vigenere_cipher function with the character array and key
  Serial.println();
}

void loop() {

  for (int i = 0; i < strlen(msg_Caesar); i++)
  {
        // Encrypt each character using XOR with the key
        unsigned short int ascii_v = caesar_cipher(msg_Caesar[i],Key_Caesar);
        
        Serial.print(ascii_v); // Print the encrypted ASCII value
        if (i<strlen(msg_Caesar)-1){
        Serial.print(" ");
        }
  }
  Serial.println();

  int sensorValue = analogRead(sensorPin); // Read the input on analog pin 0 as ADC count.... Maximum Analog Voltage expected to be measured

  // Calculate the voltage measured using the provided equation in V
  float voltage = sensorValue * (countADC / countMAX);

  float celcius = (voltage) /0.01;  // Convert voltage to temperature in degree Celsius as y = m.x + c and here c=0 , m = 0.01 V/degree C
  Serial.println((int)celcius);

  unsigned short int encrypt_XOR = manualXOR(celcius,Key_XOR);
  Serial.println(encrypt_XOR);
  delay(5000); // Wait for 5 seconds

}

// Function to perform Vigenere cipher encryption
unsigned short int vigenere_cipher(unsigned char *input, unsigned char* key ) {
  int output = 0;

  // Loop through each character in the input string
  for (int i = 0; i<strlen(input); i++) {
  
    // Convert lowercase letters to uppercase
    if (input[i] >= 'a' && input[i] <= 'z') {
      input[i] -= 32;  // Subtract the ASCII difference to convert to uppercase
    }

    // Encrypt uppercase letters using the Caesar cipher technique
    if(input[i] >= 'A' && input[i] <= 'Z') {
      // Shift the character by the key value
      output = ((input[i] + key[i%strlen(key)]) % 26) + 'A';  // Apply the Vigenere cipher formula
    } else {
      output = input[i];  // If the character is not a letter, leave it unchanged
    }

    Serial.print((char)output);  // Print the encrypted character
    if(i<strlen(input)-1){
      Serial.print(" ");
    }
  }  

  // Return the last encrypted character
  return (char)output;
}

unsigned short int caesar_cipher(unsigned short int input, unsigned short int Key )
{

    // Convert lowercase letters to uppercase by subtracting the ASCII difference
    if (input >= 'a' && input <= 'z')
    {
      input -= 32;
    }
    // Encrypt uppercase letters using the Caesar cipher technique
    if(input >= 'A' && input <= 'Z')
    {
    // Shift the character by the key value
      input += Key;

      // Handle wrap-around if the resulting character goes beyond 'Z'
      if(input > 'Z')
      {
        input -= 26;
      }
    }

    
  // Return the encrypted character
  return input;
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
