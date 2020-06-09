#include "trees/BTree.hpp"

#include "doctest.h"
#include <string>

using namespace exam::trees;

TEST_CASE("Insertion") {

std::shared_ptr<BTree<int>> tree = std::make_shared<BTree<int>>(3);
SUBCASE( "Just simple insert" ) {
tree->insert(10);
REQUIRE(tree->root != nullptr);
}

SUBCASE("Insert a lot of elements") {
for(int i = 0; i < 1000; i++)
tree->insert(i);

auto current = std::dynamic_pointer_cast<typename BTree<int>::BNode>(tree->root);
current = current->children[0];

SUBCASE("check keys size > min_degree and < 2 * min_degree ") {
REQUIRE(current->keys.size() >= current->min_degree - 1);
REQUIRE(current->keys.size() < 2 * current->min_degree);
}

SUBCASE("check children size = keys size + 1 ") {
REQUIRE(current->children.size() == current->keys.size() + 1);
}

REQUIRE(tree->root != nullptr);
}
}

TEST_CASE("Finding") {
std::shared_ptr<BTree<int>> tree = std::make_shared<BTree<int>>(3);

SUBCASE("Find for root") {
tree->insert(10);
auto it = tree->find(10);
REQUIRE(*it == 10);
}

SUBCASE("Find inside root (not only one element)") {
tree->insert(10);
tree->insert(15);
tree->insert(20);
auto it = tree->find(15);
REQUIRE(*it == 15);
}

SUBCASE("Find with a lot of elements") {
for(int i = 0; i < 1000; i++)
tree->insert(i);

SUBCASE("Find near to min elem") {
auto it = tree->find(5);
REQUIRE(*it == 5);
}

SUBCASE("Find near to middle elem") {
auto it = tree->find(400);
REQUIRE(*it == 400);
}

SUBCASE("Find near to max elem") {
auto it = tree->find(950);
REQUIRE(*it == 950);
}

SUBCASE("Find max elem") {
auto it = tree->find(999);
REQUIRE(*it == 999);
}

}
}

TEST_CASE("Check next and prev for BNode") {
std::shared_ptr<BTree<int>> tree = std::make_shared<BTree<int>>(3);

tree->insert(10);
tree->insert(11);

auto current = std::dynamic_pointer_cast<typename BTree<int>::BNode>(tree->root);
current->index = 0;
auto next = current->next();
REQUIRE(next->previous() == current);

}

TEST_CASE("BIterators in find function") {
std::shared_ptr<BTree<int>> tree = std::make_shared<BTree<int>>(3);

SUBCASE("Get next value with BIterator") {
tree->insert(10);
tree->insert(15);
auto it = tree->find(10);
REQUIRE(*it == 10);
++it;
REQUIRE(*it == 15);
}

SUBCASE("Check print method with BIterators") {
std::string tree_result;
for(int i = 0; i < 500; i++) {
tree_result += std::to_string(i);
tree->insert(i);
}

std::string iterator_result;
auto it = tree->begin();
while(it != tree->end()) {
iterator_result += std::to_string(*it);
++it;
}

REQUIRE(iterator_result == tree_result);
}
}

TEST_CASE("Begin, rbegin") {
std::shared_ptr<BTree<int>> tree = std::make_shared<BTree<int>>(3);

for(int i = 0; i < 500; i++) {
tree->insert(i);
}

SUBCASE("Begin") {
REQUIRE(*tree->begin() == *tree->find(0));
}

}

TEST_CASE("Deletion") {
std::shared_ptr<BTree<int>> tree = std::make_shared<BTree<int>>(3);

SUBCASE("Simple insert and delete") {
tree->insert(5);
REQUIRE(*tree->find(5) == 5);
tree->remove(5);
REQUIRE(tree->root == nullptr);
}

SUBCASE("Test remove with BIterators") {

std::string tree_result;
for(int i = 0; i < 500; i++) {
tree->insert(i);
if(i != 10 && i != 169)
tree_result += std::to_string(i);
}

tree->remove(10);
tree->remove(169);

std::string iterator_result;
auto it = tree->find(0);
while(it != tree->end()) {
iterator_result += std::to_string(*it);
++it;
}

REQUIRE(iterator_result == tree_result);
}

SUBCASE("Insert and delete all") {

for(int i = 0; i < 500; i++) {
tree->insert(i);
}


for(int i = 0; i < 500; i++) {
tree->remove(i);
}

REQUIRE(tree->root == nullptr);
}
}

TEST_CASE("BTree min_degree 7 and strings insertion, deletion and finding") {
std::shared_ptr<BTree<std::string>> tree = std::make_shared<BTree<std::string>>(7);

for(int i = 0; i < 5000; i++)
tree->insert(std::to_string(i) + std::to_string(2691 - i));

std::string s = "02691";
REQUIRE(*tree->find(s) == "02691");

for(int i = 0; i < 5000; i++)
tree->remove(std::to_string(i) + std::to_string(2691 - i));

REQUIRE(tree->root == nullptr);
}

