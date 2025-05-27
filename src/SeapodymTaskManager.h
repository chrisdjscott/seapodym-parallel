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

        SeapodymTaskManager(int numAgeGroups, int numWorkers, int numTimeSteps);

        std::vector<int> getInitTaskIds(int workerId) const;

        int getNumSteps(int taskId) const;

        std::set<int> getDependencies(int taskId) const;

        int getNextTask(int taskId) const;

};

#endif // SEAPODYM_TASK_MANAGER