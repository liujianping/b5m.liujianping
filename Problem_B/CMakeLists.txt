PROJECT(b5m)

#包含依赖
#SET(LIBRARYS )

ADD_EXECUTABLE(Problem_NB Problem_NB.cpp Problem_NB.cpp DocSet.cpp DocVector.cpp NBClassifier)
TARGET_LINK_LIBRARIES(Problem_NB ${LIBRARYS})

ADD_EXECUTABLE(Problem_DAGNB Problem_DAGNB.cpp DAGNBClassifier.cpp DocSet.cpp DocVector.cpp NBClassifier)
TARGET_LINK_LIBRARIES(Problem_DAGNB ${LIBRARYS})

INSTALL(TARGETS Problem_NB Problem_DAGNB RUNTIME DESTINATION bin)
