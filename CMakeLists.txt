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



find_package(SFML 2.5 COMPONENTS graphics window system)

include_directories(${PQXX_INCLUDE_DIR})


add_executable(launch_server launch_server.cpp)
add_executable(main main.cpp)

add_library(DBConnection ../back/db/DBConnection.hpp ../back/db/DBConnection.cpp)
add_library(SqlQueries ../back/db/SqlQueries.hpp ../back/db/SqlQueries.cpp)
add_library(Server ../back/Server.hpp ../back/Server.cpp)
add_library(Client ../back/Client.hpp ../back/Client.cpp)
add_library(Message ../back/Message.hpp ../back/Message.cpp)
add_library(TextBox ../front/ui_basic/TextBox.hpp ../front/ui_basic/TextBox.cpp)
add_library(UI ../front/UI.hpp ../front/UI.cpp)
add_library(App ../front/App.hpp ../front/App.cpp)
add_library(UIElements ../front/ui_elements/UIElements.hpp ../front/ui_elements/UIElements.cpp)
add_library(ClientStorage ../back/ClientStorage.hpp ../back/ClientStorage.cpp)


target_link_libraries(Message PUBLIC Server DBConnection Client App)
target_link_libraries(Server PUBLIC	${PQXX_LIBRARIES} ${PQ_LIBRARY} DBConnection Message)
target_link_libraries(DBConnection PRIVATE SqlQueries)
target_link_libraries(UI PUBLIC TextBox sfml-graphics)
target_link_libraries(TextBox PUBLIC sfml-graphics)
target_link_libraries(UIElements PUBLIC TextBox ClientStorage)



target_link_libraries(Client Message)
target_link_libraries(App PUBLIC Client TextBox UI UIElements ClientStorage sfml-graphics sfml-system sfml-window)
target_link_libraries(launch_server PUBLIC Server)
target_link_libraries(main PUBLIC App)

