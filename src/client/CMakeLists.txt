cmake_minimum_required(VERSION 3.1)
project(chat_client)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors" )

add_executable(chat_client
				client_Main.cpp
				client_ChatDisplay.cpp
				../common/common_SocketProtocol.cpp
				../common/common_Thread.cpp
				../common/common_Socket.cpp)

target_link_libraries(chat_client pthread)

if(NOT INSTALL_PATH)
  set(INSTALL_PATH "/usr/local")
endif(NOT INSTALL_PATH)


install(TARGETS chat_client DESTINATION ${INSTALL_PATH}/chat/client/bin/)
