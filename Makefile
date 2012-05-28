
GTEST_DIR = gtest

TESTS = tree-test
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

HEADER = tree.hpp
SRC = tree.cpp

CPPFLAGS += -Iinclude

CXXFLAGS += -g -Wall -Wextra

OBJECT = tree.o

TEST_SRC = tree-test.cpp
TEST_OBJECTS = tree-test.o

LDFLAGS = -lpthread 

GTEST = libgtest_main.a

.PHONY = run

all : $(TESTS) run

clean :
	rm -f $(TESTS) *.a *.o

$(GTEST_DIR) : 
	svn checkout \
	 http://googletest.googlecode.com/svn/trunk/\
	 $(GTEST_DIR)


gtest-all.o : $(GTEST_DIR) 
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_DIR)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

libgtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

tree.o : $(SRC) $(HEADER)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

tree-test.o : $(HEADER) $(TEST_SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

tree-test : $(OBJECT) $(TEST_OBJECTS) $(GTEST)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

run : $(TEST)
	./tree-test
