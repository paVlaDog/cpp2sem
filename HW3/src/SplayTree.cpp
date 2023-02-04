#include "SplayTree.h"

#include <limits>
#include <utility>
#include <vector>

struct SplayTree::Node
{
    Node * parent = nullptr;
    Node * left;
    Node * right;
    int value;
    int sz = 1;
    Node(int v, Node * l, Node * r)
        : left(l)
        , right(r)
        , value(v)
    {
    }
};

void SplayTree::calcSize(Node * v) {
    if (v == nullptr) return;
    v->sz = 1;
    if (v->left != nullptr) {
        v->sz += v->left->sz;
    }
    if (v->right != nullptr) {
        v->sz += v->right->sz;
    }
}

void SplayTree::setParent(Node * child, Node * parent)
{
    if (child != nullptr) {
        child->parent = parent;
    }
}

void SplayTree::keepParent(Node * v)
{
    setParent(v->left, v);
    setParent(v->right, v);
}

void SplayTree::inorderTraversal(const Node * x, std::vector<int> & vec)
{
    if (x != nullptr) {
        inorderTraversal(x->left, vec);
        vec.push_back(x->value);
        inorderTraversal(x->right, vec);
    }
}

std::vector<int> SplayTree::values() const
{
    std::vector<int> vec;
    vec.reserve(length);
    inorderTraversal(this->root, vec);
    return vec;
}

std::size_t SplayTree::size() const
{
    return length;
}

bool SplayTree::empty() const
{
    return length == 0;
}

SplayTree::Node * SplayTree::find(Node * v, int key) const
{
    while (v != nullptr) {
        if (key < v->value && v->left != nullptr) {
            v = v->left;
        }
        else if (key > v->value && v->right != nullptr) {
            v = v->right;
        }
        else {
            return splay(v);
        }
    }
    return nullptr;
}

int SplayTree::findMax(int k) const
{
    Node * v = root;
    while (v != nullptr) {
        if (v->left != nullptr && int(length) - k < v->left->sz) {
            v = v->left;
        }
        else if (v->right != nullptr && k <= v->right->sz) {
            v = v->right;
        }
        else {
            splay(v);
            return v->value;
        }
    }
    return 0;
}


bool SplayTree::contains(int value) const
{
    return root != nullptr && find(this->root, value)->value == value;
}

SplayTree::Node * SplayTree::createSubTree(Node *& vLink)
{
    setParent(vLink, nullptr);
    return std::exchange(vLink, nullptr);
}

bool SplayTree::insert(int key)
{
    if (contains(key)) {
        return false;
    }
    if (root == nullptr) {
        root = new Node(key, nullptr, nullptr);
    }
    else if (key < root->value) {
        root = new Node(key, createSubTree(root->left), root);
    }
    else {
        root = new Node(key, root, createSubTree(root->right));
    }
    keepParent(root);
    calcSize(root);
    length++;
    return true;
}

bool SplayTree::remove(int val)
{
    if (!contains(val)) {
        return false;
    }
    Node * leftR = root->left;
    Node * rightR = root->right;
    setParent(rightR, nullptr);
    setParent(leftR, nullptr);
    delete root;
    if (rightR == nullptr) {
        root = leftR;
        calcSize(root);
    }
    else if (leftR == nullptr) {
        root = rightR;
        calcSize(root);
    }
    else {
        rightR = find(rightR, leftR->value);
        rightR->left = leftR;
        leftR->parent = rightR;
        calcSize(rightR);
    }
    length--;
    return true;
}

void SplayTree::rotate(Node * val)
{
    bool leftSon = val->parent->left == val;
    Node *& valLink = leftSon ? val->parent->left : val->parent->right;
    Node *& sonLink = leftSon ? valLink->right : valLink->left;
    val = val->parent;
    Node * son = valLink;
    Node * par = val->parent;
    if (par != nullptr) {
        (par->left == val ? par->left : par->right) = son;
    }
    valLink = sonLink;
    sonLink = val;
    setParent(val, son);
    setParent(son, par);
    setParent(valLink, val);
    calcSize(val);
    calcSize(son);
    calcSize(par);
}

SplayTree::Node * SplayTree::splay(Node * val) const
{
    while (val->parent != nullptr) {
        if (val->parent->parent != nullptr && val->parent == val->parent->parent->left) {
            rotate(val->parent);
        }
        else if (val->parent->parent != nullptr) {
            rotate(val);
        }
        rotate(val);
    }
    root = val;
    calcSize(root);
    return val;
}

SplayTree::~SplayTree()
{
    while (root != nullptr) {
        remove(find(root, std::numeric_limits<int>::min())->value);
    }
}