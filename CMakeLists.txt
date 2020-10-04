if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif()

PROJECT(3d)
cmake_minimum_required (VERSION 3.12)
list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake/macros")
include(AutoCollect)
set(CMAKE_CXX_STANDARD 17)

set(USE_GCC ON)


add_definitions(-D_AFXDLL)
set(CMAKE_MFC_FLAG 1)

find_package(Vulkan)
if (DEFINED ENV{VULKAN_SDK})
    message(STATUS "Vulkan environment variable: $ENV{VULKAN_SDK}")
    set(VULKAN_INCLUDE "$ENV{VULKAN_SDK}/include")
else()
    message(STATUS "Vulkan environment variable: undefined")
    set(VULKAN_INCLUDE "")
endif()

#include_directories(${Vulkan_INCLUDE_DIRS})

#C:\Users\caspasex\Desktop\3dm\thirdparty\mingw64\assimp3.3.1\lib
if(WIN32 AND MINGW)
    set(ASSIMP_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mingw64/assimp)
elseif(UNIX AND NOT APPLE)
    set(ASSIMP_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/linux/assimp)
else(APPLE)
    set(ASSIMP_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/bsd/assimp)
endif()

set(ASSIMP_LIBRARY "assimp" "IrrXML" "z")

#set(ASSIMP_LIBRARY "assimp" "IrrXML" "zlibstatic")
set(ASSIMP_LIBRARY_DIRS ${ASSIMP_PREFIX}/lib)
set(ASSIMP_INCLUDE_DIRS ${ASSIMP_PREFIX}/include)
message(${ASSIMP_LIBRARY_DIRS})
message(${ASSIMP_LIBRARY})
link_directories(${ASSIMP_LIBRARY_DIRS})
INCLUDE_DIRECTORIES(${ASSIMP_INCLUDE_DIRS})
set(LIBS ${LIBS} ${ASSIMP_LIBRARY})

#include_directories(C:/Users/Xarvie/Desktop/Assimp/include)
#link_directories(C:/Users/Xarvie/Desktop/Assimp/lib)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lib)




#include_directories(${Vulkan_INCLUDE_DIRS})

#set(LIBS ${LIBS} ${Vulkan_LIBRARIES})



#option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
#option(ASSIMP_BUILD_SAMPLES OFF)
#option(ASSIMP_BUILD_TESTS OFF)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/assimp-5.0.0)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/assimp-5.0.0/include)

#option(GLEW_STATIC ON)
#add_definitions(-DGLEW_STATIC)
#option(GLEW_USE_STATIC_LIBS ON)
#add_definitions(-DGLEW_USE_STATIC_LIBS)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/glew-2.1.0/build/cmake)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/glew-2.1.0/include)
#set(LIBS ${LIBS} glew_s)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/glm2)

# cd build
# cmake .. -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" -DCMAKE_CXX_FLAGS="-static"
PickIncludeDirectories(
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    INCLUDEDIRS
    # Exclude
    ${CMAKE_CURRENT_SOURCE_DIR}/build)

PickSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    CODEFILES
    # Exclude
    ${CMAKE_CURRENT_SOURCE_DIR}/build)


MakeFilter(
    ${CMAKE_CURRENT_SOURCE_DIR}/code)





add_library(STB_IMAGE "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/stb/stb_image.cpp")
target_include_directories(STB_IMAGE
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/stb/include/)
set(LIBS ${LIBS} STB_IMAGE)


add_library(GLAD "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/glad/glad.c")
include_directories(GLAD
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/glad/include/)
set(LIBS ${LIBS} GLAD)


#PickIncludeDirectories(
#        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/imgui
#        IMGUI_INCLUDEDIRS
#        # Exclude
#        ${CMAKE_CURRENT_SOURCE_DIR}/build)

PickSourceFiles(
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/imgui
        IMGUI_CODEFILES
        # Exclude
        ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_library(IMGUI ${IMGUI_CODEFILES})
target_include_directories(IMGUI
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/imgui)
set(LIBS ${LIBS} IMGUI)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}
    ${CODEFILES})
target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${INCLUDEDIRS})

#target_include_directories(${CMAKE_PROJECT_NAME}
#        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/)

#HeadOnly Library
target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/rapidjson/)

target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/entt-3.4.0/src/)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/win64/protobuf/include/)

ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/win64/protobuf/include/)
        
ELSE()

target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/win64/protobuf/include/)

ENDIF()


set(SDL 1)
set(GLFW 0)
if(SDL)
    #add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/cdl/source")
#    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/sdl")
#    set (SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/sdl")
#    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lib)
    #PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
#    find_package(SDL2 CONFIG REQUIRED)
#    target_link_libraries(${target_name} SDL2::SDL2main SDL2::SDL2-static)
    IF(WIN32 AND MINGW)
        #include(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mingw64/sdl/lib/cmake/SDL2/sdl2-config.cmake)
        set(SDL2_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mingw64/sdl)
        set(SDL2_LIBDIR "${SDL2_PREFIX}/lib")
        set(SDL2_LIBRARIES "-L${SDL2_LIBDIR}  -lmingw32 -lSDL2main -lSDL2 -mwindows")
        set(SDL2_INCLUDE_DIRS "${SDL2_PREFIX}/include/SDL2")
        target_include_directories(${CMAKE_PROJECT_NAME}
                PUBLIC ${SDL2_INCLUDE_DIRS})
        set(LIBS ${LIBS} ${SDL2_LIBRARIES})

        #set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
    ELSEIF(WIN32)
       # target_include_directories(${CMAKE_PROJECT_NAME}
       #         PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mingw64/sdl/include/)
    ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

        target_include_directories(${CMAKE_PROJECT_NAME}
                PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mingw64/sdl/include/)

    ELSE()
        set(SDL2_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/bsd/sdl)
        set(SDL2_LIBDIR "${SDL2_PREFIX}/lib")
        set(SDL2_LIBRARIES "-L${SDL2_LIBDIR}")
        #set(SDL2_LIBRARIES ${SDL2_LIBRARIES})
        #message (${SDL2_LIBDIR}/libSDL2.a)
        set(SDL2_INCLUDE_DIRS "${SDL2_PREFIX}/include/SDL2")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -L${SDL2_LIBDIR} -Wl,-search_paths_first  -Wno-unused-command-line-argument -lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal")
        target_include_directories(${CMAKE_PROJECT_NAME}
                PUBLIC ${SDL2_INCLUDE_DIRS})
        set(LIBS ${LIBS} ${SDL2_LIBRARIES} libSDL2.a)
    ENDIF()


    message("=======")
    #find_package(SDL2 CONFIG REQUIRED)
    #target_link_libraries(${target_name} PUBLIC SDL2::SDL2main SDL2::SDL2-static)

    message(STATUS "${SDL_STATIC}")
    message(STATUS "${CMAKE_C_FLAGS}")
    message("=======")
else(GLFW)
    option(USE_MSVC_RUNTIME_LIBRARY_DLL OFF)
    option(BUILD_SHARED_LIBS OFF)
    option(GLFW_BUILD_DOCS OFF)
    option(GLFW_BUILD_EXAMPLES OFF)
    option(GLFW_BUILD_TESTS OFF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/glfw-3.3)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/glfw-3.3/include/
            %VULKAN_SDK%/include)
    set(LIBS ${LIBS} glfw)
endif()

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/win64/fmt/include/)

ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/win64/fmt/include/)
        
ELSE()
target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/win64/fmt/include/)
        
ENDIF()


link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/general/sdl/build)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows") #target_link_libraries(MyExec PUBLIC "-static")
    IF(USE_GCC)
        # first create relevant static libraries requried for other projects


        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        target_link_libraries(${CMAKE_PROJECT_NAME}

                ${LIBS})
        ELSE()

        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
        target_link_libraries(${CMAKE_PROJECT_NAME}
                ${LIBS})
    ENDIF()
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
    target_link_libraries(${CMAKE_PROJECT_NAME} pthread
            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/linux/lib/libflatbuffers.a)
ELSE()
    IF(USE_GCC)

        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        target_link_libraries(${CMAKE_PROJECT_NAME}
                pthread
                ${LIBS}
                )
    ENDIF()
ENDIF()
