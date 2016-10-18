cmake_minimum_required (VERSION 2.6)
project (OXYGINE_ADCOLONY)

set(OXYGINE_ADCOLONY_INCLUDE_DIRS 
	${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${OXYGINE_ADCOLONY_INCLUDE_DIRS})
add_library(oxygine-adcolony STATIC 
	src/adcolony.cpp 
	src/adcolony.h
	src/sim/AdcolonySimulator.cpp 
	src/sim/AdcolonySimulator.h
)

#target_link_libraries(oxyginemagicparticles)

set(OXYGINE_ADCOLONY_INCLUDE_DIRS ${OXYGINE_ADCOLONY_INCLUDE_DIRS} PARENT_SCOPE)
set(OXYGINE_ADCOLONY_LIBS ${OXYGINE_ADCOLONY_LIBS} PARENT_SCOPE)