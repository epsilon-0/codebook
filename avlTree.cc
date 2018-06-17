#include <bits/stdc++.h>

using namespace std;

template <class key_t, class value_t> class AVLTree {
public:
  class AVLNode {
  public:
    key_t key;
    value_t value;
    shared_ptr<AVLNode> left;
    shared_ptr<AVLNode> right;
    int height;
    AVLNode(key_t key, value_t value) {
      this->key = key;
      this->value = value;
      this->height = 1;
    }
  };

  shared_ptr<AVLNode> root = NULL;

  int getHeight(shared_ptr<AVLNode> node) {
    if (node == NULL)
      return 0;
    return node->height;
  }

  void updateInfo(shared_ptr<AVLNode> node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
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
    if (key == node->key)
      return node->value;
    else if (key < node->key)
      return doFind(node->left, key);
    return doFind(node->right, key);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  AVLTree<int, int> tree;
  for (int i = 0; i < 10000; i++)
    tree.insert(i, i * i);
  for (int i = 0; i < 10000; i++)
    cout << tree.find(i) << endl;
}
