#ifndef _DINIC_
#define _DINIC_

#include <queue>
#include <vector>

using namespace std;

int n;
vector<vector<pair<int, int>>> adj;
vector<vector<int>> reversePosition;
vector<vector<int>> flow;
vector<int> level;

void addEdge(int u, int v, int c) {
  adj[u].push_back(make_pair(v, c));
  adj[v].push_back(make_pair(u, 0));
  reversePosition[u].push_back(adj[v].size() - 1);
  reversePosition[v].push_back(adj[u].size() - 1);
  flow[u].push_back(0);
  flow[v].push_back(0);
}

bool BFS(int s, int t) {
  for (int i = 0; i < n; i++)
    level[i] = -1;
  level[s] = 0;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i].first;
      int cFlow = flow[u][i];

    }
  }
}

#endif // _DINIC_
