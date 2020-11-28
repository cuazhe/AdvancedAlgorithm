class Solution {
public:

    int networkDelayTime(vector<vector<int>>& times, int n, int K) {
        const int INF = 0x3f3f3f3f;
        vector<vector<int>> g(n+1, vector<int>(n+1, INF));
        for (auto &v: times){
            g[v[0]][v[1]] = v[2];
        }
        vector<int> dist(n+1, INF); // 距离起始点的最短距离
        vector<bool> st(n+1, false); // 是否已经得到最优解

        dist[K] = 0; // 起始点
        for (int i = 0; i< n - 1; i++ ){
            int t = -1;
            for (int j = 1; j <=n; j++){ // 在还未确定最短路的点中，寻找到起始点距离最小的点 的点
                if (!st[j] && (t == -1 || dist[t] > dist[j])){ 
                    t = j;
                }
            }

            st[t] = true; // t号点的最短路已经确定

            for (int j = 1; j<=n; j++){ // 用t更新其他点的距离
                dist[j] = min(dist[j], dist[t] + g[t][j]); 
            }
        }
        int ans = *max_element(dist.begin()+1, dist.end());
        return ans == INF ? -1: ans;
    }
};

# from leetcode author muyids
