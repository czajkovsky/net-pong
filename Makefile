CC=g++
LD=g++

CFLAGS=-Wall -lbox2d -framework SFML -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
LDFLAGS=-Wall -lbox2d -framework SFML -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network

SRCS=app.cpp Server.cpp Client.cpp IThread.cpp Mutex.cpp SharedMemory.cpp GameEngine.cpp
HEADERS=app.h Server.h Client.h IThread.h Mutex.h SharedMemory.h GameEngine.h dimensions.h
TARGET=pong

OBJS=$(addprefix ./obj/, $(addsuffix .o, $(SRCS)))
HDRS=$(addprefix ./src/, $(HEADERS))

$(TARGET): $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
./obj/%.cpp.o: ./src/%.cpp $(HDRS)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm $(OBJS) $(TARGET)
