import java.io.IOException;
import java.util.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.Map.Entry;
import java.util.HashMap;
import java.util.Set;
import java.io.*;

class Edge implements Comparable<Edge>
{
    int u;      // src
    int v;      // dest
    int weight; // weight of the edge

    public Edge(int u, int v, int weight)
    {
        this.u = u;
        this.v = v;
        this.weight = weight;
    }

    public String toString()
    {
        return "Edge: "+ u + " - " + v + " | " + weight;
    }

    // If current edge is longer than other edge,
    // return +ve else -ve
    public int compareTo(Edge another)
    {
        return this.weight-another.weight;
    }
};

class UnionFind
{
    class UFNode
    {
        int parent;
        int rank;

        UFNode(int parent, int rank)
        {
            this.parent = parent;
            this.rank = rank;
        }
    }

    private UFNode[] nodes;
    private int V;          // No. of vertices in the graph
    private int count;      // For keeping track of no. of clusters

    public UnionFind(int V)
    {
        if(V<0)
            throw new IllegalArgumentException();

        this.V = V;
        nodes = new UFNode[V];
        
        for(int i=0; i<V; i++)
            nodes[i] = new UFNode(i, 0);

        this.count = V;         // Initially, there are V clusters, each containing one vertex
    }

    // Find the parent of a given vertex recursively
    public int Find(int u)
    {
        if(u<0 || u>=nodes.length)
            throw new IndexOutOfBoundsException();

        if(nodes[u].parent!=u)
            nodes[u].parent = Find(nodes[u].parent);

        return nodes[u].parent;
    }

    // Perform Union of 2 Clusters
    public void Union(int u, int v)
    {
        u = Find(u);
        v = Find(v);

        if(u!=v)
        {
            if(nodes[u].rank < nodes[v].rank)
            {
                int temp = u;
                u = v;
                v = temp;
            }

            nodes[v].parent = u;

            if(nodes[u].rank==nodes[v].rank)
                nodes[u].rank++;
        }
        count--;
    }

    public int getClusters()
    {
        return count;
    }

    public boolean isConnected(int u, int v)
    {
        return (Find(u) == Find(v));
    }

    private void printClusterUtil(Set<Entry<Integer, ArrayList<Integer>>> set)
    {
        System.out.println("Following is the cluster :-\n{");
        for(Map.Entry<Integer, ArrayList<Integer>> entry:  set)
        {
            int key = entry.getKey();
            System.out.print("   "+key+": [ ");
            ArrayList<Integer> val = entry.getValue();

            for(int i: val)
            {
                System.out.print(i + ",");
            }
            System.out.print(" ]\n");
        }
        System.out.println("}");
    }

    public void printCluster()
    {
        Map<Integer, ArrayList<Integer>> leaders = new HashMap<Integer, ArrayList<Integer>>();

        for(int i=0; i<nodes.length; i++)
            leaders.put(nodes[i].parent, null);

        for(int i=0; i<V; i++)
        {
            int leader = Find(i);
            ArrayList<Integer> leaderList = leaders.get(Find(i));

            if(leaderList==null)
                leaderList = new ArrayList<Integer>();

            leaderList.add(i);
            leaders.put(leader, leaderList);
        }

        Set<Map.Entry<Integer, ArrayList<Integer>>> set=leaders.entrySet();
  
        printClusterUtil(set);
    }
}

public class KMeans1
{
    private int V;
    private int E;
    private int maxClusterDistance;

    private List<Edge> edges;

    KMeans1(int V, int E)
    {
        this.V = V;
        this.E = E;

        edges = new ArrayList<Edge>();
    }

    public int getMaxSpacing(int clusterCount)
    {
        Collections.sort(edges);

        UnionFind uf = new UnionFind(V);

        if(clusterCount>uf.getClusters())
        {
            try
            {
                throw new Exception("Present Cluster Counter is less than input.");
            }
            catch(Exception e)
            {
                System.out.println(e.getMessage());
            }
        }

        else
        {
            for(int i=0; i<E; i++)
            {
                Edge edge = edges.get(i);

                if(!uf.isConnected(edge.u, edge.v))
                {
                    if(uf.getClusters()==clusterCount)
                    {
                        //uf.printCluster();
                        return maxClusterDistance=edge.weight;
                    }

                    int v1 = uf.Find(edge.u);
                    int v2 = uf.Find(edge.v);
                    uf.Union(v1,v2);
                }

            }
        }
        return -1;
    }

    public static void main(String[] args) throws IOException
    {
        KMeans1 graph = new KMeans1(500, 124750);
        
        FileInputStream fstream = new FileInputStream("clustering.txt");
        DataInputStream in = new DataInputStream(fstream);
        BufferedReader br = new BufferedReader(new InputStreamReader(in));
        String data;
        
        while ((data = br.readLine()) != null)
        {
            int tempArr[] = new int[3];
            String[] tmp = data.split(" ");
            int i = 0;
            for(String s:tmp)
            {
                tempArr[i] = Integer.parseInt(s);
                i++;
            }
            graph.edges.add(new Edge(tempArr[0]-1, tempArr[1]-1, tempArr[2]));
        }
        
        int k = 4;      // Max no. of clusters needed
        
        graph.maxClusterDistance = graph.getMaxSpacing(k);

        if(graph.maxClusterDistance!=-1)
            System.out.println("Maximum Cluster Spacing for a " + k + "-clustering is: " + graph.maxClusterDistance);
        else
            System.out.println("Something went Wrong");

        br.close();
    }
}
