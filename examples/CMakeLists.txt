cmake_minimum_required(VERSION 3.9)

project(examples)

set(STRINGS_EXAMPLES 
    join_vector
    split_string
)

set(ALGORITHM_EXAMPLES 
    quick_pow
    heap_sort
)

set(EXECUTABLE_OUTPUT_PATH bin)
foreach(example ${STRINGS_EXAMPLES})
    add_executable(${example} strings/${example}.cpp)
endforeach()
foreach(example ${ALGORITHM_EXAMPLES})
    add_executable(${example} algorithm/${example}.cpp)
endforeach()
