#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define ALPHABET_SIZE 26

/* 19th January 2018
Victor Getty
Implement vigenere cipher */

bool is_alpha_string(char *input);

int main(int argc, char *argv[])
{
    char *key;
    key = argv[1];

    // The program only accepts single all alphabetical command line argument, if not print error and exist with main returning 1
    if (argc != 2)
    {
        printf("The program must be executed with a single command line argument! \n");
        return 1;
    }
    else if (!is_alpha_string(key))
    {
        printf("The program must be executed with all alphabetical command line argument! \n");
        return 1;
    }

    char *p;
    int counter = 0, p_length, key_length, p_i, k_j;

    p = get_string("plaintext: ");
    p_length = strlen(p);

    char result[p_length + 1];
    result[p_length] = '\0';
    key_length = strlen(key);

    // Normalizing the character for the key to 0 - 25
    for (int  i = 0; i < key_length; i++)
    {
        if (isupper((key[i])))
        {
            key[i] -= 'A';
        }
        else
        {
            key[i] -= 'a';
        }
    }


    for (int i = 0; i < p_length; i++)
    {
        // If not an alphabetical character, just copy the character
        if (!isalpha(p[i]))
        {
            result[i] = p[i];
        }
        else
        {
            // To reused the key cyclically, we utilize mod function
            k_j = key[(int) fmod(counter, key_length)];
            // Normalizing and computing the ciphertext
            if (isupper(p[i]))
            {
                p_i = p[i] - 'A';
                result[i] = fmod((p_i + k_j), ALPHABET_SIZE) + 'A';
            }
            // Lower character
            else
            {
                p_i = p[i] - 'a';
                result[i] = fmod((p_i + k_j), ALPHABET_SIZE) + 'a';
            }
            counter++;
        }
    }
    printf("ciphertext: %s\n", result);

    return 0;
}

// Function to check whether the string is all alphabetical
bool is_alpha_string(char *input)
{
    bool result;
    for (int i = 0; i < strlen(input); i++)
    {
        result = isalpha(input[i]);
        // If there is one character that is alphabetical, return 0
        if (result == 0)
        {
            break;
        }
    }
    // If all character is alphabetical, return 1
    return result;
}