#include "file_freq.h"

file_freq::file_freq()
{
}

file_freq::file_freq(string f, int fr)
{
	freq = fr;
	filename = f;


}

file_freq::file_freq(const file_freq& a)
{
	freq = a.freq;
	filename = a.filename;


}
