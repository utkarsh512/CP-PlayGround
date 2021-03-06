/**
 * Description: Policy-based data structures that supports normal set operation and
 *    * find_by_order(k)  returns iterator to kth element starting from 0;
 *    * order_of_key(k)   returns count of elements strictly [smaller] than k;
 */

template <class T, class cmp = std::less<T>>
using ordered_set = tree<T, null_type, cmp, rb_tree_tag,tree_order_statistics_node_update>;

template <class key, class value, class cmp = std::less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
 
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

template <class key, class val>
using hash_map = unordered_map<key, val, custom_hash>;

template <class T>
using hash_set = unordered_set<T, custom_hash>;

template <class key, class val>
using hash_table = gp_hash_table<key, val, custom_hash>;