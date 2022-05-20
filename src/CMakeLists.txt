# CMAKE Reference Documentation:
#  https://cmake.org/cmake/help/latest/guide/tutorial/index.html

cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD  17)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(CPPLaboratoryProject VERSION 1.0)

#To activate the Debug info and get able to debug with the IDE
if(USE_DEBUG)
    message(STATUS "Debug mode is ON")
    add_compile_options("-g")
else()
    message(STATUS "Debug mode is OFF")
endif()

add_executable( cpplab 
                const.cpp 
                constex.cpp 
                main.cpp 
                mutable.cpp 
                pointer.cpp 
                rlvalue.cpp 
                smartptr.cpp 
                template.cpp 
                virtual.cpp  
                threads.cpp 
                timetst.cpp 
                file.cpp 
                lambdas.cpp 
                str_view.cpp
                maps.cpp
                tpair.cpp
                metaprog.cpp
                parameters.cpp
                test_matrix.cpp
                )

