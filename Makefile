CXX=clang++
CC=gcc
AS=as

EXEC=$(notdir $(CURDIR))

LIBS=-I./src -I/Library/Frameworks/SDL2.framework/Headers

CXXFLAGS:=-Wall -Wextra -O2 -march=native -ftrapv -Wundef -fverbose-asm $(LIBS) -std=c++11 -Wno-sign-compare
CFLAGS:=-Wall -Wextra -O2 -ftrapv -Wundef -fverbose-asm
ASFLAGS:=

LD_FLAGS:=-framework SDL2

CPP_FILES := $(shell find src -name '*.cpp')
C_FILES := $(shell find src -name '*.c')
AS_FILES := $(shell find src -name '*.as')
SOURCES := $(CPP_FILES:.cpp=.o) $(C_FILES.cpp=.o) $(AS_FILES.cpp=.o)
OBJS := $(foreach file, $(SOURCES), $(file))

all: $(OBJS)
	@echo "[LD] ./$(EXEC)"
	@$(CXX) $(OBJS) -o $(EXEC) $(LD_FLAGS)

%o: %cpp
	@echo "[CXX] $@"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

%o: %c
	@echo "[C] $@"
	@$(C) $(CFLAGS) -o "$@" -c "$<"

%o: %as
	@echo "[AS] $@"
	@$(AS) $(ASFLAGS) -o "$@" -c "$<"


clean:
	rm -f $(EXEC) $(OBJS)

print-%:
	@echo '$*=$($*)'

-include $(OBJS:.o=.d)



