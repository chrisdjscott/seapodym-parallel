
#include "SeapodymCourrier.h"

SeapodymCourrier::SeapodymCourrier(MPI_Comm comm) {
    this->comm = comm;
}

SeapodymCourrier::~SeapodymCourrier() {
    for (auto& entry : workerData) {
        MPI_Win_free(&std::get<0>(entry.second));
    }
}

void 
SeapodymCourrier::expose(int workerId, double* data, int count) {
    MPI_Win win;
    MPI_Win_create(data, count * sizeof(double), sizeof(double), MPI_INFO_NULL, comm, &win);
    
    // Store the window and data pointer in the map
    workerData[workerId] = std::make_tuple(win, data, count);
}

void 
SeapodymCourrier::fetch(double* data, int target_rank) {

    auto it = workerData.find(target_rank);
    if (it != workerData.end()) {
        MPI_Win win = std::get<0>(it->second);
        double* remote_data = std::get<1>(it->second);
        std::size_t count = std::get<2>(it->second);

        // Ensure the window is ready for access
        MPI_Win_fence(0, win);
        
        // Fetch the data from the remote process
        MPI_Get(data, count, MPI_DOUBLE, target_rank, 0, count, MPI_DOUBLE, win);
        
        // Complete the access to the window
        MPI_Win_fence(0, win);
    } else {
        throw std::runtime_error("Worker ID not found in exposed data.");
    }
}
