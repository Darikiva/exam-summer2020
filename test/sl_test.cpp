#include "doctest.h"
#include "lists/SL.hpp"

using namespace exam::list;

TEST_CASE("SL") {
    auto sl = new SL<int>{};
    sl->add(5);
    sl->add(10);
    auto it = sl->search(5);
            REQUIRE(*it == 5);

    sl->add(3);
    sl->add(15);
    it = sl->search(3);
            REQUIRE(*it == 3);

    sl->remove(2);
    it = sl->search(3);
            REQUIRE_FALSE((it != sl->end()));

    for(int i = 0; i < 100; i++) {
        sl->add(i);
    }

    it = sl->search(50);
    ++it;
    ++it;
            REQUIRE(*it == 52);

    for(int i = 100; i > 0; i--) {
        sl->remove(i);
    }

    it = sl->search(10);
            REQUIRE_FALSE(*it == 10);
}
