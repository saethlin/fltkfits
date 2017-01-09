main: main.cpp fltkfits.o imagedisplay.o histogramdisplay.o MiniMap.o
	g++ main.cpp -o main fltkfits.o imagedisplay.o histogramdisplay.o MiniMap.o -std=c++11 -L/usr/local/lib -lcfitsio -lCCfits `fltk-config --cxxflags --ldflags` -Wall

fltkfits.o: fltkfits.cpp fltkfits.h imagedisplay.o histogramdisplay.o
	g++ fltkfits.cpp -c -std=c++11 -L/usr/local/lib -lcfitsio -lCCfits `fltk-config --cxxflags --ldflags` -Wall

imagedisplay.o: imagedisplay.cpp imagedisplay.h
	g++ imagedisplay.cpp -c -std=c++11 -L/usr/local/lib -lcfitsio -lCCfits `fltk-config --cxxflags --ldflags` -Wall

histogramdisplay.o: histogramdisplay.cpp histogramdisplay.h
	g++ histogramdisplay.cpp -c -std=c++11 -L/usr/local/lib -lcfitsio -lCCfits `fltk-config --cxxflags --ldflags` -Wall

MiniMap.o: MiniMap.cpp MiniMap.h
	g++ MiniMap.cpp -c -std=c++11 -L/usr/local/lib -lcfitsio -lCCfits `fltk-config --cxxflags --ldflags` -Wall

