project (viryatest)
cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS filesystem regex)

include_directories(base ../virya)

add_library(test_frame STATIC
    base/MRException.cpp 
    base/MuRanCommonFuncs.cpp 
    base/MRArg.cpp
    base/MRFuncEntry.cpp
)

add_executable(viryatest
    src01/vtest01.cpp
    base/main.cpp
    )

target_link_libraries(viryatest test_frame  ${Boost_LIBRARIES})

