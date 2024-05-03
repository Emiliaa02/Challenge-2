CXX ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -I/home/emilia_farina/pacs-examples/Examples/include -I/home/emilia_farina/pacs-examples/Examples/include
 
EXEC     = main
LDFLAGS ?= -L/home/emilia_farina/pacs-examples/Examples/lib -Wl,-rpath=/home/emilia_farina/pacs-examples/Examples/lib
LIBS	?=

SRCS = main.cpp 
OBJS = $(SRCS:.cpp=.o)

HDRS = MatrixTraits.hpp Matrix.hpp MatrixImplementation.hpp chrono.hpp

all: $(EXEC)

%.o: %.cpp $(HDRS)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@
 
#$(EXEC): $(OBJS)
#	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $@
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $@

clean:
	$(RM) *.o
