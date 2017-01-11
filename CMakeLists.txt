project(fltkfits)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        fltkfits.cpp fltkfits.h
        imagedisplay.cpp imagedisplay.h
        histogramdisplay.cpp histogramdisplay.h
        MiniMap.cpp MiniMap.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/usr/local/lib -lcfitsio -lCCfits")
+add_executable(main ${SOURCE_FILES})