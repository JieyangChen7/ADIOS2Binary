cmake_minimum_required(VERSION 3.19)

project(ADIOS-test C CXX)
find_package(ADIOS2 REQUIRED)
find_package(MPI REQUIRED)
#add_definitions(-DOMPI_SKIP_MPICXX -DMPICH_SKIP_MPICXX)

add_executable(adios2binary adios2binary.cpp)
target_link_libraries(adios2binary adios2::adios2 MPI::MPI_CXX)


