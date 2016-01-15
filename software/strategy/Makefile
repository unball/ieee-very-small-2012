CXX = g++
CPPFLAGS = -Wall -g

#SOURCES = Strategy.cpp Robots.cpp
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
HEADERS = $(patsubst %.cpp, %.h, $(SOURCES))
EXECUTABLE = Strategy

SHARED_OBJ = ../shared/Communicator.o ../shared/Config.o ../shared/ProcessLogger.o
BOOST_LIBS = -lboost_thread -lboost_system -lboost_filesystem -lboost_regex
LIBS = -lSM -lICE -lGLU -lGL -lm -lpthread -lrt

INC = -I. -I../shared/
DEF = -DHAVE_CONFIG_H -DdTRIMESH_ENABLED -DdSINGLE

.PHONY: all
all: $(EXECUTABLE)

# Create object files
%.o: %.cpp %.h
	$(CXX) $(CPPFLAGS) $(INC) $(DEF) -c $< -MT $@ -MD -MP -MF .deps/$*.Tpo

# Create executable file
$(EXECUTABLE): $(OBJECTS)
	/bin/bash libtool --tag=CXX --mode=link $(CXX) -O2 -o $@ \
	$^ $(ODE_LIBS) $(SHARED_OBJ) $(LIBS) $(BOOST_LIBS)

.PHONY: print
print:
	@echo Sources: $(SOURCES)
	@echo Objects: $(OBJECTS)
	@echo Headers: $(HEADERS)
	@echo Executable: $(EXECUTABLE)

.PHONY: clean
clean:
	-rm -f $(EXECUTABLE) *.o
