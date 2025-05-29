#include <SeapodymCourier.h>
#include <iostream>


int main(int argc, char* argv[]) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const int data_size = 10;
    double data[data_size];

    {
        // Create an instance of SeapodymCourier
        SeapodymCourier courier(MPI_COMM_WORLD);
        for (int i = 0; i < data_size; ++i) {
            data[i] = world_rank * 10 + i; // Fill with some test data
        }

        // Expose the memory of this process
        courier.expose(data, data_size);

        if (world_rank == 0) {
            // Process 0 fetches data from all other processes
            for (int i = 1; i < world_size; ++i) {
                double fetched_data[data_size];
                courier.fetch(fetched_data, i);
                std::cout << "Process 0 fetched data from process " << i << ": ";
                for (int j = 0; j < data_size; ++j) {
                    std::cout << fetched_data[j] << " ";
                }
                std::cout << std::endl;
            }
        }
        else {
            // Other processes can also fetch their own data
            double fetched_data[data_size];
            courier.fetch(fetched_data, world_rank);
            std::cout << "Process " << world_rank << " fetched its own data: ";
            for (int j = 0; j < data_size; ++j) {
                std::cout << fetched_data[j] << " ";
            }
            std::cout << std::endl;
        }

        // Note: The destructor of SeapodymCourier will automatically free the MPI windows
        // when the object goes out of scope.
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}