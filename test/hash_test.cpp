#include "doctest.h"
#include "hash/linear.hpp"
#include "hash/cuckoo.hpp"

#include <iostream>

using namespace exam::hash;

class Myhash {
public:
    size_t operator()(const int* value) const {
        return (size_t) value;
    }
};

TEST_CASE ("[exam][hash][linear]") {
    SUBCASE("Constructor") {
        LinearHash<int> h1;
        LinearHash<int*, Myhash> h2(1, 1, 20);
    }
    
    SUBCASE("Insertion") {
        LinearHash<int> h1;
        h1.insert(10);
        h1.insert(20);
        h1.insert(30);
        h1.insert(40);
        
        REQUIRE((h1.exist(10) == true));
        REQUIRE((h1.exist(20) == true));
        REQUIRE((h1.exist(30) == true));
        REQUIRE((h1.exist(31) == false));
        REQUIRE((h1.exist(40) == true));
        REQUIRE((h1.exist(50) == false));
    }
    
    SUBCASE("Removal") {
        LinearHash<int> h1;
        h1.insert(10);
        h1.insert(20);
        h1.insert(30);
        h1.insert(40);
        
        h1.erase(10);
        h1.erase(20);
        h1.erase(30);
        
        REQUIRE((h1.exist(10) == false));
        REQUIRE((h1.exist(20) == false));
        REQUIRE((h1.exist(30) == false));
        REQUIRE((h1.exist(31) == false));
        REQUIRE((h1.exist(40) == true));
        REQUIRE((h1.exist(50) == false));
    }
}

TEST_CASE ("[exam][hash][linear][map]") {
    
    struct Hash {
        size_t operator()(const std::pair<int, std::string> &p) {
            return p.first;
        }
    };
    
    SUBCASE("Constructor") {
        LinearHash<int> h1;
        LinearHash<int*, Myhash> h2(1, 1, 20);
    }
    
    SUBCASE("Insertion") {
        LinearHash<int, std::string> h1;
        h1.insert(10, "hello");
        h1.insert(20, "world");
        h1.insert(30, "!!!");
       
        REQUIRE((h1.get(10)->second == "hello"));
        REQUIRE((h1.get(20)->second  == "world"));
        REQUIRE((h1.get(30)->second  == "!!!"));
    }
    
    SUBCASE("Removal") {
        LinearHash<int, std::string> h1;
        h1.insert(10, "hello");
        h1.insert(110, "world");
        h1.insert(30, "hello");
        h1.insert(40, "world");
        h1.insert(50, "hello");
        h1.insert(60, "world");
        h1.insert(70, "!!!");
        
        h1.erase(10);
        h1.erase(30);
        h1.erase(40);
        h1.erase(50);
        
        REQUIRE((h1.get(110)->second == "world"));
        REQUIRE((h1.get(10) == h1.end()));
        REQUIRE((h1.get(30) == h1.end()));
    }
    
    SUBCASE("Setting") {
        LinearHash<int, std::string> h1;
        h1.insert(10, "hello");
        h1.insert(110, "mew");
        h1.set(110, "bark");
        
        REQUIRE((h1.get(10)->second == "hello"));
        REQUIRE((h1.get(110)->second  == "bark"));
    }
}

TEST_CASE ("[exam][hash][cuckoo]") {
    SUBCASE("Constructor") {
        CuckooHash<int> h1;
        CuckooHash<int*, Myhash> h2(1, 1, 20);
    }
    
    SUBCASE("Insertion") {
        CuckooHash<int> h1;
        h1.insert(10);
        h1.insert(20);
        h1.insert(30);
        h1.insert(40);
        
        REQUIRE((h1.exist(10) == true));
        REQUIRE((h1.exist(20) == true));
        REQUIRE((h1.exist(30) == true));
        REQUIRE((h1.exist(31) == false));
        REQUIRE((h1.exist(40) == true));
        REQUIRE((h1.exist(50) == false));
    }
    
    SUBCASE("Removal") {
        CuckooHash<int> h1;
        h1.insert(10);
        h1.insert(20);
        h1.insert(30);
        h1.insert(40);
        
        h1.erase(10);
        h1.erase(20);
        h1.erase(30);
        
        REQUIRE((h1.exist(10) == false));
        REQUIRE((h1.exist(20) == false));
        REQUIRE((h1.exist(30) == false));
        REQUIRE((h1.exist(31) == false));
        REQUIRE((h1.exist(40) == true));
        REQUIRE((h1.exist(50) == false));
    }
}

TEST_CASE ("[exam][hash][cuckoo][map]") {
    
    struct Hash {
        size_t operator()(const std::pair<int, std::string> &p) {
            return p.first;
        }
    };
    
    SUBCASE("Constructor") {
        CuckooHash<int> h1;
        CuckooHash<int*, Myhash> h2(1, 1, 20);
    }
    
    SUBCASE("Insertion") {
        CuckooHash<int, std::string> h1;
        h1.insert(10, "hello");
        h1.insert(20, "world");
        h1.insert(30, "!!!");
       
        REQUIRE((h1.get(10)->second == "hello"));
        REQUIRE((h1.get(20)->second  == "world"));
        REQUIRE((h1.get(30)->second  == "!!!"));
    }
    
    SUBCASE("Removal") {
        CuckooHash<int, std::string> h1;
        h1.insert(10, "hello");
        h1.insert(110, "world");
        h1.insert(30, "hello");
        h1.insert(40, "world");
        h1.insert(50, "hello");
        h1.insert(60, "world");
        h1.insert(70, "!!!");
        
        h1.erase(10);
        h1.erase(30);
        h1.erase(40);
        h1.erase(50);
        auto t = h1.get(110);
        REQUIRE((h1.get(110)->second == "world"));
        REQUIRE((h1.get(10) == h1.end()));
        REQUIRE((h1.get(30) == h1.end()));
    }
    
    SUBCASE("Setting") {
        CuckooHash<int, std::string> h1;
        h1.insert(10, "hello");
        h1.insert(110, "mew");
        h1.set(110, "bark");
        
        REQUIRE((h1.get(10)->second == "hello"));
        REQUIRE((h1.get(110)->second  == "bark"));
    }
}
