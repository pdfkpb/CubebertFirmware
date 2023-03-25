set(BIN_NAME cubebert-firmware)

add_executable(${BIN_NAME} cubebert-firmware.cpp state.cpp)

target_compile_features(${BIN_NAME} PUBLIC cxx_std_11)

target_link_libraries(
  ${BIN_NAME}
  PUBLIC pico_stdlib
  PUBLIC FirmwareIPC
  PUBLIC Lighting
)

add_dependencies(
  ${BIN_NAME}
  pico_stdlib
)

install(TARGETS ${BIN_NAME} DESTINATION sbin)

pico_add_extra_outputs(${BIN_NAME})