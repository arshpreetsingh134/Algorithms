import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;

public class StrassenMatrixMultiplication {

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
     * strassenMultiply() - For multiplying 2 arrays A & B;
     * Dimensions (nxn) of 2 arrays must be equal and must be
     * a power of 2.
     * <ul>
     * <li>Recurrence Relation:
     * T(n) = {c (if n=1) ;
     * 7x T(n/2) + dxn^2 (otherwise) }
     * where c and d are constants
     * <li>Time Complexity: O(n^log7) = O(n^2.8074)</li>
     * <li>Space Complexity: O(n^2)</li>
     * </ul>
     * 
     * @param matrix1
     * @param matrix2
     * @return Resultant Matrix
     */
    private static List<List<Integer>> strassenMultiply(List<List<Integer>> matrix1, List<List<Integer>> matrix2) {

        // For Matrix Multiplication, 1st matrix's columns must be equal to
        // 2nd matrix's rows
        if (matrix1.get(0).size() != matrix2.size()) {
            return null;
        }

        // (i x k) * (k x j) ==> (i x j)
        int i = matrix1.size();
        int j = matrix2.get(0).size();
        int k = matrix1.get(0).size();

        List<List<Integer>> result = new ArrayList<>(i);
        for (int count = 0; count < i; count++) {
            result.add(new ArrayList<>());
        }

        // Base Case - When matrices are 1 x 1
        if (i == k && i == 1 && j == 1) {
            result.get(0).add(matrix1.get(i - 1).get(k - 1) * matrix2.get(k - 1).get(j - 1));
            return result;
        }

        int mid_row_A = (i - 1) / 2;
        int mid_col_A = (k - 1) / 2;
        int mid_row_B = (k - 1) / 2;
        int mid_col_B = (j - 1) / 2;

        List<List<Integer>> A = getSubMatrix(matrix1, 0, mid_row_A,
                0, mid_col_A);
        List<List<Integer>> B = getSubMatrix(matrix1, 0, mid_row_A,
                mid_col_A + 1, k - 1);
        List<List<Integer>> C = getSubMatrix(matrix1, mid_row_A + 1, i - 1,
                0, mid_col_A);
        List<List<Integer>> D = getSubMatrix(matrix1, mid_row_A + 1, i - 1,
                mid_col_A + 1, k - 1);
        List<List<Integer>> E = getSubMatrix(matrix2, 0, mid_row_B,
                0, mid_col_B);
        List<List<Integer>> F = getSubMatrix(matrix2, 0, mid_row_B,
                mid_col_B + 1, j - 1);
        List<List<Integer>> G = getSubMatrix(matrix2, mid_row_B + 1, k - 1,
                0, mid_col_B);
        List<List<Integer>> H = getSubMatrix(matrix2, mid_row_B + 1, k - 1,
                mid_col_B + 1, j - 1);

        // P1 = A(F-H)
        List<List<Integer>> P1 = strassenMultiply(A, subtractMatrices(F, H));

        // P2 = (A+B)H
        List<List<Integer>> P2 = strassenMultiply(addMatrices(A, B), H);

        // P3 = (C+D)E
        List<List<Integer>> P3 = strassenMultiply(addMatrices(C, D), E);

        // P4 = D(G-E)
        List<List<Integer>> P4 = strassenMultiply(D, subtractMatrices(G, E));

        // P5 = (A+B)(E+H)
        List<List<Integer>> P5 = strassenMultiply(addMatrices(A, D), addMatrices(E, H));

        // P6 = (B-D)(G+H)
        List<List<Integer>> P6 = strassenMultiply(subtractMatrices(B, D), addMatrices(G, H));

        // P7 = (A-C)(E+F)
        List<List<Integer>> P7 = strassenMultiply(subtractMatrices(A, C), addMatrices(E, F));

        /**
         * All of the following matrices will have dimensions (i/2,j/2)
         */

        // Q1 = P5+P4-P2+P6
        List<List<Integer>> Q1 = addMatrices(subtractMatrices(addMatrices(P5, P4), P2), P6);
        // Q2 = P1+P2
        List<List<Integer>> Q2 = addMatrices(P1, P2);
        // Q3 = P3+P4
        List<List<Integer>> Q3 = addMatrices(P3, P4);
        // Q4 = P1+P5-P3-P7
        List<List<Integer>> Q4 = subtractMatrices(subtractMatrices(addMatrices(P1, P5), P3), P7);

        // Fit the above 4 quadrants into the n x n "result" matrix
        fitResult(result, Q1, Q2, Q3, Q4, i, j);

        return result;

    }

    private static void fitResult(List<List<Integer>> result, List<List<Integer>> Q1,
            List<List<Integer>> Q2, List<List<Integer>> Q3, List<List<Integer>> Q4, int i, int j) {

        // Insert Q1
        int count = 0;
        for (int k = 0; k < i / 2; k++) {
            for (int l = 0; l < j / 2; l++) {
                result.get(count).add(Q1.get(k).get(l));
            }
            count++;
        }

        // Insert Q2
        count = 0;
        for (int k = 0; k < i / 2; k++) {
            for (int l = 0; l < j / 2; l++) {
                result.get(count).add(Q2.get(k).get(l));
            }
            count++;
        }

        // Insert Q3
        count = i / 2;
        for (int k = 0; k < i / 2; k++) {
            for (int l = 0; l < j / 2; l++) {
                result.get(count).add(Q3.get(k).get(l));
            }
            count++;
        }

        // Insert Q4
        count = i / 2;
        for (int k = 0; k < i / 2; k++) {
            for (int l = 0; l < j / 2; l++) {
                result.get(count).add(Q4.get(k).get(l));
            }
            count++;
        }
    }

    /**
     * addMatrices(), subtractMatrices() -
     * For adding/subtracting two matrices A & B
     * <ul>
     * <li>Time Complexity: θ(n^2)</li>
     * </ul>
     * 
     * @param A First Matrix
     * @param B Second Matrix
     * @return Resultant Matrix
     */
    private static List<List<Integer>> addMatrices(List<List<Integer>> A, List<List<Integer>> B) {

        int n = A.size();
        List<List<Integer>> result = new ArrayList<>(n);

        for (int i = 0; i < n; i++) {
            result.add(new ArrayList<>());
            for (int j = 0; j < n; j++) {
                result.get(i).add(A.get(i).get(j) + B.get(i).get(j));
            }
        }

        return result;
    }

    private static List<List<Integer>> subtractMatrices(List<List<Integer>> A, List<List<Integer>> B) {

        int n = A.size();
        List<List<Integer>> result = new ArrayList<>(n);

        for (int i = 0; i < n; i++) {
            result.add(new ArrayList<>());
            for (int j = 0; j < n; j++) {
                result.get(i).add(A.get(i).get(j) - B.get(i).get(j));
            }
        }

        return result;
    }

    /**
     * getSubMatrix() - For getting sub-matrix of
     * two matrices A & B
     * <ul>
     * <li>Time Complexity: θ(n^2)</li>
     * </ul>
     * 
     * @param A         Matrix
     * @param start_row Start Row of sub-matrix B
     * @param end_row   End Row of sub-matrix B
     * @param start_col Start Column of sub-matrix B
     * @param end_col   End Column of sub-matrix B
     * @return B Resultant Sub-Matrix
     */
    private static List<List<Integer>> getSubMatrix(List<List<Integer>> A,
            int start_row,
            int end_row,
            int start_col,
            int end_col) {

        int n = end_row - start_row + 1;
        int count = 0;

        List<List<Integer>> B = new ArrayList<>(n);
        for (int i = start_row; i <= end_row; i++) {
            B.add(new ArrayList<>());
            for (int j = start_col; j <= end_col; j++) {
                B.get(count).add(A.get(i).get(j));
            }
            count++;
        }

        return B;
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
        result = strassenMultiply(A, B);
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
3

2
8 10
6 3

5 7
9 15

4
5 7 9 10
2 3 3 8
8 10 2 3
3 3 4 8
 
3 10 12 18
12 1 4 9
9 10 12 2
3 12 4 10
 
8
5 7 9 10 2 5 6 8
2 3 3 8 4 5 6 3
8 10 2 3 7 4 5 6
3 3 4 8 8 7 9 6
1 2 5 4 9 12 10 15
12 11 2 5 6 8 6 5
2 2 5 6 7 8 9 4
19 28 15 6 4 5 6 8
 
3 10 12 18 8 7 6 6
12 1 4 9 1 2 5 3
9 10 12 2 4 7 8 9
3 12 4 10 21 5 65 4
1 2 3 8 5 9 8 4
6 8 7 6 3 8 8 7
25 22 1 2 3 55 6 5
12 2 55 8 5 9 8 7

 *
 * 
 */

/********************************************
 * Output
 * ******************************************
 *
Array 1 is:
 
130 206
57 87

 
Array 2 is:
 
210 267 236 271
93 149 104 149
171 146 172 268
105 169 128 169
 
 
Array 3 is:
 
488 459 723 393 376 622 943 301
313 335 322 247 267 514 703 182
399 314 556 406 237 529 475 231
452 451 540 341 329 772 807 263
595 474 1042 370 300 928 664 348
465 429 587 517 317 638 656 288
421 428 422 278 270 741 658 244
826 636 1037 822 459 802 936 494

 * 
 * 
 */