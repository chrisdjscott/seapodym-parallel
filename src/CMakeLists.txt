include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)
set(SRCS
   SeapodymCohortFake.cpp
   SeapodymTaskManager.cpp
   )

add_library(seapodym_api ${SRCS})
target_link_libraries(seapodym_api admb)
