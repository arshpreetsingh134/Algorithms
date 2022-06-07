import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;

public class RecursiveMatrixMultiplication {

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
     * multiply() - For multiplying 2 arrays A & B;
     * Dimensions (nxn) of 2 arrays must be equal and
     * must be a power of 2
     * <ul>
     * <li>Recurrence Relation: T(N) = 8T(N/2) + O(N^2)
     * <li>Time Complexity: O(n^3)</li>
     * <li>Space Complexity: O(n^2)</li>
     * </ul>
     * 
     * @param matrix1
     * @param matrix2
     * @param result1
     * @param start_row_A Start Row of matrix A
     * @param end_row_A   End Row of matrix A
     * @param start_col_A Start Column of matrix A
     * @param end_col_A   End Column of matrix A
     * @param start_row_B Start Row of matrix B
     * @param end_row_B   End Row of matrix B
     * @param start_col_B Start Column of matrix B
     * @param end_col_B   End Column of matrix B
     * @return A 2-dimensional matrix A*B
     */
    private static List<List<Integer>> multiply(List<List<Integer>> matrix1, List<List<Integer>> matrix2,
            List<List<Integer>> result1,
            int start_row_A,
            int end_row_A,
            int start_col_A,
            int end_col_A,
            int start_row_B,
            int end_row_B,
            int start_col_B,
            int end_col_B) {

        if (matrix1.size() != matrix2.size() || matrix1.get(0).size() != matrix2.get(0).size()) {
            return null;
        }

        // int n_col_A = end_col_A - start_col_A + 1;
        int n_row_A = end_row_A - start_row_A + 1;
        int n_col_B = end_col_B - start_col_B + 1;

        List<List<Integer>> result = new ArrayList<>(matrix2.get(0).size());
        for (int i = 0; i < n_row_A; i++) {
            result.add(new ArrayList<>());
        }

        // Base Case - When matrix is 1x1
        if (n_row_A == n_col_B && n_row_A == 1) {
            result.get(0).add(matrix1.get(start_row_A).get(start_col_A) * matrix2.get(start_row_B).get(start_col_B));
            return result;
        }

        int mid_row_A = (start_row_A + end_row_A) / 2;
        int mid_col_A = (start_col_A + end_col_A) / 2;
        int mid_row_B = (start_row_B + end_row_B) / 2;
        int mid_col_B = (start_col_B + end_col_B) / 2;

        List<List<Integer>> EI = multiply(matrix1, matrix2, result1,
                start_row_A,
                mid_row_A,
                start_col_A,
                mid_col_A,
                start_row_B,
                mid_row_B,
                start_col_B,
                mid_col_B);

        List<List<Integer>> FK = multiply(matrix1, matrix2, result1,
                start_row_A,
                mid_row_A,
                mid_col_A + 1,
                end_col_A,
                mid_row_B + 1,
                end_row_B,
                start_col_B,
                mid_col_B);

        List<List<Integer>> EJ = multiply(matrix1, matrix2, result1,
                start_row_A,
                mid_row_A,
                start_col_A,
                mid_col_A,
                start_row_B,
                mid_row_B,
                mid_col_B + 1,
                end_col_B);

        List<List<Integer>> FL = multiply(matrix1, matrix2, result1,
                start_row_A,
                mid_row_A,
                mid_col_A + 1,
                end_col_A,
                mid_row_B + 1,
                end_row_B,
                mid_col_B + 1,
                end_col_B);

        List<List<Integer>> GI = multiply(matrix1, matrix2, result1,
                mid_row_A + 1,
                end_row_A,
                start_col_A,
                mid_col_A,
                start_row_B,
                mid_row_B,
                start_col_B,
                mid_col_B);

        List<List<Integer>> HK = multiply(matrix1, matrix2, result1,
                mid_row_A + 1,
                end_row_A,
                mid_col_A + 1,
                end_col_A,
                mid_row_B + 1,
                end_row_B,
                start_col_B,
                mid_col_B);

        List<List<Integer>> GJ = multiply(matrix1, matrix2, result1,
                mid_row_A + 1,
                end_row_A,
                start_col_A,
                mid_col_A,
                start_row_B,
                mid_row_B,
                mid_col_B + 1,
                end_col_B);

        List<List<Integer>> HL = multiply(matrix1, matrix2, result1,
                mid_row_A + 1,
                end_row_A,
                mid_col_A + 1,
                end_col_A,
                mid_row_B + 1,
                end_row_B,
                mid_col_B + 1,
                end_col_B);

        addMatrices(EI, FK, result, 0);
        addMatrices(EJ, FL, result, 0);
        addMatrices(GI, HK, result, n_row_A / 2);
        addMatrices(GJ, HL, result, n_row_A / 2);

        return result;
    }

    /**
     * addMatrices() - For adding 2 matrices A & B
     * <ul>
     * <li>Time Complexity: θ(n^2)</li>
     * </ul>
     * 
     * @param A      First Matrix
     * @param B      Second Matrix
     * @param result Resultant Matrix in which result to be assigned
     * @param row    Row to start from
     */
    private static void addMatrices(List<List<Integer>> A, List<List<Integer>> B,
            List<List<Integer>> result, int row) {

        int n = A.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result.get(row + i).add(A.get(i).get(j) + B.get(i).get(j));
            }
        }
    }

    private static void print(String display, List<List<Integer>> matrix,
            int start_row, int start_column, int end_row,
            int end_column) {
        System.out.println("\n" + display + "\n");
        for (int i = start_row; i <= end_row; i++) {
            for (int j = start_column; j <= end_column; j++) {
                System.out.print(matrix.get(i).get(j) + "\t");
            }
            System.out.println();
        }
        System.out.println();
        return;
    }

    private static void solve(int t1, InputReader in) {

        int dim = in.readInt();
        List<List<Integer>> A = new ArrayList<>(dim);
        List<List<Integer>> B = new ArrayList<>(dim);

        for (int i = 0; i < dim; i++) {
            A.add(new ArrayList<>());
            for (int j = 0; j < dim; j++) {
                A.get(i).add(in.readInt());
            }
        }

        for (int i = 0; i < dim; i++) {
            B.add(new ArrayList<>());
            for (int j = 0; j < dim; j++) {
                B.get(i).add(in.readInt());
            }
        }

        List<List<Integer>> result = new ArrayList<>(B.get(0).size());
        for (int i = 0; i < dim; i++) {
            result.add(new ArrayList<>());
        }

        result = multiply(A, B, result, 0, A.size() - 1, 0, A.size() - 1, 0, B.size() - 1, 0, B.size() - 1);
        print("Array " + t1 + " is: ", result, 0, 0, result.size() - 1, result.size() - 1);
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

/********************************************
 * Test Cases
 * ******************************************
 * 
 * 2
 * 
 * 4
 * 5 7 9 10
 * 2 3 3 8
 * 8 10 2 3
 * 3 3 4 8
 * 
 * 3 10 12 18
 * 12 1 4 9
 * 9 10 12 2
 * 3 12 4 10
 * 
 * 8
 * 5 7 9 10 2 5 6 8
 * 2 3 3 8 4 5 6 3
 * 8 10 2 3 7 4 5 6
 * 3 3 4 8 8 7 9 6
 * 1 2 5 4 9 12 10 15
 * 12 11 2 5 6 8 6 5
 * 2 2 5 6 7 8 9 4
 * 19 28 15 6 4 5 6 8
 * 
 * 3 10 12 18 8 7 6 6
 * 12 1 4 9 1 2 5 3
 * 9 10 12 2 4 7 8 9
 * 3 12 4 10 21 5 65 4
 * 1 2 3 8 5 9 8 4
 * 6 8 7 6 3 8 8 7
 * 25 22 1 2 3 55 6 5
 * 12 2 55 8 5 9 8 7
 *
 * 
 */

/********************************************
 * Output
 * ******************************************
 * 
 * Array 1 is:
 * 
 * 210 267 236 271
 * 93 149 104 149
 * 171 146 172 268
 * 105 169 128 169
 * 
 * 
 * Array 2 is:
 * 
 * 488 459 723 393 376 622 943 301
 * 313 335 322 247 267 514 703 182
 * 399 314 556 406 237 529 475 231
 * 452 451 540 341 329 772 807 263
 * 595 474 1042 370 300 928 664 348
 * 465 429 587 517 317 638 656 288
 * 421 428 422 278 270 741 658 244
 * 826 636 1037 822 459 802 936 494
 *
 * 
 */