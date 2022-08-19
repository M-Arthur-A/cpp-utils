# tataru helper linux analog

CXX = clang #g++
NAME = tataru
EXE_PATH = ./bin
EXE = -o $(EXE_PATH)/$(NAME)
SOURCES = ./$(NAME).cpp ./objects/get-screen.o ./objects/get-ocr.o ./objects/get-translate.o
CXXFLAGS_RELEASE  += -Wall -w -march=native -m64 -funroll-loops -mavx2 -O3 # -mfpmath=both -Ofast
CXXFLAGS_DEBUG += -g -fsanitize=address $(CXXFLAGS_RELEASE)
LIBS-screen = -lX11 -lXext $(shell pkg-config --libs opencv4) -lstdc++ -I/usr/include/opencv4/ -I/usr/include/x86_64-linux-gnu/c++/10/ -I/usr/include/opencv4/opencv2/ #  -stdlib=libstdc++
LIBS-ocr = -ltesseract
LIBS-translate = -lcpr

release: ./$(NAME).cpp
	$(CXX) -c get-screen.cpp $(CXXFLAGS_RELEASE) -o ./objects/get-screen.o $(LIBS-screen)
	$(CXX) -c get-ocr.cpp $(CXXFLAGS_RELEASE) -o ./objects/get-ocr.o $(LIBS-screen)
	$(CXX) -c get-translate.cpp $(CXXFLAGS_RELEASE) -o ./objects/get-translate.o $(LIBS-translate)
	$(CXX) $(SOURCES) $(CXXFLAGS_RELEASE) $(EXE) $(LIBS-screen) $(LIBS-ocr) $(LIBS-translate)

debug: ./$(NAME).cpp
	$(CXX) -c get-screen.cpp $(CXXFLAGS_DEBUG) -o ./objects/get-screen.o $(LIBS-screen)
	$(CXX) -c get-ocr.cpp $(CXXFLAGS_DEBUG) -o ./objects/get-ocr.o $(LIBS-screen)
	$(CXX) -c get-translate.cpp $(CXXFLAGS_DEBUG) -o ./objects/get-translate.o $(LIBS-translate)
	$(CXX) $(SOURCES) $(CXXFLAGS_DEBUG) $(EXE) $(LIBS-screen) $(LIBS-ocr) $(LIBS-translate)
