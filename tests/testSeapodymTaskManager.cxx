#include <iostream>
#include <SeapodymTaskManager.h>

void test1() {
    int na = 3;
    int nw = 3;
    int nt = 5;
    SeapodymTaskManager tm(na, nw, nt);

    for (auto iw = 0; iw < na; ++iw) {
        std::cout << "worker " << iw << ": "; 
        auto tasks = tm.getInitTaskIds(iw);
        for (auto tid : tasks) {
            while (tid >= 0) {
                auto nsteps = tm.getNumSteps(tid);
                for (auto i = 0; i < nsteps; ++i) {
                    std::cout << tid << " ";
                }
                tid = tm.getNextTask(tid);
            }
        }
        std:: cout << '\n';
    }
}

int main() {
    test1();
    return 0;
}