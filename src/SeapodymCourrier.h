
#include <mpi.h>
#include <map>


using Tuple3 = std::tuple<MPI_Win, double*, std::size_t>;

/**
 * @brief SeapodymCourrier class for managing memory exposure and data fetching between MPI processes
 * 
 * This class allows workers to expose their memory to other processes and fetch data from them.
 * It uses MPI windows for memory exposure and communication.
 */
class SeapodymCourrier {
    
    private:
    
        MPI_Comm comm;

        std::map<int, Tuple3> workerData; // Maps worker ID to its exposed memory

    public:

    /**
     * @brief Constructor
     * @param comm MPI communicator to use for communication
     */
    SeapodymCourrier(MPI_Comm comm=MPI_COMM_WORLD);

    /**
     * @brief Destructor
     */
    ~SeapodymCourrier();

    /**
     * @brief Expose the memory to other processes
     * @param workerId Unique identifier for the worker
     * @param data Pointer to the data to be exposed
     * @param count Number of elements in the data array
     */
    void expose(int workerId, double* data, int count);

    /**
     * @brief Fetch data from a remote process
     * @param data Pointer to the buffer where data will be stored
     * @param target_rank Rank of the target process from which to fetch data
     */
    void fetch(double* data, int target_rank);

    SeapodymCourrier(const SeapodymCourrier&) = delete; // Disable copy constructor
    SeapodymCourrier& operator=(const SeapodymCourrier&) = delete; // Disable assignment operator
    SeapodymCourrier(SeapodymCourrier&& other) noexcept; // Move constructor
    SeapodymCourrier& operator=(SeapodymCourrier&& other) noexcept; // Move assignment operator
};
