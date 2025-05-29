#include <mpi.h>
#include <set>
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
     * @brief Get the pointer to the exposed data
     * @return Pointer to the exposed data
     */
    double* getDataPtr() const { return this->data;}

    /**
     * @brief Expose the memory to other processes
     * @param data Pointer to the data to be exposed
     * @param data_size Number of elements in the data array
     */
    void expose(double* data, int data_size);

    /**
     * @brief Fetch data from a remote process and store it in the local data array
     * @param target_worker Rank of the target process from which to fetch data
     */
    void fetch(int target_worker);

    /**
     * @brief Accumulate/sum the data from multiple source workers into a target worker's local data array
     * @param source_workers Set of ranks of source processes from which to fetch data
     * @param target_worker Rank of the target process from which to fetch data
     */
    void accumulate(const std::set<int>& source_workers, int target_worker); 

    SeapodymCourier(const SeapodymCourier&) = delete; // Disable copy constructor
    SeapodymCourier& operator=(const SeapodymCourier&) = delete; // Disable assignment operator
    SeapodymCourier(SeapodymCourier&& other) noexcept; // Move constructor
    SeapodymCourier& operator=(SeapodymCourier&& other) noexcept; // Move assignment operator
};

#endif // SEAPODYM_COURIER