/**
 * Description: Directed graph containing edges from/to a given vertex to a contiguous range
 *              range of vertices (See problem at https://codeforces.com/contest/786/problem/B)
 * Methods:
 *   1. digraph<T, SZ> g => initializes a directed graph with SZ (must be a power of 2) number of nodes
 *                          with edge weights having 'T' as their datatype
 *   2. add_edge(u, v, w) => adds a directed edge from vertex u to vertex v with weight w
 *   3. add_edge_from(u, l, r, w) => adds directed edge from vertex u to each vertex in the range [l; r], each edge having weight w
 *   4. add_edge_to(u, l, r, w) => adds directed edge from each of the vertex in range [l; r] to vertex u, each edges having weight w
 *
 * Verification: https://codeforces.com/contest/786/submission/113369043
 */

template <class T, int SZ>
struct digraph {
  vector<vector<int>> g;
  vector<pair<pi, T>> edges;

  void _add_edge(int from, int to, T w) {
    g[from].pb(sz(edges));
    edges.pb(make_pair(make_pair(from, to), w));
  }

  void _add_edge_to_children(int v = 1, int tl = 1, int tr = SZ) {
    if (tl == tr) return;
    else {
      int tm = (tl + tr) >> 1;
      _add_edge(SZ + v, SZ + (v << 1), (T) 0);
      _add_edge(SZ + v, SZ + (v << 1 | 1), (T) 0);
      _add_edge_to_children(v << 1, tl, tm);
      _add_edge_to_children(v << 1 | 1, tm + 1, tr);
    }
  }

  void _add_edge_to_parent(int v = 1, int tl = 1, int tr = SZ) {
    if (tl == tr) return;
    else {
      int tm = (tl + tr) >> 1;
      _add_edge(3 * SZ + (v << 1), 3 * SZ + v, (T) 0);
      _add_edge(3 * SZ + (v << 1 | 1), 3 * SZ + v, (T) 0);
      _add_edge_to_parent(v << 1, tl, tm);
      _add_edge_to_parent(v << 1 | 1, tm + 1, tr);
    }
  }

  void _add_edge_from(int l, int r, int u, T w, int v = 1, int tl = 0, int tr = SZ - 1) {
    if (l > tr || r < tl) return;
    if (l <= tl && tr <= r) {
      _add_edge(u, SZ + v, w);
    } else {
      int tm = (tl + tr) >> 1;
      _add_edge_from(l, r, u, w, v << 1, tl, tm);
      _add_edge_from(l, r, u, w, v << 1 | 1, tm + 1, tr);
    }
  }

  void _add_edge_to(int l, int r, int u, T w, int v = 1, int tl = 0, int tr = SZ - 1) {
    if (l > tr || r < tl) return;
    if (l <= tl && tr <= r) {
      _add_edge(3 * SZ + v, u, w);
    } else {
      int tm = (tl + tr) >> 1;
      _add_edge_to(l, r, u, w, v << 1, tl, tm);
      _add_edge_to(l, r, u, w, v << 1 | 1, tm + 1, tr);
    }
  }

  void add_edge(int from, int to, T w = (T) 1) {
    _add_edge(from, to, w);
  }

  void add_edge_from(int from, int l, int r, T w = (T) 1) {
    _add_edge_from(l, r, from, w);
  }

  void add_edge_to(int to, int l, int r, T w = (T) 1) {
    _add_edge_to(l, r, to, w);
  }

  digraph() {
    g.resize(5 * SZ);
    for (int i = 0; i < SZ; i++) {
      _add_edge(i + 2 * SZ, i, (T) 0);
      _add_edge(i, i + 4 * SZ, (T) 0);
    }
    _add_edge_to_children();
    _add_edge_to_parent();
  }
};
