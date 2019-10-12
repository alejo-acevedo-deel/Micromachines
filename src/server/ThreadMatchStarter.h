#ifndef MICROMACHINES_THREADMATCHSTARTER_H
#define MICROMACHINES_THREADMATCHSTARTER_H

#include <atomic>
#include "Thread.h"
#include "ThreadMatch.h"
#include "ProtectedMap.h"

class ThreadMatchStarter : public Thread {
    ProtectedMap& matches;
    std::list<ThreadMatch*>& running_matches;
    std::atomic<bool> server_running{};

    private:
        void run();

        void close_ended_matches();

    public:
        ThreadMatchStarter(ProtectedMap& matches, std::list<ThreadMatch*>& running_matches);



};

#endif //MICROMACHINES_THREADMATCHSTARTER_H