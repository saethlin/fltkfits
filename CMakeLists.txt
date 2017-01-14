project(fltkfits)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES fltkfits.cpp
        imagedisplay.cpp imagedisplay.h
        histogramdisplay.cpp histogramdisplay.h
        MiniMap.cpp MiniMap.h
        DirList.cpp DirList.h draw_changed.cpp draw_changed.h CursorDisplay.cpp CursorDisplay.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcfitsio -lCCfits")
add_executable(fltkfits ${SOURCE_FILES})