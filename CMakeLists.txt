cmake_minimum_required(VERSION 3.15)
project(soldierApp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Tell cmake where Qt is located
set(Qt5_DIR "~/Qt/5.9.9/gcc_64/lib/cmake/Qt5")

# Tell cmake to find the modules Qt5Core and Qt5widgets
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
add_executable(soldierApp main.cpp MainWindow.h MainWindow.cpp MainWindow.ui Map.cpp Map.h GameConfiguration.cpp GameConfiguration.h AddSoldierDialog.cpp AddSoldierDialog.h AddSoldierDialog.ui Soldier.cpp Soldier.h)

target_link_libraries(soldierApp Qt5::Core Qt5::Widgets)