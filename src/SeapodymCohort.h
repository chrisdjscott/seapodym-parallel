#include <string>
#include <vector>
#include <admodel.h>



#ifndef SEAPODYM_COHORT
#define SEAPODYM_COHORT

class SeapodymCohort {

private:

    // unique Id for this cohort
    int id;

    // how long a forward step takes in milliseconds
    long long milliseconds_step;

    // size of the data to required to produce a new cohort from larvae
    std::size_t data_size;

public:

    /**
     * @brief Constructor
     * @param parFile XML input file
     * @param id unique identifier of this cohort (e.g. based on the date yyyymmdd of birth)
     */
    SeapodymCohort(const std::string& parFile, int id);

    /**
     * @brief Constructor
     * @param restartFile Restaret file
     */

    SeapodymCohort(const std::string& restartFile);

    /**
     * Constructor from other cohorts' spawning data
     * @param data serialized data
     */
    SeapodymCohort(const std::vector<double>& data);


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

#endif // SEAPODYM_COHORT