CXX=g++
CXXFLAGS= -MMD
OBJECTS=fasearch.o finiteautomation.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=a5q2

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}


clean:
	rm ${DEPENDS} ${OBJECTS} ${EXEC}