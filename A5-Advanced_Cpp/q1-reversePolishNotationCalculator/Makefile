CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
EXEC = a5q1
OBJECTS = main.o expressionVisitor.o calculate.o parse.o tree.o expressionNode.o numNode.o plusNode.o minusNode.o multNode.o divNode.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${DEPENDS} ${OBJECTS} ${EXEC}