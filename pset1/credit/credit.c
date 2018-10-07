#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Victor Getty
// 17th June 2018
// Check the validity and company of the credit card

int main(void)
{
    long long number, digit_base10;
    int nDigits, digit, first_digit, second_digit, summation_mod_10, summation = 0;
    do
    {
        number = get_long_long("Number: ");
    }
    while (number <= 0);

    nDigits = floor(log10(number)) + 1;

    for (int i = 0; i < nDigits; i++)
    {
        digit_base10 = fmod(number, (pow(10, i + 1)));
        number = number - digit_base10;
        digit = digit_base10 / pow(10, i);

        if (i == nDigits - 1)
        {
            first_digit = digit;
        }
        else if (i == nDigits - 2)
        {
            second_digit = digit;
        }

        // Add the sum to the sum of the digits that weren't multiplied by 2
        if (fmod(i, 2) == 0)
        {
            summation += digit;
        }
        // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together.
        else
        {
            digit *= 2;
            // Add the product's digit (i.e not products themselves) together, note that the maximum number is 2*9 = 18.
            if (digit > 9)
            {
                digit = fmod(digit, 10) + 1;
            }
            summation += digit;
        }
    }

    summation_mod_10 = fmod(summation, 10);

    // Visa uses 13- and 16-digit numbers and all start with 4
    if ((summation_mod_10 == 0) && (first_digit == 4) && (nDigits == 13 || nDigits == 16))
    {
        printf("VISA\n");
    }
    // American Express uses 15-digit numbers and all start with 34 or 37
    else if ((summation_mod_10 == 0) && ((first_digit == 3) && ((second_digit == 4) || (second_digit == 7))) && (nDigits == 15))
    {
        printf("AMEX\n");
    }
    // MasterCard uses 16-digit numbers and  all start with 51, 52, 53, 54, or 55
    else if ((summation_mod_10 == 0)
             && (((first_digit == 5) && ((second_digit == 1) || (second_digit == 2) || (second_digit == 3)
                                         || (second_digit == 4) || (second_digit == 5)))) && (nDigits == 16))
    {
        printf("MASTERCARD\n");
    }
    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    else
    {
        printf("INVALID\n");
    }

    return 0;
}