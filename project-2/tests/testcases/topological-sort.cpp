#include <vector>
#include <algorithm>

struct Edge {
    int from;
    int to;
    int weight; // default = 1 if unweighted graph
};

std::vector<int> topological_sort(int n, std::vector<Edge> edges);


int main() {

    double total_score = 5.0;
    double score = 0.0;

    // Test 1: Simple linear graph
    std::vector<Edge> test1 = {Edge(0,1,1), Edge(1,2,1), Edge(2,3,1), Edge(3,4,1)};
    std::vector<int> res1 = topological_sort(5, test1);
    std::vector<int> ans1 = {0, 1, 2, 3, 4};
    if(res1 == ans1) ++score;

    // Test 2: Multiple valid topological sorts
    std::vector<Edge> test2 = {Edge(0,1,1), Edge(2,1,1), Edge(0,3,1), Edge(2,3,1)};
    std::vector<int> res2 = topological_sort(4, test2);
    std::vector<int> ans21 = { 0, 2, 1, 3 };
    std::vector<int> ans22 = { 0, 2, 3, 1 };
    std::vector<int> ans23 = { 2, 0, 1, 3 };
    std::vector<int> ans24 = { 2, 0, 3, 1 };
    if(res2 == ans21 || res2 == ans22 || res2 == ans23 || res2 == ans24) ++score;

    // Test 3: Graph with a cycle
    std::vector<Edge> test3 = {Edge(0,1,1), Edge(1,2,1), Edge(2,3,1), Edge(3,0,1)};
    std::vector<int> res3 = topological_sort(4, test3);
    if(res3.empty()) ++score;

    // Test 4: Single node with no edges
    std::vector<Edge> test4 = {};
    std::vector<int> res4 = topological_sort(1, test4);
    if(res4.size() == 1 && res4[0] == 0) ++score;

    // Test 5: Disconnected graph
    std::vector<Edge> test5 = {Edge(0,1,1), Edge(2,3,1)};
    std::vector<int> res5 = topological_sort(4, test5);
    std::vector<int> ans51 = {0, 2, 1, 3};
    std::vector<int> ans52 = {2, 0, 3, 1};
    if(res5 == ans51 || res5 == ans52) ++score;

    RESULT(100*(score / total_score));

    return 0;
}