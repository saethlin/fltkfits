project(fltkfits)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES fltkfits.cpp
        ImageWidget.cpp ImageWidget.h
        HistogramWidget.cpp HistogramWidget.h
        MiniMap.cpp MiniMap.h
        DirList.cpp DirList.h draw_changed.cpp draw_changed.h CursorTracker.cpp CursorTracker.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcfitsio -lCCfits")
add_executable(fltkfits ${SOURCE_FILES})