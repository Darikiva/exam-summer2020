set(LIB_NAME ${PROJECT_NAME}core)

set(SRC_LIST
        AVLtree.hpp
        AVLtree.tpp
        
        sortings/Change.hpp
        sortings/Sort.hpp
        sortings/Type.hpp

        trees/splay_set.hpp
        trees/splay_map.hpp
		trees/BplusTree.hpp
        trees/BplusTree.tpp


        lists/DLsircular.hpp
        lists/DLsircular.tpp
    )

add_library(${LIB_NAME} STATIC ${SRC_LIST})

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
