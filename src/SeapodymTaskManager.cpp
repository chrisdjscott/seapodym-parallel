#include "SeapodymTaskManager.h"


SeapodymTaskManager::SeapodymTaskManager(int numAgeGroups, int numWorkers, int numTimeSteps) {

            this->numAgeGroups = numAgeGroups;
            this->numWorkers = numWorkers;
            this->numTimeSteps = numTimeSteps;

            for (auto wid = 0; wid < this->numWorkers; ++wid) {
                this->worker2task.insert({wid, std::vector<int>()});
            }

            // initially
            for (auto i = 0; i < this->numAgeGroups; ++i) {
                int workerId = i % this->numWorkers;
                this->worker2task[workerId].push_back(i);
            }
        
        }

std::vector<int> 
SeapodymTaskManager::getInitTaskIds(int workerId) const {
    auto it = this->worker2task.find(workerId);
    return it->second;
}

int 
SeapodymTaskManager::getNumSteps(int taskId) const {
            
    if (this->numAgeGroups <= taskId && taskId < this->numTimeSteps) {
        return this->numAgeGroups;
    }
    else if (taskId >= this->numTimeSteps) {
        return this->numAgeGroups + this->numTimeSteps - taskId - 1;
    }
    else {
        // if taskId < this->numAgeGroups
        return this->numAgeGroups - taskId;
    }
}

std::set<int> 
SeapodymTaskManager::getDependencies(int taskId) const {

    std::set<int> res;
    
    if (taskId > 2*this->numAgeGroups - 1) {
                
        for (auto i = taskId - this->numAgeGroups + 1; i < taskId; ++i) {
            res.insert(i);
        }

    }
    else if (this->numAgeGroups <= taskId && taskId <= 2*this->numAgeGroups - 1) {

        // first range: 0 to (2*na - 1 - task_id - 1)
        for (int i = 0; i < 2 * this->numAgeGroups - 1 - taskId; ++i) {
            res.insert(i);
        }

        // second range: na to (task_id - 1)
        for (int i = this->numAgeGroups; i < taskId; ++i) {
            res.insert(i);
        }
    }
        
    return res;
}


int 
SeapodymTaskManager::getNextTask(int taskId) const {
            
    int res = taskId + this->numAgeGroups;
            
    if (taskId < this->numAgeGroups) {
        res = taskId + 2*(this->numAgeGroups - 1 - taskId) + 1;
    }
    else if (taskId >= this->numTimeSteps - 1) {
        //last task
        res = -1;
    }
    return res;
}
