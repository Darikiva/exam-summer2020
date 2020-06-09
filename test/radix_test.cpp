#include "doctest.h"
#include "sortings/RadixSort.hpp"

TEST_CASE("Radix Sort Int") {
    RadixSort<int> rs{std::vector<int>{170, 45, 75, 90, 802, 24, 2, 66}};
    rs.sort();
    std::string res = rs.print();
            REQUIRE(res == "2 24 45 66 75 90 170 802" );
            REQUIRE(rs.getElements() == std::vector<int>{2, 24, 45, 66, 75, 90, 170, 802});
}

TEST_CASE("Radix Sort long long") {
    RadixSort<long long> rs{std::vector<long long>{20, 887, 1556, 1749, 2626, 2636, 3003, 3236, 3466, 3933, 5473, 5868, 6346, 6358, 6770, 7405, 7747, 7839, 7905, 8295, 8693, 9029, 9500, 10447, 10764, 11516, 12007, 12431, 12790, 12828, 13313, 13411, 14011, 14027, 14341, 14823, 14844, 15813, 15818, 15958, 16326, 16688, 16781, 17511, 17864, 17921, 18048, 19653, 19690, 19854}};
    rs.sort();
    std::string res = rs.print();
            REQUIRE(rs.getElements() == std::vector<long long>{20, 887, 1556, 1749, 2626, 2636, 3003, 3236, 3466, 3933, 5473, 5868, 6346, 6358, 6770, 7405, 7747, 7839, 7905, 8295, 8693, 9029, 9500, 10447, 10764, 11516, 12007, 12431, 12790, 12828, 13313, 13411, 14011, 14027, 14341, 14823, 14844, 15813, 15818, 15958, 16326, 16688, 16781, 17511, 17864, 17921, 18048, 19653, 19690, 19854});
}

TEST_CASE("Radix Sort reversed") {
    RadixSort<int> rs{std::vector<int>{10, 8, 6, 2, 1}};
    rs.sort();
    std::string res = rs.print();
            REQUIRE(rs.getElements() == std::vector<int>{1, 2, 6, 8, 10});
}
