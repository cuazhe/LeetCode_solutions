#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

typedef pair<int, int> pii;


class Solution {
public:
    vector<int> par;
    int n;
    
    int find(int i) {
        if (par[i] != i) {
            int p = find(par[i]);
            par[i] = p;
        }
        return par[i];
    }
    
    unordered_map<int, int> mp;
    
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        n = vals.size();
        vector<pii> arr;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            arr.push_back({vals[i], i});
        }
        sort(arr.begin(), arr.end());
        
        /*
        for (int i = 0; i < n; i++) {
            cout << arr[i].first << " ; " << arr[i].second << "\n";
        }
        */
        
        vector<vector<int>> graph(n);
        for (auto &e: edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        
        par.resize(n);
        
        
        for (int i = 0; i < n; i++) {
            par[i] = i;
            //cout << "par[i] = " << par[i] << "\n";
        }
        
        
        int res = 0;
        int j = 0;
        
        for (int i = 0; i < n; i++) {
            if (arr[i].first != arr[j].first) {
                j = i;
                mp.clear();
            }
            
            int sn = arr[i].second;
            mp[sn] = 1;
            visited[sn] = true;
            
            for (auto fn: graph[sn]) {
                int par_fn, par_sn;
                if (visited[fn]) {
                    //cout << "sn = " << sn << " ; fn = " << fn << "\n";
                    par_fn = find(fn);
                    par_sn = find(sn);
                    /*
                    if (par_fn == par_sn) {
                        continue;
                    }
                    */
                    res += mp[par_sn] * mp[par_fn];
                    mp[par_fn] += mp[par_sn];
                    par[par_sn] = par_fn;
                    //cout << "par_fn = " << par_fn << " ;  mp[par_fn] = " << mp[par_fn] << "\n";
                }
            }
        }
        return res + n;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    //vector<int> vals = {1,3,2,1,3};
    //vector<vector<int>> edges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    vector<int> vals = {1,1,2,2,3};
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {2, 4}};
    int res = a.numberOfGoodPaths(vals, edges);
    std::cout << res << "\n";
    return 0;
}


// AC. From solution. 576 ms, beats 27%; 181 MB, beats 18%.
