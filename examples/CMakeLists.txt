cmake_minimum_required(VERSION 3.9)

project(examples)

set(EXAMPLES 
    quick_pow
    heap_sort
    join_vector
)
set(EXECUTABLE_OUTPUT_PATH bin)
foreach(example ${EXAMPLES})
    add_executable(${example} ${example}/${example}.cpp)
endforeach()
