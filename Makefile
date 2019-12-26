exec = game.out
sources := $(wildcard src/*.cpp)
objects = $(sources:.cpp=.o)
flags = -IGL/include -lglfw -ldl -lGL -lGLEW -Wall

$(exec): $(objects)
	g++ $(objects) $(flags) -o build/$(exec)

%.o: %.c include/%.h
	g++ -c $(flags) $< -o $@

clean:
	-rm build/*.out
	-rm src/*.o
