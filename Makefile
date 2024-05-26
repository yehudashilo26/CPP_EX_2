# id: 325550069 , gmail: yehudav03@gmail.com
#!make -f

CXX=clang++-10
CXXFLAGS=-std=c++11 -Werror -Wall -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))


run: demo test tidy valgrind
	./$^

demo: Demo.o $(filter-out Test.o TestCounter.o, $(OBJECTS))
	@echo "Compiling $^"
	@echo "-------------------------------"
	$(CXX) $(CXXFLAGS) $^ -o demo 

test: TestCounter.o Test.o $(filter-out Demo.o, $(OBJECTS))
	@echo "Compiling $^"
	@echo "-------------------------------"
	$(CXX) $(CXXFLAGS) $^ -o test 

tidy:
	@echo "Running clang-tidy"
	@echo "-------------------------------"
	clang-tidy $(filter-out Test.cpp TestCounter.cpp , $(SOURCES)) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	@echo "Running valgrind"
	@echo "-------------------------------"
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test *.tmp
