class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> cost(n, vector<int>(n, pow(10, 6)));
        for (auto e: edges) {
            cost[e[0]][e[1]] = e[2];
            cost[e[1]][e[0]] = e[2];
        }
        int candi = -1;
        int cur = INT_MAX;
        for (int i = 0; i < n; i++) {
            vector<int> temp_path = Dijkstra(cost, i, n);
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (j != i && temp_path[j] <= distanceThreshold) {
                    cnt++;
                }
            }
            if (cnt < cur || (cnt == cur && i > candi)) {
                candi = i;
                cur = cnt;
            }
        }
        return candi;
    }
    
    vector<int> Dijkstra(vector<vector<int>> cost, int start_point, int n) {
        vector<int> shortestPath(n, INT_MAX);
        vector<int> used(n, 0);
        shortestPath[start_point] = 0;
        while (true) {
            int v = -1;
            for (int i = 0; i < n; i++) {
                if (used[i] == 0 && (v == -1 || shortestPath[i] < shortestPath[v])) {
                    v = i;
                }
            }
            if (v == -1) {
                break;
            }
            used[v] = 1;
            for (int j = 0; j < n; j++) {
                shortestPath[j] = min(shortestPath[j], shortestPath[v] + cost[v][j]);
            }
        }
        return shortestPath;
    }
};

//Dijkstra's algorithm.
