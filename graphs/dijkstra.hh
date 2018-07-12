#ifndef _DIJKSTRA_
#define _DIJKSTRA_

#include <set>
#include <vector>

using namespace std;

template <class num_t = long long>
vector<num_t> distance(vector<vector<pair<int, num_t>>> &graph, int source,
                       num_t _INF = 999999999) {
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

#endif // _DIJKSTRA_
