#ifndef BALL_GRAPH_2_H
#define BALL_GRAPH_2_H

#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int id;
    Node* ptr = nullptr;
};

class G2 {
public:
    G2() {}

    std::vector<bool> visited;
    std::vector<std::vector<int>> adj;
    void dfs(int start) {
        std::cout << start << " ";
        visited[start] = true;
        for (int v: adj[start]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
    }

    void bfs(int start) {
        std::vector<int> dist(adj.size(), -1);
        std::queue<int> q;

        std::cout << "\nnow visit: " << start << "->" << std::endl;

        dist[start] = 0;
        q.push(start);

        while(! q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        for (int i = 0; i < dist.size(); i ++) {
            std::cout << i << " dist = " << dist[i] << std::endl;
        }
    }

    void solve() {
        int n, m;
        std::cin >> n >> m;
        adj.assign(n, {});

        visited.assign(n, false);

        for (int i = 0; i < m; i ++) {
            int a, b;
            std::cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        std::cout << "T1 Result: ";
        dfs(0);

        std::cout << "T2 Result: ";
        bfs(0);
    }
};

#endif // !BALL_GRAPH_2_H
