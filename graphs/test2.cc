#include <bits/stdc++.h>

using namespace std;

template <class num_t> class Dijkstra {
public:
  Dijkstra() {}

  vector<num_t> distance(vector<vector<pair<int, num_t>>> &graph, int source) {
    vector<num_t> distance(graph.size(), _INF);
    distance[source] = 0;
    set<pair<num_t, int>> que;
    que.insert(make_pair(0, source));
    while (!que.empty()) {
      pair<num_t, int> closest = *que.begin();
      que.erase(que.begin());
      int vert = closest.second;
      num_t dist = closest.first;
      for (auto nbh : graph[vert]) {
        int nbhVert = nbh.first;
        num_t cost = nbh.second;
        if (distance[nbhVert] > distance[vert] + cost) {
          if (distance[nbhVert] != _INF) {
            que.erase(que.find(make_pair(distance[nbhVert], nbhVert)));
          }
          distance[nbhVert] = distance[vert] + cost;
          que.insert(make_pair(distance[nbhVert], nbhVert));
        }
      }
    }
    return distance;
  }

  void setInfinity(num_t inf) { _INF = inf; }

private:
  num_t _INF = 99999999;
};

vector<vector<pair<int, int>>> adj;

int main() {
  Dijkstra<int> djk;
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d %d", &n, &m);
    adj.clear();
    adj.resize(n);
    for (int i = 0; i < m; i++) {
      int x, y;
      int w;
      scanf("%d %d %d", &x, &y, &w);
      x--;
      y--;
      adj[x].push_back(make_pair(y, w));
      adj[y].push_back(make_pair(x, w));
    }
    int s;
    scanf("%d", &s);
    s--;
    vector<int> distance = djk.distance(adj, s);
    for (int i = 0; i < n; i++)
      if (i != s)
        printf("%d ", ((distance[i] == 99999999) ? -1 : distance[i]));
    printf("\n");
  }
}
