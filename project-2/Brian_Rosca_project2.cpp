#include <functional>
#include <limits.h>
#include <random>
#include <iostream>
#include <queue>

// be sure to change FIRSTNAME and LASTNAME with your own first and last name
#include "Brian_Rosca_project2.h"

using namespace std;

/****************
 * INSTRUCTIONS *
 ****************
 *
 * - Replace all instances of "Firstname_Lastname" with your firstname and
 *   your last name. This include the .h and .cpp files, along with the
 *   header guards at the top of the .h file.
 *
 * - Implement the appropriate algorithms as described below.
 *   You must follow the specifications as written below.
 *
 * - Certain function signatures may not be modified (as it will affect auto
 *   grading). These functions will be specified.
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Lastname_project2.h."
 *
 * - The file "testing.cpp" has various functions you can utilize to test
 *   your code. You can also add your own tests!
 *
 * - If you are working in a group, please modify the comments directly below.
 *   
 * - IMPORTANT: If you are working in a group, every member is expected to submit their
 *   source code individually.
 *
 */


/*** GROUP PROJECT ***/
// Please list ALL of your other group members as comments below.
//   Member 1: Victoria Rossi
//   Member 2: Mauricio Alvarez



/*** PART 1: Hashing ***/

/* Birthday Attack 1
 *
 * 10 Points
 *
 * In this problem, you will implement a birthday attack on a simple hash function that is provided
 * in the header file. The goal will be to find a collision in the hash function using the Birthday 
 * Attack (with at least a 50% chance of success).
 *
 * Assumptions
 * - The hash function will have a 16 bit output (2 bytes). We will use the `unsigned short` type
 *   as the output type to make things simple.
 * - The hash function will take `unsigned integers` as input, again to make things simple.
 * - Your function will output:
 *     (a) two inputs a and b such that h(a) = h(b) (a collision), as a list [a, b], or 
 *     (b) {} if no collision is found.
 *   The output type of the function will be `vector<unsigned int>`.
 *
 * Algorithm Description
 * - Do the following a small constant number of times (at least 2):
 *     - Randomly generate 350 unsigned integers. Feel free to use the provided helper function
 *       `sample_int()`.
 *     - For each of the generated integers:
 *         - Hash the integer
 *         - Check if you find a collision. If yes, you can stop and output the two colliding inputs.
 * - If no collision is found, output {} (an empty list).
 *
 * Hash Function Signature
 *   unsigned short test_hash(unsigned int input);
 *
 */

unsigned int sample_int() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned int> dist(0);
    return dist(mt);
}

unsigned short test_hash(unsigned int input) {
    const unsigned int a = 3177205741;
    const unsigned int b = 2371597069;
    return static_cast<unsigned short>(a*input + b);
}

// Do not modify this function signature. 
vector<unsigned int> birthday_attack_1(function<unsigned short(unsigned int)> hash_function) {
    // Here, hash_function is an actual function. To test this function with
    // the provided `test_hash`, you can call your function in main as:
    //     vector<long> out = birthday_attack_1(test_hash);
    // Note you can implement your own test hash functions so long as their 
    // signatures match the `test_hash` function signature.
    std::unordered_map<unsigned short, unsigned int> collided;
    for (int i = 0; i < 10; ++i){
        for (int j = 0; j < 350; ++i){
            unsigned int x = sample_int();
            unsigned short hashed = hash_function(x);
            // check table, if its there, return the collision and the current number
            if (collided.find(hashed) != collided.end()) return {collided[hashed], x};
            // if no return, add it 
            collided[hashed] = x;
        }
    }
    return {};
}



/* Birthday Attack 2
 *
 * 5 Points
 *
 * In this problem, you will implement a slightly different birthday attack on a simple 
 * hash function that is provided in the header file. The birthday attack described in 
 * part 1 above has the drawback of potentially needing too much space to implement
 * (proportional to sqrt(hash_output_domain_size)). You will address this in this
 * problem.
 *
 * The birthday-type attack you will implement in this problem is known as "Floyd's
 * tortoise and hare algorithm" (which is actually just a cycle finding algorithm).
 * We'll use it to implement a small-space birthday attack.
 *
 * Assumptions
 * - The hash function will have a 16 bit output (2 bytes). We will use the `unsigned short` type
 *   as the output type to make things simple.
 * - The hash function will take `unsigned integers` as input, again to make things simple.
 * - Your function will output two inputs a and b such that h(a) = h(b) (a collision), as a list [a, b].
 *
 * Algorithm Description
 * - Maintain two values, `tort` and `hare`, initialized as 
 *   tort = hash(0) and hare = hash(hash(0)).
 * - While tort != hare, take "one-step" with tort and "two-steps" with hare.
 *   This means updating tort by hashing the previous value of tort once, and hare
 *   by computing the double hash of the previous value of hare (see the initialization
 *   as an example).
 * - Once tort == hare, reset tort = 0.
 * - Now, while hash(tort) != hash(hare) take "one-step" with
 *   both tort and hare, until hash(tort) == hash(hare).
 * - Output [tort, hare]
 *
 * Additional Resources
 * - The following lecture notes explain both birthday attack algorithms:
 *      https://people.cs.uchicago.edu/~davidcash/284-autumn-21/12-hash.pdf
 *
 * Hash Function Signature
 *   unsigned short test_hash(unsigned int input);
 */

// Do not modify this function signature. 
vector<unsigned int> birthday_attack_2(function<unsigned short(unsigned int)> hash_function) {
    // Here, hash_function is an actual function. To test this function with
    // the provided `test_hash`, you can call your function in main as:
    //     vector<unsigned int> out = birthday_attack_1(test_hash);
    // Note you can implement your own test hash functions so long as their 
    // signatures match the `test_hash` function signature.
    
    // Your code here!

    return {0, 1};
}


/*** PART 2: Graphs ***/

/* Topological Sorting
 *
 * 5 Points
 *
 * In this problem, you are tasked with reading the description of a
 * directed graph as input, then outputting a valid topological
 * sort of the graph, if one exists.
 *
 * Input
 *  - int n: number of nodes/vertices in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: a list of directed edges in the graph
 *
 * Output
 *  - vector<int>: a valid topological sorting of the graph. If
 *    no topological sorting exists, output an empty list.
 *    If multiple topological sortings exist, you only need to
 *    output a single one.
 *
 * Note: Edge is a struct defined in Firstname_Lastname_project2.h.
 *
 */


vector<int> topological_sort(int n, vector<Edge> edges) {
    // Your code here!

    // Keep track of degrees for each node, and neighbors
    vector<int> res {};
    unordered_map<int, int> node_degrees {};
    unordered_map<int, vector<int>> neighbors {};

    for (int i = 0; i < n; i++) {
        node_degrees[i] = 0;
        neighbors[i] = {};
    } 

    // Sum up incoming edges for each node for the in-degree and add neighbors 
    for (const auto& edge : edges){
        node_degrees[edge.to]++;
        neighbors[edge.from].push_back(edge.to);
    }

    // Add all degree-0 nodes to the work queue
    queue<int> work_queue;
    for (int i = 0; i < n; i++){
        if (node_degrees[i] == 0) work_queue.push(i);
    }

    while (!work_queue.empty()){
        int node = work_queue.front();
        work_queue.pop();

        // Subtract 1 from the degree of all the node's neighbors
        for (size_t i = 0; i < neighbors[node].size(); i++){
            int neighbor = neighbors[node][i];
            // Add a neighbor to the queue if it becomes degree 0
            if (--node_degrees[neighbor] == 0)
                work_queue.push(neighbor);
        }
        
        // Add node to result
        res.push_back(node);
    }

    return (res.size() == n) ? res : vector<int> {};
}


/* Single Source Shortest Paths on DAGs
 *
 * 10 points
 *
 * In this problem, you will be given a directed acyclic graph with 
 * arbitrary integer edge weights (i.e., they can be negative!), as
 * well as a single source node. Your goal will be to output the
 * shortest distance from the source to every other vertex in the
 * graph.
 *
 * Input
 *  - int n: number of nodes in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: list of weighted directed edges in the graph
 *  - int source: ID of the source node
 *
 * Output
 *  - vector<int>: vector of size n such that entry i is the distance
 *    from source to i in the given graph. Use the value "INT_MAX" to
 *    indicate that there is no path from source to i.
 *
 * Algorithm
 *  - Topological Sorting + BFS is enough to solve this problem.
 *
 * Assumptions
 *  - The graph given as input will always be a DAG
 *
 */
vector<int> dag_single_source(int n, vector<Edge> edges, int source) {
    // Build adjacency list and compute in-degrees
    vector<vector<pair<int, int>>> adj(n); // adj[u] = {(v, weight), ...}
    vector<int> in_degree(n, 0);
    
    for (const Edge& e : edges) {
        adj[e.from].push_back({e.to, e.weight});
        in_degree[e.to]++;
    }
    
    // Perform topological sort using Kahn's algorithm
    queue<int> q;
    vector<int> topo_order;
    
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);
        
        for (auto [v, w] : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // Initialize distances
    vector<int> dist(n, INT_MAX);
    dist[source] = 0;
    
    // Process vertices in topological order
    for (int u : topo_order) {
        // Skip if this vertex is unreachable from source
        if (dist[u] == INT_MAX) {
            continue;
        }
        
        // Relax all outgoing edges
        for (auto [v, w] : adj[u]) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    return dist;
}


/* Dijkstra's Algorithm
 *
 * 20 Points
 *
 * In this problem, you are simply tasked to implement Dijkstra's Algorithm.
 *
 * Input
 *  - int n: number of nodes in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: list of weighted directed edges in the graph
 *  - int source: ID of the source node
 *
 * Output
 *  - vector<Node>: a list of size n such that entry i contains a Node node
 *    with the following properties:
 *      - node.id = i
 *      - node.path_cost = cost of the shortest path from source to i
 *      - node.pred = id of the predecessor of i on the shortest path from
 *        source to i
 *
 * Assumptions
 *  - You are guaranteed that the graph contains only non-negative edges
 *    (i.e., weight at least 0). For simplicity, all weights will be
 *    integers.
 * 
 * Note: Node is a struct defined in Firstname_Lastname_project2.h.
 */


vector<Node> dijkstras_algorithm(int n, vector<Edge> edges, int source) {
    // Your code here!
    // Note: see the LeetCode from in-class for the problem "Cheapest Flights
    // K stops" to see how you can create a priority_queue with the Node struct.
    
    return {};
}


/* A-star Algorithm
 *
 * 25 Points
 *
 * In this problem, you are asked to implement a modified version of Dijkstras,
 * known as A* (A-star). The A* algorithm is very similar to Dijkstras, with
 * two notable differences:
 *  (a) A* uses some heuristic function h to estimate the distance between any
 *      two nodes; and
 *  (b) A* only finds a path from a specified source node and a target node.
 *
 * Recall in Dijkstras, the algorithm finds the shortest path from a single
 * source to all other nodes in the graph.
 *
 * Given a source s and a target t, A* is guaranteed to output a shortest path
 * from s to t as long as the heuristic h underestimates the distance between 
 * any two nodes u,v in the graph. If d(u,v) represents the actual distance
 * between u and v, then h(u,v) <= d(u,v) for all u,v is enough to guarantee
 * that A* outputs a shortest path from s to t.
 *
 * For this specific version of A*, you will be given two points on a grid (a
 * start point and an end point). The grid will be specified by a graph, with
 * nodes being a GridNode (each with their own x and y value on the grid), and
 * edges being a GridEdge. Each GridEdge has a weight that is of a double type.
 * A GridEdge will only connect adjacent or diagonal nodes. Formally, for a
 * GridNode at point (x,y), all of the following edges are possible:
 *
 *  - (x+1, y) (cost = 1.0)
 *  - (x-1, y) (cost = 1.0)
 *  - (x, y+1) (cost = 1.0)
 *  - (x, y-1) (cost = 1.0)
 *  - (x+1, y+1) (cost = 1.5)
 *  - (x-1, y+1) (cost = 1.5)
 *  - (x+1, y-1) (cost = 1.5)
 *  - (x-1, y-1) (cost = 1.5)
 * 
 * Here, edges all have an implicit movement cost, described above. Moving along
 * a diagonal edge has a cost of 1.5, while moving along a cardinally adjacent  
 * edge (north, south, east, west) has a cost of 1.
 *
 * Note that GridEdge and GridNode are structs defined in Firstname_Lastname_project2.h.
 *
 * Input:
 *  - int m: number of columns (x-axis)
 *  - int n: number of rows in the grid (y-axis)
 *  - vector<GridEdge> edges: list of edges in the graph
 *  - GridNode source: source node of the algorithm
 *  - GridNode target: target node of the algorithm
 *  - function<double(GridNode, GridNode)> h: h is a function which takes as input
 *      two GridNodes and outputs a double. This represents the heruistic_cost
 *      function for A*.
 *
 * Output:
 *  - vector<GridNode>: a list of nodes containing the path from source to target.
 *                      Note that if variable "output" is your output vector, then
 *                      it must satisfy the following properties:
 *                          - if a path from source to target exists, then
 *                              - output[0] = source
 *                              - output[output.size()-1] = target
 *                              - Moreover, output[output.size()-1].path_cost is the cost
 *                                of the path from source to target.
 *                          - if no path from source to target exists, then
 *                              - output = {} (the empty list)
 *
 * Algorithm:
 *  The algorithm is nearly identical to Dijkstra's Algorithm, with the following changes.
 *      - Suppose in Dijkstra's you are currently considering node u and expanding the 
 *        frontier along the neighbors of u.
 *      - Let v be a neighbor of u.
 *      - In Dijkstra's, you check if u.cost + weight(u,v) < v.cost, where weight(u,v) 
 *        is the weight of the edge from u to v. If this is true, you update v.cost as
 *        v.cost = u.cost + weight(u,v), update it in / add it to the priority queue,
 *        and continue.
 *      - In A*, this is modified as: v.cost = u.cost + weight(u,v) + heuristic_cost(v, target),
 *        where heuristic_cost(v, target) is a heuristic distance from node v to the target node
 *        target.
 *          - Note you also change the dijkstra's check to u.cost+weight(u,v)+heuristic_cost(v,target) < v.cost
 *  
 *  As part of your implementation of A*, you are required to implement the function
 *  heuristic_cost(GridNode start, GridNode dest) defined below. Your heuristic should never
 *  over estimate the distance between any two nodes start and dest. Remember, in theory you
 *  can move north, south, east, west, or along any diagonal (so long as there is an edge).
 *  Use this information to write a heuristic function that never over estimates the distance.
 *
 *
 * Additional Resources:
 *  - Wikipedia: https://en.wikipedia.org/wiki/A*_search_algorithm
 *  - GeeksForGeeks: https://www.geeksforgeeks.org/dsa/a-search-algorithm/
 *  - Stanford: https://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html
 *
 */



// You must implement this function.
double heuristic_cost(GridNode start, GridNode dest) {
    // Your code here!
}

// To test your algorithm with the function "heruistic_cost" above,
// simply pass "heuristic_cost" as a parameter to the function.
vector<GridNode> a_star_algorithm(
    int m, 
    int n, 
    vector<GridEdge> edges, 
    GridNode source, 
    GridNode target,
    function<double(GridNode,GridNode)> h
) 
{
    // Your code here!
    // Be sure to use "h" from the inputs in your implementation; do not
    // directly use "heruistic_cost" above!

    return {};
}

int main() {
    birthday_attack_1(test_hash);
    birthday_attack_2(test_hash);

    topological_sort(1, {});
    dag_single_source(1, {}, 0);

    return 0;
}
