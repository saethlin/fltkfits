CC=clang++
CFLAGS=-std=c++11 -Wall -pedantic -march=native -fno-omit-frame-pointer

fltkfits: fltkfits.cpp imagedisplay.o histogramdisplay.o MiniMap.o DirList.o
	$(CC) fltkfits.cpp imagedisplay.o histogramdisplay.o MiniMap.o DirList.o -o fltkfits -lcfitsio -lCCfits `fltk-config --cxxflags --ldflags` -pthread $(CFLAGS)

imagedisplay.o: imagedisplay.cpp imagedisplay.h
	$(CC) imagedisplay.cpp -c $(CFLAGS)

histogramdisplay.o: histogramdisplay.cpp histogramdisplay.h
	$(CC) histogramdisplay.cpp -c $(CFLAGS)

MiniMap.o: MiniMap.cpp MiniMap.h
	$(CC) MiniMap.cpp -c $(CFLAGS)

DirList.o: DirList.cpp DirList.h
	$(CC) DirList.cpp -c $(CFLAGS)

