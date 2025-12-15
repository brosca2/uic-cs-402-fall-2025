#include <vector>
#include <string>

using std::vector;
using std::string;
using std::pair;

vector<pair<unsigned int,string>> smallest_subset_sum(unsigned int n, unsigned int t, const vector<pair<unsigned int, string>>& values);


int main() {

    double total_score = 6.0;
    double score = 0.0;

    // test 1
    {
        vector<pair<unsigned int, string>> values = { {1, "dog"}, {1, "cat"}, {2, "bird"}, {3, "mouse"}, {1, "snake"}, {4, "fish"} };
        unsigned int n = 6;
        unsigned int t = 5;

        vector<pair<unsigned int, string>> sol = { {1,"dog"}, {4, "fish"} };
        auto ans = smallest_subset_sum(n, t, values);
        if (sol == ans) ++score;
    }

    // test 2: single element equals target (size 1)
    {
        vector<pair<unsigned int, string>> values = { {2, "a"}, {5, "b"}, {3, "c"} };
        unsigned int n = 3;
        unsigned int t = 5;

        vector<pair<unsigned int, string>> sol = { {5, "b"} };
        auto ans = smallest_subset_sum(n, t, values);
        if (sol == ans) ++score;
    }

    // test 3: multiple size of 1 solutions, choose the lexicographically first (earliest index)
    {
        vector<pair<unsigned int, string>> values = { {5, "first"}, {5, "second"} };
        unsigned int n = 2;
        unsigned int t = 5;

        vector<pair<unsigned int, string>> sol = { {5, "first"} };
        auto ans = smallest_subset_sum(n, t, values);
        if (sol == ans) ++score;
    }

    // test 4: mmultiple minimum-size solutions of size 2, choose the lexicographically smallest indices
    // options are (1 at idx0 + 3 at idx2) where the indices are [0,2] vs (2 at idx1 + 2 at idx3) => [1,3]
    {
        vector<pair<unsigned int, string>> values = { {1, "a"}, {2, "b"}, {3, "c"}, {2, "d"} };
        unsigned int n = 4;
        unsigned int t = 4;

        vector<pair<unsigned int, string>> sol = { {1, "a"}, {3, "c"} };
        auto ans = smallest_subset_sum(n, t, values);
        if (sol == ans) ++score;
    }

    // test 5: duplicate values; must prefer earlier index for lexicographic minimum
    {
        vector<pair<unsigned int, string>> values = { {2, "x"}, {2, "y"}, {2, "z"} };
        unsigned int n = 3;
        unsigned int t = 4;

        vector<pair<unsigned int, string>> sol = { {2, "x"}, {2, "y"} };
        auto ans = smallest_subset_sum(n, t, values);
        if (sol == ans) ++score;
    }

    // test 6: empty, so no solution
    {
        vector<pair<unsigned int, string>> values = { {2, "only"} };
        unsigned int n = 1;
        unsigned int t = 1;

        vector<pair<unsigned int, string>> sol = {};
        auto ans = smallest_subset_sum(n, t, values);
        if (sol == ans) ++score;
    }

    RESULT(100 * (score / total_score));
    return 0;
}
