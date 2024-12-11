/******************************************
*Student name: Arbel Feldman
*Student ID: 216303990
*Exercise name: ex_2
*Submit system username: feldmaaf
******************************************/

#include <stdio.h>
#include <math.h>

#define BIN 2
#define OCT 8
#define HEX 16

int main() {
    int opt, exit = 0;
    while (exit == 0) {
        printf("Choose an option:\n"
               "1. octal to hex\n"
               "2. binary addition\n"
               "3. print HI\n"
               "4. count bits\n"
               "5. decimal to binary\n"
               "6. Zig-Zag bits\n"
               "7. exit\n");
        scanf("%d", &opt);

        switch(opt) {
            case 1: // octal to hex
                printf("Please enter number in octal base: ");
                // "invalid" is to mark when the input is invalid.
                int octNum, i, len, original, counter, remainder = 0, invalid = 0, decimal = 0;
                scanf("%d", &octNum);

                // Log with base 10 tells me how many digits are in the number, I just have to round it up
                len = floor(log10(octNum)) + 1;

                if (octNum == 0)
                    printf("0\n");
                else {
                    if (octNum < 0)
                        invalid = 1;
                    else {

                        /*
                         * First I convert from octal to decimal.
                         * I take each digit and multiply it by 8 to the power of its index
                         * and sum it all up to get the decimal number.
                         * For example: the number 123 in octal is:
                         * 3*8^0 + 2*8^1 + 1*8^3 in decimal.
                         * Each time I remove the last digit of the number, so I can use the next.
                         */

                        for (i = 0; octNum != 0; i++) {
                            // Checking if there's a digit above 7:
                            if (octNum % 10 > OCT - 1) {
                                invalid = 1;
                                break;
                            } else {
                                // (octNum % 10) gives the octal number's last digit.
                                decimal += (octNum % 10) * pow(OCT, len - i - 1);
                                // Removes the last digit from the number (like shift for decimal):
                                octNum /= 10;
                            }
                        }
                    }

                    if (invalid == 1)
                        printf("Invalid input!\n");
                    else {

                        /*
                         * Now I convert the number from decimal to hex.
                         * Each time I take the number's remainder when dividing by 16 to get the hex number's digit.
                         * Then I divide by 16 to reduce the number to the next "level", so that I can find the next digit.
                         * This is like when converting a number from decimal to binary you divide by 2 each time.
                         * I repeat this until I get the hex number's last digit, I print it and do it all
                         * again to find the 2nd to last digit and print it and so on.
                         * I have to do this to do it like this because I can't
                         * use strings, and I need to print the MSB first.
                         */

                        original = decimal;
                        while (original != 0) {
                            counter = 0;
                            while (decimal != 0) {
                                remainder = decimal % HEX;
                                decimal /= HEX;
                                counter++;
                            }
                            // If the digit is above 9 I use ASCII:
                            if (remainder > 9)
                                printf("%c", 55 + remainder);
                            else
                                printf("%d", remainder);
                            original -= remainder * pow(HEX, (counter - 1));
                            decimal = original;
                        }
                        printf("\n");
                    }
                } // end of if-else

                break;
            case 2: // binary addition
                printf("Please enter two binary numbers: ");
                int len1, len2;
                invalid = 0;
                long long binNum1, binNum2, decSum = 0, result = 0;
                scanf("%lld\n%lld", &binNum1, &binNum2);

                long long tempNum = binNum1;
                if (binNum1 < 0 || binNum2 < 0)
                    invalid = 1;
                else {
                    // I convert both numbers to decimal, and I only use one variable to do it (decSum), so it already adds them up:
                    for (i = 0; i < 2; i++) {
                        counter = 0;
                        while (tempNum != 0 && invalid == 0) {
                            // Checking if there's a digit other than 0,1:
                            if (tempNum % 10 > BIN - 1)
                                invalid = 1;
                            else {

                                /*
                                 * This is the conversion from binary to decimal.
                                 * Like the conversion from octal, I multiply each binary digit
                                 * by a power of 2, according to its index, for example:
                                 * the number 100: 0*2^0 + 0*2^1 + 1*2^2
                                 * (tempNum % 10) gives the number's last digit, then I multiply it,
                                 * remove it and do it for the next one and so on.
                                 */

                                decSum += (tempNum % 10) * pow(BIN, counter);
                                // Removes the last digit from the number (like shift for decimal):
                                tempNum /= 10;
                                counter++;
                            }
                        }
                        tempNum = binNum2;
                    }

                    /*
                     * And now I convert the sum back to binary.
                     * I get the number's remainder, and that is the first digit.
                     * Then I multiply it by a power of 10 to shift the number ("result") left,
                     * Divide decSum by 2 and repeat.
                     */

                    counter = 0;
                    while (decSum != 0) {
                        result += (decSum % BIN) * pow(10, counter);
                        decSum /= BIN;
                        counter++;
                    }

                    // Log with base 10 tells me how many digits are in the number, I just have to round it up
                    len1 = floor(log10(binNum1)) + 1;
                    len2 = floor(log10(binNum2)) + 1;
                    // I have to check if the numbers are 0 because log(0) is not defined
                    if (binNum1 == 0)
                        len1 = 1;
                    if (binNum2 == 0)
                        len2 = 1;
                    // If the first number is longer I switch them, so that the shorter number would be printed first:
                    if (len1 > len2) {
                        tempNum = binNum1;
                        binNum1 = binNum2;
                        binNum2 = tempNum;
                    }
                }
                if (invalid == 0) {
                    // I print 0's based on the difference in the numbers' lengths, so they would have the same length:
                    for (i = 0; i < fabs(len1 - len2); i++)
                        printf("0");
                    printf("%lld + %lld = %lld\n", binNum1, binNum2, result);
                } else
                    printf("Invalid Input!\n");

                break;
            case 3: // print HI
                printf("Please enter size: ");
                int x, spaces;
                scanf("%d", &x);

                if (x < 0)
                    printf("Invalid input!\n");
                else {
                    // First line:
                    for (i = 0; i < x + 2; i++)
                        printf("#");
                    for (i = 0; i < x + 1; i++)
                        printf(" ");
                    for (i = 0; i < x + 2; i++)
                        printf("#");
                    printf("  ");
                    for (i = 0; i < x + 2; i++)
                        printf("#");
                    printf("\n");

                    // Top part of the HI:
                    for (i = 0; i < x; i++) {
                        spaces = x + 1;
                        for (int p = 0; p < 3; p++) {
                            printf("#");
                            for (int j = 0; j < x; j++)
                                printf("*");
                            printf("#");
                            for (int j = 0; j < spaces; j++)
                                printf(" ");
                            // I use "spaces" to change the number of spaces I print in each iteration of the for loop:
                            spaces = 2;
                            if (p == 1)
                                spaces = 0;
                        }
                        printf("\n");
                    }

                    // Line before the middle part:
                    printf("#");
                    for (i = 0; i < x; i++)
                        printf("*");
                    for (i = 0; i < x + 3; i++)
                        printf("#");
                    for (i = 0; i < x; i++)
                        printf("*");
                    printf("#  #");
                    for (i = 0; i < x; i++)
                        printf("*");
                    printf("#\n");

                    // Middle part:
                    for (i = 0; i < x; i++) {
                        printf("#");
                        for (int j = 0; j < 3 * x + 3; j++)
                            printf("*");
                        printf("#  #");
                        for (int j = 0; j < x; j++)
                            printf("*");
                        printf("#\n");
                    }

                    // Line after the middle part:
                    printf("#");
                    for (i = 0; i < x; i++)
                        printf("*");
                    for (i = 0; i < x + 3; i++)
                        printf("#");
                    for (i = 0; i < x; i++)
                        printf("*");
                    printf("#  #");
                    for (i = 0; i < x; i++)
                        printf("*");
                    printf("#\n");

                    // Bottom part of the HI (same as the top part, same use for "spaces"):
                    for (i = 0; i < x; i++) {
                        spaces = x + 1;
                        for (int p = 0; p < 3; p++) {
                            printf("#");
                            for (int j = 0; j < x; j++)
                                printf("*");
                            printf("#");
                            for (int j = 0; j < spaces; j++)
                                printf(" ");
                            // Same use for spaces:
                            spaces = 2;
                            if (p == 1)
                                spaces = 0;
                        }
                        printf("\n");
                    }

                    // Last line:
                    for (i = 0; i < x + 2; i++)
                        printf("#");
                    for (i = 0; i < x + 1; i++)
                        printf(" ");
                    for (i = 0; i < x + 2; i++)
                        printf("#");
                    printf("  ");
                    for (i = 0; i < x + 2; i++)
                        printf("#");
                    printf("\n");
                } // end of if-else

                break;
            case 4: // count bits
                printf("Please enter a binary number: ");
                invalid = 0;
                long long num;
                scanf("%lld", &num);
                counter = 0;

                if (num < 0)
                    invalid = 1;
                else {
                    while (num != 0) {
                        // Checks if digit in the one's place is 1:
                        if (num % 10 == 1)
                            counter++;
                            // Checks if it's not 0 or 1:
                        else if ((num % 10) > BIN - 1) {
                            invalid = 1;
                            break;
                        }
                        // Removes the last digit from the number (like shift for decimal):
                        num /= 10;
                    }
                }
                if (invalid == 0)
                    printf("%d\n", counter);
                else
                    printf("Invalid input!\n");

                break;
            case 5: // decimal to binary
                printf("Enter a non negative decimal number: ");
                int answer = 0;
                scanf("%d", &original);
                // I use "original" to preserve the original value while I convert it using the "num" variable:
                num = original;

                if (original < 0) {
                    printf("Invalid input!\n");
                    break;
                } else {
                    // Exactly the same conversion from decimal to binary as in case 2:
                    counter = 0;
                    while (num != 0) {
                        answer += (num % BIN) * pow(10, counter);
                        num /= BIN;
                        counter++;
                    }
                }
                printf("%d => %d\n", original, answer);

                break;
            case 6: // Zig-Zag bit
                printf("Enter a non negative decimal number: ");
                scanf("%lld", &num);
                answer = 0;
                int lastDigit;
                // This variable is the final result, true/false:
                int zigZag = 1;

                if (num < 0) {
                    printf("Invalid input!\n");
                    break;
                } else {
                    // Exactly the same conversion from decimal to binary as in case 2:
                    counter = 0;
                    while (num != 0) {
                        answer += (num % BIN) * pow(10, counter);
                        num /= BIN;
                        counter++;
                    }

                    /*
                     * The "zigZag" variable starts at 1, and if at any point the code detects 2 identical consecutive digits, it sets it to 0.
                     * At first, I set "lastDigit" to be the last digit of the binary number.
                     * Then I remove it from the original number (like shifting it right once).
                     * Then I check if the shifted number's last digit is equal to lastDigit (meaning there are 2 identical consecutive digits).
                     * If so, I set zigZag to 0 and exit the while loop.
                     * If not, I set lastDigit to the number's last digit and shift it right again.
                     * And so on. If no 2 identical consecutive digits were detected, that means the number has a zigzag form.
                     */

                    // answer % 10 gives the last digit of answer.
                    lastDigit = answer % 10;
                    // Shift right:
                    answer /= 10;
                    while (answer != 0) {
                        if (lastDigit == answer % 10) {
                            zigZag = 0;
                            break;
                        }
                        lastDigit = answer % 10;
                        // Shift right:
                        answer /= 10;
                    }
                } // end of if-else

                if (zigZag == 0)
                    printf("false\n");
                else
                    printf("true\n");

                break;
            case 7: // exit
                printf("Bye!\n");
                exit = 1;
                break;
            default:
                printf("Invalid option!\n");
        } // end of switch
    } // end of while loop

    return 0;
}
