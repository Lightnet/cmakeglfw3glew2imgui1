# cimgui

cmake_minimum_required(VERSION 3.20) # FetchContent is available in 3.11+

project(glfwglew VERSION 0.0.1)

#target_compile_definitions(cimguiapp PRIVATE CIMGUI_DEFINE_ENUMS_AND_STRUCTS=1)

# https://stackoverflow.com/questions/36089291/why-cmake-library-output-directory-doesnt-work
# https://bytefreaks.net/tag/cmake_archive_output_directory
# user must config manual
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# https://cmake.org/cmake/help/latest/module/FetchContent.html
# dev settings for fast compile time
#set(FETCHCONTENT_FULLY_DISCONNECTED ON) # Skip Download and Update
#set(FETCHCONTENT_UPDATES_DISCONNECTED ON) # Skip update

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPP_INCLUDE_DIRS "")
set(CPP_SOURCES_FILES "")
set(CPP_HEADERS_FILES "")

if (NOT glfw_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.4
  )
  FetchContent_GetProperties(glfw)
  if (NOT glfw_POPULATED) # Have we downloaded glfw yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(glfw)
    #message("glfw_SOURCE_DIR " ${glfw_SOURCE_DIR})
    #message("glfw_BINARY_DIR " ${glfw_BINARY_DIR})

    #set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE) # don't build the tests
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) # don't build the docs
    set(GLFW_INSTALL OFF CACHE INTERNAL "" FORCE)

    list(APPEND CPP_INCLUDE_DIRS ${glfw_SOURCE_DIR}/include)

    include_directories(${glfw_SOURCE_DIR}/include)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
  endif()
endif()

if (NOT glew_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    glew
    URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip
  )
  FetchContent_GetProperties(glew)
  if (NOT glew_POPULATED) # Have we downloaded glfw yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(glew)
    #message("glew_SOURCE_DIR " ${glew_SOURCE_DIR})

    include_directories(${glew_SOURCE_DIR}/include)
    list(APPEND CPP_INCLUDE_DIRS ${glew_SOURCE_DIR}/include)
  endif()
endif()

if (NOT imgui_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.82
  )
  FetchContent_GetProperties(imgui)
  if (NOT imgui_POPULATED) # Have we downloaded imgui yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(imgui)
    #message("imgui_SOURCE_DIR " ${imgui_SOURCE_DIR})
    
    include_directories(${imgui_SOURCE_DIR})
    include_directories(${imgui_SOURCE_DIR}/backends)

    list(APPEND CPP_HEADERS_FILES ${imgui_SOURCE_DIR}/imgui.cpp)
    list(APPEND CPP_SOURCES_FILES ${imgui_SOURCE_DIR}/imgui_demo.cpp)
    list(APPEND CPP_SOURCES_FILES ${imgui_SOURCE_DIR}/imgui_draw.cpp)
    list(APPEND CPP_SOURCES_FILES ${imgui_SOURCE_DIR}/imgui_tables.cpp)
    list(APPEND CPP_SOURCES_FILES ${imgui_SOURCE_DIR}/imgui_widgets.cpp)
    list(APPEND CPP_SOURCES_FILES ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp)
    list(APPEND CPP_SOURCES_FILES ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)

    list(APPEND CPP_HEADERS_FILES ${imgui_SOURCE_DIR}/imgui.h)
    list(APPEND CPP_HEADERS_FILES ${imgui_SOURCE_DIR}/imconfig.h)
    list(APPEND CPP_HEADERS_FILES ${imgui_SOURCE_DIR}/imgui_internal.h)
    #list(APPEND CPP_HEADERS_FILES ${imgui_SOURCE_DIR}/imstb_rectpack.h)
    #list(APPEND CPP_HEADERS_FILES ${imgui_SOURCE_DIR}/imstb_textedit.h)
    #list(APPEND CPP_HEADERS_FILES ${imgui_SOURCE_DIR}/imstb_truetype.h)
    list(APPEND CPP_HEADERS_FILES ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h)
    list(APPEND CPP_HEADERS_FILES ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h)

    list(APPEND CPP_INCLUDE_DIRS ${imgui_SOURCE_DIR})
    list(APPEND CPP_INCLUDE_DIRS ${imgui_SOURCE_DIR}/backends)
  endif()
endif()

#look for lib file
#find_library(glfw3_LIB NAMES glfw3 HINTS ${glfw_BINARY_DIR}/src/Debug) #lib search
#find_library(glew_LIB NAMES glew32 HINTS ${glew_SOURCE_DIR}/lib/Release/x64) #lib search

include_directories(${CPP_INCLUDE_DIRS}) #need to be added in else error
link_directories(${CMAKE_BINARY_DIR}/Debug) # dlls, libs

add_executable(${PROJECT_NAME}
  glfw3glew2imgui.cpp
  #glfw3glew2.cpp
  ${CPP_HEADERS_FILES}
  ${CPP_SOURCES_FILES}
)

target_link_libraries(${PROJECT_NAME} 
  PUBLIC
  opengl32 # add this since it need the link
  PRIVATE 
  glfw3
  glew32
  #${glfw3_LIB} 
  #${glew_LIB} 
  #${CMAKE_DL_LIBS}
)

add_custom_command(TARGET ${PROJECT_NAME} 
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy 
	${glew_SOURCE_DIR}/lib/Release/x64/glew32.lib
	${PROJECT_BINARY_DIR}/Debug
)
add_custom_command(TARGET ${PROJECT_NAME} 
	POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy 
	${glew_SOURCE_DIR}/bin/Release/x64/glew32.dll
	${PROJECT_BINARY_DIR}/Debug
)
#[[
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
  ${glfw_BINARY_DIR}/src/Debug/glfw3.dll
  ${PROJECT_BINARY_DIR}/Debug
)
]]