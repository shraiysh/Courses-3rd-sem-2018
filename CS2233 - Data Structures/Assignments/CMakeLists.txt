cmake_minimum_required(VERSION 3.0)

project("CS2233-Data-Structures-Assignments-1-and-2A")

## TODO: Add build targets for all the Assignments
add_executable(Assignment_1 Assignment_1/Assignment_1_Sol.c)
add_executable(Assignment_2A Assignment_2/Assignment_2A_Sol.c)
add_custom_command(TARGET Assignment_1
        POST_BUILD
        COMMAND "chmod" 755 "./A1_test_cases.sh"
        COMMAND "./A1_test_cases.sh"
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/test")
add_custom_command(TARGET Assignment_2A
        POST_BUILD
        COMMAND "chmod" 755 "./A2a_test_cases.sh"
        COMMAND "./A2a_test_cases.sh"
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/test")

find_program(VALGRIND "valgrind")

## stack tracing is broken in the Windows Subsystem for Linux (version 1):
## https://github.com/microsoft/WSL/issues/3589
## https://github.com/Microsoft/WSL/issues/3031
##
## For example, starting `valgrind` on my machine[*] results in:
##	 ==1032== error calling PR_SET_PTRACER . . .
## ----
## [*] Host: Windows 10,Build 18362
##
if(VALGRIND AND NOT DEFINED ENV{WSL_DISTRO_NAME})
	add_custom_command(TARGET Assignment_1
	    POST_BUILD
        COMMAND "${VALGRIND}" --leak-check=full --show-leak-kinds=all --show-reachable=yes "$<TARGET_FILE:Assignment_1>"
        COMMENT "\nEnter two numbers to add.\nPress CRTL+D when finished")
	add_custom_command(TARGET Assignment_2A
		POST_BUILD
        COMMAND "${VALGRIND}" --leak-check=full --show-leak-kinds=all --show-reachable=yes "$<TARGET_FILE:Assignment_2A>"
        COMMENT "\nEnter two numbers to compare.\nPress CRTL+D when finished")
endif()

## force building of Assignment_1 first
add_dependencies(Assignment_2A Assignment_1)
set_target_properties(Assignment_1 Assignment_2A
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
