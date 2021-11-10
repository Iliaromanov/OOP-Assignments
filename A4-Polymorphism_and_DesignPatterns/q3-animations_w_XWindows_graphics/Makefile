CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla 
EXEC = a4q3
OBJECTS = studio.o asciiart.o blank.o decorator.o filledbox.o blinkingbox.o movingbox.o maskbox.o subject.o window.o textObserver.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}