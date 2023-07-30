#include "Stats.h"

void InitStats(Stats& stats)
{
	stats.dataLength = 0;
	stats.steps = 0;
	stats.memory = 0;
}

void WriteStatsCSV(const std::string& filename, const Stats* stats, int numStats)
{
	std::ofstream file(filename);
	if (file.is_open())
	{
		file << "DataLength;Steps;Memory;" << std::endl;

		for (int i = 0; i < numStats; ++i)
		{
			file << stats[i].dataLength << ";";
			file << stats[i].steps << ";";
			file << stats[i].memory << ";";
			file << std::endl;
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file " << filename << std::endl;
	}
}

void PrintStats(const Stats& stats)
{
	std::cout << "Data length: " << stats.dataLength << std::endl;
	std::cout << "Steps: " << stats.steps << std::endl;
	std::cout << "Memory: " << stats.memory << std::endl;
}
