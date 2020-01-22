class Solution {
public:
    vector<int> par = {0};
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        size_t n = edges.size();
        for (int i = 0; i < n; i++) {
            par.push_back(i + 1);
        }
        vector<int> res;
        for (auto c: edges) {
            if (find(c[0]) == find(c[1])) {
                res = c;
            }
            else {
                unite(c[0], c[1]);
            }
        }
        return res;
    }
    
    int find(int a) {
        if (a == par[a]) return a;
        par[a] = find(par[a]);
        return par[a];
    }
    
    void unite(int a, int b) {
        int x = find(a);
        int y = find(b);
        if (x == y) return;
        par[x] = y;
        return;
    }
};
