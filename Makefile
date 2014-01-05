CC=g++
LD=g++

CFLAGS=-Wall -lbox2d -framework SFML -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
LDFLAGS=-Wall -lbox2d -framework SFML -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network

SRCS=app.cpp server.cpp client.cpp IThread.cpp mutex.cpp sharedMemory.cpp
HEADERS=app.h server.h client.h IThread.h mutex.h sharedMemory.h
TARGET=pong

OBJS=$(addprefix ./obj/, $(addsuffix .o, $(SRCS)))
HDRS=$(addprefix ./src/, $(HEADERS))

$(TARGET): $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
./obj/%.cpp.o: ./src/%.cpp $(HDRS)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm $(OBJS) $(TARGET)
