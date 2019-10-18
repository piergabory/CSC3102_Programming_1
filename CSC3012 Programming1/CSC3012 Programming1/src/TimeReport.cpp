//
//  TimeReport.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory and Wasim Alam on 17/10/2019.
//   
//

#include "TimeReport.hpp"

namespace CSC3012_P1 {

void TimeReport::startRecording(std::string name) {
    stopwatch.startTimer();
    running = name;
}

void TimeReport::stopRecording() {
    stopwatch.stopTimer();
    results.push_back(Result(stopwatch.getElapsedTime(), running));
    stopwatch.refreshTimer();
}

std::string TimeReport::report() {
    if (results.empty()) return "";
    std::string report = "";
    double min = results[0].time;
    double max = results[0].time;
    for(Result result: results) {
        min = min < result.time ? min : result.time;
        max = max > result.time ? max : result.time;
    }
    
    report += "Report -------------------------\n";
    const double chart_length = 64;
    for(Result result: results) {
        int bar = chart_length * (result.time - min) / (max - min);
        report += result.name + " :\t" + std::to_string((int)result.time);
        report += " \t| " + std::string(bar + 1, '+') + "\n";
    }
    results.clear();
    return report;
}

}
