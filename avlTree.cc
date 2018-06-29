#include <bits/stdc++.h>
#include <memory>

using namespace std;

template <class key_t, class value_t> class AVLTree {
public:
  class AVLNode {
  public:
    key_t key;
    value_t value;
    value_t carry;
    key_t minK;
    key_t maxK;
    shared_ptr<AVLNode> left;
    shared_ptr<AVLNode> right;
    int height;
    int size;
    AVLNode(key_t key, value_t value) {
      this->key = key;
      this->minK = key;
      this->maxK = key;
      this->value = value;
      this->height = 1;
      this->carry = 0;
      this->size = 0;
    }
  };

  shared_ptr<AVLNode> root = NULL;

  int getHeight(shared_ptr<AVLNode> node) {
    if (node == NULL)
      return 0;
    return node->height;
  }

  int getSize(shared_ptr<AVLNode> node) {
    if (node == NULL)
      return 0;
    return node->size;
  }

  void pushDown(shared_ptr<AVLNode> node) {
    node->value += node->carry;
    if (node->right != NULL)
      node->right->carry += node->carry;
    if (node->left != NULL)
      node->left->carry += node->carry;
    node->carry = 0;
  }

  void updateInfo(shared_ptr<AVLNode> node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    node->size = getSize(node->left) + getSize(node->right) + 1;
    node->maxK = node->key;
    if (node->right != NULL)
      node->maxK = node->right->maxK;
    node->minK = node->key;
    if (node->left != NULL)
      node->minK = node->left->minK;
  }

  shared_ptr<AVLNode> rightRotate(shared_ptr<AVLNode> node) {
    shared_ptr<AVLNode> nodel = node->left;
    shared_ptr<AVLNode> nodelr = nodel->right;
    nodel->right = node;
    node->left = nodelr;
    updateInfo(node);
    updateInfo(nodel);
    return nodel;
  }

  shared_ptr<AVLNode> leftRotate(shared_ptr<AVLNode> node) {
    shared_ptr<AVLNode> noder = node->right;
    shared_ptr<AVLNode> noderl = noder->left;
    noder->left = node;
    node->right = noderl;
    updateInfo(node);
    updateInfo(noder);
    return noder;
  }

  int getBalance(shared_ptr<AVLNode> node) {
    if (node == NULL)
      return 0;
    return getHeight(node->left) - getHeight(node->right);
  }

  shared_ptr<AVLNode> doInsert(shared_ptr<AVLNode> node, key_t key,
                               value_t value) {
    if (node == NULL)
      return (make_shared<AVLNode>(key, value));
    pushDown(node);
    if (key < node->key)
      node->left = doInsert(node->left, key, value);
    else if (key > node->key)
      node->right = doInsert(node->right, key, value);
    else {
      node->value = value;
      return node;
    }
    updateInfo(node);
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
      return rightRotate(node);
    if (balance < -1 && key > node->right->key)
      return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
    return node;
  }

  void insert(key_t key, value_t value) { root = doInsert(root, key, value); }

  value_t find(key_t key) { return doFind(root, key); }

  value_t doFind(shared_ptr<AVLNode> node, key_t key) {
    if (node == NULL)
      return -1;
    pushDown(node);
    if (key == node->key)
      return node->value;
    else if (key < node->key)
      return doFind(node->left, key);
    return doFind(node->right, key);
  }

  void doUpdate(shared_ptr<AVLNode> node, key_t left, key_t right,
                value_t added) {
    if (node == NULL) {
      return;
    } else if (node->minK >= left && node->maxK <= right) {
      node->carry += added;
      return;
    } else if (node->minK > right || node->maxK < left) {
      return;
    } else {
      if (node->key <= right && node->key >= left)
        node->value += added;
      doUpdate(node->left, left, right, added);
      doUpdate(node->right, left, right, added);
    }
  }

  void update(key_t left, key_t right, value_t added) {
    doUpdate(root, left, right, added);
  }

  // this function only works when working on type <string, int>
  vector<string> treeList(shared_ptr<AVLNode> node) {
    vector<string> output;
    if (node != NULL) {
      auto left = treeList(node->left);
      auto right = treeList(node->right);
      string current = "[" + node->key + ": " + to_string(node->value) + "]-{" +
                       node->minK + ", " + node->maxK + ", " +
                       to_string(node->carry) + +", " + to_string(node->size) +
                       "}";
      string padding = "";
      for (int i = 0; i < current.size(); i++)
        padding += " ";
      for (auto level : left)
        output.push_back(padding + level);
      output.push_back(current);
      for (auto level : right)
        output.push_back(padding + level);
    }
    return output;
  }
  string str() {
    auto levels = treeList(root);
    string output = "";
    for (auto level : levels)
      output += level + "\n";
    return output;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  AVLTree<string, long long> tree;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int t;
    cin >> t;
    if (t == 1) {
      string s;
      long long v;
      cin >> s >> v;
      //      cout << "1 " << s << " " << v << endl;
      tree.insert(s, v);
    } else if (t == 2) {
      string a, b;
      long long v;
      cin >> a >> b >> v;
      //      cout << "2 " << a << " " << b << " " << v << endl;
      tree.update(min(a, b), max(a, b), v);
    } else if (t == 3) {
      string s;
      cin >> s;
      //      cout << 3 << " " << s << endl;
      cout << tree.find(s) << endl;
    }
  }
}
