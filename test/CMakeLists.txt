project(test)

set(SRC_LIST
    avl_test.cpp
    sort_test.cpp
    splay_test.cpp
    sl_test.cpp
    radix_test.cpp
    dlsirc_test.cpp
    slsirc_test.cpp
    hash_test.cpp
    )

add_executable(tests ${SRC_LIST})
target_link_libraries(tests PRIVATE ${LIB_NAME})


