#include <string>
#include <vector>
#include <admodel.h>
#include "SeapodymCohortAbstract.h"


#ifndef SEAPODYM_COHORT_FAKE
#define SEAPODYM_COHORT_FAKE

class SeapodymCohortFake : public SeapodymCohortAbstract {

  private:

      // how long a forward step takes in milliseconds
      long long milliseconds_step;

      // unique Id for this cohort
      int id;

      // data to exchange with other cohorts
      std::vector<double> data;

  public:

      /**
      * @brief Constructor
      * @param milliseconds_step execution time for a single step
      * @param id unique identifier of this cohort
      */
      SeapodymCohortFake(int milliseconds_step, std::size_t data_size, int id) : milliseconds_step(milliseconds_step), id(id) {
        this->data.resize(data_size);
      }

      /**
      * @brief Constructor
      * @param parFile XML input file
      * @param id unique identifier of this cohort (e.g. based on the date yyyymmdd of birth)
      */
      SeapodymCohortFake(const std::string& parFile, int id);

      /**
      * @brief Constructor
      * @param restartFile Restaret file
      */

      SeapodymCohortFake(const std::string& restartFile);

      /**
      * Constructor from other cohorts' spawning data
      * @param data serialized data
      * @param id unique identifier of this cohort
      */
      SeapodymCohortFake(const std::vector<double>& data, int id);

      /**
      * @brief Step forward
      * @param paramVector
      */
      void stepForward(const dvar_vector& paramVector);

      /**
        * Set state from array
        * @param array serialization of the object's state
        */
      void setStateFromArray(const std::vector<double>& array);

      /**
        * @brief Serialize the state
        * @return array serialization of the object's state
        */
      std::vector<double> getArrayFromState() const;

      /**
        * @brief Save the current state to a file
        * @param restartFile
        */
      void save(const std::string& restartFile) const;

};

#endif // SEAPODYM_COHORT_FAKE