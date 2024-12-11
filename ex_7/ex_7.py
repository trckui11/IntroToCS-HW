# """
# *Student name: Arbel Feldman
# *Student ID: 216303990
# *Exercise name: ex_7
# *Submit User Name: feldmaaf
# """
#
# import math
#
# MAX_CHECK_NUM = 100
#
#
# def is_prime(number, efficiency):
#     """
#     The function checks if a number is prime, and prints "YES" or "NO"
#     accordingly.
#
#     Keyword arguments:
#         number - the number to check if prime.
#         efficiency - the place you want to stop checking if number is prime.
#     Return: none.
#     """
#
#     if efficiency == 'a':
#         check_up_to = number
#     else:
#         check_up_to = math.ceil(math.sqrt(number)) + 1
#     # edge cases:
#     if number < 2:
#         print("NO")
#         return
#     if number == 2:
#         print("YES")
#         return
#
#     # checks if number is divisible by each number (depending on mission type)
#     for i in range(2, check_up_to):
#         # if number is divisible by i:
#         if (number % i) == 0:
#             print("NO")
#             return
#     print("YES")
# # end of function is_prime
#
#
# def mission_1():
#     """
#     The function asks for the mission type and for a number, to check if it's
#     prime. Then if activates the is_prime function.
#
#     Keyword arguments:
#         none.
#     Return: none.
#     """
#
#     efficiency = input("please enter the mission type:\n")
#     number = int(input("please enter a number:\n"))
#     is_prime(number, efficiency)
#
#
# def mission_2():
#     """
#     The function asks for 2 numbers and prints a list of all the numbers
#     between 1-100 that they divide.
#
#     Keyword arguments:
#         none.
#     Return: none.
#     """
#
#     numbers = input("please enter two numbers:\n")
#     # splits the input into the 2 numbers:
#     numbers = numbers.split(' ')
#     # the list of divisors:
#     divisible = []
#
#     # goes through 1-100 and checks if they're by 1 of the 2 inputted numbers:
#     for i in range(1, MAX_CHECK_NUM + 1):
#         if (i % int(numbers[0]) == 0) or (i % int(numbers[1]) == 0):
#             # if so, it adds the number to the list:
#             divisible.append(i)
#     # print the list:
#     print(divisible)
# # end of function mission_2
#
#
# def main():
#     exit_program = False
#
#     while not exit_program:
#         option = int(input("please enter a mission number:\n"))
#
#         # all the options:
#         if option == 0:
#             # exit:
#             exit_program = True
#         elif option == 1:
#             # mission 1:
#             mission_1()
#         else:
#             # mission 2:
#             mission_2()
# # end of main
#
#
# if __name__ == '__main__':
#     main()







a = 255
print(int(bin(a)[2:])) #prints an int: 110
