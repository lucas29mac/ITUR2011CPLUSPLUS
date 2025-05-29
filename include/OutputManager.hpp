#ifndef OUTPUTMANAGER_HPP
#define OUTPUTMANAGER_HPP

#include <string>

class OutputManager {
public:
    void printResults(double Lbf, double Lb, const std::string& mecanismo);
    void saveResultsToFile(const std::string& filename, double Lbf, double Lb, const std::string& mecanismo);
};

#endif
