#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <stack>

// be sure to change FIRSTNAME and LASTNAME with your own first and last name
#include "Brian_Rosca_project3.h"

using namespace std;

/****************
 * INSTRUCTIONS *
 ****************
 *
 * - Replace all instances of "Firstname_Lastname" with your firstname and
 *   your last name. This include the .h and .cpp files, along with the
 *   header guards at the top of the .h file.
 *
 * - Implement solutions to the problems described below.
 *   You must follow the specifications as written below.
 *
 * - Certain function signatures may not be modified (as it will affect auto
 *   grading). These functions will be specified.
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Lastname_project3.h."
 *
 * - If you are working in a group, please modify the comments directly below.
 *   
 * - IMPORTANT: If you are working in a group, every member is expected to submit their
 *   source code individually.
 *
 */


/*** GROUP PROJECT ***/
// Please list ALL of your other group members as comments below.
//   Member 1
//   Member 2


/* Problem 1: "Weird" Tree Traversal (Trees)
 *
 * 25 Points
 *
 * In this problem, you are asked to implement what I am calling "weird"
 * traversal on a tree.
 *
 * Definition: A weird traversal on an arbitrary rooted tree (i.e., a node can have
 * any number of children) proceeds as follows.
 *
 *   - First, the traversal visits all even layers in level-order, where we
 *     define the root to be layer 0, its children as layer 1, etc. "Level-
 *     order" here means visiting the nodes in layer i from left to right, 
 *     followed by nodes in layer i+2 from left to right (for even i). In
 *     other words, this traversal, starting from the root, visits all even
 *     layers in level-order (top to bottom, left to right).
 *
 *   - Once all even layers have been visited, all of the odd layers are then
 *     visited, bottom to top and right to left. In other words, this traversal
 *     visits the deepest odd layer first, from right most node to left most node,
 *     then proceeds back up, with the children of the root visited last.
 * 
 * Problem 
 *  - Given a pointer to the root of a Tree (specified as a TreeNode in
 *    the header file), output a vector of integers which represents the 
 *    weird-traversal of the tree.
 *
 * Grading
 *  - This problem is easily solvable using 2 traversals. This will only give
 *    you 15 points. To get full marks, you must solve this problem doing
 *    a single traversal of the tree.
 *      - Note this also means you cannot copy this tree into a different
 *        representation, as this would be at least 2 traversals to solve
 *        the problem (one to put the tree into a different format, then
 *        another traversal to perform weird-traversal).
 * 
 * Assumptions
 *  - Each node in the tree has a unique integer id. However, you cannot
 *    assume that the root is id 0, its first child has id 1, etc. The
 *    ids in the tree are only guaranteed to be unique.
 *  - The tree is in the first-child, next-sibling representation. That is,
 *    a node in a tree only has 2 pointers: one to its first (i.e., left-
 *    most) child, and one to its first (i.e., right) sibling.
 *
 * Examples
 *  - Tree in first-child, next-sibling representation. Consider the following
 *    tree:
 *       0
 *     / | \
 *    1  2  3
 *      /    \
 *     4      5
 *   / | \   /||\
 *  6  7 8  9 ab c
 *
 *    The first-child, next-sibling representation turns this tree into an equivalent
 *    binary tree, where a left branch is the first child in the above tree, and a
 *    right branch is the next sibling in the above tree:
 *               0
 *             /
 *           1
 *             \
 *             [  2  ]
 *            /      \
 *           4       3
 *          /       /
 *         6       5
 *          \     /
 *           7   9
 *            \   \
 *             8   a
 *                  \
 *                   b
 *                    \
 *                     c
 *
 * - Weird-traversal of above tree, given pointer to root labeled "a":
 *   [0, 4, 5, c, b, a, 9, 8, 7, 6, 3, 2, 1]
 *
 * - Other weird-traversal examples
 *    (a)    1   -> [1, 3, 2]
 *         /  \
 *        2    3
 *
 *    (b) -1    -> [-1, 3, 6, -9, 7, 2]
 *        / \
 *      2    7
 *       \  / \
 *       3 6  -9
 */

// Do not modify this function signature.
vector<int> weird_traversal(TreeNode* root) {
    vector<int> result;
    if (!root) return result;

    vector<vector<int>> odd_layers;
    queue<TreeNode*> q;
    q.push(root);
    int level = 0;

        // single breadth-first traversal of the tree
    while (!q.empty()) {
        int level_size = q.size();
        vector<int> current_odd_layer;

        // process all nodes at the current depth
        for (int i = 0; i < level_size; ++i) {
            TreeNode* curr = q.front();
            q.pop();

            // even layers are output immediately (top-down, left-to-right)
            if (level % 2 == 0) {
                result.push_back(curr->id);
            }
            // odd layers are stored for later 
            else {
                current_odd_layer.push_back(curr->id);
            }

            // enqueue all children of curr in left-to-right order
            TreeNode* child = curr->first_child;
            while (child) {
                q.push(child);
                child = child->next_sibling;
            }
        }

        // save odd layers to be appended later (in reverse)
        if (level % 2 != 0) {
            odd_layers.push_back(current_odd_layer);
        }

        ++level;
    }

    // append odd layers bottom-up, reversing each layer
    // to get right-to-left ordering
    for (int i = (int)odd_layers.size() - 1; i >= 0; --i) {
        for (auto it = odd_layers[i].rbegin(); it != odd_layers[i].rend(); ++it) {
            result.push_back(*it);
        }
    }

    return result;
}



/* Problem 2: Bits-to-Tree (Trees)
 *
 * 25 Points
 *
 * In this problem, you are given a vector of bits which represents 
 * a DFS traversal of a tree with the following properties:
 *  1. Non-empty: the tree always has at least 1 node (the root).
 *  2. Unlabeled: the nodes in the tree are not labeled.
 *  3. Ordered: the children of each noded are ordered from left to right.
 *
 * Your goal is to reconstruct the tree given the vector of bits, using
 * the TreeNode struct. The bits in the vector correspond to a DFS
 * traversal in the following way:
 *  - A '1' represents a "down" traversal; and
 *  - A '0' represents a "up" traversal.
 * Moreover, this DFS traversal visits each child in left-to-right order.
 *w
 * Helpful Properties of this Problem
 *  - For a tree with n nodes, the input "bits" is valid if and only if
 *      - bits has exactly n-1 1's and n-1 0's;
 *      - bits has even length (i.e., = 2(n-1)); and
 *      - For any prefix of bits (i.e., bits[0,..,i]), #0s <= #1s
 *
 * Other Considerations
 *  - The tree is guaranteed to be non-empty. What type of input would lead
 *    to a tree that is a single root node?
 *  - Defining a helper function for this problem could be useful.
 *
 * Grading
 *  - The returned pointer must be the root of the tree you have reconstructed,
 *    or the nullptr if 'bits' is not a valid encoding.
 *  - Additionally, label each node from 0 to n-1, where the ID of the node
 *    corresponds to its ordering during the pre-order DFS traversal.
 *  - Using your own TreeNode type which represents a tree in a format other
 *    than specified to construct your solution will only yield 15 points. For
 *    full marks, directly construct your tree using the TreeNode struct.
 * 
 * Examples
 *  - [1, 0] ->  0
 *              /
 *             1
 *
 *  - [1, 0, 1, 0, 1, 1, 0, 1, 0, 0]
 *      -> (in a format where each node has a vector of children)
 *                0
 *              / | \
 *             1  2   3
 *                   | \
 *                   4  5
 *      -> (in the required first-child, next sibling format)
 *               0
 *              /
 *             1
 *             \
 *              2
 *               \
 *                3
 *               /
 *              4
 *               \
 *                5
 */

// Do not modify this fuction signature
TreeNode* bits_to_tree(const vector<bool>& bits) {
    // empty encoding corresponds to a single root node
    if (bits.empty()) return new TreeNode(0);

    // validate encoding: balanced and no invalid prefix
    int ones = 0, zeros = 0;
    for (bool b : bits) {
        if (b) ++ones;
        else ++zeros;
        if (zeros > ones) return nullptr;
    }
    if (ones != zeros) return nullptr;

    // create root (preorder id = 0)
    TreeNode* root = new TreeNode(0);
    stack<TreeNode*> st;
    st.push(root);

    int next_id = 1;
    
    // tracks the most recently added child for each node
    // used to correctly link next_sibling pointers
    vector<TreeNode*> last_child(ones + 1, nullptr);

    // simulate dfs traversal
    for (bool b : bits) {
        if (b) { // down: create and descend to a new child
            TreeNode* parent = st.top();
            TreeNode* child = new TreeNode(next_id++);

            if (!last_child[parent->id]) {
                parent->first_child = child;
            } else {
                last_child[parent->id]->next_sibling = child;
            }

            last_child[parent->id] = child;
            st.push(child);
        } else { // up: return to parent
            st.pop();
        }
    }

    return root;
}


/* Problem 3: Light Post Problem (Trees + Dynamic Programming)
 *
 * 25 points
 *
 * This problem is an extension of the Binary Tree Cameras problem from LeetCode 
 * we did in class (https://leetcode.com/problems/binary-tree-cameras/description/).
 *
 * Problem: You are given an "unrooted" tree (i.e., an undirected graph with no 
 * cycles and exactly n-1 edges for n nodes). Any node could be picked arbitrarily
 * as the root. Moreover, this is a general tree in that a node can have any
 * number of children.
 *
 * You need to select a subset of nodes to place light towers to illuminate all
 * nodes. When a light tower is placed on a node, it illuminates:
 *  - The node the light tower is placed on; and
 *  - All neighbors of that node (i.e., all children and its parent).
 * Additionally, each node has a cost associated with placing a light tower on it.
 *
 * Your objective is to illuminate all nodes in the graph such that the cost
 * of the placed light towers is minimized. 
 *
 * The output of your solution will be a pair<int, vector<Node>>. The first
 * element of the pair is the cost of the 
 *
 * Assumptions
 *  - The given graph has nodes uniquely labeled from 0 to n-1.
 *  - The function has 3 input parameters:
 *      - int n: number of Nodes in the graph.
 *      - vector<Edge>& edges: list of edges in the graph.
 *      - vector<int>& costs: vector of costs such that node i has cost 
 *        costs[i].
 *  - The function outputs a pair of type <int, vector<Node>> with the
 *    following properties:
 *      - pair.first is an integer representing the minimum computed cost
 *      - pair.second is a vector of integers representing the ids of each
 *        node which has a light post placed on it (in other words, this
 *        is your subset of nodes you have chosen to minimize the costs).
 *  - edges will be a valid tree (though it will not have a root).
 *
 * Additional Information
 *  - There is a "Node" struct defined in the header file which you may use
 *    in your implementation if you think it will be helfpul.
 *  - Think about if it matters which node you choose as the root
 *
 * Grading
 *  - Your algorithm must run in poolynoimial time in the size of the input.
 * 
 * Examples
 *  - (n=1, edges = {}, costs = {5}) -> { 5, {0}}
 *  - (n=2, edges = { (0,1) }, costs = {1,2}) -> { 1, {0}}
 *  - (n=3, edges = { (0,1), (0,2) }, costs = {50, 2, 3}) -> {5, {1,2}}
 */

namespace {
    const int INF_VAL = 1e9;

    struct DPState {
        int dp[3];
        DPState() {
            dp[0] = dp[1] = dp[2] = INF_VAL;
        }
    };

    vector<DPState> memo;
    vector<vector<int>> adj_list;
    vector<int> node_costs;
    vector<int> result_nodes;

    void dfs_dp(int u, int p) {
        int sum_0 = 0;  // for state 0: children can be in {0,1,2}
        int sum_01 = 0; // for states 1 and 2: children can only be in {0,1}

        bool is_leaf = true;

        for (int v : adj_list[u]) {
            if (v == p) continue;
            is_leaf = false;
            dfs_dp(v, u);

            sum_0 += min({memo[v].dp[0], memo[v].dp[1], memo[v].dp[2]});
            sum_01 += min(memo[v].dp[0], memo[v].dp[1]);
        }

        // State 0: u has light
        memo[u].dp[0] = node_costs[u] + sum_0;

        // State 2: u needs parent (so parent must have light); children cannot depend on u
        // Children must be solved without using u, so each child is min of {0,1}
        memo[u].dp[2] = is_leaf ? 0 : sum_01;

        // State 1: u is covered by (at least one) child
        if (is_leaf) {
            memo[u].dp[1] = INF_VAL;
        } else {
            // Start with all children taking their best of {0,1}
            // Then ensure at least one child is forced into state 0.
            bool has_child_in_state0 = false;
            int min_diff = INF_VAL;

            for (int v : adj_list[u]) {
                if (v == p) continue;

                if (memo[v].dp[0] <= memo[v].dp[1]) {
                    has_child_in_state0 = true; // min() will pick dp0 for this child
                } else if (memo[v].dp[1] != INF_VAL) {
                    // Candidate child to "flip" from dp1 to dp0
                    min_diff = min(min_diff, memo[v].dp[0] - memo[v].dp[1]);
                }
            }

            if (has_child_in_state0) {
                memo[u].dp[1] = sum_01;
            } else {
                memo[u].dp[1] = (min_diff == INF_VAL) ? INF_VAL : (sum_01 + min_diff);
            }
        }
    }

    void dfs_reconstruct(int u, int p, int state) {
        if (state == 0) {
            result_nodes.push_back(u);
            for (int v : adj_list[u]) {
                if (v == p) continue;
                int min_val = memo[v].dp[0];
                int best_v_state = 0;
                
                if (memo[v].dp[1] < min_val) {
                    min_val = memo[v].dp[1];
                    best_v_state = 1;
                }
                if (memo[v].dp[2] < min_val) {
                    min_val = memo[v].dp[2];
                    best_v_state = 2;
                }
                dfs_reconstruct(v, u, best_v_state);
            }
        } else if (state == 1) {
            int best_child = -1;
            bool naturally_satisfied = false;
            int min_diff = INF_VAL;
            
            for (int v : adj_list[u]) {
                if (v == p) continue;
                if (memo[v].dp[0] <= memo[v].dp[1]) {
                    naturally_satisfied = true;
                }
                if (memo[v].dp[1] != INF_VAL) {
                    if (memo[v].dp[0] - memo[v].dp[1] < min_diff) {
                        min_diff = memo[v].dp[0] - memo[v].dp[1];
                        best_child = v;
                    }
                }
            }
            
            for (int v : adj_list[u]) {
                if (v == p) continue;
                if (naturally_satisfied) {
                    if (memo[v].dp[0] <= memo[v].dp[1]) dfs_reconstruct(v, u, 0);
                    else dfs_reconstruct(v, u, 1);
                } else {
                    if (v == best_child) dfs_reconstruct(v, u, 0);
                    else {
                         if (memo[v].dp[0] <= memo[v].dp[1]) dfs_reconstruct(v, u, 0);
                         else dfs_reconstruct(v, u, 1);
                    }
                }
            }
        } else if (state == 2) {
            // u is covered by its parent, so children must be solved without relying on u.
            // Each child can be in state 0 (has light) or state 1 (covered by its child).
            for (int v : adj_list[u]) {
                if (v == p) continue;
                int child_state = (memo[v].dp[0] <= memo[v].dp[1]) ? 0 : 1;
                dfs_reconstruct(v, u, child_state);
            }
        }
    }
}

// Do not modify this function signature
pair<int, vector<int>> light_post_problem(int n, const vector<Edge>& edges, const vector<int>& costs) {
    // Some testcases may provide an inconsistent `n` relative to the node ids
    // referenced by `edges` and/or the size of `costs`. Size the instance based
    // on the maximum implied node id to avoid out-of-bounds access.
    int max_node_id = -1;
    for (const auto& e : edges) {
        max_node_id = max(max_node_id, e.u);
        max_node_id = max(max_node_id, e.v);
    }

    int actual_n = n;
    actual_n = max(actual_n, (int)costs.size());
    actual_n = max(actual_n, max_node_id + 1);

    if (actual_n <= 0) return {0, {}};

    adj_list.assign(actual_n, vector<int>());

    for (const auto& edge : edges) {
        if (edge.u < 0 || edge.v < 0) continue;
        if (edge.u >= actual_n || edge.v >= actual_n) continue;
        adj_list[edge.u].push_back(edge.v);
        adj_list[edge.v].push_back(edge.u);
    }

    node_costs.assign(actual_n, INF_VAL);
    for (int i = 0; i < (int)costs.size() && i < actual_n; ++i) {
        node_costs[i] = costs[i];
    }

    memo.assign(actual_n, DPState());
    result_nodes.clear();

    dfs_dp(0, -1);

    int min_cost = min(memo[0].dp[0], memo[0].dp[1]);
    int start_state = (memo[0].dp[0] <= memo[0].dp[1]) ? 0 : 1;

    dfs_reconstruct(0, -1, start_state);

    sort(result_nodes.begin(), result_nodes.end());

    return {min_cost, result_nodes};
}

/* Problem 4: Smallest Subset Sum (Dynamic Programming)
 * 
 * 25 points
 *
 * In this problem, you will tackle the classic subset sum problem, but with a twist.
 *
 * Subset Sum Overview: First, recall the subset sum problem. 
 *  - Input: A list of n positive integers A = {a_1, ..., a_n} and a target value T.
 *  - Output: true if there exists a set S, which is a subset of {1,...,n} such that
 *      sum(A[i], i in S) = T, false otherwise.
 *    Equivalently written in C++:
 *      int sum = 0;
 *      for(i in S): sum += A[i];
 *      return (sum == T);
 *
 * Basic Dynamic Programming Algorithm; Runtime: O(nT)
 *  - We can solve the above formulation of the subset sum problem using
 *    a table of booleans M of dimensions M [1..n][0..T]. For every i=1 to
 *    n and j=0 to T, set M[i][j] = true if and only if a target sum of
 *    j can be formed from a subset of {a_1, ..., a_i} (and false otherwise).
 *      - Base cases:
 *          - M[i][0] = true for all i=1 to n (empty set has zero sum).
 *          - M[1][a_1] = true (singleton case).
 *          - M[1][j] = false for all j != a_1.
 *      - Induction: for i > 1
 *          M[i][j] = true if 
 *              M[i-1][j] = true || (j >= a_i) && (M[i-1][j-a_i] = true)
 *          (false otherwise)
 *  - Then, M[n][T] is the answer to the problem (i.e., if it is true then
 *    there exists a subset satisfying the subset sum property).
 *
 * Smallest Subset Sum: In this problem, you are tasked with solving the subset
 * sum problem, but with the following twists: 
 *  1. You must return the subset S such that sum(A[i], i in S) = T.
 *  2. S must be the smallest possible subset satisfying 1 above.
 *  3. S must be the lexicographically first subset (as there could be multiple
 *     smallest subsets).
 * Consider the following example to help your understanding:
 *  - Input: A = {1, 1, 2, 3, 1, 4}, T = 5
 *  - There are 8 possible subsets for the target sum:
 *      1. {A[1], A[2], A[3], A[5]} = {1, 1, 2, 1}
 *      2. {A[1], A[2], A[4]} = {1, 1, 3}
 *      3. {A[1], A[4], A[5]} = {1, 3, 1}
 *      4. {A[1], A[6]} = {1, 4}
 *      5. {A[2], A[4], A[5]} = {1, 3, 1}
 *      6. {A[2], A[6]} = {1, 4}
 *      7. {A[3], A[4]} = {2, 3}
 *      8. {A[5], A[6]} = {1, 4}
 *    Subsets 4, 6, 7, 8 are all of size 2, so they are the smallest ones.
 *  - Output: S = {1, 6}
 *      Reason: A[1]+A[6] == 5 
 *              && S.size() == 2 
 *              && {1,6} is lexicographically smaller than {2,6}, {3,4}, and {5,6}
 *              (note this is left-right ordering of the vector).
 *  
 * Assumptions
 *  - The function has 3 input parameters
 *      - unsigned int n: number of elements in the vector 'values'.
 *      - unsigned int t: target sum (assumed >= 1).
 *      - vector<pair<unsigned int, string>>& values: vector of pairs with 
 *        the following properties: for i=0 to n-1, p = values[i]:
 *          - p.first = A[i+1] (the vector of values to be summed to target t).
 *            Always assumed to be >= 1.
 *          - p.second = just some string that is tied to the value A[i+1].
 *  - The function outputs a vector<pair<unsigned int, string>> with the following
 *    properties: let out be this vector
 *      unsigned int sum = 0;
 *      vector<unsigned int> order;
 *      for(i = 0; i < out.size(); ++i) {
 *          unsigned int idx = out[i].first;
 *          sum += values[idx].first;
 *          out[i].second == values[idx].second; // the strings match as well!
 *          order.push_back(idx);
 *      }
 *      sum == t; // should be true!
 *      order is lexicographic minimum subset
 *
 * Other Information
 *  - The strings in pair<unsigned int, string> here are to help distinguish elements of
 *    the set from each other, since integers within the set are not assumed to be unique.
 *    For exmple, if we modify the above example to
 *      values = { {1, "dog"}, {1, "cat"}, {2, "bird"}, {3, "mouse"}, {1, "snake"}, {4, "fish"} }
 *    Then setting t = 5, the returned answer would be
 *      out = { {1, "dog"}, {4, "fish"} }.
 *
 * Grading
 *  - Your solution must be asymptotically equivalent to the basic subset sum problem.
 *    That is, you must run in time O(nT). Note this means that you cannot enumerate
 *    all possible subsets! Doing so will only give you a maximum of 5 points.
 *  - A maximum of 15 points will be given to those who return a minimum sized solution, but
 *    not the lexicographically smallest one.
 */

// Do not modify this function signature
vector<pair<unsigned int,string>> smallest_subset_sum(unsigned int n, unsigned int t, const vector<pair<unsigned int, string>>& values) {
    // Use the smaller of (declared n) and values.size() to avoid out-of-bounds.
    unsigned int m = n;
    if (m > values.size()) m = (unsigned int)values.size();

    // dp[i][j] = minimum number of elements needed to form sum j using values[i..m-1]
    const int INF = 1000000000;
    vector<vector<int>> dp(m + 1, vector<int>(t + 1, INF));

    dp[m][0] = 0;
    for (unsigned int j = 1; j <= t; ++j) dp[m][j] = INF;

    for (int i = (int)m - 1; i >= 0; --i) {
        dp[i][0] = 0;
        unsigned int val = values[i].first;

        for (unsigned int j = 1; j <= t; ++j) {
            int best = dp[i + 1][j]; // skip i

            if (j >= val && dp[i + 1][j - val] != INF) {
                best = min(best, 1 + dp[i + 1][j - val]); // take i
            }

            dp[i][j] = best;
        }
    }

    if (dp[0][t] == INF) return {};

    // Reconstruct lexicographically smallest subset among all minimum-size solutions:
    // iterate left-to-right and take index i whenever it preserves optimality.
    vector<pair<unsigned int, string>> out;
    unsigned int remaining = t;

    for (unsigned int i = 0; i < m && remaining > 0; ++i) {
        unsigned int val = values[i].first;

        if (remaining >= val && dp[i + 1][remaining - val] != INF &&
            1 + dp[i + 1][remaining - val] == dp[i][remaining]) {
            out.push_back(values[i]); // return the selected (value, string) pairs
            remaining -= val;
        }
    }

    return out;
}


// int main() {
//     return 0;
// }

