#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int D;
    long long n;
    cin >> D >> n;
    
    // Calculate total number of switches (internal nodes)
    int total_switches = (1 << D) - 1;  // 2^D - 1
    
    // Initialize all switches to closed (0)
    vector<int> switches(total_switches + 1, 0);  // 1-based indexing
    
    int last_position = -1;
    
    // Simulate each ball
    for (long long ball = 1; ball <= n; ball++) {
        int current_pos = 1;  // Start at root
        int last_switch = -1;
        
        // Fall through the tree until reaching a leaf
        while (current_pos <= total_switches) {
            last_switch = current_pos;  // Remember the last switch we visited
            if (switches[current_pos] == 0) {
                // Switch is closed, open it and go left
                switches[current_pos] = 1;
                current_pos = 2 * current_pos;  // Go to left child
            } else {
                // Switch is open, close it and go right
                switches[current_pos] = 0;
                current_pos = 2 * current_pos + 1;  // Go to right child
            }
        }
        
        // The last position is the last switch visited
        last_position = last_switch;
    }
    
    // Output the position where the last ball landed
    cout << last_position << endl;
    
    // Output the state of all switches at the bottom level (level D)
    // These are switches at positions 2^(D-1) to 2^D - 1
    int bottom_start = 1 << (D - 1);  // 2^(D-1)
    int bottom_end = (1 << D) - 1;  // 2^D - 1
    
    for (int i = bottom_start; i <= bottom_end; i++) {
        if (i > bottom_start) cout << " ";
        cout << switches[i];
    }
    cout << endl;
    
    return 0;
}