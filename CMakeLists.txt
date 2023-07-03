cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 20)

project(Messenger)

if (NOT WIN32)
	find_package(PkgConfig)
	if (PKG_CONFIG_FOUND)
		pkg_check_modules(PQXX libpqxx)
		if (PQXX_FOUND)
			if (PQXX_VERSION STRGREATER "7")
				message(STATUS "libpqxx version ${PQXX_VERSION}, requesting c++17")
				set (CMAKE_CXX_STANDARD 17)
			endif()
		endif()
	endif()
else()

	FIND_PATH(PQXX_INCLUDE_DIR pqxx/pqxx PATHS)
	MARK_AS_ADVANCED(PQXX_INCLUDE_DIR)

	FIND_LIBRARY(PQXX_LIBRARIES pqxx )
	MARK_AS_ADVANCED(PQXX_LIBRARIES)

	FIND_LIBRARY(PQ_LIBRARY pq )
	MARK_AS_ADVANCED(PQ_LIBRARY)

	if(PQXX_LIBRARY AND PQ_LIBRARY AND PQXX_INCLUDE_DIR)
		set( PQXX_FOUND 1 )
		message( STATUS "Found pqxx: ${PQXX_LIBRARIES}, ${PQ_LIBRARY}, ${PQXX_INCLUDE_DIR}")
		if (PQXX_VERSION STRGREATER "7")
			message(STATUS "libpqxx version ${PQXX_VERSION}, requesting c++17")
			set (CMAKE_CXX_STANDARD 17)
		endif()
	else()
		message(STATUS "Could NOT find pqxx and pq library")
	endif()
endif()

include_directories(${PQXX_INCLUDE_DIR})


add_executable(launch_server launch_server.cpp)
add_executable(main main.cpp)

add_library(DBConnection DBConnection.hpp DBConnection.cpp)
add_library(SqlQueries SqlQueries.hpp SqlQueries.cpp)
add_library(Server Server.hpp Server.cpp)
add_library(Client Client.hpp Client.cpp)
add_library(Message Message.hpp Message.cpp)


target_link_libraries(Message PUBLIC Server DBConnection)
target_link_libraries(Server PUBLIC	${PQXX_LIBRARIES} ${PQ_LIBRARY} DBConnection Message)
target_link_libraries(DBConnection PRIVATE SqlQueries)

target_link_libraries(Client Message)

target_link_libraries(launch_server PUBLIC Server)
target_link_libraries(main PUBLIC Client)

