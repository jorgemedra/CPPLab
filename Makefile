
#********************************
# Compile with debug option:
#	make DBGFLG=-g
#********************************

TARGET 	=		tutorial 
SRC_DIR	= 		./src
OBJ_DIR = 		./obj
BIN_DIR = 		./bin

OBJ_FLS = 		$(OBJ_DIR)/const.o \
				$(OBJ_DIR)/constex.o \
				$(OBJ_DIR)/main.o \
				$(OBJ_DIR)/mutable.o \
				$(OBJ_DIR)/pointer.o \
				$(OBJ_DIR)/rlvalue.o \
				$(OBJ_DIR)/smartptr.o \
				$(OBJ_DIR)/template.o \
				$(OBJ_DIR)/virtual.o \
				$(OBJ_DIR)/threads.o \
				$(OBJ_DIR)/timetst.o \
				$(OBJ_DIR)/file.o \
				$(OBJ_DIR)/lambdas.o \
				$(OBJ_DIR)/str_view.o

CC 			= g++
GDB			= gdb
LFLAGS		= -pthread -lstdc++fs
CPPFLAGS	= -c -std=c++17 -Wall -MD

ifdef DBGFLG
override CPPFLAGS += $(DBGFLG)
endif

all: build
	@echo "Debug Flag: " $(DBGFLAGS)

help:
	@echo "............................................."
	@echo "Build test: make"
	@echo "Run, after building: make run"
	@echo "Build and activate debug: make DBGFLG=-g"
	@echo "Clean compiled files: make clean"

build: $(OBJ_DIR) $(OBJ_FLS) $(BIN_DIR)
	@echo "Building..."
	$(CC) $(LFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJ_FLS)
	@echo "Build finished."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $< -o $@

-include $(OBJ_DIR)/*.d

run: $(BIN_DIR)/$(TARGET)
	$(BIN_DIR)/$(TARGET)

debug: $(BIN_DIR)/$(TARGET)
	$(GDB) $(BIN_DIR)/$(TARGET)


$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) 

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BIN_DIR)
	@rm -f $(SRC_DIR)/*.o
	@rm -f $(SRC_DIR)/*.d
	@echo "Cleaned"