//
//  TimeReport.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 17/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef TimeReport_hpp
#define TimeReport_hpp

#include <vector>

#include "timer.hpp"
#include "Instructions.hpp"


class TimeReport {
    struct Result {
        double time;
        std::string name;

        Result(double time, std::string name) : time(time), name(name) {}
    };

    std::string running = "";
    CStopWatch stopwatch;
    std::vector<Result> results;

public:
    void startRecording(std::string name) {
        stopwatch.startTimer();
        running = name;
    }

    void stopRecording() {
        stopwatch.stopTimer();
        results.emplace_back(stopwatch.getElapsedTime(), running);
        stopwatch.refreshTimer();
    }

    std::string report() {
        if (results.empty()) return "";
        std::string report = "";
        double min = results[0].time;
        double max = results[0].time;
        for(Result result: results) {
            min = min < result.time ? min : result.time;
            max = max > result.time ? max : result.time;
        }

        report += "Report -------------------------\n";
        const double chart_length = 16;
        for(Result result: results) {
            int bar = chart_length * (result.time - min) / (max - min);
            report += result.name + " :\t" + std::to_string(result.time);
            report += " \t| " + std::string(bar + 1, '#') + "\n";
        }
        results.clear();
        return report;
    }
};

#endif /* TimeReport_hpp */
