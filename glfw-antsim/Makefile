##
# GLFW+imgui ant simulation with compute shaders
#
# @file
# @version 0.1

CXX = g++
NAME = glfw-antsim
EXE_PATH = ./bin
EXE = -o $(EXE_PATH)/$(NAME)-test
IMGUI_DIR = /usr/include
SOURCES = ./$(NAME).cpp
SOURCES += $(IMGUI_DIR)/imgui_impl_glfw.cpp $(IMGUI_DIR)/imgui_impl_opengl3.cpp
CXXFLAGS_RELEASE += -Wall -w
CXXFLAGS_DEBUG += -g -Wall -w
LIBS = -lglfw -lglad -limgui -lGL

release: ./$(NAME).cpp
	$(CXX) $(SOURCES) $(CXXFLAGS_RELEASE) $(LIBS) $(EXE)

debug: ./$(NAME).cpp
	$(CXX) $(SOURCES) $(CXXFLAGS_DEBUG) $(LIBS) $(EXE)
