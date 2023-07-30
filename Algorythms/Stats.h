#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>

struct Stats
{
	int dataLength = 0;
	int steps = 0;
	int memory = 0;
};

void InitStats(Stats& stats);
void WriteStatsCSV(const std::string& filename, const Stats* stats, int numStats);
void PrintStats(const Stats& stats);

template<int N>
struct MultiStats
{
	std::string statNames[N];
	std::vector<std::array<Stats, N>> stats;
};

template<int N>
void WriteMultipleStatsCSV(const std::string& filename, const MultiStats<N>& multiStats)
{
	std::ofstream file(filename);
	if (file.is_open())
	{
		file << "DataLength;";
		for (const std::string& statName : multiStats.statNames)
		{
			file << statName << " steps" << ";";
			file << statName << " memory" << ";";
		}
		file << std::endl;

		for (const auto& stat : multiStats.stats)
		{
			file << stat[0].dataLength << ";";
			for (int i = 0; i < N; ++i)
			{
				file << stat[i].steps << ";";
				file << stat[i].memory << ";";
			}
			file << std::endl;
		}

		file.close();
	}
	else
	{
		std::cout << "Unable to open file " << filename << std::endl;
	}
}
