SRCS = src/test.cpp src/main.cpp src/LinkedList.cpp src/OrderOstream.cpp src/HashTable.cpp src/OrderSystem.cpp src/interactive-main.cpp
OBJS = $(SRCS:.cpp=.o)
SUBMISSION = SmartPtr-impl.h BST-impl.h Order.h
OBJ_DEBUG_PREFIX = leak

CPPFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -g -Iinclude
CPPFLAGS_DEBUG = -std=c++11 -fsanitize=address,undefined,leak -Wall -Wextra -Wpedantic -g
OBJS_DEBUG = $(addprefix $(OBJ_DEBUG_PREFIX)_,$(OBJS))

ifeq (Windows_NT, $(OS))
RM_CMD := /C del
PA3=system.exe
PA3_LEAK=system_leak.exe
else
RM_CMD := rm -vf
PA3=system
PA3_LEAK=system_leak
endif

all: $(PA3)
debug: $(PA3_LEAK)

.PHONY: test-all
test-all: $(PA3)
ifeq (Windows_NT, $(OS))
	@echo "Running all tests using PowerShell script"
	@powershell -ExecutionPolicy Bypass -File .\\scripts\\run-tests.ps1 $(PA3)
else
	@echo "Running all tests using shell script"
	@sh ./scripts/run-tests.sh
endif

$(PA3): $(OBJS)
	g++ -o $@ $(CPPFLAGS) $^

$(PA3_LEAK): $(OBJS_DEBUG)
	g++ -o $@ $(CPPFLAGS_DEBUG) $^

clean:
	$(RM_CMD) $(OBJS) $(OBJS_DEBUG) $(PA3) $(PA3_LEAK)

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@

$(OBJ_DEBUG_PREFIX)_%.o: %.cpp
	g++ $(CPPFLAGS_DEBUG) -c $< -o $@
