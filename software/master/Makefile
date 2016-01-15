CXX = g++
CPPFLAGS = -Wall

SOURCES = Master.cpp
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
EXECUTABLE = Master

SHARED_OBJ = $(wildcard ../shared/*.o)
BOOST_LIBS = -lboost_thread -lboost_system -lboost_filesystem -lboost_regex -lboost_program_options -lrt
LIBS = -lpthread -lcurses
INC = -I. -I../shared

NO_COLOR=\033[0m
INFO_COLOR=\033[29;01m
OK_COLOR=\033[32;01m
ERROR_COLOR=\033[31;01m
WARN_COLOR=\033[33;01m

OK_STRING=$(OK_COLOR)OK$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)ERROR$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)WARNING$(NO_COLOR)

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CXX) $(CPPFLAGS) $(INC) $(SHARED_OBJ) $(BOOST_LIBS) $(LIBS) $^ -o $@

.cpp.o:
	@echo -n "$(INFO_COLOR)compiling $<... $(NO_COLOR)"
	@$(CXX) $(CPPFLAGS) $(INC) -c -g $< -o $@ 2> temp.log || touch temp.errors
	@if test -e temp.errors; then echo "$(ERROR_STRING)" && cat temp.log; elif test -s temp.log; then echo "$(WARN_STRING)" && cat temp.log; else echo "$(OK_STRING)"; fi;
	@rm -f temp.errors temp.log

.PHONY: print
print:
	@echo Sources: $(SOURCES)
	@echo Objects: $(OBJECTS)
	@echo Executable: $(EXECUTABLE)

.PHONY: clean
clean:
	@echo "$(INFO_COLOR)removing $(EXECUTABLE) *.o$(NO_COLOR)"
	@-rm -f $(EXECUTABLE) *.o
