#include <vector>

// Struct for tree in first-child, next-sibling representation
struct TreeNode {
    int id;
    TreeNode* first_child;
    TreeNode* next_sibling;

};

TreeNode* bits_to_tree(const std::vector<bool>& bits);

bool check_equal(TreeNode* t1, TreeNode* t2) {
    if(t1 == nullptr && t2 == nullptr) return true;
    if(t1 != nullptr && t2 == nullptr) return false;
    if(t1 == nullptr && t2 != nullptr) return false;
    if(t1->id != t2->id) return false;
    return check_equal(t1->first_child, t2->first_child)
            && check_equal(t1->next_sibling, t2->next_sibling);
}

int main() {
    const std::vector<bool> test1 = {1, 0};
    const std::vector<bool> test2 = {1, 0, 1, 0, 1, 1, 0, 1, 0, 0};

    TreeNode* ans1 = bits_to_tree(test1);
    TreeNode* ans2 = bits_to_tree(test2);

    TreeNode* sol1 = new TreeNode(0, new TreeNode(1));
    TreeNode* sol2 = new TreeNode(
      0, new TreeNode(1,
        nullptr,
        new TreeNode(2,
          nullptr,
          new TreeNode(3,
            new TreeNode(4, nullptr, new TreeNode(5))
          )
        )
      )
    );


    const std::vector<bool> test3 = {}; // empty bits -> single root
    TreeNode* ans3 = bits_to_tree(test3);
    TreeNode* sol3 = new TreeNode(0);

    const std::vector<bool> test4 = {0, 1}; // invalid prefix
    TreeNode* ans4 = bits_to_tree(test4);
    TreeNode* sol4 = nullptr;

    const std::vector<bool> test5 = {1, 1, 0}; // invalid count
    TreeNode* ans5 = bits_to_tree(test5);
    TreeNode* sol5 = nullptr;

    double total_score = 5.0;
    double score = 0.0;

    if(check_equal(ans1, sol1)) ++score;
    if(check_equal(ans2, sol2)) ++score;
    if(check_equal(ans3, sol3)) ++score;
    if(check_equal(ans4, sol4)) ++score;
    if(check_equal(ans5, sol5)) ++score;


    RESULT(100*(score / total_score));

    return 0;

}
