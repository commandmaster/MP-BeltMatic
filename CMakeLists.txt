cmake_minimum_required(VERSION 3.11)
project(ENetProject)

# Enable C and C++ languages
enable_language(C CXX)

# Include FetchContent module
include(FetchContent)

# Declare and fetch ENet
FetchContent_Declare(
  enet
  GIT_REPOSITORY https://github.com/lsalzman/enet.git
  GIT_TAG        master  # You can specify a specific tag or branch if needed
)
FetchContent_MakeAvailable(enet)

# Set client and server source directories
set(CLIENT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/client/src)
set(SERVER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/server/src)

# Add the client executable
file(GLOB CLIENT_SOURCES ${CLIENT_SRC_DIR}/*.cpp)
add_executable(ClientApp ${CLIENT_SOURCES})

# Link ENet to the client application
target_link_libraries(ClientApp PRIVATE enet)

# Include ENet headers for client
target_include_directories(ClientApp PRIVATE ${enet_SOURCE_DIR}/include)

# Add the server executable
file(GLOB SERVER_SOURCES ${SERVER_SRC_DIR}/*.cpp)
add_executable(ServerApp ${SERVER_SOURCES})

# Link ENet to the server application
target_link_libraries(ServerApp PRIVATE enet)

# Include ENet headers for server
target_include_directories(ServerApp PRIVATE ${enet_SOURCE_DIR}/include)
