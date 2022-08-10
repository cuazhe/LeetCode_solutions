#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    
    vector<int> arr, tree;
    
    //int prev_max = -1;
    
    void build(int node, int L, int R) {
        if (L == R) {
            tree[node] = arr[L];
        }
        else {
            int left_node = 2 * node + 1, right_node = 2 * node + 2;
            int mid = (L + R) / 2;
            build(left_node, L, mid);
            build(right_node, mid + 1, R);
            tree[node] = max(tree[left_node], tree[right_node]);
        }
    }
    
    void update(int node, int L, int R, int cur_L, int cur_R, int k, int prev_max) {
        //if (prev_max < 0) {
        //    prev_max = query(0, 0, arr.size() - 1, cur_L, cur_R);
        //}
        if (R < cur_L || L > cur_R) {
            return;
        }
        else if (L == R) {
            //arr[node] += k;
            //int prev = query(0, 0, arr.size() - 1, cur_L, cur_R);
            tree[node] = max(tree[node] + k, prev_max + k);
        }
        else {
            int left_node = 2 * node + 1, right_node = 2 * node + 2;
            int mid = (L + R) / 2;
            update(left_node, L, mid, cur_L, cur_R, k, prev_max);
            update(right_node, mid + 1, R, cur_L, cur_R, k, prev_max);
            tree[node] = max(tree[left_node], tree[right_node]);
        }
        //prev_max = -1;
    }
    
    int query(int node, int L, int R, int cur_L, int cur_R) {
        if (R < cur_L || L > cur_R) {
            return 0;
        }
        else if (L == R) {
            return tree[node];
        }
        else if (cur_L <= L && R <= cur_R) {
            return tree[node];
        }
        else {
            int left_node = 2 * node + 1, right_node = 2 * node + 2;
            int mid = (L + R) / 2;
            int res_left = query(left_node, L, mid, cur_L, cur_R);
            int res_right = query(right_node, mid + 1, R, cur_L, cur_R);
            return max(res_left, res_right);
        }
    }
    
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> discreted_pos;
        unordered_set<int> uniq_pos;
        for (int i = 0; i < n; i++) {
            int cur_pos_L = positions[i][0], cur_pos_R = positions[i][0] + positions[i][1] - 1;
            if (uniq_pos.find(cur_pos_L) == uniq_pos.end()) {
                uniq_pos.insert(cur_pos_L);
            }
            if (uniq_pos.find(cur_pos_R) == uniq_pos.end()) {
                uniq_pos.insert(cur_pos_R);
            }
        }
        for (auto c: uniq_pos) {
            discreted_pos.push_back(c);
        }
        sort(discreted_pos.begin(), discreted_pos.end());
        
        /*
        for (auto c: discreted_pos) {
            cout << c << " ";
        }
        cout << "\n";
        */
        
        int m = discreted_pos.size();
        
        unordered_map<int, int> pos_lookup;
        
        for (int i = 0; i < m; i++) {
            pos_lookup[discreted_pos[i]] = i;
        }
        
        arr = vector<int>(m, 0);
        tree = vector<int>(4 * m, 0);
        
        build(0, 0, m - 1);
        
        vector<int> res;
        
        int cur;
        
        for (int i = 0; i < n; i++) {
            int cur_L = pos_lookup[positions[i][0]];
            int cur_R = pos_lookup[positions[i][0] + positions[i][1] - 1];
            //cout << "cur_L = " << cur_L << " ; cur_R = " << cur_R << "\n";
            int prev_max = query(0, 0, m - 1, cur_L, cur_R);
            update(0, 0, m - 1, cur_L, cur_R, positions[i][1], prev_max);
            
            /*
            for (auto c: tree) {
                cout << c << " ";
            }
            cout << "\n";
            */
            
            
            cur = query(0, 0, m - 1, 0, m - 1);
            res.push_back(cur);
        }
        return res;
    }
};



int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    //vector<vector<int>> positions = {{1, 2}, {2, 3}, {6, 1}};
    // vector<vector<int>> positions = {{100,100},{200,100}};
    //vector<vector<int>> positions = {{1,2},{2,2}, {3, 5}};
    vector<vector<int>> positions = {{2,82},{57,22},{16,66},{46,15},{5,11},{9,83},{1,32},{87,91},{64,61},{87,53}};
    vector<int> res = a.fallingSquares(positions);
    for (auto c: res) {
        cout << c << " ";
    }
    std::cout << "\n";
    return 0;
}

//AC. 32 ms, beats 61%; 14 MB, beats 25%. Segment tree. Note the use of prev_max argument in the fucntion update. Also, the technique of value squeezing is worth of mastering. 
