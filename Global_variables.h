#pragma once

#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES
#include <stack>

#include <vector>
#include "file_freq.h"
extern stack<string>backStack;


extern std::vector<file_freq> links;
extern std::vector<string> files_displayed;
extern int count_global;
extern string to_search;

#endif