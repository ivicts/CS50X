#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#define SALT_SIZE 2
#define MAX_LENGTH 5


/*
17th January 2018
Cracking password assuming that each password has been hashed with C's DES based crypt function
Assume that password is no longer than five characters and is composed entirely of alphabetical characters
(uppercase and/or lowercase)

anushree:50xcIMJ0y.RXo: YES
brian:50mjprEcqC/ts: CA
bjbrown:50GApilQSG3E2 UPenn
lloyd:50n0AAUD.pL8g lloyd
malan:50CcfIk1QrPr6 maybe
maria:509nVI8B9VfuA TF
natmelo:50JIIyhDORqMU nope
rob:50JGnXUgaafgc ROFL
stelios:51u8F0dkeDSbY NO
zamyla:50cI2vYkF0YU2 LOL
*/

bool generate_string(int n, char *salt, char *hash_pass);
bool generate_string_recursive(int index, char *generated, char *salt, string hash_pass);
bool check_cryptic(string generated, char *salt, char *hash_pass);

int main(int argc, char *argv[])
{
    string hash_pass;

    // If the argument is not one, program exited with error message
    if (argc != 2)
    {
        printf("The program must be executed with a single command-line argument: a hashed password!\n");
        return 1;
    }

    hash_pass = argv[1];
    // Extracting the salt from the arguments
    char salt[SALT_SIZE + 1] = {hash_pass[0], hash_pass[1], '\0'} ;

    // Generate string with length i, iterating from length 1 to MAX_LENGTH
    for (int i = 1; i <= MAX_LENGTH; i++)
    {
        if (generate_string(i, salt, hash_pass))
        {
            break;
        }
    }
    return 0;


}


// Recursive helper to generate string
bool generate_string(int n, char *salt, char *hash_pass)
{
    char generated[n + 1];
    // To mark the end of the string
    generated[n] = '\0';
    if (generate_string_recursive(n - 1, generated, salt, hash_pass))
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

// Generate string and check if it has the same hash as the password
bool generate_string_recursive(int index, char *generated, char *salt, char *hash_pass)
{
    // Base cases and check the generated string
    if (index < 0)
    {
        if (check_cryptic(generated, salt, hash_pass))
        {
            return 1;
        }
        else
        {
            return 0;
        }

    }
    // Iterate from 'A' to 'z'
    for (char ch = 'A' ; ch <= 'z' ; ch == 'Z' ? ch = 'a' : ++ch)
    {
        generated[index] = ch;
        if (generate_string_recursive(index - 1, generated, salt, hash_pass))
        {
            return 1;
        }
    }
    return 0;
}

// Function to check if the generated string is the same as the password
bool check_cryptic(char *generated, char *salt, char *hash_pass)
{

    // Compared hashed generated string with hasshed password
    if (strcmp(crypt(generated, salt), hash_pass) == 0)
    {
        printf("%s\n", generated);
        return 1;
    }
    else
    {
        return 0;
    }

}