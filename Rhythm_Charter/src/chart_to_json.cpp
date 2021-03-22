#include "chart_to_json.h"

Chart_To_JSON::Chart_To_JSON()
{
}

void Chart_To_JSON::saveJSON(std::string filePath, std::vector<float> timings)
{
	// create an empty structure (null)
	jsonf jsonfile;

	for(auto itr = timings.begin(); itr<timings.end(); ++itr)
		jsonfile["test"] += *itr;

	std::ofstream file("../timingChart.json");
	file << jsonfile;
}

void Chart_To_JSON::loadJSON(std::string filePath)
{

}

