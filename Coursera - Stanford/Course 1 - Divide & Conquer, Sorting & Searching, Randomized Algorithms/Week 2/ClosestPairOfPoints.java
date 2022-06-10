import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.InputMismatchException;
import java.util.List;

import static java.lang.Math.min;
import static java.lang.Math.sqrt;
import static java.lang.Math.ceil;
import java.util.stream.Collectors;

public class ClosestPairOfPoints {

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
     * Data Structure to store a point (x,y)
     */
    private static class Point {
        int x;
        int y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public int getx() {
            return this.x;
        }

        public int gety() {
            return this.y;
        }

        @Override
        public String toString() {
            return "(" + this.x + ", " + this.y + ")";
        }

    }

    /**
     * Data Structure to store a pair of points P1(x1,y1) and P2(x2,y2)
     */
    private static class ClosestPointsSet {
        Point P1;
        Point P2;

        public ClosestPointsSet() {
            this.P1 = null;
            this.P2 = null;
        }

        public void setP1(Point P1) {
            this.P1 = P1;
        }

        public void setP2(Point P2) {
            this.P2 = P2;
        }

        public Point getP1() {
            return this.P1;
        }

        public Point getP2() {
            return this.P2;
        }

        public double getDelta() {
            return euclidianDistance(this.P1, this.P2);
        }

        public boolean isEmpty() {
            return (this.P1 == null && this.P2 == null);
        }
    }

    /**
     * ClosestSplitPair() - For calculating the closest split pair of points
     * in the band (x̄ - δ) and (x̄ + δ), where x̄ is the median of x-coordinates
     * and δ is the minimum of euclidian distances computed at left and right 
     * sides of the line x = x̄.
     * <ul>
     * <li>Time Complexity: O(n)</li>
     * </ul>
     * @param P_x All Points sorted by x-coordinates
     * @param P_y All Points sorted by y-coordinates
     * @param delta (δ) Min of euclidian distances computed at left and right sides
     * @return ClosestPointsSet
     */
    private static ClosestPointsSet ClosestSplitPair(List<Point> P_x, List<Point> P_y,
            double delta) {

        // S_y => Only those points that lie within the band x̄ - δ and x̄ + δ,
        // sorted by y-coordinates
        List<Point> S_y = new ArrayList<>();

        int n = P_x.size();
        int x_bar_index = (int) ceil((double) n / 2) - 1;
        int x_bar = P_x.get(x_bar_index).getx();

        for (Point p : P_y) {
            if (x_bar - delta >= p.getx() && p.getx() < x_bar + delta) {
                S_y.add(p);
            }
        }

        ClosestPointsSet closestPointsSet = new ClosestPointsSet();
        double minDelta;
        for (int i = 0; i < S_y.size(); i++) {
            for (int j = i + 1; j < min(7, S_y.size() - i); j++) {
                minDelta = euclidianDistance(S_y.get(i), S_y.get(j));
                if (minDelta < delta) {
                    closestPointsSet.setP1((S_y.get(i)));
                    closestPointsSet.setP2(S_y.get(j));
                }
            }
        }

        return closestPointsSet;
    }

    /**
     * ClosestPair() - For calculating the 2 points in the 2-D Plane with the
     * smallest Euclidian Distance between them
     * <ul>
     * <li>Recurrence: T(n) ≤ 2T(n/2) + cn</li>
     * <li>Time Complexity: O(nlogn)
     * </ul>
     * @param P_x All Points sorted by x-coordinates
     * @param P_y All Points sorted by y-coordinates
     * @return closestPointsSet Set of closest points found in the ClosestPair()
     */
    private static ClosestPointsSet ClosestPair(List<Point> P_x, List<Point> P_y) {

        // x_bar (x̄) => Median of x-coordinates in the 2-D Plane
        int n = P_x.size();

        if (n <= 3) {
            return bruteForceFind(P_x);
        }

        int x_bar_index = (int) ceil((double) n / 2) - 1;
        int x_bar = P_x.get(x_bar_index).getx();

        List<Point> L_x = P_x.subList(0, x_bar_index + 1);
        List<Point> R_x = P_x.subList(x_bar_index + 1, P_x.size());

        List<Point> L_y = new ArrayList<>();
        List<Point> R_y = new ArrayList<>();

        for (int i = 0; i < P_y.size(); i++) {
            if (P_y.get(i).getx() <= x_bar) {
                L_y.add(P_y.get(i));
            } else {
                R_y.add(P_y.get(i));
            }
        }

        ClosestPointsSet closestPointsSet = new ClosestPointsSet();
        ClosestPointsSet closestSplitPairPts_left = new ClosestPointsSet();
        ClosestPointsSet closestSplitPairPts_right = new ClosestPointsSet();
        ClosestPointsSet closestSplitPairPts_split = new ClosestPointsSet();

        // Conquer Left
        closestSplitPairPts_left = ClosestPair(L_x, L_y);
        // Conquer Right
        closestSplitPairPts_right = ClosestPair(R_x, R_y);

        double delta;
        double delta_l = closestSplitPairPts_left.getDelta();
        double delta_r = closestSplitPairPts_right.getDelta();

        if (delta_l > delta_r) {
            delta = delta_r;
            closestPointsSet = closestSplitPairPts_right;
        } else {
            delta = delta_l;
            closestPointsSet = closestSplitPairPts_left;
        }

        // Conquer Split
        closestSplitPairPts_split = ClosestSplitPair(P_x, P_y, delta);

        if (!closestSplitPairPts_split.isEmpty()) {
            closestPointsSet = closestSplitPairPts_split;
        }

        return closestPointsSet;

    }

    /**
     * bruceForceFind() - Finds the shortest Euclidian Distance between n<=3 points;
     * Used in the Base Case for ClosestPair()
     * <ul>
     * <li>Time Complexity: O(1)</li>
     * </ul>
     * @param P List of points with size no more than 3
     * @return ClosestPointsSet Set of 2 points having shortest Euclidian Distance
     * between them
     */
    private static ClosestPointsSet bruteForceFind(List<Point> P) {

        double delta = Double.MAX_VALUE;
        ClosestPointsSet closestPointsSet = new ClosestPointsSet();
        for (int i = 0; i < P.size(); i++) {
            for (int j = i + 1; j < P.size(); j++) {
                double currentDelta = euclidianDistance(P.get(i), P.get(j));
                if (currentDelta < delta) {
                    delta = currentDelta;
                    closestPointsSet.setP1(P.get(i));
                    closestPointsSet.setP2(P.get(j));
                }
            }
        }
        return closestPointsSet;
    }

    /**
     * euclidianDistance() - Finds the Euclidian Distance between the 2 points p1 & p2;
     * Takes constant time
     * @param p1 Point p1
     * @param p2 Point p2
     * @return double Euclidian Distance between p1 & p2
     */
    private static double euclidianDistance(Point p1, Point p2) {
        return sqrt(Math.pow(p2.getx() - p1.getx(), 2) + Math.pow(p2.gety() - p1.gety(), 2));
    }

    private static void solve(int t1, InputReader in) {

        int n = in.readInt();

        List<Point> P = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            int x = in.readInt();
            int y = in.readInt();
            P.add(new Point(x, y));
        }

        // P_x => Points sorted by x-axis
        List<Point> P_x = P.stream().sorted(Comparator.comparing(Point::getx)).collect(Collectors.toList());
        
        // P_y => Points sorted by y-axis
        List<Point> P_y = P.stream().sorted(Comparator.comparing(Point::gety)).collect(Collectors.toList());

        ClosestPointsSet closestPointsSet = ClosestPair(P_x, P_y);
        System.out.println("\nClosest Distance for Test Case " + t1 +": " + closestPointsSet.getDelta());
        System.out.println("Point 1: " + closestPointsSet.getP1().toString());
        System.out.println("Point 2: " + closestPointsSet.getP2().toString());
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

6
2 3
12 30
40 50
5 1
12 10
3 4

5
4 6
1 3
2 1
12 13
28 56

7
0 0
-2 0
4 0
1 1
3 3
-2 2
5 2

 *
 * 
 */


/********************************************
 * Output
 * ******************************************
 *

Closest Distance for Test Case 1: 1.4142135623730951
Point 1: (2, 3)
Point 2: (3, 4)

Closest Distance for Test Case 2: 2.23606797749979
Point 1: (1, 3)
Point 2: (2, 1)

Closest Distance for Test Case 3: 1.4142135623730951
Point 1: (0, 0)
Point 2: (1, 1)

 * 
 * 
 */