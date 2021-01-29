import jdk.nashorn.internal.ir.ReturnNode;

public class PalindromePermutation
{
    // Check that no more than 1 character has an odd count
    boolean checkOddCount(int[] table)
    {
        boolean foundOdd = false;
        for(int i:table)
        {
            // If odd found
            if(i%2==1)
            {
                //check if it's the first odd
                if(foundOdd)
                    return false;

                // if it is, assign 'true' to the variable
                foundOdd=true;
            }
        }
        return true;
    }

    // Maps characters to ints. a-0, b-1, c-2,...and so on
    // Non-letter characters map to -1
    int getCharNumber(char ch)
    {
        int a = Character.getNumericValue('a');
        int z = Character.getNumericValue('z');
        int val = Character.getNumericValue(ch);
        if(val>=a && val<=z)
            return val-a;

        return -1;
    }

    // Building the Hash Table
    int[] buildCharFrequencyTable(String s)
    {
        int table[] = new int[Character.getNumericValue('z')-Character.getNumericValue('a')+1];

        for(char ch:s.toCharArray())
        {
            int x = getCharNumber(ch);
            if(x!=-1)
                table[x]++;
        }
        return table;
    }

    // First Method (using Hash Table)
    boolean isPermutation1(String str)
    {
        int[] table = buildCharFrequencyTable(str);
        return checkOddCount(table);
    }

    /***********************************************************/

    // Toggle the i-th bit in the integer
    int toggle(int bitVector, int index)
    {
        if(index<0)
            return bitVector;

        int mask = 1<<index;

        if((bitVector&mask)==0)
            bitVector|=mask;
        else
            bitVector&=~mask;
        return bitVector;
    }

    // Create a bit vector for the string. For each letter with
    // value i, toggle the i-th bit
    int createBitVector(String s)
    {
        int bitVector = 0;
        for(char ch:s.toCharArray())
        {
            int x = getCharNumber(ch);
            // if(x>=0)
            //     bitVector = (bitvector^(1<<x));
            bitVector=toggle(bitVector, x);
        }
        return bitVector;
    }

    // Check that exactly one bit is set by subtracting one from
    // the integer and ANDing it with the original integer
    boolean checkForSingleBit(int bitVector)
    {
        return ((bitVector - 1) & bitVector)==0;
    }

    boolean isPermutation2(String s)
    {
        int bitVector = createBitVector(s);
        return (bitVector==0 || checkForSingleBit(bitVector));
    }

    public static void main(String[] args)
    {
        String str = "Cato catoo";
        PalindromePermutation pp = new PalindromePermutation();
        if(pp.isPermutation2(str))
            System.out.println("Yes");
        else
            System.out.println("No");
    }
}