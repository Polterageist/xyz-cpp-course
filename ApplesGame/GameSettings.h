#pragma once
#include <string>

namespace ApplesGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";

	// Game settings constants
	const float PLAYER_SIZE = 20.f;
	const float APPLE_SIZE = 20.f;
	const float INITIAL_SPEED = 100.f;
	const float ACCELERATION = 10.f; // For each eaten apple player speed will be increased by this value
	const int MIN_APPLES = 20;
	const int MAX_APPLES = 40;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEGHT = 600;
	const int MAX_RECORDS_TABLE_SIZE = 5;
}
