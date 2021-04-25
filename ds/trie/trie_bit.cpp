struct Node {
  int cnt[2];
  Node *pt[2];
  Node() {
    for (int i = 0; i < 2; i++) {
      cnt[i] = 0;
      pt[i] = nullptr;
    }
  }
};

template <int BITS>
struct Trie {
  Node *root, *cur;
  Trie() {
    root = new Node();
  }
  void insert(int x) {
    insert(root, x, BITS - 1);
  }
  void remove(int x) {
    remove(root, x, BITS - 1);
  }
  int max_xor(int x) {
    return max_xor(root, x, BITS - 1);
  }
  bool insert(Node *cur, int x, int b) {
    if (b == -1) return true;
    bool c = (x & (1 << b))? 1: 0;
    if (cur->pt[c] == nullptr) {
      cur->pt[c] = new Node();
    }
    cur->cnt[c]++;
    return insert(cur->pt[c], x, b - 1);
  }
  void remove(Node *cur, int x, int b) {
    if (b == -1) {
      return;
    }
    bool c = (x & (1 << b))? 1: 0;
    cur->cnt[c]--;
    remove(cur->pt[c], x, b - 1);
  }
  int max_xor(Node *cur, int x, int b) {
    if (b == -1) {
      return 0;
    }
    bool c = (x & (1 << b))? 1: 0;
    c ^= 1;
    if (cur->cnt[c]) {
      return (1 << b) + max_xor(cur->pt[c], x, b - 1);
    } else {
      return max_xor(cur->pt[c ^ 1], x, b - 1);
    }
  }
};
