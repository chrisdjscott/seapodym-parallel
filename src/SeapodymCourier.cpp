
#include "SeapodymCourier.h"
#include <sstream>
#include <string>

SeapodymCourier::SeapodymCourier(MPI_Comm comm) {
    this->comm = comm;
    this->data = nullptr;
    this->data_size = 0;
    this->win = MPI_WIN_NULL;
}

SeapodymCourier::~SeapodymCourier() {
    if (this->win != MPI_WIN_NULL) {
        MPI_Win_free(&this->win);
    }
    this->data = nullptr;
    this->data_size = 0;
}

void 
SeapodymCourier::expose(double* data, int data_size) {
    this->data = data;
    this->data_size = data_size;
    // Create an MPI window to expose the data
    if (this->win != MPI_WIN_NULL) {
        MPI_Win_free(&this->win);
    }
    MPI_Win_create(data, data_size * sizeof(double), sizeof(double), MPI_INFO_NULL, this->comm, &this->win);
}

void 
SeapodymCourier::fetch(double* data, int target_rank) {

        // Ensure the window is ready for access
        MPI_Win_fence(0, win);
        
        // Fetch the data from the remote process
        MPI_Get(data, this->data_size, MPI_DOUBLE, target_rank, 0, this->data_size, MPI_DOUBLE, this->win);
        
        // Complete the access to the window
        MPI_Win_fence(0, win);
}
