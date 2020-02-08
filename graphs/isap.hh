#ifndef _ISAP_
#define _ISAP_

#include "graph.hh"
#include <queue>

using namespace std;

class ISAP {
public:
#define oo 10000000000000l // Infinity

  // Nodes, Arcs, the source node and the sink node
  int n, m, source, sink;

  // graph classes for maintaining
  // Graph and Flow
  graph<long long> G, F;
  // int G[N][N], F[N][N];

  vector<int> pi;          // predecessor list
  vector<int> CurrentNode; // Current edge for each node

  queue<int> q; // Queue for reverse BFS

  vector<int> d;     // Distance function
  vector<int> numbs; // numbs[k] is the number of nodes i with d[i]==k

  ISAP(graph<long long> G, int n, int source, int sink) {
    this->G = G;
    this->n = n;
    this->source = source;
    this->sink = sink;
    pi.resize(n, 0);
    CurrentNode.resize(n, 0);
    d.resize(n, 0);
    numbs.resize(n, 0);
  }

#endif // _ISAP_
