cmake_minimum_required(VERSION 3.28)
project(ing_library_project C)

set(CMAKE_C_STANDARD 99)


if(NOT DEFINED ING_GUI_BACKEND)
    if(WIN32)
        set(ING_GUI_BACKEND "win32")
    elseif(APPLE)
        set(ING_GUI_BACKEND "cocoa")
    elseif(UNIX)
        set(ING_GUI_BACKEND "gtk") # At least for now, I'm not going to bother trying to figure out whether the current desktop is gtk based or qt based
    else()                         # in order to build with qt, you'll have to explicitly ask for it
        message(FATAL_ERROR "ing tried to automatically determine which gui backend to use, but it couldn't recognize your platform!\n"
                            "You could try manually setting ING_GUI_BACKEND, but if you're compiling on a truly weird platform, then it's likely that you'll run into other issues...")
    endif()
endif()

add_library(ing

            ing_${ING_GUI_BACKEND}_main_loop.c)

add_subdirectory(internal)

target_link_libraries(ing PUBLIC ing_internal) # use PUBLIC visibility because users should be able to extend the library,
                                               # and they'll need to link against the internal api to do that
if(${ING_GUI_BACKEND} STREQUAL "win32")
    if(WIN32)

    else()
        message(FATAL_ERROR "ING_GUI_BACKEND \"win32\" is only supported on Windows (current platform is ${CMAKE_SYSTEM_NAME})")
    endif()
elseif(${ING_GUI_BACKEND} STREQUAL "cocoa")
    if(APPLE) # it might be better to do if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin") instead

    else()
        message(FATAL_ERROR "ING_GUI_BACKEND \"cocoa\" is only supported on Apple platforms (current platform is ${CMAKE_SYSTEM_NAME})")
    endif()
elseif(${ING_GUI_BACKEND} STREQUAL "gtk")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

    target_link_libraries(ing PUBLIC PkgConfig::GTK4)
elseif(${ING_GUI_BACKEND} STREQUAL "qt")

else()
    message(FATAL_ERROR "ing didn't recognize the provided ING_GUI_BACKEND! (it was set to \"${ING_GUI_BACKEND}\")\n"
                        "the supported values are \"win32\" (Windows only), \"cocoa\" (Apple platforms only), \"gtk\", and \"qt\"\n"
                        "(note that gui backend detection is CASE SENSITIVE)")
endif()