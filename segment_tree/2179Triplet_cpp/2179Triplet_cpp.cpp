#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;



class Solution {
public:
    vector<int> tree, leaves;
    
    void build_tree(int node, int left, int right) {
        if (left == right) {
            tree[node] = leaves[left];
        }
        else {
            int mid = (left + right) / 2;
            int left_node = 2 * node + 1, right_node = 2 * node + 2;
            build_tree(left_node, left, mid);
            build_tree(right_node, mid + 1, right);
            tree[node] = tree[left_node] + tree[right_node];
        }
        return;
    }
    
    void update(int node, int left, int right, int idx, int k) {
        if (idx < left || idx > right) {
            return;
        }
        if (left == right) {
            tree[node] += k;
            return;
        }
        int mid = (left + right) / 2;
        int left_node = 2 * node + 1, right_node = 2 * node + 2;
        update(left_node, left, mid, idx, k);
        update(right_node, mid + 1, right, idx, k);
        tree[node] = tree[left_node] + tree[right_node];
        return;
    }
    
    int query(int node, int left, int right, int cur_L, int cur_R) {
        if (left > cur_R || right < cur_L) {
            return 0;
        }
        if (left >= cur_L && right <= cur_R) {
            return tree[node];
        }
        int mid = (left + right) / 2;
        int left_node = 2 * node + 1, right_node = 2 * node + 2;
        int res_L = query(left_node, left, mid, cur_L, cur_R);
        int res_R = query(right_node, mid + 1, right, cur_L, cur_R);
        return res_L + res_R;
    }
    
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> lookup;
        int n = nums1.size();
        for (int i = 0; i < n; i++) {
            lookup[nums1[i]] = i;
        }
        vector<int> arr(n, 0);
        for (int i = 0; i < n; i++) {
            arr[i] = lookup[nums2[i]];
        }
        tree = vector<int> (4 * n, 0);
        leaves = vector<int> (n, 0);
        long long res = 0;
    
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                update(0, 0, n - 1, arr[i], 1);
                continue;
            }
            if (arr[i] > 0) {
                long long cur_smaller = query(0, 0, n - 1, 0, arr[i] - 1);
                long long cur_larger = (n - 1 - arr[i]) - (i - cur_smaller);
                res += cur_smaller * cur_larger;
            }
            update(0, 0, n - 1, arr[i], 1);
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    //vector<int> nums1 = {2,0,1,3};
    //vector<int> nums2 = {0,1,2,3};
    vector<int> nums1 = {4,0,1,3,2};
    vector<int> nums2 = {4,1,0,2,3};
    int res = a.goodTriplets(nums1, nums2);
    std::cout << res << "\n";
    return 0;
}

// segment tree. AC. 340 ms, beats 11%; 110 MB, beats 10%.
