cmake_minimum_required(VERSION 2.4)

project(baye)

set (bayelib_SRCS
FgtCount.c
FgtPkAi.c
Fight.c
FightSub.c
PublicFun.c
Size.c
citycmd.c
citycmdb.c
citycmdc.c
citycmdd.c
citycmde.c
cityedit.c
comIn.c
comOut.c
datman.c
debug.c
gamEng.c
infdeal.c
itoa.c
paccount.c
pconst.c
pstring.c
showface.c
strcnt.c
tactic.c
varma.c
data-bind.c
bind-objects.c
touch.c
config.c
platform/common/bios.c
platform/common/gui.c
platform/common/sys.c
)

set (bayelib_js_SRCS
platform/js/fsys.c
platform/js/sem.c
platform/js/timer.c
platform/js/script.c
platform/js/sys-js.c
)

set (bayelib_win_SRCS
platform/win/fsys.c
platform/win/game.c
platform/win/script.c
platform/win/sem.c
platform/win/sys.c
platform/win/timer.c
)

add_library(bayeliba ${bayelib_SRCS})

if (${CMAKE_SYSTEM_NAME} STREQUAL Emscripten)
	target_sources(bayeliba PRIVATE ${bayelib_js_SRCS})
	add_executable(baye
		platform/js/main.c
		version.c
	)

	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/baye/version.h
		COMMAND ./genver.py > ${CMAKE_CURRENT_SOURCE_DIR}/baye/version.h
	)

	add_custom_target(ver_header ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/baye/version.h)

	add_dependencies(ver_header bayeliba)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL Windows)
	target_sources(bayeliba PRIVATE ${bayelib_win_SRCS})
	add_executable(baye
		platform/win/window.c
		version.c
	)
	find_package (Threads)
	target_link_libraries (baye ${CMAKE_THREAD_LIBS_INIT})
	SET_TARGET_PROPERTIES(baye PROPERTIES LINK_FLAGS "-pthread")
	#SET_TARGET_PROPERTIES(baye PROPERTIES COMPILE_OPTIONS "-g")
	#SET_TARGET_PROPERTIES(bayeliba PROPERTIES COMPILE_OPTIONS "-g")
endif()


#target_link_libraries(baye bayeliba msgpackc-static)
target_link_libraries(baye bayeliba)

target_include_directories(baye PRIVATE . ./platform/common)
target_include_directories(bayeliba PRIVATE . ./platform/common)


#target_include_directories(bayeliba PRIVATE ${msgpack_SOURCE_DIR}/include)
if (${CMAKE_SYSTEM_NAME} STREQUAL Emscripten)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s EMTERPRETIFY=1")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s EMTERPRETIFY_ASYNC=1")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ASSERTIONS=0")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s EMTERPRETIFY_WHITELIST='@whitelist.json'")
	target_link_libraries(baye "--memory-init-file 0")
#	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --memoryprofiler")
#	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s EMTERPRETIFY_ADVISE=1")
endif (${CMAKE_SYSTEM_NAME} STREQUAL Emscripten)

