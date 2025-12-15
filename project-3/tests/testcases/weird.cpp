#include <vector>
#include <iostream>
#include <algorithm>
#include <string>


// Struct for tree in first-child, next-sibling representation
struct TreeNode {
    int id;
    TreeNode* first_child;
    TreeNode* next_sibling;

};

// Function signature
std::vector<int> weird_traversal(TreeNode* root);

void print_vector(const std::vector<int>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << (i < v.size() - 1 ? ", " : "");
    }
    std::cout << "]" << std::endl;
}


double total_points = 0;

bool check(const std::vector<int>& got, const std::vector<int>& expected, const std::string& name, double points) {
    if (got == expected) {
        std::cout << "Test " << name << ": PASS (+" << points << " pts)" << std::endl;
        total_points += points;
        return true;
    } else {
        std::cout << "Test " << name << ": FAIL (+0 pts)" << std::endl;
        std::cout << "  Expected: "; print_vector(expected);
        std::cout << "  Got:      "; print_vector(got);
        return false;
    }
}

int main() {
    // Test 1: Original Example (5 pts)
    TreeNode* test1 = new TreeNode(
      0, 
      new TreeNode(1, nullptr,
        new TreeNode(
          2,
          new TreeNode(4,
            new TreeNode(6, nullptr, 
              new TreeNode(7, nullptr, new TreeNode(8))
            ),
            nullptr
          ),
          new TreeNode(3,
            new TreeNode(5,
              new TreeNode(9, nullptr,
                new TreeNode(10, nullptr,
                  new TreeNode(11, nullptr, new TreeNode(12))
                )
              )
            ),
            nullptr
          )
        )
      ),
      nullptr
    );
    std::vector<int> wd_ans1 = {0, 4, 5, 12, 11, 10, 9, 8, 7, 6, 3, 2, 1};
    check(weird_traversal(test1), wd_ans1, "Original Example", 5.0);
    // delete_tree(test1);

    // Test 2: single Node (4 pts)
    TreeNode* test2 = new TreeNode(99);
    std::vector<int> wd_ans2 = {99};
    check(weird_traversal(test2), wd_ans2, "Single Node", 4.0);
    // delete_tree(test2);

    // Test 3: empty Tree (4 pts)
    TreeNode* test3 = nullptr;
    std::vector<int> wd_ans3 = {};
    check(weird_traversal(test3), wd_ans3, "Empty Tree", 4.0);

    // Test 4: line Tree (4 pts)
    TreeNode* test4 = new TreeNode(0, new TreeNode(1, new TreeNode(2, new TreeNode(3))));
    std::vector<int> wd_ans4 = {0, 2, 3, 1};
    check(weird_traversal(test4), wd_ans4, "Line Tree", 4.0);
    // delete_tree(test4);

    // Test 5: wide Tree (4 pts)
    TreeNode* test5 = new TreeNode(0, 
        new TreeNode(1, nullptr, 
            new TreeNode(2, nullptr, 
                new TreeNode(3, nullptr, 
                    new TreeNode(4)
                )
            )
        )
    );
    std::vector<int> wd_ans5 = {0, 4, 3, 2, 1};
    check(weird_traversal(test5), wd_ans5, "Wide Tree", 4.0);
    // delete_tree(test5);

    // Test 6: Unbalanced (4 pts)
    TreeNode* test6 = new TreeNode(0,
        new TreeNode(1, 
            new TreeNode(3),
            new TreeNode(2)
        )
    );
    std::vector<int> wd_ans6 = {0, 3, 2, 1};
    check(weird_traversal(test6), wd_ans6, "Unbalanced", 4.0);
    // delete_tree(test6);

    std::cout << "Total Points: " << total_points << "/25" << std::endl;
    
    if (total_points == 25.0) {
        PASS();
    } else {
        FAIL();
    }
    return 0;
}