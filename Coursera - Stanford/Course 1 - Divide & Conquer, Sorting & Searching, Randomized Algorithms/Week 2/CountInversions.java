import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.InputMismatchException;

public class CountInversions {

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
     * Merge() Subroutine
     * <ul>
     * <li>Time Complexity: O(n)</li>
     * <li>Space Complexity: O(n)
     * </ul>
     * </li>
     * 
     * @param A   Array to be sorted
     * @param f   First Position
     * @param mid Mid Position
     * @param l   Last Position
     */
    private static int merge(int[] A, int f, int mid, int l) {

        int n1 = mid - f;
        int n2 = l - mid + 1;

        int[] L = new int[n1];
        int[] R = new int[n2];

        int j = 0;
        int k = 0;

        for (int i = f; i < mid; i++) {
            L[j++] = A[i];
        }

        for (int i = mid; i <= l; i++) {
            R[k++] = A[i];
        }

        j = 0;
        k = 0;
        int count = 0;

        for (int i = f; i <= l; i++) {

            // Whenever an element from the right array is copied to the sorted array
            if (k < n2 && (j >= n1 || L[j] >= R[k])) {
                A[i] = R[k++];

                // Increment the count by no. of remaining elements in
                // the left array
                count+=n1-j;
            }

            else {
                A[i] = L[j++];
            }
        }

        return count;

    }

    /**
     * Merge Sort - Recursive (Top-Down) Approach
     * <ul>
     * <li>Time Complexity: O(nlogn)</li>
     * <li>Space Complexity: O(n + logn) = O(n)</li>
     * </ul>
     * 
     * @param A Array to be sorted
     * @param f First Position
     * @param l Last Position
     */
    private static int mergeSortRecursive(int[] A, int f, int l) {
        if (f >= l)
            return 0;

        int mid = (int) Math.ceil((double) (f + l) / 2);
        int a = mergeSortRecursive(A, f, mid - 1);
        int b = mergeSortRecursive(A, mid, l);
        int c = merge(A, f, mid, l);
        return a+b+c;
    }

    /**
     * Collaborative Filtering -
     * Count the no. of inversions in an array A w.r.t. the sorted array A'
     * (Piggybacking on the canonical MergeSort algorithm)
     * <ul>
     * <li>Time Complexity: O(nlogn)</li>
     * <li>Space Complexity: O(n)</li>
     * </ul>
     * @param A Array for which inversions need to be computed
     * @return int No. of Inversions
     */
    public static int countInversions(int[] A) {
        int[] B = new int[A.length];
        for(int i=0; i<A.length; i++) {
            B[i] = A[i];
        }
        return mergeSortRecursive(B, 0, A.length - 1);
    }

    private static void solve(int t1, InputReader in) {

        int n = in.readInt();
        int[] A = new int[n];
        for (int i = 0; i < n; i++) {
            A[i] = in.readInt();
        }
        int numInversions = countInversions(A);
        System.out.println("No. of Inversions in array " + t1 + ": " + numInversions);
    }

    public static void main(String[] args) {
        int t = in.readInt();
        int t1 = 1;
        while (t1 <= t) {
            solve(t1, in);
            t1++;
        }
    }
}

/**
 * Test Cases
 * 
    5

    8
    87 65 45 39 35 31 22 15

    7
    8 5 2 1 3 9 4

    9
    8 7 10 3 5 2 6 9 1

    12
    4 11 7 10 8 15 33 6 9 28 112 2

    25
    58 66 156 23 47 89 33 25 101 47 99 65 83 27 56 42 13 10 5 7 15 86 55 34 78

*/

/**
 * Output
 * 
    No. of Inversions in array 1: 28
    No. of Inversions in array 2: 11
    No. of Inversions in array 3: 24
    No. of Inversions in array 4: 26
    No. of Inversions in array 5: 185

 */