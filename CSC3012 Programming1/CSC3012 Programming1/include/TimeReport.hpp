//
//  TimeReport.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory and Wasim Alam on 17/10/2019.
//   
//

#ifndef TimeReport_hpp
#define TimeReport_hpp

#include <vector>
#include <string>

namespace CSC3012_P1 {

#include "timer.hpp"

class TimeReport {
    struct Result {
        double time;
        std::string name;

        Result(double time, std::string name) : time(time), name(name) {}
    };

    std::string running;
    CStopWatch stopwatch;
    std::vector<Result> results;

public:
    void startRecording(std::string name);
    void stopRecording();
    std::string report();
};

}

#endif /* TimeReport_hpp */
