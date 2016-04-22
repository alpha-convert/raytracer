CXX=g++
CC=gcc
AS=as

EXEC=$(notdir $(CURDIR))

DOCS=docs

INCLUDES=-I./src -I./src/math -I./src/graphics -I./src/json

LIBS=-framework SDL2 -framework OpenGL -framework GLUT /usr/local/lib/libGLEW.dylib

CXXFLAGS:=-Wall -Wextra -O2 -g -ggdb -march=native -ftrapv -Wundef -fverbose-asm $(INCLUDES) -std=c++11 -Wno-sign-compare
CFLAGS:=-Wall -Wextra -O2 -ftrapv -Wundef -fverbose-asm

CPP_FILES := $(shell find src -name '*.cpp')
C_FILES := $(shell find src -name '*.c')
AS_FILES := $(shell find src -name '*.as')
LD_FLAGS := $(LIBS)
SOURCES := $(CPP_FILES:.cpp=.o) $(C_FILES:.c=.o) $(AS_FILES:.S=.o)
OBJS := $(foreach file, $(SOURCES), $(file))

.PHONY: docs

all: $(OBJS)
	@echo "[LD] ./$(EXEC)" 
	@$(CXX) $(OBJS) -o $(EXEC) $(LD_FLAGS)

docs:
	@echo "Generating docs for $(EXEC)"
	@doxygen


%o: %cpp
	@echo "[CXX] $@"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

%o: %c
	@echo "[C] $@"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

%o: %as
	@echo "[AS] $@"
	@$(AS) $(ASFLAGS) -o "$@" -c "$<"


clean:
	rm -f $(EXEC) $(OBJS)
	rm -rf $(DOCS)

print-%:
	@echo '$*=$($*)'

-include $(OBJS:.o=.d)



