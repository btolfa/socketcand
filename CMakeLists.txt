cmake_minimum_required(VERSION 3.3.1 FATAL_ERROR)

project(socketcand C)

find_package(Threads REQUIRED)

set(SRC
    socketcand.c
    statistics.c
    beacon.c
    state_bcm.c
    state_raw.c
    state_isotp.c
    state_control.c
)

add_executable(socketcand ${SRC})

target_include_directories(socketcand PUBLIC
        include
        ${CMAKE_BINARY_DIR}
        )

target_link_libraries(socketcand Threads::Threads)
target_compile_definitions(socketcand PUBLIC PF_CAN=29 AF_CAN=PF_CAN)

include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckSymbolExists)

set(DEBUG $<$<CONFIG:Debug>:1> CACHE INTERNAL "Debug flag for config.h.in")
check_include_files("arpa/inet.h" HAVE_ARPA_INET_H)
check_function_exists(fork HAVE_FORK)
check_function_exists(gethostname HAVE_GETHOSTNAME)
check_function_exists(gettimeofday HAVE_GETTIMEOFDAY)
check_function_exists(inet_ntoa HAVE_INET_NTOA)
check_include_files("inttypes.h" HAVE_INTTYPES_H)

# /* Define to 1 if you have the `config' library (-lconfig). */
# cmakedefine HAVE_LIBCONFIG

set(HAVE_LIBPTHREAD $<BOOL:THREADS_FOUND> CACHE INTERNAL "PThread flag for config.h.in")
check_function_exists(malloc HAVE_MALLOC)
check_include_files("memory.h" HAVE_MEMORY_H)
check_function_exists(memset HAVE_MEMSET)
check_include_files("netinet/in.h" HAVE_NETINET_IN_H)
check_function_exists(realloc HAVE_SELECT)
check_function_exists(select HAVE_SELECT)
check_function_exists(socket HAVE_SOCKET)
check_include_files("stdint.h" HAVE_STDINT_H)
check_include_files("stdlib.h" HAVE_STDLIB_H)
check_function_exists(strerror HAVE_STRERROR)
check_include_files("strings.h" HAVE_STRINGS_H)
check_include_files("string.h" HAVE_STRING_H)
check_include_files("syslog.h" HAVE_SYSLOG_H)
check_include_files("sys/ioctl.h" HAVE_SYS_IOCTL_H)
check_include_files("sys/socket.h" HAVE_SYS_SOCKET_H)
check_include_files("sys/stat.h" HAVE_SYS_STAT_H)
check_include_files("sys/time.h" HAVE_SYS_TIME_H)
check_include_files("sys/types.h" HAVE_SYS_TYPES_H)
check_include_files("unistd.h" HAVE_UNISTD_H)
check_function_exists(vfork HAVE_VFORK)
check_include_files("vfork.h" HAVE_VFORK_H)
set(HAVE_WORKING_FORK $<BOOL:HAVE_FORK>)
set(HAVE_WORKING_VFORK $<BOOL:HAVE_VFORK>)
set(PACKAGE_BUGREPORT "https://github.com/dschanoeh/socketcand/issues")
set(PACKAGE_NAME "socketcand")
set(PACKAGE_STRING "socketcand 0.4.2")
set(PACKAGE_TARNAME "socketcand")
set(PACKAGE_URL "https://github.com/dschanoeh/socketcand")
set(PACKAGE_VERSION "0.4.2")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmakeconfig.h.in ${CMAKE_BINARY_DIR}/config.h)