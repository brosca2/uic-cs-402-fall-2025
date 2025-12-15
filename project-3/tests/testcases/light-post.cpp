#include <vector>


// undirected edges
struct Edge {
    int u;
    int v;
};

std::pair<int, std::vector<int>> light_post_problem(int n, const std::vector<Edge>& edges, const std::vector<int>& costs);


int main() {

    int n1 = 1;
    std::vector<Edge> e1 = {};
    std::vector<int> c1 = {5};

    int n2 = 2;
    std::vector<Edge> e2 = { Edge(0,1) };
    std::vector<int> c2 = {1, 2};

    int n3 = 2;
    std::vector<Edge> e3 = { Edge(0,1), Edge(0,2) };
    std::vector<int> c3 = {50, 2, 3};
    // n4: path/line tree of length 4 with cheaper internal nodes

    int n4 = 4;
    std::vector<Edge> e4 = { Edge(0,1), Edge(1,2), Edge(2,3) };
    std::vector<int> c4 = {10, 1, 1, 10};
    // n5: star-shaped tree where leaves are cheaper than center
    int n5 = 5;
    std::vector<Edge> e5 = { Edge(0,1), Edge(0,2), Edge(0,3), Edge(0,4) };
    std::vector<int> c5 = {100, 1, 1, 1, 1};
    // n6: star-shaped tree where center is cheaper than leaves
    int n6 = 5;
    std::vector<Edge> e6 = { Edge(0,1), Edge(0,2), Edge(0,3), Edge(0,4) };
    std::vector<int> c6 = {2, 10, 10, 10, 10};

    std::pair<int, std::vector<int>> sol1 = {5, {0}};
    std::pair<int, std::vector<int>> sol2 = {1, {0}};
    std::pair<int, std::vector<int>> sol3 = {5, {1,2}};
    std::pair<int, std::vector<int>> sol4 = {2, {1, 2}};
    std::pair<int, std::vector<int>> sol5 = {4, {1, 2, 3, 4}};
    std::pair<int, std::vector<int>> sol6 = {2, {0}};

    auto ans1 = light_post_problem(n1, e1, c1);
    auto ans2 = light_post_problem(n2, e2, c2);
    auto ans3 = light_post_problem(n3, e3, c3);
    auto ans4 = light_post_problem(n4, e4, c4);
    auto ans5 = light_post_problem(n5, e5, c5);
    auto ans6 = light_post_problem(n6, e6, c6);

    double total_score = 6.0;
    double score = 0.0;

    if(ans1 == sol1) ++score;
    if(ans2 == sol2) ++score;
    if(ans3 == sol3) ++score;
    if(ans4 == sol4) ++score;
    if(ans5 == sol5) ++score;
    if(ans6 == sol6) ++score;


    RESULT(100*(score / total_score));

    return 0;
}
