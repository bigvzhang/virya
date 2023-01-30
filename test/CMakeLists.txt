project (viryatest)
cmake_minimum_required(VERSION 2.8)

include_directories(../base ../virya)

add_library(test_frame STATIC
	../base/varg.cpp
	../base/vfile.cpp
	../base/vfuncentry.cpp
	../base/vioman.cpp
	../base/vstring.cpp
	../base/vsys.cpp
	../base/vtest.cpp
    ../base/vtest_main.cpp
	../base/vtestcommon.cpp
	../base/vtime.cpp
	../base/vutility.cpp
)

add_executable(viryatest
    src01/vtest01.cpp
    src01/vtest02.cpp
    src01/vtest03.cpp
    src01/vtest05.cpp
    src01/vtest06.cpp
    )

target_link_libraries(viryatest test_frame)

