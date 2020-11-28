class Solution {
public:
    
    int p[110];
    
    
    int find(int a) {
        if (a != p[a]) p[a] = find(p[a]);
        return p[a];
    }

    int work1(int n, vector<vector<int>>& edges, int k) { // 不选第k条边的最小生成树的权重
        for (int i = 0; i < n; i ++ ) p[i] = i;
        int cost = 0, cnt = 0;
        for (auto& e:edges) {
            if (e[3] == k) continue;  //  如果是第k条边，则跳过
            int f1 = find(e[1]), f2 = find(e[2]);
            if (f1 != f2) {
                cost += e[0];
                cnt ++;
                if (cnt == n - 1) break;
                p[f1] = f2;
            }
        }
        if (cnt == n - 1) return cost;
        else return INT_MAX;
    }
    
    int work2(int n, vector<vector<int>>& edges, int k) { // 一定选第k条边的最小生成树的权重
        for (int i = 0; i < n; i ++ ) p[i] = i;
        int cost = 0, cnt = 0;
        
        for (auto& e : edges) {  // 先向第k条边加入到集合中
            if (e[3] == k) {
                cost += e[0];
                cnt ++;
                p[e[1]] = e[2];
                break;
            }
        }
        
        for (auto& e: edges) {
            int f1 = find(e[1]), f2 = find(e[2]);
            if (f1 != f2) {
                cost += e[0];
                cnt ++;
                if (cnt == n - 1) break;
                p[f1] = f2;
            }
        }
        if (cnt == n - 1) return cost;
        else return INT_MAX;
    }
    
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
            
        int m = edges.size();
        for (int i = 0; i < m; i ++ ) {
            auto& e = edges[i];
            swap(e[0], e[2]);
            e.push_back(i);
        }
        sort(edges.begin(), edges.end());
        
        int min_cost = work1(n, edges, -1);   // 求出最小生成树权重
        // cout << min_cost << endl;
        vector<vector<int>> ans(2);
        for (int i = 0; i < m; i ++ ) {
            if (work1(n, edges, i) > min_cost) ans[0].push_back(i);  // 判断是否为关键边
            else if (work2(n, edges, i) == min_cost) ans[1].push_back(i);  // 判断是否为伪关键边
        } 
        return ans;
        
    }
};

// from author wangdh15 leetcode
