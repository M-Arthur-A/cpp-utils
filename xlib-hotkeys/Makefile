# creating windows with Xlib

CXX = clang
NAME = x-hotkeys
EXE_PATH = ./bin
EXE = -o $(EXE_PATH)/$(NAME)
SOURCES = ./$(NAME).cpp
CXXFLAGS_RELEASE  += -Wall -w -O3
CXXFLAGS_DEBUG += -g -fsanitize=address $(CXXFLAGS_RELEASE)
LIBS = -lstdc++ -lX11 -lXext -lXi

release: ./$(NAME).cpp
	$(CXX) $(SOURCES) $(CXXFLAGS_RELEASE) $(EXE) $(LIBS)

debug: ./$(NAME).cpp
	$(CXX) $(SOURCES) $(CXXFLAGS_DEBUG) $(EXE) $(LIBS)
