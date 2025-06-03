#include <SeapodymCohortFake.h>
#include <SeapodymTaskManager.h>
#include <SeapodymCourier.h>
#include <CmdLineArgParser.h>
#include <mpi.h>
#include <admodel.h>
#include <iostream>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);
    
    CmdLineArgParser cmdLine;
    cmdLine.set("-na", 3, "Number of age groups");
    cmdLine.set("-nt", 5, "Total number of time steps");
    if (!cmdLine.parse(argc, argv) || cmdLine.get<bool>("-h")) {
        std::cerr << "Error parsing command line arguments." << std::endl;
        cmdLine.help();
        MPI_Finalize();
        return 1;
    }
    int na = cmdLine.get<int>("-na");
    int nt = cmdLine.get<int>("-nt");
    int numWorkers;
    MPI_Comm_size(MPI_COMM_WORLD, &numWorkers);
    int workerId;
    MPI_Comm_rank(MPI_COMM_WORLD, &workerId);
    if (na <= 0 || nt <= 0 || na > numWorkers) {
        std::cerr << "Invalid number of age groups or time steps." << std::endl;
        MPI_Finalize();
        return 1;
    }

    if (workerId == 0) {
        std::cout << "Running with " << numWorkers << " workers." << std::endl;
        std::cout << "Number of age groups: " << na << ", Total number of time steps: " << nt << std::endl;
    }

    SeapodymCohortFake cohort(100, 10, workerId); // Create a fake cohort for testing
    SeapodymCourier courier(MPI_COMM_WORLD);

    // Initialize the SeapodymTaskManager
    SeapodymTaskManager taskManager(na, numWorkers, nt);

    for (auto taksId : taskManager.getInitTaskIds(workerId)) {
        int numSteps = taskManager.getNumSteps(taksId);
        std::cout << "Worker " << workerId << " has task " << taksId << " with " << numSteps << " steps." << std::endl;

        // march forward
        for (int step = 0; step < numSteps; ++step) {
            // Simulate a forward step
            cohort.stepForward(dvar_vector());
        }
        std::cout << "Worker " << workerId << " completed task " << taksId << "." << std::endl;

    }


    MPI_Finalize();
    return 0;
}
