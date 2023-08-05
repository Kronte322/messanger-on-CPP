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
				set (CMAKE_CXX_STANDARD 20)
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
			set (CMAKE_CXX_STANDARD 20)
		endif()
	else()
		message(STATUS "Could NOT find pqxx and pq library")
	endif()
endif()



include_directories(include ${PQXX_INCLUDE_DIR})


pkg_check_modules(GTKMM gtkmm-4.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(launch_server launch_server.cpp)
add_executable(main main.cpp)

add_library(DBConnection ../back/db/DBConnection.hpp ../back/db/DBConnection.cpp)
add_library(SqlQueries ../back/db/SqlQueries.hpp ../back/db/SqlQueries.cpp)
add_library(Server ../back/Server.hpp ../back/Server.cpp)
add_library(Client ../back/Client.hpp ../back/Client.cpp)
add_library(Message ../back/Message.hpp ../back/Message.cpp)
add_library(ClientStorage ../back/ClientStorage.hpp ../back/ClientStorage.cpp)
add_library(App ../front/App.hpp ../front/App.cpp)
add_library(UI ../front/UI.hpp ../front/UI.cpp)
add_library(ClientController ../back/ClientController.hpp ../back/ClientController.cpp)
add_library(ClientImplementer ../back/ClientImplementer.hpp ../back/ClientImplementer.cpp)
add_library(ServerImplementer ../back/ServerImplementer.hpp ../back/ServerImplementer.cpp)

target_link_libraries(Message PUBLIC Server DBConnection Client)
target_link_libraries(Server PUBLIC	${PQXX_LIBRARIES} ${PQ_LIBRARY} DBConnection Message ServerImplementer)
target_link_libraries(DBConnection PRIVATE SqlQueries)
target_link_libraries(UI PUBLIC ${GTKMM_LIBRIRIES} ClientController)
target_link_libraries(App PUBLIC Client ClientStorage UI ClientController)
target_link_libraries(Client PUBLIC Message)
target_link_libraries(launch_server PUBLIC Server)
target_link_libraries(ClientController PUBLIC Client ClientImplementer ClientStorage)
target_link_libraries(ClientImplementer PUBLIC ClientStorage)
target_link_libraries(ServerImplementer PUBLIC DBConnection Message)
target_link_libraries(main PUBLIC App)

target_link_libraries (main PUBLIC ${GTKMM_LIBRARIES})
