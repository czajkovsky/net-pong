CC=g++
LD=g++

CFLAGS=-Wall
LDFLAGS=-Wall

SRCS=app.cpp server.cpp
HEADERS=app.h server.h
TARGET=pong

OBJS=$(addprefix ./obj/, $(addsuffix .o, $(SRCS)))
HDRS=$(addprefix ./src/, $(HEADERS))

$(TARGET): $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
./obj/%.cpp.o: ./src/%.cpp $(HDRS)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm $(OBJS) $(TARGET)
