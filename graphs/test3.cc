#include <bits/stdc++.h>
#include <tuple>

using namespace std;

template <class w_type = short> class graph {
public:
  typedef tuple<w_type, int, int> edge;
#define reverseEdge(e) get<0>(e)
  vector<edge> edges;
  vector<vector<edge *>> adj;
  graph(int n) {
    adj.clear();
    adj.resize(n);
    edges.clear();
  }
  graph() {}
  edge *addEdge(int a, int b, w_type weight = 0) {
    edge e(b, weight);
    edges.push_back(e);
    adj[a].push_back((&(edges.back())));
    return &(edges.back());
  }
  void addUEdge(int a, int b, w_type weight1 = 0, w_type weight2 = 0) {
    edge *e1 = addEdge(a, b, weight1);
    edge *e2 = addEdge(b, a, weight2);
    reverseEdge(*e1) = e2;
    reverseEdge(*e2) = e1;
  }
  inline edge &operator()(const int &a, const int &i) {
    return edges[adj[a][i]];
  }
  inline vector<edge *> &operator[](const int &a) { return adj[a]; }
  int size() const { return adj.size(); }
};

template <class w_type = short> class dijkstra {
public:
  vector<w_type> shortest_path(graph<w_type> &g, int source) {
    vector<w_type> distance(g.size(), _INF);
    distance[source] = 0;
    set<pair<w_type, int>> que;
    que.insert(make_pair(0, source));
    while (!que.empty()) {
      pair<w_type, int> closest = *que.begin();
      que.erase(que.begin());
      int vert = closest.second;
      w_type dist = closest.first;
      for (auto e : g[vert]) {
        int nbhVert = e->to;
        w_type cost = e->weight;
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

  void setInfinity(w_type inf) { _INF = inf; }

private:
  w_type _INF = 255;
};

const int inf = 1000000000;

int main() {
  int t;
  scanf("%d", &t);
  dijkstra<int> djk;
  djk.setInfinity(inf);
  while (t--) {
    int n, m;
    scanf("%d %d", &n, &m);
    graph<int> g(n);
    for (int i = 0; i < m; i++) {
      int x, y;
      int w;
      scanf("%d %d %d", &x, &y, &w);
      x--;
      y--;
      g.addUEdge(x, y, w, w);
    }
    int s;
    cin >> s;
    s--;
    vector<int> distance = djk.shortest_path(g, s);
    for (int i = 0; i < n; i++)
      if (i != s)
        printf("%d ", ((distance[i] == inf) ? -1 : distance[i]));
    printf("\n");
  }
}
