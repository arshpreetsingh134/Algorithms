// Detecting a cycle within a graph using Union-Find

public class Union {

    int v, e;       //Vertices and Edges
    class Edge{
        int src, dest;
    }

    Edge edge[];        //To keep track of edges in a graph

    Union(int v, int e){
        this.v=v;
        this.e=e;
        edge = new Edge[e];
        for(int i=0; i<e; i++) edge[i]=new Edge();
    }

    //For finding parent set of a value
    int find(int parent[], int p){
        if(parent[p]==-1)
            return p;
        return find(parent, parent[p]);
    }

    //For performing union of two sets
    void union(int parent[], int x, int y){
        int xset = find(parent, x);
        int yset = find(parent, y);
        if(xset!=yset)
            parent[xset] = yset;
    }

    boolean isCycle(Union graph){
        int parent[] = new int[graph.v];    //For creating v subsets

        for(int i=0; i<graph.v; i++){
            parent[i]=-1;
        }

        for(int i=0; i<graph.e; i++) {
            int x = graph.find(parent, graph.edge[i].src);
            int y = graph.find(parent, graph.edge[i].dest);
            if (x == y)
                return true;

            union(parent, x, y);
        }
        return false;

    }

    public static void main(String[] args) {

        /* Let us create the following graph
         0
        |  \
        |    \
        1-----2 */

        int v=3, e=2;
        Union graph = new Union(v,e);

        //0-1 edge
        graph.edge[0].src=0;
        graph.edge[0].dest=1;

        //1-2 edge
        graph.edge[1].src=1;
        graph.edge[1].dest=2;

        //2-0 edge
        //graph.edge[2].src=2;
        //graph.edge[0].dest=0;

        if(graph.isCycle(graph))
            System.out.println("Graph has a cycle");
        else
            System.out.println("Graph doesn't have a cycle.");
    }
}
