# ===== Directories =====
INC_DIR := inc
SRC_DIR := src
OUT_DIR := out
# -- Sub Dirs --
UTILS_DIR := $(SRC_DIR)/utils
BIN_DIR := $(OUT_DIR)/bin
OBJ_DIR := $(OUT_DIR)/obj

# ===== Files =====
MAIN_SRC := $(SRC_DIR)/main.cpp
MAIN_EXE := $(BIN_DIR)/crux.exe

# ===== Compiler =====
CPPC := g++
CFLAGS := -I $(INC_DIR)

# ===== Objects =====
UTIL_SRCS := $(shell find $(UTILS_DIR) -name "*.cpp")
UTIL_OBJS := $(patsubst $(UTILS_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(UTIL_SRCS))
MAIN_OBJ := $(OBJ_DIR)/main.o

# ===== Build target =====
.PHONY: build
build: $(MAIN_EXE)

$(MAIN_EXE): $(MAIN_OBJ) $(UTIL_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CPPC) $(CFLAGS) $(MAIN_OBJ) $(UTIL_OBJS) -o $(MAIN_EXE)

# Compile main object
$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CPPC) $(CFLAGS) -c $< -o $@

# Compile utility objects
$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CPPC) $(CFLAGS) -c $< -o $@

# ===== Run target =====
.PHONY: run
run: 
	./$(MAIN_EXE) source.cx

# ===== Clean target =====
.PHONY: clean
clean:
	rm -rf $(OUT_DIR)

# ===== Clean, build, run =====
.PHONY: cbr
cbr: clean build run