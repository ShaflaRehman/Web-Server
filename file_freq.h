#pragma once
#ifndef  FILE_FREQ
#define FILE_FREQ
#include<fstream>
using namespace std;

class file_freq
{
public:
	int freq;
	string filename;
	file_freq();
	file_freq(string f, int fr);
	file_freq(const file_freq& a);






};


#endif
