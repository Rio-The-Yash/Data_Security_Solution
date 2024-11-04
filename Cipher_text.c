#include <stdio.h>
#include <string.h>

#define NUM_BIT 16
unsigned short int key = 0b00101101; // 28
unsigned short int plainText;

void char_Ascii(char *c, int i)
{
    int ascii_v = (int)(c[i]);
    // for (int i = 0; i < strlen(c); i++)
    // {
        printf("%c\t\t%d\t\t",c[i],ascii_v);  
    // }
    // return ascii_v;
}

// Function to get the kth bit of input
int getBit(unsigned short int input, int k)
{
	return (unsigned short int)((input >> k) & 1);
}  

unsigned short int manualXOR(unsigned short int input, unsigned short int key)
{
	int cipherText = input ^ key;
	printf("\t\t%d", cipherText);

}

int main(int argc, char const *argv[])
{
    char c[20] = "random Message";
    for (int i = 0; i < strlen(c); i++)
    {
        
        int ascii_v = (int)(c[i]);
        char_Ascii(c,i);

        for(int j=7; j>=0; j--)
	    {
            printf("%u", getBit(ascii_v, j));

	    }

        manualXOR(ascii_v, key);
        printf("\n");
    }
    
    FILE *file = fopen("CipherText.txt", "w+");
    

    return 0;
}
