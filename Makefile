include config.mk

# .cpp files
#SOURCES := $(shell find . -name '*.cpp')
SOURCES := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
HEADERS := $(wildcard includes/*.h) $(wildcard includes/**/*.h)

# Object files
OBJ=$(subst src,objects,$(subst .cpp,.o, $(SOURCES)))
DIRS=$(dir $(OBJ))

# Compiler and linker
CC=$(shell $(WX_CFG_PATH) --cxx)

# Flags for compiler
CC_FLAGS += -std=c++17 -I./include -I./lib $(shell $(WX_CFG_PATH) --cxxflags) -g -c -Wall
LD_FLAGS += $(shell $(WX_CFG_PATH) --libs) -lPocoFoundation -lPocoNet  -lPocoNetSSL -lPocoJSON

# Command used at clean target
RM = rm -rf

# Compilation and linking
all: objFolder binFolder $(PROJ_NAME)
	@ echo 'Done!'

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o bin/$@ $(LD_FLAGS)
	@ echo 'Finished building binary: $@'
	@ echo ' '

objects/%.o: src/%.cpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p objects
	@ mkdir -p $(DIRS)

binFolder:
	@ mkdir -p bin

clean:
	@ $(RM) ./objects ./bin/rwxet* *~

.PHONY: all clean