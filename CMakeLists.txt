project(JAGOLYGUI)
cmake_minimum_required(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wno-comment")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-strict-aliasing")
else()
    message(FATAL_ERROR "Non-GNU compilers are not yet supported, please help fix this :)")
endif()

set(INCDIR "${PROJECT_SOURCE_DIR}/include/JagolyGUI/")
set(SRCDIR "${PROJECT_SOURCE_DIR}/source/JagolyGUI/")

set(SOURCES
    "${INCDIR}/Assert.hpp"
    "${INCDIR}/Variant.hpp"
    "${INCDIR}/DataTypes.hpp"
    "${INCDIR}/EnumTypes.hpp"

    "${INCDIR}/Widget.hpp"  "${SRCDIR}/Widget.cpp"
    "${INCDIR}/Helpers.hpp" "${SRCDIR}/Helpers.cpp"
    "${INCDIR}/Container.hpp" "${SRCDIR}/Container.cpp"
    "${INCDIR}/RenderTree.hpp" "${SRCDIR}/RenderTree.cpp"
    "${INCDIR}/ChildMulti.hpp"
    "${INCDIR}/ChildSingle.hpp"

    "${INCDIR}/text/FontFace.hpp" "${SRCDIR}/text/FontFace.cpp"

    "${INCDIR}/containers/BoxBase.hpp" "${SRCDIR}/containers/BoxBase.cpp"
    "${INCDIR}/containers/BoxH.hpp"    "${SRCDIR}/containers/BoxH.cpp"
    "${INCDIR}/containers/BoxV.hpp"    "${SRCDIR}/containers/BoxV.cpp"
    "${INCDIR}/containers/Frame.hpp"   "${SRCDIR}/containers/Frame.cpp"

    "${INCDIR}/widgets/Label.hpp" "${SRCDIR}/widgets/Label.cpp"

    "${INCDIR}/redist/stb_truetype.hpp" 
    "${SRCDIR}/redist/stb_truetype.cpp"
    "${INCDIR}/redist/utf8_cpp.hpp"
)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

add_library(JagolyGUI SHARED ${SOURCES})
