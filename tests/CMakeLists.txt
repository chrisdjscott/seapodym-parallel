include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${MPI_CXX_INCLUDE_PATH}
)

# Add the test executables
configure_file(testSeapodymCohort.cpp testSeapodymCohort.cxx)
add_executable(testSeapodymCohort testSeapodymCohort.cxx)
target_link_libraries(testSeapodymCohort PRIVATE seapodym_api)

add_executable(testSeapodymTaskManager testSeapodymTaskManager.cxx)
target_link_libraries(testSeapodymTaskManager PRIVATE seapodym_api)

add_executable(testSeapodymTaskManagerFake testSeapodymTaskManagerFake.cxx)
target_link_libraries(testSeapodymTaskManagerFake PRIVATE seapodym_api)

add_executable(testSeapodymCourier testSeapodymCourier.cxx)
target_link_libraries(testSeapodymCourier PRIVATE seapodym_api)

add_executable(testParallel testParallel.cxx)
target_link_libraries(testParallel PRIVATE seapodym_api)


# Register the test
add_test(NAME testSeapodymCohort COMMAND testSeapodymCohort)

add_test(NAME testSeapodymTaskManager COMMAND testSeapodymTaskManager)

add_test(NAME testSeapodymTaskManagerFake COMMAND testSeapodymTaskManagerFake)

add_test(NAME testSeapodymCourier2 COMMAND mpiexec -n 2 testSeapodymCourier)
