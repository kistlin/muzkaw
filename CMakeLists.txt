cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Muzkaw CXX C)

add_subdirectory(ElectroStat)
add_subdirectory(FFT2)
add_subdirectory(Graph)
add_subdirectory(ParticlePursuers)
