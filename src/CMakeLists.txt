set(LIB_NAME ${PROJECT_NAME}core)

set(SRC_LIST
        AVLtree.hpp
        AVLtree.tpp
        
        sortings/Change.hpp
        sortings/Sort.hpp
        sortings/Type.hpp
    )

add_library(${LIB_NAME} STATIC ${SRC_LIST})

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
