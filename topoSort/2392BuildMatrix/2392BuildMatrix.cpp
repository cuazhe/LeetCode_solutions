#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;


class Solution {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<int> row_res = topSort(rowConditions, k);
        vector<int> col_res = topSort(colConditions, k);
        
//        for (auto c: row_res) {
//            cout << c << " ";
//        }
//        cout << "\n";
//        for (auto c: col_res) {
//            cout << c << " ";
//        }
//        cout << "\n";
        
        if ((row_res.size() < k) || (col_res.size() < k)) {
            return {};
        }
        unordered_map<int, int> col_pos;
        for (int i = 0; i < k; i++) {
            col_pos[col_res[i]] = i;
        }
        vector<vector<int>> res(k, vector<int>(k, 0));
        for (int i = 0; i < k; i++) {
            int cur = row_res[i];
            res[i][col_pos[cur]] = cur;
        }
        return res;
    }
    
    vector<int> topSort(vector<vector<int>>& arr, int k) {
        vector<int> res;
        vector<int> indeg(k + 1, 0);
        unordered_map<int, vector<int>> graph;
        for (auto c: arr) {
            indeg[c[1]]++;
            graph[c[0]].push_back(c[1]);
        }
        queue<int> stk;
        for (int i = 1; i <= k; i++) {
            if (indeg[i] == 0) {
                stk.push(i);
            }
        }
        while (stk.size() > 0) {
            int cur = stk.front();
            stk.pop();
            res.push_back(cur);
            for (auto nxt: graph[cur]) {
                indeg[nxt]--;
                if (indeg[nxt] == 0) {
                    stk.push(nxt);
                }
            }
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    vector<vector<int>> rowConditions = {{1, 2}, {3, 2}};
    vector<vector<int>> colConditions = {{2, 1}, {3, 2}};
    int k = 3;
    vector<vector<int>> res = a.buildMatrix(k, rowConditions, colConditions);
    for (auto &c: res) {
        for (auto d: c) {
            cout << d << " ";
        }
        cout << "\n";
    }
    //std::cout << "Hello, World!\n";
    return 0;
}

// AC. 152 ms, beats 25%; 61 MB, beats 24%.
