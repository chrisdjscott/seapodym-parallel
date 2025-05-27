#include <string>
#include <vector>
#include <admodel.h>



#ifndef SEAPODYM_COHORT_ABSTRACT
#define SEAPODYM_COHORT_ABSTRACT

class SeapodymCohortAbstract {

  public:

    /**
     * @brief Step forward
     * @param paramVector
     */
     virtual void stepForward(const dvar_vector& paramVector) = 0;

     /**
      * Set state from array
      * @param array serialization of the object's state
      */
    virtual void setStateFromArray(const std::vector<double>& array) = 0;
  
     /**
      * @brief Serialize the state
      * @return array serialization of the object's state
      */
    virtual std::vector<double> getArrayFromState() const = 0;

     /**
      * @brief Save the current state to a file
      * @param restartFile
      */
    virtual void save(const std::string& restartFile) const = 0;

};

#endif // SEAPODYM_COHORT_ABSTRACT