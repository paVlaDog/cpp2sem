#pragma once

#include <vector>

class SplayTree
{
private:
    struct Node;
    mutable Node * root = nullptr;
    std::size_t length = 0;

    static void rotate(Node * val);
    static void setParent(Node * child, Node * parent);
    static void keepParent(Node * v);
    static Node * createSubTree(Node *& vLink);
    Node * splay(Node * v) const;
    Node * find(Node * v, int key) const;
    static void inorderTraversal(const Node * x, std::vector<int> & vec);
    static void calcSize(Node * v);

public:
    bool contains(int value) const;
    int findMax(int k) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~SplayTree();
};
