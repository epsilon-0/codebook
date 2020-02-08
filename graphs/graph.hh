#ifndef _GRAPH_
#define _GRAPH_

#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <class w_type = short> class graph {
public:
  struct edge {
    int to;
    w_type weight;
    int reverseEdge;
    edge(int to, w_type weight) : to(to), weight(weight), reverseEdge(-1) {}
    string to_str() { return ""; }
  };
  vector<edge> edges;
  vector<vector<int>> adj;
  graph(int n) { adj.resize(n); }
  graph() {}
  int addEdge(int a, int b, w_type weight = 0) {
    if (adj.size() <= max(a, b))
      adj.resize(max(a, b) + 1);
    edge e(b, weight);
    adj[a].push_back(edges.size());
    edges.push_back(e);
    return edges.size() - 1;
  }
  void addUEdge(int a, int b, w_type weight1 = 0, w_type weight2 = 0) {
    int e1 = addEdge(a, b, weight1);
    int e2 = addEdge(b, a, weight2);
    edges[e1].reverseEdge = e2;
    edges[e2].reverseEdge = e1;
  }
  inline edge operator()(const int &a, const int &i) {
    return edges[adj[a][i]];
  }
  inline vector<int> operator[](const int &a) { return adj[a]; }
  int size() const { return adj.size(); }
};

// typedef long long w_type;
// typedef map<pair<int, int>, w_type> dw_sgraph;
// typedef vector<vector<int>> u_graph;
// typedef vector<vector<pair<w_type, int>>> uw_graph;
// typedef vector<vector<int>> d_graph;
// typedef vector<vector<pair<w_type, int>>> dw_graph;

// template <class graph> void pprint(graph g) {
//   int n = g.size();
//   cout << n << endl;
//   for (int i = 0; i < n; i++) {
//     cout << i << " :{\n";
//     for (auto nbh : g[i])
//       cout << " " << nbh << ",   ";
//     cout << "}\n";
//   }
// }

// inline void add_dwsEdge(dw_sgraph &g, int a, int b, w_type w) {
//   g[make_pair(a, b)] = w;
// }
// #define setWeight add_dwsEdge

// inline w_type getWeight(dw_sgraph &g, int a, int b) {
//   pair<int, int> node = make_pair(a, b);
//   return g[node];
// }

// inline void add_uEdge(u_graph &g, int a, int b) {
//   if (g.size() <= max(a, b)) {
//     g.resize(max(a, b) + 1);
//   }
//   cout << g.size() << endl;
//   g[a].push_back(b);
//   g[b].push_back(a);
// }

// inline void add_uwEdge(uw_graph &g, int a, int b, w_type w) {
//   if (g.size() <= max(a, b)) {
//     g.resize(max(a, b) + 1);
//   }
//   g[a].push_back(make_pair(w, b));
//   g[b].push_back(make_pair(w, a));
// }

// inline void add_dEdge(d_graph &g, int a, int b) {
//   if (g.size() <= a) {
//     g.resize(a + 1);
//   }
//   g[a].push_back(b);
// }

// inline void add_dwEdge(dw_graph &g, int a, int b, w_type w) {
//   if (g.size() <= a) {
//     g.resize(a + 1);
//   }
//   g[a].push_back(make_pair(w, b));
// }
#endif // _GRAPH_
