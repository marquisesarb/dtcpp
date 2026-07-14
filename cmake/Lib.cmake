add_library(dtcpp 
    STATIC
        src/dtconstructor.cpp
        src/dtoperators.cpp
        src/dtfunc.cpp
)

target_include_directories(dtcpp PUBLIC include)