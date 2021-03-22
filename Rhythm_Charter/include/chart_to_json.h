#ifndef CHART_TO_JSON_H
#define CHART_TO_JSON_H

#include <iostream>
#include <fstream>
#include "../../include/json.h"

class Chart_To_JSON
{
private:
    /* data */
public:
    Chart_To_JSON();

    void saveJSON(std::vector<float> timings);
    std::vector<float> loadJSON();
};

#endif