#include "doctest.h"
#include "sortings/Sort.hpp"

#include <forward_list>
#include <list>
#include <vector>
#include <cassert>

TEST_CASE("[exam][sort]") {
    using namespace exam::sort::type;
    using namespace exam::sort;

    const std::vector<std::vector<int>> RAIter_cases = {
        {},
        {42},
        {1, 0, -10, 12, 1002, 20},
        {1, 0, -10, 12, 1002, 0, 20},
        {1, 1, 2, 3, 3, 3, 10},
        {10, 9, 8, 8, 1, 1, -1},
    };
    auto RAIter_direct_expected = RAIter_cases;
    auto RAIter_reverse_expected = RAIter_cases;
    
    for (size_t test_id = 0; test_id < RAIter_cases.size(); ++test_id) {
        std::sort(RAIter_direct_expected[test_id].begin(), RAIter_direct_expected[test_id].end());
        std::sort(RAIter_reverse_expected[test_id].begin(), RAIter_reverse_expected[test_id].end(), std::greater<int>());
    }
    
    const std::vector<std::forward_list<int>> FIter_cases = {
        {},
        {42},
        {1, 0, -10, 12, 1002, 20},
        {1, 0, -10, 12, 1002, 0, 20},
        {1, 1, 2, 3, 3, 3, 10},
        {10, 9, 8, 8, 1, 1, -1},
    };
    auto FIter_direct_expected = FIter_cases;
    auto FIter_reverse_expected = FIter_cases;
    for (size_t test_id = 0; test_id < FIter_cases.size(); ++test_id) {
        FIter_direct_expected[test_id].sort();
        FIter_reverse_expected[test_id].sort(std::greater<int>());
    }
    
    const std::vector<std::list<int>> BIter_cases = {
        {},
        {42},
        {1, 0, -10, 12, 1002, 20},
        {1, 0, -10, 12, 1002, 0, 20},
        {1, 1, 2, 3, 3, 3, 10},
        {10, 9, 8, 8, 1, 1, -1},
    };
    auto BIter_direct_expected = BIter_cases;
    auto BIter_reverse_expected = BIter_cases;
    for (size_t test_id = 0; test_id < BIter_cases.size(); ++test_id) {
        BIter_direct_expected[test_id].sort();
        BIter_reverse_expected[test_id].sort(std::greater<int>());
    }
    
    SUBCASE("Bubble sort") {
        SUBCASE("Random access iterators") {
            SUBCASE("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Bubble>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Bubble>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Bidirectional iterators") {
            SUBCASE("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Bubble>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Bubble>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Forward iterators") {
            SUBCASE("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Bubble>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Bubble>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    }
    SUBCASE("Quick sort") {
        SUBCASE("Random access iterators") {
            SUBCASE("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Quick>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Quick>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Bidirectional iterators") {
            SUBCASE("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Quick>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Quick>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Forward iterators") {
            SUBCASE("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Quick>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Quick>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    }
    SUBCASE("Insertion sort") {
        SUBCASE("Random access iterators") {
            SUBCASE("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Insertion>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Insertion>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Bidirectional iterators") {
            SUBCASE("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Insertion>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Insertion>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Forward iterators") {
            SUBCASE("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Insertion>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Insertion>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    }
    SUBCASE("Merge sort") {
        SUBCASE("Random access iterators") {
            SUBCASE("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Merge>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Merge>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Bidirectional iterators") {
            SUBCASE("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Merge>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Merge>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Forward iterators") {
            SUBCASE("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Merge>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Merge>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    }
    SUBCASE("Selection sort") {
        SUBCASE("Random access iterators") {
            SUBCASE("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Selection>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Selection>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Bidirectional iterators") {
            SUBCASE("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Selection>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Selection>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Forward iterators") {
            SUBCASE("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Selection>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Selection>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    }
    SUBCASE("Heap sort") {
        SUBCASE("Random access iterators") {
            SUBCASE("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Heap>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    Sort<Heap>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Bidirectional iterators") {
            SUBCASE("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Heap>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    Sort<Heap>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SUBCASE("Forward iterators") {
            SUBCASE("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Heap>{}(results[case_id].begin(), results[case_id].end(), std::less{});
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SUBCASE("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    Sort<Heap>{}(results[case_id].begin(), results[case_id].end(), std::greater{});
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    } 
}
