import java.io.*;
import java.util.*;


// class UnionFind same as that implemented in "KMeans.java"

class BigClustering
{
    // Loading the labels of vertices from a file
    private static String[] loadLabelsFromFile(String filename)
    {
        Scanner reader = null;

        // Open the file for reading
        try{
            reader = new Scanner(new File(filename));
        } catch (FileNotFoundException e) {
            System.err.println("Error: File not found");
            e.printStackTrace();
            return null;
        }

        // Get the no. of vertices
        int V = reader.hasNextInt()? reader.nextInt():0;
        int bits = reader.hasNextInt()?reader.nextInt():0;

        // Clear buffer till the end of line
        reader.nextLine();

        // List of all labels
        String[] labels = new String[V];

        for(int i=0; i<V; i++)
        {
            String line = reader.nextLine();
            char[] characters = line.toCharArray();

            // Remove all spaces from the character array of bits
            StringBuilder sb = new StringBuilder();
            for(char c:characters)
                if(!Character.isSpaceChar(c))
                    sb.append(c);

            // Add the label of bits to our list of labels
            labels[i] = sb.toString();
        }

        reader.close();
        return labels;
    }

    // Get only the unique labels
    private static ArrayList<String> getUniqueLabels(String filename)
    {
        String[] labels = loadLabelsFromFile(filename);

        if(labels==null) return null;

        // Sort the labels
        Arrays.sort(labels);

        // Create an arrayList to hold onto the unique labels
        ArrayList<String> uniqueLabels = new ArrayList<String>();

        uniqueLabels.add(labels[0]);

        for(int i=1; i<labels.length; i++)
        {
            while(labels[i].equals(labels[i-1]))
                i++;
            uniqueLabels.add(labels[i]);
        }
        return uniqueLabels;
    }

    // Returns the total no. of combinations when choosing k elements out of n
    private static int getNChooseK(int n, int k)
    {
        int result =1;

        for(int i=0; i<k; i++)
            result = (result * (n-i))/(k+i);

        return result;
    }

// Returns the inverted character (0 or 1) for the given character. 
  private static char invertBit(char bit) throws IllegalArgumentException 
  {
    switch (bit) 
    {
      case '0':
        return '1';
      case '1':
        return '0';
      default:
        throw new IllegalArgumentException();
    }
  }

   /** Utility function for generating inverted permutations of a binary string. */
  private static void generateCombinationsUtil(
      char[] characters, int startIndex, int bitsToInvert, ArrayList<String> combinations) {
    if (bitsToInvert == 0) return;

    for (int i = startIndex; i <= characters.length - bitsToInvert; i++) {
      // Invert the bit at current position.
      characters[i] = invertBit(characters[i]);

      // Generate combinations starting from the next index but with one less bit inverted.
      generateCombinationsUtil(characters, i + 1, bitsToInvert - 1, combinations);

      // Add to the list of combinations.
      if (bitsToInvert == 1) combinations.add(new String(characters));

      // Invert back the bit at the current position.
      characters[i] = invertBit(characters[i]);
    }
  }

  /** Generates inverted permutations of a binary string with `k` bits inverted. */
  private static ArrayList<String> generateCombinations(String string, int k) {
    // Calculate the total number of combinations that can be produced.
    int totalCombos = getNChooseK(string.length(), k);

    // Create a list for holding the combinations.
    ArrayList<String> combinations = new ArrayList<String>(totalCombos);

    // Generate the combinations.
    generateCombinationsUtil(string.toCharArray(), 0, k, combinations);

    return combinations;
  }

  /** Returns the maximum number of clusters that can be formed while ensuring the given spacing. */
  private static int getMaxClusters(ArrayList<String> vertices, int spacing) {
    // Create a hash table and hash all labels.
    HashMap<String, Integer> hashTable = new HashMap<String, Integer>(vertices.size());

    for (int i = 0; i < vertices.size(); i++) hashTable.put(vertices.get(i), i);

    // Initialize a UnionFind.
    UnionFind uf = new UnionFind(vertices.size());

    // Initially, the number of clusters will be the same as total vertices.
    int numClusters = vertices.size();

    // Start grouping vertices, starting from the shortest edges.
    for (int i = 1; i < spacing; i++) {

      for (int j = 0; j < vertices.size(); j++) {
        // Get the possible candidate vertices that are at distance `i + 1` away from the current
        // vertex.
        ArrayList<String> possibleLabels = generateCombinations(vertices.get(j), i);

        for (String label : possibleLabels) {
          // If a vertex with this label exists, then find which cluster it belongs to.
          if (hashTable.containsKey(label)) {
            int vertex = hashTable.get(label);

            // Merge the two clusters if they aren't merged already.
            if (uf.Find(j) != uf.Find(vertex)) {
              // Everytime two clusters are merged, total number of clusters gets reduced by 1.
              numClusters--;
              uf.Union(j, vertex);
            }
          }
        }
      }
    }

    return numClusters;
  }


  public static void main(String[] args) {

    // Get the inputs.
    String fileName = "clustering_big.txt";
    int spacing = 3;

    // Benchmarks.
    double timeLoadingLabels = 0.0;
    double timeFindingMaxClusters = 0.0;

    // Load the labels and benchmark the time taken.
    double startTime = System.nanoTime();
    ArrayList<String> labels = getUniqueLabels(fileName);
    timeLoadingLabels = (System.nanoTime() - startTime) / 1000000.0;
    if (labels == null) {
      System.err.println("Could not load labels");
      System.exit(3);
    }

    // Get the max number of clusters for a given spacing and benchmark the time taken.
    startTime = System.nanoTime();
    int maxClusters = getMaxClusters(labels, spacing);
    timeFindingMaxClusters = (System.nanoTime() - startTime) / 1000000.0;

    System.out.println("Max clusters: " + maxClusters + "\n");

    // Display the benchmark results.
    System.out.printf("TIME IN loading labels:           %8.2fms\n", timeLoadingLabels);
    System.out.printf("TIME IN finding the max clusters: %8.2fms\n", timeFindingMaxClusters);
  }
}