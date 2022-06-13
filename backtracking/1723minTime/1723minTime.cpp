class Solution {
public:
    int res = INT_MAX;
    int K;
    vector<int> dist;

    int minimumTimeRequired(vector<int>& jobs, int k) {
        K = k;
        dist = vector<int> (k, 0);
        int n = jobs.size();
        dfs(jobs, 0, n);
        return res;
    }

     void dfs(vector<int>& jobs, int i, int n) {
        if (i == n) {
            int cur_m = 0;
            for (int j = 0; j < K; j++) {
                cur_m = max(cur_m, dist[j]);
            }
            res = min(res, cur_m);
            return;
        }
        int ept = 0;
        for (int j = 0; j < K; j++) {
            if (dist[j] == 0) {
                ept++;
            }
        }
        if (ept > n - i) {
            return;
        }
        
        for (int j = 0; j < K; j++) {
            if (i == 0) {
                if (j != 0) {
                    return;
                }
                if (dist[j] + jobs[i] > res) {
                    continue;
                }
                dist[j] += jobs[i];
                dfs(jobs, i + 1, n);
                dist[j] -= jobs[i];
            }
            else {
                if (dist[j] + jobs[i] > res) {
                    continue;
                }
                dist[j] += jobs[i];
                dfs(jobs, i + 1, n);
                dist[j] -= jobs[i];
                if (dist[j] == 0) {
                    break; // This is the most important logic!
                }
            }
        }
        return;
    }

};
