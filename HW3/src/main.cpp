#include "SplayTree.h"

#include <iostream>

int main()
{
    SplayTree tree;
    //std::cout << tree.contains(1) << " ";
    for (int i = 10; i > 0; --i) {
        tree.insert(i);
    }
    for (int i = 10; i > 0; --i) {
        tree.contains(i);
    }
    std::cout << tree.findMax(1) << '\n';
    std::cout << tree.findMax(5);
    std::cout << tree.findMax(10);
    std::cout << tree.findMax(7);
    std::cout << tree.findMax(4);
//    for (const auto value : tree.values()) {
//        std::cout << value << std::endl; // 1 .. 10
//    }
//    std::cout << "wtf";
}
