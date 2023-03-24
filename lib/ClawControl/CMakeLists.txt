set(LIB_NAME ClawControl)

add_library(${LIB_NAME} fingers.cpp wrist.cpp)

target_include_directories(
  ${LIB_NAME}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
  ${LIB_NAME}
  pico_stdlib
)

add_dependencies(
  ${LIB_NAME}
)

install(TARGETS ${LIB_NAME} DESTINATION lib)

pico_add_extra_outputs(${LIB_NAME})