#include "chart_to_json.h"

Chart_To_JSON::Chart_To_JSON()
{
}

void Chart_To_JSON::saveJSON(std::vector<float> timings)
{
	nlohmann::json jsonfile;

	for(auto itr = timings.begin(); itr<timings.end(); ++itr)
		jsonfile["test"] += *itr;

	std::ofstream file("../timingChart.json");
	file << jsonfile;
}

std::vector<float> Chart_To_JSON::loadJSON()
{	
	std::vector<float> timings;
	std::ifstream fileStream("../timingChart.json");
	nlohmann::json jTimings = nlohmann::json::parse(fileStream);

	timings.push_back(jTimings["test"]);
	return timings;
}

