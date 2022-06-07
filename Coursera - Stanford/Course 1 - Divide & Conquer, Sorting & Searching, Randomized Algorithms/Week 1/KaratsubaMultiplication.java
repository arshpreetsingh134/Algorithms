import static java.lang.Math.ceil;
import static java.lang.Math.floor;
import static java.lang.Math.min;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.InputMismatchException;
import java.util.regex.Pattern;

public class KaratsubaMultiplication {

    // ********************************************************************* //
    static final File ip = new File("input.txt");
    static final File op = new File("output.txt");
    static InputReader in;

    static {
        try {
            System.setOut(new PrintStream(op));
            System.setIn(new FileInputStream(ip));
        } catch (Exception e) {
            System.out.println("I/O Exception");
            e.printStackTrace();
        }
        in = new InputReader(System.in);
    }

    static class InputReader {
        private InputStream stream;
        private byte[] buf = new byte[1024];
        private int curChar;
        private int numChars;
        private SpaceCharFilter filter;

        public InputReader(InputStream stream) {
            this.stream = stream;
        }

        public int read() {
            if (numChars == -1)
                throw new InputMismatchException();
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (numChars <= 0)
                    return -1;
            }
            return buf[curChar++];
        }

        public int readInt() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            int res = 0;
            do {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public String readString() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            StringBuilder res = new StringBuilder();
            do {
                res.appendCodePoint(c);
                c = read();
            } while (!isSpaceChar(c));
            return res.toString();
        }

        public boolean isSpaceChar(int c) {
            if (filter != null)
                return filter.isSpaceChar(c);
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }

        public String next() {
            return readString();
        }

    }

    interface SpaceCharFilter {
        public boolean isSpaceChar(int ch);
    }

    // ********************************************************************* //

    /**
     * Finding integer sum of 2 large integers as string
     * 
     * @param num1
     * @param num2
     * @return String
     */
    private static String findSum(String str1, String str2) {
        // Before proceeding further, make sure length
        // of str2 is larger.
        if (str1.length() > str2.length()) {
            String t = str1;
            str1 = str2;
            str2 = t;
        }

        // Take an empty String for storing result
        String str = "";

        // Calculate length of both Strings
        int n1 = str1.length(), n2 = str2.length();
        int diff = n2 - n1;

        // Initially take carry zero
        int carry = 0;

        // Traverse from end of both Strings
        for (int i = n1 - 1; i >= 0; i--) {
            // Do school mathematics, compute sum of
            // current digits and carry
            int sum = ((int) (str1.charAt(i) - '0') +
                    (int) (str2.charAt(i + diff) - '0') + carry);
            str += (char) (sum % 10 + '0');
            carry = sum / 10;
        }

        // Add remaining digits of str2[]
        for (int i = n2 - n1 - 1; i >= 0; i--) {
            int sum = ((int) (str2.charAt(i) - '0') + carry);
            str += (char) (sum % 10 + '0');
            carry = sum / 10;
        }

        // Add remaining carry
        if (carry > 0)
            str += (char) (carry + '0');

        // reverse resultant String
        return new StringBuilder(str).reverse().toString();
    }

    /**
     * Karatsuba Multiplication - ab x cd = ((10^n'*a)+b) x ((10^n'*c)+d) = 10^n*ac
     * + 10^n'(ad + bc) + bd
     * where n' = n/2
     * Recurrence Relation: T(n) = 3T(n/2) + O(n)
     * Time Complexity: O(n^log3) = O(n^1.59)
     * Space Complexity: O(n)
     * 
     * @param num1
     * @param num2
     * @return String - Product of 2 numbers
     */
    private static String multiply(String num1, String num2) {

        // Base case 1 - If one of the numbers is 0 or 1
        if (Pattern.matches("^0+$", num1)) {
            return "0";
        }

        if (Pattern.matches("^0+$", num2)) {
            return "0";
        }

        if (Pattern.matches("^0*1$", num1)) {
            return num2;
        }

        if (Pattern.matches("^0*1$", num2)) {
            return num1;
        }

        int n1 = num1.length();
        int n2 = num2.length();

        // Base Case 2 - If both numbers are less than equal to 2,
        // perform simple multiplication
        if (n1 <= 2 && n2 <= 2) {
            return String.valueOf(Integer.valueOf(num1) * Integer.valueOf(num2));
        }
        int mid1 = (int) ceil((double) n1 / 2);
        int mid2 = (int) ceil((double) n2 / 2);
        int n = min(n1, n2);

        String a = num1.substring(0, mid1);
        String b = num1.substring(mid1, n1);
        String c = num2.substring(0, mid2);
        String d = num2.substring(mid2, n2);

        if (n / 2 <= 1) {
            Integer bi1 = Integer.parseInt(num1);
            Integer bi2 = Integer.parseInt(num2);
            return String.valueOf(bi1 * bi2);
        }

        String ac = multiply(a, c);
        String bd = multiply(b, d);
        String ad = multiply(a, d);
        String bc = multiply(b, c);

        // Apply the Karatsuba Equation
        String add12 = findSum(ac + new String(new char[n]).replace("\0", "0"),
                ad + new String(new char[(int) floor(n1 / 2)]).replace("\0", "0"));

        String add123 = findSum(add12, bc + new String(new char[(int) ceil(n2 / 2)]).replace("\0", "0"));

        String add1234 = findSum(add123, bd);

        return add1234;

    }

    private static void solve(int t1, InputReader in) {
        String num1 = in.readString();
        String num2 = in.readString();
        System.out.println(multiply(num1, num2));
    }

    public static void main(String[] args) throws FileNotFoundException {

        int t = in.readInt();
        int t1 = 1;
        while (t1 <= t) {
            solve(t1, in);
            t1++;
        }
    }
}


/********************************************
 * Test Cases
 * ******************************************
 * 
4

2
3

56
2

56
258

3141592653589793238462643383279502884197169399375105820974944592
2718281828459045235360287471352662497757247093699959574966967627

 *
 * 
 */


/********************************************
 * Output
 * *******************************************
 *

6
112
14448
8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184

 *
 *
 */