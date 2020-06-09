#include "doctest.h"
#include "trees/splay_set.hpp"
#include "trees/splay_map.hpp"
#include <iostream>
#include <set>

using namespace exam::trees;

TEST_CASE ("[exam][trees][splay][set]") {
    SUBCASE("Constructor") {
        SplaySet<int> t1;
        SplaySet<int, std::greater<int>> t2;
    }
    
    SUBCASE("Insertion") {
        SplaySet<int> t;
        t.insert(1);
        t.insert(42);
        t.insert(42);
        t.insert(32);
        t.insert(52);
        
        REQUIRE((t.exist(1) != t.end()));
        REQUIRE((t.exist(42) != t.end()));
        REQUIRE((t.exist(32) != t.end()));
        REQUIRE((t.exist(52) != t.end()));
        REQUIRE((t.exist(62) == t.end()));
        REQUIRE((t.exist(72) == t.end()));
        
        t.insert(5);
        t.insert(6);
        t.insert(1);
        t.insert(7);
        t.insert(8);
        t.insert(9);
        t.insert(11);
        REQUIRE((t.exist(5) != t.end()));
        REQUIRE((t.exist(6) != t.end()));
        REQUIRE((t.exist(7) != t.end()));
        REQUIRE((t.exist(8) != t.end()));
        REQUIRE((t.exist(9) != t.end()));
        REQUIRE((t.exist(11) != t.end()));
    }
    
    SUBCASE("Removal") {
        SplaySet<int> t;
        t.insert(1);
        t.insert(42);
        t.insert(42);
        t.insert(32);
        t.insert(52);
        t.erase(1);
        t.erase(2);
        t.erase(42);
        
        REQUIRE((t.exist(1) == t.end()));
        REQUIRE((t.exist(42) == t.end()));
        REQUIRE((t.exist(32) != t.end()));
        REQUIRE((t.exist(52) != t.end()));
        REQUIRE((t.exist(62) == t.end()));
        REQUIRE((t.exist(72) == t.end()));
    }
    
    SUBCASE("Unite") {
        SplaySet<int> t1;
        SplaySet<int> t2;
        t1.insert(1);
        t1.insert(42);
        t2.insert(42);
        t2.insert(32);
        t2.insert(52);
        auto t3 = unite(t1, t2);
        
        REQUIRE((t3.exist(1) != t3.end()));
        REQUIRE((t3.exist(42) != t3.end()));
        REQUIRE((t3.exist(32) != t3.end()));
        REQUIRE((t3.exist(52) != t3.end()));
        REQUIRE((t3.exist(62) == t3.end()));
        REQUIRE((t3.exist(72) == t3.end()));
    }
    
    SUBCASE("Cross") {
        SplaySet<int> t1;
        SplaySet<int> t2;
        t1.insert(1);
        t1.insert(42);
        t1.insert(32);
        
        t2.insert(42);
        t2.insert(16);
        t2.insert(32);
        t2.insert(52);
        auto t3 = cross(t1, t2);
        
        REQUIRE((t3.exist(1) == t3.end()));
        REQUIRE((t3.exist(42) != t3.end()));
        REQUIRE((t3.exist(32) != t3.end()));
        REQUIRE((t3.exist(52) == t3.end()));
        REQUIRE((t3.exist(62) == t3.end()));
        REQUIRE((t3.exist(72) == t3.end()));
    }
    
    SUBCASE("Symmetrical Cross") {
        SplaySet<int> t1;
        SplaySet<int> t2;
        t1.insert(1);
        t1.insert(42);
        t1.insert(32);
        
        t2.insert(42);
        t2.insert(16);
        t2.insert(32);
        t2.insert(52);
        auto t3 = symmertical_cross(t1, t2);
        
        REQUIRE((t3.exist(1) != t3.end()));
        REQUIRE((t3.exist(42) == t3.end()));
        REQUIRE((t3.exist(32) == t3.end()));
        REQUIRE((t3.exist(52) == t3.end()));
        REQUIRE((t3.exist(62) == t3.end()));
        REQUIRE((t3.exist(72) == t3.end()));
    }
    
    SUBCASE("Iteration") {
        SplaySet<int> t1;
        std::set<int> exist;
        t1.insert(1);
        t1.insert(42);
        t1.insert(32);
        t1.insert(10);
        t1.insert(420);
        t1.insert(320);
        int index = 0;
        for (auto it = t1.begin(); it != t1.end(); ++it) {
            switch (index) {
                case 0:
                    REQUIRE((*it == 1));
                    break;
                case 1:
                    REQUIRE((*it == 10));
                    break;
                case 2:
                    REQUIRE((*it == 32));
                    break;
                case 3:
                    REQUIRE((*it == 42));
                    break;
                case 4:
                    REQUIRE((*it == 320));
                    break;
                case 5:
                    REQUIRE((*it == 420));
                    break;
            }
            index++;
        }
    }
}

TEST_CASE ("[exam][trees][splay][map]") {
    SUBCASE("Constructor") {
        SplayMap<int, int> t1;
        SplayMap<int, std::string, std::greater<int>> t2;
    }
    
    SUBCASE("Insertion") {
        SplayMap<int, std::string> t;
        t.insert(10, std::string("hello"));
        t.insert(42, std::string("world"));
        REQUIRE(((*t.exist(10)).second == "hello"));
        REQUIRE(((*t.exist(42)).second == "world"));
        REQUIRE((t.exist(5) == t.end()));
    }
    
    SUBCASE("Removal") {
        SplayMap<int, std::string> t;
        t.insert(10, std::string("hello"));
        t.insert(42, std::string("world"));
        t.insert(16, std::string("!!!"));
        REQUIRE(((*t.exist(10)).second == "hello"));
        REQUIRE(((*t.exist(42)).second == "world"));
        REQUIRE(((*t.exist(16)).second == "!!!"));
        t.erase(10);
        t.erase(16);
        REQUIRE((t.exist(10) == t.end()));
        REQUIRE(((*t.exist(42)).second == "world"));
        REQUIRE((t.exist(16) == t.end()));
    }
    
    SUBCASE("Setting") {
        SplayMap<int, std::string> t;
        t.insert(10, std::string("hello"));
        t.insert(42, std::string("world"));
        t.insert(16, std::string("!!!"));
        t.insert(10, std::string("yo!"));
        REQUIRE(((*t.exist(10)).second == "yo!"));
    }
}
