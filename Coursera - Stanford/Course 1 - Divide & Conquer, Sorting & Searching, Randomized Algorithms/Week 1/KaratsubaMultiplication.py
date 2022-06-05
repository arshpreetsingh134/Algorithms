# -*- coding: utf-8 -*-
"""
Updated on Sun Jun 5 13:47:56 2022

@author: ARSHPREET SINGH
"""

import io, os;

def karatsuba(x, y):
    """Performs Karatsuba multiplication on two numbers."""
    
    # Calculate the length of the two integers and take the minimum of the two.
    n = min(len(str(x)), len(str(y)))

    # Perform simple multiplication if any of the two numbers is less than 10.
    if n == 1:
        return x * y

    # Calculate half length and the power of 10 raised to that half length.
    half = n // 2
    power_of_10 = 10 ** half

    # Divide and conquer.
    # Here, x = (a * power_of_10) + b
    # Here, y = (c * power_of_10) + d
    a = x // power_of_10
    b = x % power_of_10
    c = y // power_of_10
    d = y % power_of_10

    # 3 recursive calls to calculate (a * c), (b * d) and ((a + b) * (c + d)).
    ac = karatsuba(a, c)
    bd = karatsuba(b, d)
    a_plus_b_into_c_plus_d = karatsuba(a + b, c + d)

    # Multiply the results with the appropriate powers of 10,
    # and add them.
    return (ac * pow(power_of_10, 2)) + bd + \
        ((a_plus_b_into_c_plus_d - ac - bd) * power_of_10)


def main():
    """The main function."""
    
    # Change the current working directory
    os.chdir(os.getcwd()+'\Coursera - Stanford\Course 1 - Divide & Conquer, Sorting & Searching, Randomized Algorithms\Week 1')

    # Get the current working directory
    cwd = os.getcwd()
    print("Current working directory: {0}".format(cwd))

    input = open('input.txt')
    output = open('output.txt', "w")
    tests = input.readline()

    for i in range(int(tests)):
        input.readline()
        x = input.readline()
        y = input.readline()

        result = karatsuba(int(x), int(y))

        output.write(str(result) + '\n')
        
    output.close()
    input.close()

main()

# Test Cases
# 3

# 56
# 568

# 1111
# 1111

# 3141592653589793238462643383279502884197169399375105820974944592
# 2718281828459045235360287471352662497757247093699959574966967627

# Output
# 31808
# 1234321
# 8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184

