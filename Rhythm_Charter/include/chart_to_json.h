#ifndef CHART_TO_JSON_H
#define CHART_TO_JSON_H

#include <iostream>
#include <fstream>
#include "../../include/json.h"

using json = nlohmann::json;
using jsonf = nlohmann::json;
class Chart_To_JSON
{
private:
    /* data */
public:
    Chart_To_JSON();

    void saveJSON(std::string filePath, std::vector<float> timings);
    void loadJSON(std::string filePath);
};

#endif