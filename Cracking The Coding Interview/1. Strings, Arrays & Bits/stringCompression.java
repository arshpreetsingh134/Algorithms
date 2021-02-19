// String Compression using counts of repeated characters
// E.g.: aabcccccaaa should become a2b1c5a3
// Efficient Solution: works for small strings
// StringBuilder not unnecesarily used

public class stringCompression
{
    int getFinalLength(String str)
    {
        int compressedLength=0;
        int maxSeq=0;
        for(int i=0; i<str.length(); i++)
        {
            maxSeq++;

            if(i+1>=str.length() || str.charAt(i)!=str.charAt(i+1))
            {
                compressedLength+= 1 + String.valueOf(maxSeq).length();
                maxSeq = 0;
            }
        }
        return compressedLength;
    }

    String CompressedString(String str)
    {
        int finalLength = getFinalLength(str);
        if(finalLength>str.length())
            return str;

        StringBuilder sb = new StringBuilder(finalLength);
        int maxSeq=0;

        for(int i=0; i<str.length(); i++)
        {
            maxSeq++;

            if(i+1>=str.length() || str.charAt(i)!=str.charAt(i+1))
            {
                sb.append(str.charAt(i));
                sb.append(maxSeq);
                maxSeq = 0;
            }   
        }
        return sb.toString();
    }

    public static void main(String[] args)
    {
        stringCompression sc =  new stringCompression();
        String str = "aabcccccaaa";
        System.out.println(sc.CompressedString(str));
    }
}