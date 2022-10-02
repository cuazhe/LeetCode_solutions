#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int N;
    vector<long long> arr, tree, marker;
    
    void build_tree(int node, int left, int right) {
        if (left == right) {
            //cout << "left = " << left << " ; node = " << node << "\n";
            tree[node] = arr[left];
            return;
        }
        int mid = (left + right) / 2;
        int left_node = 2 * node + 1;
        int right_node = 2 * node + 2;
        build_tree(left_node, left, mid);
        build_tree(right_node, mid + 1, right);
        tree[node] = tree[left_node] + tree[right_node];
        return;
    }
    
    void pushdown(int node, int left, int right) {
        int left_node = 2 * node + 1, right_node = 2 * node + 2;
        int mid = (left + right) / 2;
        marker[left_node] += marker[node];
        marker[right_node] += marker[node];
        tree[left_node] += marker[node] * (mid - left + 1);
        tree[right_node] += marker[node] * (right - mid);
        marker[node] = 0;
    }
    
    void update(int node, int left, int right, int L, int R, int delta) {
        if (left > R || right < L) {
            return;
        }
        else if ((left >= L) && (right <= R)) {
            tree[node] += (right - left + 1) * delta;
            if (left < right) {
                marker[node] += delta;
            }
        }
        else {
            pushdown(node, left, right);
            int left_node = 2 * node + 1, right_node = 2 * node + 2;
            int mid = (left + right) / 2;
            update(left_node, left, mid, L, R, delta);
            update(right_node, mid + 1, right, L, R, delta);
            tree[node] = tree[left_node] + tree[right_node];
        }
        return;
    }
    
    long long query(int node, int left, int right, int L, int R) {
        if (left > R || right < L) {
            return 0;
        }
        else if ((left >= L) && (right <= R)) {
            return tree[node];
        }
        else {
            int mid = (left + right) / 2;
            int left_node = 2 * node + 1, right_node = 2 * node + 2;
            pushdown(node, left, right);
            return query(left_node, left, mid, L, R) + query(right_node, mid + 1, right, L, R);
        }
    }
    
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n = s.size();
        //cout << "n = " << n << "\n";
        N = n;
        arr = vector<long long> (N, 0);
        tree = vector<long long> (4 * N, 0);
        marker = vector<long long> (4 * N, 0);
        //cout << arr.size() << " ; " << tree.size() << "\n";
        build_tree(0, 0, N - 1);
        int m = shifts.size();
        for (int i = 0; i < m; i++) {
            if (shifts[i][2] == 0) {
                update(0, 0, N - 1, shifts[i][0], shifts[i][1], -1);
            }
            else {
                update(0, 0, N - 1, shifts[i][0], shifts[i][1], 1);
            }
            
            /*
            for (int i = 0; i < 4 * N; i++) {
                cout << tree[i] << " ";
            }
            cout << "\n";
            */
            
        }
        string res = "";
        for (int i = 0; i < n; i++) {
            int ori = s[i] - 'a';
            long long cur = ori + query(0, 0, N - 1, i, i);
            while (cur < 0) {
                cur += 26;
            }
            cur %= 26;
            res += ('a' + cur);
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    string s = "dztz";
    vector<vector<int>> shifts = {{0,0,0}, {1,1,1}};
    string res = a.shiftingLetters(s, shifts);
    std::cout << res << "\n";
    return 0;
}

// Segment tree with lazy propogation. AC. 676 ms, beats 5%; 111 MB, beats 5%.
