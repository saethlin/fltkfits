CC=clang++
CFLAGS=-std=c++11 -Wall -pedantic -march=native -fno-omit-frame-pointer

fltkfits: fltkfits.cpp ImageWidget.o HistogramWidget.o MiniMap.o DirList.o CursorTrackerWidget.o draw_changed.o
	$(CC) fltkfits.cpp ImageWidget.o HistogramWidget.o MiniMap.o DirList.o draw_changed.o CursorTrackerWidget.o -o fltkfits -lcfitsio -lCCfits `fltk-config --cxxflags --ldflags` -pthread $(CFLAGS)

ImageWidget.o: ImageWidget.cpp ImageWidget.h
	$(CC) ImageWidget.cpp -c $(CFLAGS)

HistogramWidget.o: HistogramWidget.cpp HistogramWidget.h
	$(CC) HistogramWidget.cpp -c $(CFLAGS)

MiniMap.o: MiniMap.cpp MiniMap.h
	$(CC) MiniMap.cpp -c $(CFLAGS)

DirList.o: DirList.cpp DirList.h
	$(CC) DirList.cpp -c $(CFLAGS)

CursorTrackerWidget.o: CursorTrackerWidget.cpp CursorTrackerWidget.h
	$(CC) CursorTrackerWidget.cpp -c $(CFLAGS)

draw_changed.o: draw_changed.cpp draw_changed.h
	$(CC) draw_changed.cpp -c $(CFLAGS)

