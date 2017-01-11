CC=clang++
CFLAGS=-std=c++11 -lcfitsio -lCCfits `fltk-config --cxxflags --ldflags` -Wall -pthread -march=native -flto -Ofast -funroll-loops

fltkfits: fltkfits.cpp imagedisplay.o histogramdisplay.o MiniMap.o
	$(CC) fltkfits.cpp imagedisplay.o histogramdisplay.o MiniMap.o -o fltkfits $(CFLAGS)

imagedisplay.o: imagedisplay.cpp imagedisplay.h
	$(CC) imagedisplay.cpp -c $(CFLAGS)

histogramdisplay.o: histogramdisplay.cpp histogramdisplay.h
	$(CC) histogramdisplay.cpp -c $(CFLAGS)

MiniMap.o: MiniMap.cpp MiniMap.h
	$(CC) MiniMap.cpp -c $(CFLAGS)

