project(halsim_linux_can)

include(CompileWarnings)

file(GLOB halsim_linux_can_src src/main/native/cpp/*.cpp)

add_library(halsim_linux_can SHARED ${halsim_linux_can_src})
wpilib_target_warnings(halsim_linux_can)
set_target_properties(halsim_linux_can PROPERTIES DEBUG_POSTFIX "d")
target_link_libraries(halsim_linux_can PUBLIC hal wpinet)

target_include_directories(halsim_linux_can PRIVATE src/main/native/include)

set_property(TARGET halsim_linux_can PROPERTY FOLDER "libraries")

install(TARGETS halsim_linux_can EXPORT halsim_linux_can DESTINATION "${main_lib_dest}")
