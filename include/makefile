VPATH = ../include

DESFILE = manager

FLAGS = -llog4cplus -levent -lzookeeper_mt
COMMON = Aqueduct.o cJSON.o

objects := $(patsubst %.cpp, %.o,$(wildcard *.cpp))

monitor:$(objects) $(COMMON)
	g++ $(FLAGS) $(COMMON) $(objects) -o $(DESFILE) 

.PHONY:clean
clean:
	rm -f *.o $(DESFILE) *_log
