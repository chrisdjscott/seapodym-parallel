#include <map>
#include <vector>
#include <set>

#ifndef SEAPODYM_TASK_MANAGER
#define SEAPODYM_TASK_MANAGER

class SeapodymTaskManager {

    private:

        // number of age groups for each time step, ideally matching the number of workers
        int numAgeGroups; 

        // number of workers 0...numWorkers-1
        int numWorkers;

        // number of time steps
        int numTimeSteps;

        int numCohorts = this->numAgeGroups + this->numTimeSteps - 1;

        std::map<int, std::vector<int> > worker2task;

    public:

        /**
         * Constructor
         * @param numAgeGroups number of age groups that are run concurrently
         * @param numWorkers number of workers
         * @param numTimeSteps total number of time steps of the simulation
         * @retun list of tasks
         */
        SeapodymTaskManager(int numAgeGroups, int numWorkers, int numTimeSteps);

        /**
         * Get the initial list of tasks
         * @param workerId worker ID
         * @retun list of tasks
         */
        std::vector<int> getInitTaskIds(int workerId) const;

        /**
         * Get the number of current steps a task will run
         * @param taskId task ID
         * @retun number of steps
         */
        int getNumSteps(int taskId) const;

        std::set<int> getDependencies(int taskId) const;

        int getNextTask(int taskId) const;

};

#endif // SEAPODYM_TASK_MANAGER