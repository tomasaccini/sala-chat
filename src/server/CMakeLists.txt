cmake_minimum_required(VERSION 3.1)
project(chat_server)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors" )

add_executable(chat_server
				server_ChatThread.cpp
				server_ServerThread.cpp
				server_ClientHandler.cpp
				server_Main.cpp
				../common/common_Socket.cpp
				../common/common_Thread.cpp
				../common/common_SocketProtocol.cpp)

target_link_libraries(chat_server pthread)


if(NOT INSTALL_PATH)
  set(INSTALL_PATH "/usr/local")
endif(NOT INSTALL_PATH)

install(TARGETS chat_server DESTINATION ${INSTALL_PATH}/chat/server/bin/)
