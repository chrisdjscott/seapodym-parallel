include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(seapodym_api SeapodymCohortFake.cpp)
target_link_libraries(seapodym_api admb)
