CXX = g++
CPPFLAGS = -Wall

SOURCES = main.cpp blobs.cpp color_table.cpp communication.cpp preprocessor.cpp rsvs.cpp segmenter.cpp tracker.cpp ui.cpp utils.cpp output_data.cpp homography.cpp
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
EXECUTABLE = Vision

SHARED_OBJ = $(wildcard ../shared/*.o)
BOOST_LIBS = -lboost_thread -lboost_system -lboost_filesystem -lboost_regex -lboost_program_options -lpthread -lrt 
OPENCV_LIBS = `pkg-config --libs opencv`
#DC1394_LIBS = -lm -ldc1394

INC = -I. -I../shared `pkg-config --cflags opencv`

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(INC) $(SHARED_OBJ) -lcurses $^ -o $@  $(OPENCV_LIBS) $(DC1394_LIBS) $(BOOST_LIBS)

.cpp.o:
	$(CXX) $(CPPFLAGS) $(INC) -c -g $< -o $@

.PHONY: print
print:
	@echo Sources: $(SOURCES)
	@echo Objects: $(OBJECTS)
	@echo Executable: $(EXECUTABLE)

.PHONY: clean
clean:
	-rm -f $(EXECUTABLE) *.o
