#include "SeapodymCohort.h"

// to sleep...
#include <thread>
#include <chrono>

SeapodymCohort::SeapodymCohort(const std::string& parFile, int id) {
  this->id = id;
  this->milliseconds_step = 15; // HARDWIRED
  // NEED TO PROCESS parFile
}

SeapodymCohort::SeapodymCohort(const std::string& restartFile) {
  // TO IMPLEMENT
}

SeapodymCohort::SeapodymCohort(const double* data) {
  // TO IMPLEMENT
}

void 
SeapodymCohort::stepForward(const dvar_vector& paramVector) {
  // currently just sleep
  std::this_thread::sleep_for(std::chrono::milliseconds(this->milliseconds_step));
}

void SeapodymCohort::setStateFromArray(const double* array) {
  // TO IMPLEMENT
}

double* 
SeapodymCohort::getArrayFromState() const {
  // TO IMPLEMENT
  return nullptr;
}

void 
SeapodymCohort::save(const std::string& restartFile) const {
  // TO IMPLEMENT
}
