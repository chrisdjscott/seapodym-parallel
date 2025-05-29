#include <mpi.h>
#ifndef SEAPODYM_COURIER
#define SEAPODYM_COURIER


using Tuple3 = std::tuple<MPI_Win, double*, std::size_t>;

/**
 * @brief SeapodymCourier class for managing memory exposure and data fetching between MPI processes
 * 
 * This class allows workers to expose their memory to other processes and fetch data from them.
 * It uses MPI windows for memory exposure and communication.
 */
class SeapodymCourier {
    
    private:
    
        MPI_Comm comm;
        double *data; // Pointer to the data exposed by this worker
        int data_size; // Size of the data exposed by this worker
        MPI_Win win; // MPI window for the exposed data

    public:

    /**
     * @brief Constructor
     * @param comm MPI communicator to use for communication
     */
    SeapodymCourier(MPI_Comm comm=MPI_COMM_WORLD);

    /**
     * @brief Destructor
     */
    ~SeapodymCourier();

    /**
     * @brief Expose the memory to other processes
     * @param data Pointer to the data to be exposed
     * @param data_size Number of elements in the data array
     */
    void expose(double* data, int data_size);

    /**
     * @brief Fetch data from a remote process
     * @param data Pointer to the buffer where data will be stored
     * @param target_rank Rank of the target process from which to fetch data
     */
    void fetch(double* data, int target_rank);

    SeapodymCourier(const SeapodymCourier&) = delete; // Disable copy constructor
    SeapodymCourier& operator=(const SeapodymCourier&) = delete; // Disable assignment operator
    SeapodymCourier(SeapodymCourier&& other) noexcept; // Move constructor
    SeapodymCourier& operator=(SeapodymCourier&& other) noexcept; // Move assignment operator
};

#endif // SEAPODYM_COURIER