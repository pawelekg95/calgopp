cmake_minimum_required(VERSION 3.14)

list(APPEND sources JacymirskiTransform.cpp Signal.cpp)

if(${GPU_PARALLEL} MATCHES "1")
    find_package(OpenCL REQUIRED)
    list(APPEND sources FourierTransformOpenCL.cpp)
else()
    list(APPEND sources FourierTransform.cpp)
endif()

add_library(calgopp-signal EXCLUDE_FROM_ALL
        ${sources}
        )

if(${GPU_PARALLEL} MATCHES "1")
    target_link_libraries(calgopp-signal
            PRIVATE calgopp::gpu OpenCL::OpenCL)
endif()

add_library(calgopp::signal ALIAS calgopp-signal)

target_include_directories(calgopp-signal
        PUBLIC include
        )

target_link_libraries(calgopp-signal
        PUBLIC calgopp::types etl)

if  (NOT DEFINED MAX_SIGNAL_SIZE)
    set (MAX_SIGNAL_SIZE "10000")
endif ()
    
target_compile_definitions(calgopp-signal
    PUBLIC -DMAX_SIGNAL_SIZE=${MAX_SIGNAL_SIZE})
