PROJECT(b5m)

#包含依赖
#SET(LIBRARYS )

ADD_EXECUTABLE(Problem_A_1 Problem_A_1.cpp GramClassifier.cpp GramLanguager.cpp GramHash.cpp GramHeap.cpp)
TARGET_LINK_LIBRARIES(Problem_A_1 ${LIBRARYS})

ADD_EXECUTABLE(Problem_A_2 Problem_A_2.cpp GramClassifier.cpp GramLanguager.cpp GramHash.cpp GramHeap.cpp)
TARGET_LINK_LIBRARIES(Problem_A_2 ${LIBRARYS})

INSTALL(TARGETS Problem_A_1 Problem_A_2 RUNTIME DESTINATION bin)
