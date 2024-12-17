cmake_minimum_required(VERSION 3.12) #cmake minimum version

set(proj_name AST)
project(${proj_name})
message("------------ Project files genertion for ${proj_name} ------------")


# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#common options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
message("Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

if(MCVS)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${proj_name})
endif(MCVS)


#cpp options
set(CMAKE_CXX_STANDART 20)


#app options
set(INC
        "INode.hh"
        "Node.hh"
)

set(SRC
        "Node.cc"
)

#source_group("Header Files" FILES "src/List.h")

#source_group("Source Files" FILES "src/List.cc" "src/main.cc")


add_executable(${proj_name} ${SRC} ${INC})


#includes
#target_include_directories(${proj_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})