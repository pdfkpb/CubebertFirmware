set(LIB_NAME ClawControl)

add_library(${LIB_NAME} claw.cpp fingers.cpp palm.cpp wrist.cpp)

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
  pico_stdlib
)

install(TARGETS ${LIB_NAME} DESTINATION lib)
