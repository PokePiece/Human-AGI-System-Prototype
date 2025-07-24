cmake_minimum_required(VERSION 3.16)

project(Human_AGI_System VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


cmake_minimum_required(VERSION 3.16)
project(CoreBrain)

set(CMAKE_CXX_STANDARD 17)

include_directories(llama.cpp)

add_executable(corebrain
    src/corebrain.cpp
    src/main.cpp
    # <-- add llama.cpp/ prefix here
    llama.cpp/ggml/src/ggml.c
    llama.cpp/ggml/src/ggml-alloc.c
    llama.cpp/ggml/src/ggml-backend-reg.cpp
    llama.cpp/ggml/src/ggml-backend.cpp
    llama.cpp/ggml/src/ggml-opt.cpp
    llama.cpp/ggml/src/ggml-quants.c
    llama.cpp/ggml/src/ggml-threading.cpp
    llama.cpp/ggml/src/ggml.cpp
    llama.cpp/ggml/src/gguf.cpp
)








target_link_libraries(corebrain pthread)
target_include_directories(corebrain PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(corebrain PRIVATE "${CMAKE_SOURCE_DIR}/llama.cpp/include")




set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    src/Body.cpp
    include/Body.h
    src/Brain.cpp
    include/Brain.h
    src/LanguageComponent.cpp
    include/LanguageComponent.h
    src/VisionComponent.cpp
    include/VisionComponent.h
    include/Component.h
    include/VoidBrain.h
    src/VoidBrain.cpp
    include/CoreBrain.h
)
 

# Assuming your Python script is in the 'scripts' folder relative to your CMakeLists.txt
set(PYTHON_SCRIPTS
    scripts/VoidAGI.py
    scripts/VoidAGIPlaceholder.py
    scripts/prompts.py
)

# Copy Python scripts to the binary output directory
foreach(script ${PYTHON_SCRIPTS})
    configure_file(${script} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Human_AGI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    ) 
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Human_AGI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Human_AGI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Human_AGI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Human_AGI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(Human_AGI PRIVATE include)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Human_AGI)
endif()
set_target_properties(Human_AGI PROPERTIES
    WIN32_EXECUTABLE TRUE
)




include(GNUInstallDirs)
install(TARGETS Human_AGI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Human_AGI)
endif()
