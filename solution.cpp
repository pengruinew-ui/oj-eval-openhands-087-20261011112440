#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to find the final position of the nth ball
int findFinalPosition(int D, long long n) {
    int pos = 1;  // Start at root
    
    for (int level = 1; level <= D; level++) {
        // At each switch, balls alternate between left and right
        // If n is odd, the ball goes left; if even, it goes right
        if (n % 2 == 1) {
            // Go left
            pos = 2 * pos;
            // Number of balls that go to the left subtree
            n = (n + 1) / 2;
        } else {
            // Go right
            pos = 2 * pos + 1;
            // Number of balls that go to the right subtree
            n = n / 2;
        }
    }
    
    return pos / 2;  // Return the last switch position
}

// Function to compute how many balls pass through each switch
void computeBallCounts(int D, long long n, vector<long long>& counts) {
    int total_switches = (1 << D) - 1;
    counts.resize(total_switches + 1, 0);
    
    // Use a queue for BFS traversal
    vector<pair<int, long long>> queue;  // (switch_position, ball_count)
    queue.push_back({1, n});
    
    while (!queue.empty()) {
        auto [pos, ball_count] = queue.back();
        queue.pop_back();
        
        if (pos > total_switches) continue;
        
        counts[pos] = ball_count;
        
        if (ball_count > 0) {
            long long left_count = (ball_count + 1) / 2;  // Balls going left
            long long right_count = ball_count / 2;      // Balls going right
            
            if (2 * pos <= total_switches && left_count > 0) {
                queue.push_back({2 * pos, left_count});
            }
            if (2 * pos + 1 <= total_switches && right_count > 0) {
                queue.push_back({2 * pos + 1, right_count});
            }
        }
    }
}

// Function to compute the final state of all switches
vector<int> computeFinalStates(int D, long long n) {
    int total_switches = (1 << D) - 1;
    vector<int> states(total_switches + 1, 0);
    
    vector<long long> ball_counts;
    computeBallCounts(D, n, ball_counts);
    
    // Each switch is toggled ball_counts[pos] times
    // If the count is odd, the switch ends up open (1)
    // If the count is even, the switch ends up closed (0)
    for (int i = 1; i <= total_switches; i++) {
        states[i] = ball_counts[i] % 2;
    }
    
    return states;
}

int main() {
    int D;
    long long n;
    cin >> D >> n;
    
    // Find the final position of the last ball
    int last_position = findFinalPosition(D, n);
    
    // Compute the final states of all switches
    vector<int> states = computeFinalStates(D, n);
    
    // Output the position where the last ball landed
    cout << last_position << endl;
    
    // Output the state of all switches at the bottom level (level D)
    // These are switches at positions 2^(D-1) to 2^D - 1
    int bottom_start = 1 << (D - 1);  // 2^(D-1)
    int bottom_end = (1 << D) - 1;  // 2^D - 1
    
    for (int i = bottom_start; i <= bottom_end; i++) {
        if (i > bottom_start) cout << " ";
        cout << states[i];
    }
    cout << endl;
    
    return 0;
}