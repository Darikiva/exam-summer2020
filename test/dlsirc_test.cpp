//
// Created by darik on 6/9/2020.
//

#include "doctest.h"
#include "lists/DLsircular.hpp"

using namespace exam::lists;

TEST_CASE ("DL sircular") {
    DLsircular<int> list;
    for (int i = 0; i < 10; ++i) list.add(i);
    SUBCASE("Iterators") {
        int count{0};
        for (auto it = list.begin(); it < list.end(); ++it) {
                    REQUIRE(*it == count);
            ++count;
        }
        --count;
        for (auto it = --list.end(); it != list.begin(); --it) {
                    REQUIRE(*it == count);
            --count;
        }
    }
    SUBCASE("Search by value") {
                REQUIRE(*list.searchByValue(5) == 5);
                REQUIRE(*list.searchByValue(0) == 0);
                REQUIRE(*list.searchByValue(9) == 9);
    }
    SUBCASE("Search by index") {
            REQUIRE(*list.searchByIndex(0) == 0);
            REQUIRE(*list.searchByIndex(10) == 0);
            REQUIRE(*list.searchByIndex(5) == 5);
    }
    SUBCASE("Remove by index") {
        DLsircular<int> new_list;
        for(int i = 0; i < 5; ++i) {
            new_list.add(i);
        }
        new_list.removeByIndex(0);
        REQUIRE(*new_list.begin() == 1);
        new_list.removeByIndex(2);
        REQUIRE(*new_list.searchByIndex(2) == 4);
        new_list.removeByIndex(10);
        REQUIRE(*new_list.searchByIndex(10) == 1);
    }
    SUBCASE("Remove By Value") {
        list.removeByValue(0);
        REQUIRE(list.getStart()->_value == 1);
        list.removeByValue(4);
        REQUIRE(list.searchByValue(4).getCount() == list.end().getCount());
    }
}