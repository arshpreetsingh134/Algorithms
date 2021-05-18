// Return the Lowest Significant Bit (LSB) of i
    int lsb(int i)
    {
        // Taking AND of a number and it's 2's complement
        // isolates the lowest one bit value
        return (i & -i);
    }
