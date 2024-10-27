// Get memory usage statistics for the current process
// From https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace memUsage
{

inline int parseLine(char* line) {
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

inline int getMemUsageKB() { // Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

template<typename T>
void dumpVectorToFile(const std::vector<T>& vec, const std::string& filename) {
    std::ofstream outFile(filename);  // Open the file for writing

    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const T& value: vec) {
        outFile << value << "\n";  // Write each element to the file, followed by a newline
    }

    outFile.close();  // Close the file
    std::cout << "Vector dumped to " << filename << std::endl;
}

};
