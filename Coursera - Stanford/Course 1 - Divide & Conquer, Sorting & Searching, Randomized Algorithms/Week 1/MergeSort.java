import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.InputMismatchException;

public class MergeSort {

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
    private static void merge(int[] A, int f, int mid, int l) {

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

        for (int i = f; i <= l; i++) {
            if (k < n2 && (j >= n1 || L[j] >= R[k])) {
                A[i] = R[k++];
            }

            else {
                A[i] = L[j++];
            }
        }

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
    private static void mergeSortRecursive(int[] A, int f, int l) {
        if (f >= l)
            return;

        int mid = (int) Math.ceil((double) (f + l) / 2);
        mergeSortRecursive(A, f, mid - 1);
        mergeSortRecursive(A, mid, l);
        merge(A, f, mid, l);
    }

    /**
     * Merge Sort - Iterative (Bottom-Up) Approach
     * <ul>
     * <li>Time Complexity: O(nlogn)</li>
     * <li>Space Complexity: O(n)</li>
     * </ul>
     * 
     * @param A Array to be sorted
     * @param f First Position
     * @param l Last Position
     */
    private static void mergeSortIterative(int[] A) {
        int low, mid, high, p, i;

        // p is the number of passes.
        // We will need to pass by the (log n) passes and each time merge the items
        // there
        for (p = 2; p <= A.length; p *= 2) {
            for (i = 0; i + p - 1 < A.length; i += p) {
                low = i;
                high = i + p - 1;
                mid = ((int) Math.ceil((double) (low + high) / 2));
                merge(A, low, mid, high);
            }

        }

        // Include remaining items (in case if array is odd, some residual sub-arrays
        // might be left)
        if (p / 2 < A.length) {
            merge(A, 0, p / 2, A.length - 1);
        }

        merge(A, 0, A.length - 1, A.length - 1);
    }

    public static void sort(int[] A, boolean isIterative) {
        if (isIterative)
            mergeSortIterative(A);
        else
            mergeSortRecursive(A, 0, A.length - 1);
    }

    private static void solve(int t1, InputReader in) {

        int n = in.readInt();
        int[] A = new int[n];
        for (int i = 0; i < n; i++) {
            A[i] = in.readInt();
        }
        sort(A, true);
        System.out.println(Arrays.toString(A));
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
    [15, 22, 31, 35, 39, 45, 65, 87]
    [1, 2, 3, 4, 5, 8, 9]
    [1, 2, 3, 5, 6, 7, 8, 9, 10]
    [2, 4, 6, 7, 8, 9, 10, 11, 15, 28, 33, 112]
    [5, 7, 10, 13, 15, 23, 25, 27, 33, 34, 42, 47, 47, 55, 56, 58, 65, 66, 83, 86, 78, 89, 99, 101, 156]

 */