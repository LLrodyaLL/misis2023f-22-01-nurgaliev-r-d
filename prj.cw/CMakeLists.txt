cmake_minimum_required (VERSION 3.8)

project ("astMarker")


find_package(imgui REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

add_executable(astMarker
        "main.cpp"
        "image.cpp"
        "image.h"
        )



target_link_libraries(astMarker
        imgui::imgui
        unofficial::nativefiledialog::nfd
        sfml-system sfml-network sfml-graphics sfml-window
        ImGui-SFML::ImGui-SFML
        )


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET astMarker PROPERTY CXX_STANDARD 20)
endif()


find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
       set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
       set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_IN})

       add_custom_target(doc ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM
       )

endif()

install (TARGETS astMarker)

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/
    DESTINATION bin
    CONFIGURATIONS Debug
    FILES_MATCHING PATTERN "*.dll*"
    )
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/
    CONFIGURATIONS Release
    DESTINATION bin
    FILES_MATCHING PATTERN "*.dll*"
    )
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO}/
    DESTINATION bin
    CONFIGURATIONS RelWithDebInfo
    FILES_MATCHING PATTERN "*.dll*"
    )


if(DOXYGEN_FOUND)
       install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/rtf
               DESTINATION docs)
   endif()
