#from https://www.youtube.com/watch?v=LFSJcdYZcvo&t=9s
cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD  17)
set(CMAKE_C_STANDARD_REQUIRED ON)
#set(CMAKE_LINK_LIBRARY_FLAG -pthread -lstdc++fs)

project(CPPLaboratoryProject VERSION 1.0)


add_executable(cpplab 
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
                )

