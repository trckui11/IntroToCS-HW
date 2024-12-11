/******************************************
*Student name: Arbel Feldman
*Student ID: 216303990
*Exercise name: ex_3
*Submit system username: feldmaaf
******************************************/

#include <stdio.h>
#include <math.h>

#define ASCII_UPPERA 65
#define ASCII_UPPERZ 90
#define ASCII_LOWERA 97
#define ASCII_LOWERZ 122
#define ASCII_0 48
#define ASCII_9 57
#define TEN 10


/*************************************************************************
* function name: expression *
* The Input: The function gets a minimal expression of the form (a op b)*
* The output: The function returns true or false *
* The Function operation: The function identifies the operator and calculates the result *
*************************************************************************/

int expression
        (long long a, int op, long long b, int isALetter, int isBLetter) {
    // If the letter is capital this "turns it into" a lowercase letter:
    if (isALetter) {
        if (ASCII_UPPERA <= a && a <= ASCII_UPPERZ)
            // It adds the difference in the ASCII value:
            a += (ASCII_LOWERA - ASCII_UPPERA);
    }
    if (isBLetter) {
        if (ASCII_UPPERA <= b && b <= ASCII_UPPERZ)
            b += (ASCII_LOWERA - ASCII_UPPERA);
    }

    if (op == '<')
        return a < b;
    else if (op == '>')
        return a > b;
    return a == b;
}


/*************************************************************************
* function name: isInvalid *
* The Input: The char that the user inputted and its index *
* The output: True of false *
* The Function operation: Each index has a specific type it needs to be.
 * The function checks if it is that type to identify when there's a syntax error *
 * index:  1       2         3         4       5  6
 * format: ( number/letter </=/> number/letter ) &/|
*************************************************************************/

int isInvalid(long long input, int index) {
    switch (index) {
        case 1:
            if (input != '(')
                return 1;
            break;
        case 2:
        case 4:
            if (!((ASCII_0 <= input && input <= ASCII_9)
                  || (ASCII_UPPERA <= input && input <= ASCII_UPPERZ)
                  || (ASCII_LOWERA <= input && input <= ASCII_LOWERZ)))
                return 1;
            break;
        case 3:
            if (!('<' <= input && input <= '>'))
                return 1;
            break;
        case 5:
            if (input != ')')
                return 1;
            break;
        case 6:
            if (input != '&' && input != '|' && input != '\n' && input != ' ')
                return 1;
            // End of switch
    }
    return 0;
}


/*************************************************************************
* function name: digitCount *
* The Input: A number, a digit, and the counter *
* The output: How many times the digit appears in the number *
* The Function operation: It checks if a the number's last digit is the digit
 * and then removes it from the number, then calls the function again with the
 * new number. It stops when the number is 0 (when all the digits were checked)*
*************************************************************************/

int digitCount(long long num, int digit, int counter) {
    if (num == 0)
        return counter;
    // num % TEN gives the number's last digit:
    if (num % TEN == digit)
        counter++;
    // num /= TEN removes the last digit from the number:
    num /= TEN;
    return digitCount(num, digit, counter);
}


/*************************************************************************
* function name: GCD *
* The Input: 2 numbers *
* The output: Their Greatest Common Divisor *
* The Function operation: The function uses euclid's algorithm and prints the steps. *
*************************************************************************/

void GCD(long long num1, long long num2) {
    // Set num1 to be the larger of the two and num2 the lower:
    long long temp = num1;
    num1 = fmax(num1, num2);
    num2 = fmin(num2, temp);

    // GCD(0,x) = x:
    if (num1 == 0)
        printf("GCD = %lld\n", num2);
    else if (num2 == 0)
        printf("GCD = %lld\n", num1);
    else {
        printf("%lld*%lld+%lld = %lld (num1=%lld, num2=%lld)\n",
               num2, num1 / num2, num1 % num2, num1, num1, num2);
        GCD(num2, num1 % num2);
    }
}


int main() {
    int exit = 0;
    char opt;
    while (exit == 0) {
        printf("Choose an option:\n"
               "\t1: Logical Statement Calculator\n"
               "\t2: Count digit in a number\n"
               "\t3: GCD Calculator\n"
               "\t4: Exit\n");
        scanf(" %c", &opt);

        switch (opt) {
            case '1':
                // * Logical Statement Calculator *
                printf("\nPlease write your logical statement: ");

                /*
                 * Variables:
                 * - a and b are the numbers/letter in the expression: (a op b)
                 * - op is the operator </=/>.
                 * - result is the final true/false.
                 * - isALetter, isBLetter is for when a/b are letters because I don't want
                 * the "expression" function to convert them into lowercase letters when they are not letters.
                 * (65 is a number and also a capital "A")
                 * - invalid is for when there's a syntax error. the "isInvalid" function detects, and it adds 1 to
                 * invalid when there's an error (so when there are no errors invalid is 0)
                 * - negation is to mark when there's a "~" sign.
                 * - inputChar is the input.
                 * - index is the index of the input.
                 * - "and" and "or" are to mark when there's "&" or "|".
                 * - tempResult is to save the previous result when there's "&" or "|" and compare them.
                 */

                long long a, b;
                int result, isALetter, isBLetter, op, tempResult;
                int invalid = 0, negation = 0, inputChar = '.', index = 0;
                int and = 0, or = 0;

                while (inputChar != '\n') {
                    inputChar = getchar();

                    if (inputChar == '~') {
                        negation = 1;
                        /*
                         * the isInvalid function compares the index to the expected input.
                         * But there isn't always a "~" sign, so I need to "ignore" it in order
                         * for the function to work, so I reduced the index by 1.
                         */
                        index--;
                    }

                    invalid += isInvalid(inputChar, index);
                    // I only want to detect "a", "op" and "b" after a "(" symbol:
                    if (inputChar == '(') {
                        isALetter = 1;
                        isBLetter = 1;

                        index++;
                        a = getchar();

                        // In case the input ends after the "(":
                        if (a == '\n' || a == ' ') {
                            invalid++;
                            break;
                        }
                        invalid += isInvalid(a, index);

                        // If "a" is a digit, I put it back in the buffer and scan for a number in case it has multiple digits:
                        if (ASCII_0 <= a && a <= ASCII_9) {
                            ungetc(a, stdin);
                            scanf("%lld", &a);
                            isALetter = 0;
                        }

                        index++;
                        op = getchar();

                        // In case the input ends after the "a":
                        if (op == '\n' || op == ' ') {
                            invalid++;
                            break;
                        }
                        invalid += isInvalid(op, index);

                        index++;
                        b = getchar();

                        // In case the input ends after the operator:
                        if (b == '\n' || b == ' ') {
                            invalid++;
                            break;
                        }
                        invalid += isInvalid(b, index);

                        // Same concept as with "a", but for "b":
                        if (ASCII_0 <= b && b <= ASCII_9) {
                            ungetc(b, stdin);
                            scanf("%lld", &b);
                            isBLetter = 0;
                        }
                        result = expression(a, op, b, isALetter, isBLetter);

                        if (negation == 1) {
                            result = !result;
                            negation = 0;
                        }
                        if (and == 1) {
                            result = result && tempResult;
                            and = 0;
                        } else if (or == 1) {
                            result = result || tempResult;
                            or = 0;
                        }
                    } else if (inputChar == '&') {
                        // Saving the result to compare with the next one:
                        tempResult = result;
                        invalid += isInvalid(inputChar, index);
                        and = 1;
                        // When the "(a op b)&" format ends, I reset the index in preparation for the next one:
                        index = 0;
                    } else if (inputChar == '|') {
                        tempResult = result;
                        invalid += isInvalid(inputChar, index);
                        or = 1;
                        // When the "(a op b)|" format ends, I reset the index in preparation for the next one:
                        index = 0;
                    // End of if-else
                    }

                    // Validity check when it doesn't enter the if (inputChar == "("):
                    if (inputChar != '(')
                        invalid += isInvalid(inputChar, index);
                    index++;

                    // For when the expression ends with a space:
                    if (index > 1 && inputChar == ' ')
                        break;

                // End of while loop
                }

                if (invalid != 0)
                    printf("You have a syntax error in your statement.\n");
                else if (result == 1)
                    printf("The statement is true.\n");
                else
                    printf("The statement is false.\n");

                break;
            case '2':
                // * Count digit in a number *
                printf("\nEnter a number and a digit: ");
                int digit, count;
                long long num;
                scanf("%lld %d", &num, &digit);

                // Error check (negative number/digit or multiple digits in "digit" variable):
                if (num < 0 || digit < 0 || 9 < digit)
                    printf("You should stay positive, "
                           "and so should your input.\n");
                else {
                    // Edge case that the function can deal with:
                    if (num == 0 && digit == 0)
                        count = 1;
                    else
                        count = digitCount(num, digit, 0);
                    printf("The digit %d appears %d times "
                           "in the number %lld\n", digit, count, num);
                }

                break;
            case '3':
                // * GCD Calculator *
                printf("\nEnter two positive numbers: ");
                long long num1, num2;
                scanf("%lld %lld", &num1, &num2);

                // Error check (negative numbers):
                if (num1 < 0 || num2 < 0)
                    printf("You should stay positive, "
                           "and so should your input.\n");
                else
                    GCD(num1, num2);

                break;
            case '4':
                // * Exit *
                printf("So Long, and Thanks for All the Fish!");
                exit = 1;
                break;
            default:
                printf("Fool of a Took!\n"
                       "This is a serious journey,"
                       " not a hobbit walking-party.\n"
                       "Throw yourself in next time,"
                       " and then you will be no further nuisance.\n"
                );
        // End of switch
        }
    // End of while loop
    }

    return 0;
}
