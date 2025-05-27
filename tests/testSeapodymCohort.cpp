#include <SeapodymCohortFake.h>
#include <admodel.h>
#include <iostream>
#include <string>
#include <vector>


int main() {
    // Create a SeapodymCohort object
    int id = 12345;
    std::string parFile = "@CMAKE_SOURCE_DIR@/data/skipjack_F0.xml"; 
    SeapodymCohortFake cohort(parFile, id);

    cohort.stepForward(dvar_vector());

    // Serialize the state
    std::vector<double> stateArray = cohort.getArrayFromState();
    if (stateArray.size() > 0) {
        // Print the serialized state
        std::cout << "Serialized state: ";
        double checksum = 0.0;
        for (std::size_t i = 0; i < stateArray.size(); ++i) {
            checksum += std::fabs(stateArray[i]);
        }
        std::cout << "checksum: " << checksum << std::endl;
    } else {
        std::cout << "Failed to serialize state." << std::endl;
    }
    return 0;
}
