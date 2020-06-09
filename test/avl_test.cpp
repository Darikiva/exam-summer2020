//
// Created by darik on 6/8/2020.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../src/trees/AVLTree.hpp"

#include <cstdlib>

using namespace exam::trees;

TEST_CASE ("AVLTree insertion") {
    {
        AVLTree<int> tree;
        tree.insert(59);
        tree.insert(1);
        tree.insert(5);
        tree.insert(78);
        tree.insert(12);
        tree.insert(23);
        tree.insert(80);
        tree.insert(45);
        tree.insert(39);
                REQUIRE(tree.print() == "12(5(1),59(39(23,45),78(80)))");
    }

    {
        AVLTree<int> tree;
        for (int i = 0; i < 16; ++i) {
            tree.insert(i);
        }
                REQUIRE(tree.print() == "7(3(1(0,2),5(4,6)),11(9(8,10),13(12,14(15))))");
    }

    {
        AVLTree<int> tree;
        for (int i = 16; i > 0; --i) {
            tree.insert(i);
        }
                REQUIRE(tree.print() == "9(5(3(2(1),4),7(6,8)),13(11(10,12),15(14,16)))");
    }
}

TEST_CASE ("AVLTree search") {
    AVLTree<int> tree;
    for (int i = 0; i < 40; ++i) {
        tree.insert(i);
    }

    for (int i = 0; i < 10; ++i) {
        int searching = std::rand() % 40;
                REQUIRE(tree.search(searching)->_key == searching);
    }

            REQUIRE(tree.search(40) == nullptr);
            REQUIRE(tree.search(-1) == nullptr);
}

TEST_CASE ("AVLTree iterators") {
    AVLTree<int> tree;
    for (int i = 0; i < 30; ++i) {
        tree.insert(i);
    }
    int count{0};
    for (const auto &item: tree) {
                REQUIRE(item == tree.search(count)->_key);
        ++count;
    }
            REQUIRE(count == 30);
}

TEST_CASE ("AVLTree deletion") {
    {
        AVLTree<int> tree;
        for (int i = 0; i < 16; ++i) {
            tree.insert(i);
        }
        tree.remove(5);
        tree.remove(2);
        tree.remove(10);
        tree.remove(15);
        tree.remove(13);
        tree.remove(8);
        tree.remove(7);

                REQUIRE(tree.print() == "6(3(1(0),4),11(9,12(14)))");
    }

    {
        AVLTree<int> tree;
        for (int i = 0; i < 50; ++i) {
            tree.insert(i);
        }
        for (int i = 0; i < 50; ++i) {
            tree.remove(i);
        }
                REQUIRE(tree.print().empty());
    }

    {
        AVLTree<int> tree;
        for (int i = 0; i < 5; ++i) {
            tree.insert(i);
            tree.remove(i);
        }
                REQUIRE(tree.print().empty());
    }
}
