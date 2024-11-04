
#include <stdio.h>
#include <string.h>

// Function to reverse the array (in this case, a string)
 void reverseArray(char arr[], int size) {
     int start = 0;
     int end = size - 1;

     // Swap elements from the outer edges towards the center
     while (start < end) {
         // Swap elements at start and end indices
         char temp = arr[start];
         arr[start] = arr[end];
         arr[end] = temp;

         // Move indices towards the center
         start++;
         end--;
     }
 }

// Function to perform the Luhn algorithm
int luhn(char *cardNumber) {
    // Get the length of the credit card number
    int len = strlen(cardNumber);
	
//	if (len != 16)
//	{
//		printf("Incorrect Credit Card");
//	}
    // Reverse the order of the digits for Luhn algorithm
    reverseArray(cardNumber, len);
    // Variables to store partial sums
    int s1 = 0, s2 = 0;

    // Calculate the sum of digits using Luhn algorithm
    for (int i = 0; i < len; i++) {
    	
    	// convert the char index number into integer for the calculation
        int digit = cardNumber[i] - '0';

        // Double every second digit from the right (even-positioned digits)
        if (i % 2 == 1) {
            digit *= 2;

            // If the result is greater than 9, then subtract it by 9
            if (digit > 9) {
                digit -= 9;
            }

            // Add the modified digit to s2
            s2 += digit;
        } else if(i%2==0) {
            // Add every other digit (odd-positioned digits) to s1
            s1 += digit;
        }
    }

    // Sum the results
    int sum = s1 + s2;

    // If the total sum is a multiple of 10, the credit card number passes the Luhn test
    return (sum % 10 == 0);
}

int main() {
    // Open the file for reading
    FILE *file = fopen("input.txt", "r");
    
    // if the file is not opened it will show error
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    char cardNumber[20];

    // Read credit card numbers from the file until the end of file is reached
    while (fscanf(file, "%s", cardNumber) == 1) {
    	
    	printf("Credit Card Number: %s ", cardNumber);
        // Perform the Luhn test and print the result
//        if ()
	    if (luhn(cardNumber)) {
            printf("is a valid.\n");
        } else {
            printf("is an invalid.\n");
        }
    }

    // Close the file
    fclose(file);

    return 0;
}
