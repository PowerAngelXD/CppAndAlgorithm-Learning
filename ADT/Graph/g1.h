#ifndef BALL_GRAPH_1_H
#define BALL_GRAPH_1_H

#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int id;
    Node* ptr = nullptr;
};

class G1 {
public:
    G1() {}

    std::vector<bool> visited;
    void dfs(int start, int n, std::vector<std::vector<int>> map) {
        std::cout << start << " ";
        visited[start] = true;
        for (std::size_t i = 0; i < n; i ++) {
            if (map[start][i] == 1 && !visited[i]) {
                dfs(i, n, map);
            }
        }
    }

    void bfs(int start, int n, std::vector<std::vector<int>> map) {
        std::vector<int> dists(n, -1);
        std::queue<int> q;

        dists[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; v ++) {
                if (map[u][v] == 1 && dists[v] == -1) {
                    dists[v] = dists[u] + 1;
                    q.push(v);
                }
            }
        }

        for (int i = 0; i < n ; i ++) {
            std::cout << i << " dist = " << dists[i] << std::endl;
        }
    }

    void solve() {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<int>> mm(n, std::vector<int>(n, 0));

        visited.assign(n, false);

        for (int i = 0; i < m; i ++) {
            int a, b;
            std::cin >> a >> b;
            mm[a][b] = 1;
            mm[b][a] = 1;
        }
        std::cout << "T1 Result: ";
        dfs(0, n, mm);
        std::cout << std::endl;
        std::cout << "T2 Result: ";
        bfs(0, n, mm);
    }
};

#endif // !BALL_GRAPH_1_H
