#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
struct GridNode {
    int x;
    int y;
    double path_cost;
    int pred_x;
    int pred_y;
    bool operator> (const GridNode&) const;
    bool operator>=(const GridNode&) const;
    bool operator==(const GridNode&) const;
    bool operator< (const GridNode&) const;
    bool operator<=(const GridNode&) const;
    bool operator!=(const GridNode&) const;
};

inline bool GridNode::operator> (const GridNode& node) const { return path_cost > node.path_cost; }
inline bool GridNode::operator>=(const GridNode& node) const { return path_cost >= node.path_cost; }
inline bool GridNode::operator==(const GridNode& node) const { return path_cost == node.path_cost; }
inline bool GridNode::operator< (const GridNode& node) const { return path_cost < node.path_cost; }
inline bool GridNode::operator<=(const GridNode& node) const { return path_cost <= node.path_cost; }
inline bool GridNode::operator!=(const GridNode& node) const { return path_cost != node.path_cost; }

struct GridEdge {
    int from_x;
    int from_y;
    int to_x;
    int to_y;
};

double heuristic_cost(GridNode start, GridNode dest);

std::vector<GridNode> a_star_algorithm(
    int m, 
    int n, 
    std::vector<GridEdge> edges, 
    GridNode source, 
    GridNode target,
    std::function<double(GridNode,GridNode)> h
);



int main() {
    double total_score = 25.0;
    double score = 0.0;

    // Test 1: Simple straight horizontal path
    // Grid: 5x1, path from (0,0) to (4,0)
    {
        std::vector<GridEdge> edges = {
            {0,0,1,0}, {1,0,2,0}, {2,0,3,0}, {3,0,4,0}
        };
        GridNode source{0, 0, 0.0, -1, -1};
        GridNode target{4, 0, 0.0, -1, -1};
        
        std::vector<GridNode> result = a_star_algorithm(5, 1, edges, source, target, heuristic_cost);
        
        if (result.size() == 5 && 
            result[0].x == 0 && result[0].y == 0 &&
            result[4].x == 4 && result[4].y == 0 &&
            std::abs(result[4].path_cost - 4.0) < 0.001) {
            score += 5.0;
        }
    }

    // Test 2: Path with diagonal movements
    // Grid: 3x3, path from (0,0) to (2,2)
    {
        std::vector<GridEdge> edges = {
            {0,0,1,0}, {0,0,0,1}, {0,0,1,1},
            {1,0,2,0}, {1,0,1,1}, {1,0,2,1},
            {0,1,1,1}, {0,1,0,2}, {0,1,1,2},
            {1,1,2,1}, {1,1,1,2}, {1,1,2,2},
            {2,0,2,1}, {2,1,2,2}, {1,2,2,2}, {0,2,1,2}
        };
        GridNode source{0, 0, 0.0, -1, -1};
        GridNode target{2, 2, 0.0, -1, -1};
        
        std::vector<GridNode> result = a_star_algorithm(3, 3, edges, source, target, heuristic_cost);
        
        if (result.size() == 3 && 
            result[0].x == 0 && result[0].y == 0 &&
            result[2].x == 2 && result[2].y == 2 &&
            std::abs(result[2].path_cost - 3.0) < 0.001) { // Two diagonal moves
            score += 5.0;
        }
    }

    // Test 3: Path with obstacle (no direct diagonal)
    // Grid: 3x3, path from (0,0) to (2,2), but no direct diagonal at (1,1)
    {
        std::vector<GridEdge> edges = {
            {0,0,1,0}, {0,0,0,1}, // No diagonal from (0,0) to (1,1)
            {1,0,2,0}, {1,0,1,1}, 
            {0,1,1,1}, {0,1,0,2},
            {1,1,2,1}, {1,1,1,2}, // No diagonal from (1,1) to (2,2)
            {2,0,2,1}, {2,1,2,2}, {1,2,2,2}, {0,2,1,2}
        };
        GridNode source{0, 0, 0.0, -1, -1};
        GridNode target{2, 2, 0.0, -1, -1};
        
        std::vector<GridNode> result = a_star_algorithm(3, 3, edges, source, target, heuristic_cost);
        
        if (result.size() == 5 && // Should take longer path
            result[0].x == 0 && result[0].y == 0 &&
            result[4].x == 2 && result[4].y == 2 &&
            std::abs(result[4].path_cost - 4.0) < 0.001) { // Four cardinal moves
            score += 5.0;
        }
    }

    // Test 4: No path exists
    // Grid: 3x3, disconnected components
    {
        std::vector<GridEdge> edges = {
            {0,0,1,0}, {1,0,0,0}, // Component 1
            {2,2,2,1}, {2,1,2,2}  // Component 2 (disconnected)
        };
        GridNode source{0, 0, 0.0, -1, -1};
        GridNode target{2, 2, 0.0, -1, -1};
        
        std::vector<GridNode> result = a_star_algorithm(3, 3, edges, source, target, heuristic_cost);
        
        if (result.empty()) {
            score += 5.0;
        }
    }

    // Test 5: Complex path with multiple options
    // Grid: 4x4, multiple paths from (0,0) to (3,3)
    {
        std::vector<GridEdge> edges;
        // Create a fully connected 4x4 grid
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                // Add all 8 directional edges (if valid)
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4) {
                            edges.push_back({x, y, nx, ny});
                        }
                    }
                }
            }
        }
        
        GridNode source{0, 0, 0.0, -1, -1};
        GridNode target{3, 3, 0.0, -1, -1};
        
        std::vector<GridNode> result = a_star_algorithm(4, 4, edges, source, target, heuristic_cost);
        
        // Optimal path should use 3 diagonal moves
        if (!result.empty() && 
            result[0].x == 0 && result[0].y == 0 &&
            result.back().x == 3 && result.back().y == 3 &&
            std::abs(result.back().path_cost - 4.5) < 0.001) { // 3 diagonal moves at 1.5 each
            score += 5.0;
        }
    }

    RESULT(100*(score / total_score));

    return 0;
}