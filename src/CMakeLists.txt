set(LIB_NAME ${PROJECT_NAME}core)

set(SRC_LIST
        trees/AVLTree.hpp
        trees/AVLTree.tpp

        trees/splay_set.hpp
        trees/splay_map.hpp
		trees/BplusTree.hpp
        trees/BplusTree.tpp
		trees/BTree.hpp
		trees/RBTree.hpp
		trees/RBTree.tpp

        lists/DLsircular.hpp
        lists/DLsircular.tpp
		lists/SL.hpp
		lists/SLsircular.tpp lists/SLsircular.hpp
		
		types/Official.hpp
		types/Official.cpp
		)

add_library(${LIB_NAME} STATIC ${SRC_LIST})

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
