CC=clang++
CFLAGS=-std=c++14 -Wall -pedantic -march=native -fno-omit-frame-pointer

fltkfits: fltkfits.cpp RWindow.o ImageWidget.o HistogramWidget.o MiniMap.o DirList.o CursorTracker.o draw_changed.o
	$(CC) fltkfits.cpp RWindow.o ImageWidget.o HistogramWidget.o MiniMap.o DirList.o draw_changed.o CursorTracker.o -o fltkfits -lcfitsio -lCCfits `fltk-config --cxxflags --ldflags` -pthread $(CFLAGS)

RWindow.o: RWindow.cpp RWindow.h
	$(CC) RWindow.cpp -c $(CFLAGS)

ImageWidget.o: ImageWidget.cpp ImageWidget.h
	$(CC) ImageWidget.cpp -c $(CFLAGS)

HistogramWidget.o: HistogramWidget.cpp HistogramWidget.h
	$(CC) HistogramWidget.cpp -c $(CFLAGS)

MiniMap.o: MiniMap.cpp MiniMap.h
	$(CC) MiniMap.cpp -c $(CFLAGS)

DirList.o: DirList.cpp DirList.h
	$(CC) DirList.cpp -c $(CFLAGS)

CursorTracker.o: CursorTracker.cpp CursorTracker.h
	$(CC) CursorTracker.cpp -c $(CFLAGS)

draw_changed.o: draw_changed.cpp draw_changed.h
	$(CC) draw_changed.cpp -c $(CFLAGS)

