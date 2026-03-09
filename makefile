-include config.cfg

DIR_RES ?= res
DIR_SCENARIO ?= scenario
DIR_MUSIC ?= music
DIR_SFX ?= sfx
DIR_SAVE ?= save
USE_CUSTOM_ABOUT ?= false

CXX = g++

CXXFLAGS = -std=c++17 -Wall -I$(HDR_DIR) -MMD -MP \
           -DAPP_VERSION=\"$(APP_VERSION)\" \
           -DAPP_NAME=\"$(APP_NAME)\" \
           -DDEFAULT_LANG=\"$(DEFAULT_LANG)\" \
           -DDIR_RES=\"$(DIR_RES)\" \
           -DDIR_SCENARIO=\"$(DIR_SCENARIO)\" \
           -DDIR_MUSIC=\"$(DIR_MUSIC)\" \
           -DDIR_SFX=\"$(DIR_SFX)\" \
           -DDIR_SAVE=\"$(DIR_SAVE)\" \
           -DUSE_CUSTOM_ABOUT=$(USE_CUSTOM_ABOUT)

TARGET = $(if $(TARGET_NAME),$(TARGET_NAME),game.exe)

SRC_DIR = cpp
HDR_DIR = hpp
OBJ_DIR = build

CORE_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
CMD_SOURCES  = $(wildcard $(SRC_DIR)/cmds/*.cpp)

CORE_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CORE_SOURCES))
CMD_OBJECTS  = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CMD_SOURCES))

ALL_OBJECTS = $(CORE_OBJECTS) $(CMD_OBJECTS)

LDFLAGS = -lole32 -lwinmm -static -static-libgcc -static-libstdc++

all: prepare $(TARGET)

$(TARGET): $(ALL_OBJECTS)
	@echo [3/4] Linking: $@
	@$(CXX) $(ALL_OBJECTS) -o $@ $(LDFLAGS)
	@echo [4/4] Success! Project: $(APP_NAME) v$(APP_VERSION)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp config.cfg
	@if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	@echo Compiling: $<...
	@$(CXX) $(CXXFLAGS) -c $< -o $@

prepare:
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@if not exist $(OBJ_DIR)\cmds mkdir $(OBJ_DIR)\cmds

clean:
	@echo Cleaning...
	@if exist $(OBJ_DIR) rd /s /q $(OBJ_DIR)
	@if exist $(TARGET) del $(TARGET)

run: all
	@echo Running $(TARGET)...
	@./$(TARGET)

-include $(ALL_OBJECTS:.o=.d)

.PHONY: all prepare clean run