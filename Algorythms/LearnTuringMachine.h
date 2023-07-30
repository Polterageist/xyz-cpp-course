#pragma once
#include <string>
#include "Stats.h"

void LearnHelloWorldWithTuringMachine();

std::string InvertStringWithTuringMachine(const std::string& input, Stats& stats);
// Equivalent in C++
std::string InvertStringWithCpp(const std::string& input, Stats& stats);
// Faster version in C++, but with more states
std::string InvertStringWithCppFast(const std::string& input, Stats& stats);

void LearnNontrivialTuringMachine();
void LearnTuringMachine();
