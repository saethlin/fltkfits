CC=clang++
CFLAGS=-std=c++11 -Wall -pedantic -march=native -fno-omit-frame-pointer

fltkfits: fltkfits.cpp imagedisplay.o histogramdisplay.o MiniMap.o DirList.o CursorDisplay.o draw_changed.o
	$(CC) fltkfits.cpp imagedisplay.o histogramdisplay.o MiniMap.o DirList.o draw_changed.o CursorDisplay.o -o fltkfits -lcfitsio -lCCfits `fltk-config --cxxflags --ldflags` -pthread $(CFLAGS)

imagedisplay.o: imagedisplay.cpp imagedisplay.h
	$(CC) imagedisplay.cpp -c $(CFLAGS)

histogramdisplay.o: histogramdisplay.cpp histogramdisplay.h
	$(CC) histogramdisplay.cpp -c $(CFLAGS)

MiniMap.o: MiniMap.cpp MiniMap.h
	$(CC) MiniMap.cpp -c $(CFLAGS)

DirList.o: DirList.cpp DirList.h
	$(CC) DirList.cpp -c $(CFLAGS)

CursorDisplay.o: CursorDisplay.cpp CursorDisplay.h
	$(CC) CursorDisplay.cpp -c $(CFLAGS)

draw_changed.o: draw_changed.cpp draw_changed.h
	$(CC) draw_changed.cpp -c $(CFLAGS)

