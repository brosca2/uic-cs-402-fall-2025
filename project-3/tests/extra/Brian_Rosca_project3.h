

#ifndef FIRSTNAME_LASTNAME_PROJECT3
#define FIRSTNAME_LASTNAME_PROJECT3

#include <vector>
#include <string>

using namespace std;

// Struct for tree in first-child, next-sibling representation
struct TreeNode {
    int id;
    TreeNode* first_child;
    TreeNode* next_sibling;
};

// undirected edges
struct Edge {
    int u;
    int v;
};

// nodes in an undirected graph; each node has a cost and a vector of neighbor ids
struct Node {
    int id;
    int cost;
    vector<int> neighbors;
};



// function delcarations
vector<int> weird_traversal(TreeNode* root);
TreeNode* bits_to_tree(const vector<bool>& bits);
pair<int, vector<int>> light_post_problem(int n, const vector<Edge>& edges, const vector<int>& costs);
vector<pair<unsigned int,string>> smallest_subset_sum(unsigned int n, unsigned int t, const vector<pair<unsigned int, string>>& values);

#endif


