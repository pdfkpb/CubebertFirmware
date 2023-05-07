set(LIB_NAME Lighting)

add_library(${LIB_NAME} lighting.cpp)

include(FetchContent)
FetchContent_Declare(
  pico-neopixel
  GIT_REPOSITORY https://github.com/pdfkpb/pico-neopixel.git
  GIT_TAG        4a9ae19991bc8841942c62305bf8b5595d2acc15
)
FetchContent_MakeAvailable(pico-neopixel)

target_include_directories(
  ${LIB_NAME}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
  ${LIB_NAME}
  pico_stdlib
  pico_neopixel
)

add_dependencies(
  ${LIB_NAME}
  pico_stdlib
  pico_neopixel
)

install(TARGETS ${LIB_NAME} DESTINATION lib)
