#ifndef SEARCH_H
#define SEARCH_H
#include<string>
#include<map>
#include <fstream>
#include<queue>
#include<list>
#include<algorithm>
#include "file_freq.h"
#include <sstream>
#include <utility>
#include "stopwords.h"
#include "Global_variables.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include "gnode.h"
using namespace std;
const int max_size = 45;



class Search
{

    map<std::string, map<std::string, int>> my_map;
    ifstream myfile[max_size];
    string array[max_size];
    std::vector<std::string> split_words(const std::string& phrase);
    stopwords st;
    



public:
    Search();
    void search(std::string w);
    int frequency(string w, ifstream& f);
   void arrange_files(string& w);
   void SearchHistory(string w);
   // void hyperlink_graph(string a , string b);


};
#endif


Search::Search()
{
    array[0] = "Artificial_Intelligence.txt";
    array[1] = "Artificial_Reality.txt";
    array[2] = "Virtual_Reality.txt";
    array[3] = "Biotechnology.txt";
    array[4] = "Blockchain.txt";
    array[5] = "Climate Change.txt";
    array[6] = "Cloud Computing.txt";
    array[7] = "Crypto Currency.txt";
    array[8] = "Cyber Security.txt";
    array[9] = "Digital Marketing.txt";
    array[10] = "Fitness.txt";
    array[11] = "Machine Learning.txt";
    array[12] = "Mars Exploration.txt";
    array[13] = "Mental Health.txt";
    array[14] = "Nutrition.txt";
    array[15] = "Pages.txt";
    array[16] = "Plastic Pollution.txt";
    array[17] = "Quantum Computing.txt";
    array[18] = "Smart Cities.txt";
    array[19] = "Text.txt";
    array[20] = "Software Development.txt";
    array[21] = "App Development.txt";
    array[22] = "IoT.txt";
    array[23] = "Financial Technology.txt";
    array[24] = "Financial Health.txt";
    array[25] = "Agriculture.txt";
    array[26] = "Global Warming.txt";
    array[27] = "Renewable Energy.txt";
    array[28] = "Marine Biology.txt";
    array[29] = "Oceanography.txt";
    array[30] = "Velocity.txt";
    array[31] = "Speed.txt";
  array[32] = "Astronomy.txt";
    array[33] = "Robotics.txt";
    array[34] = "E-Commerce.txt";
    array[35] = "Finance Management.txt";
    array[36] = "Stock Exchange.txt";
    array[37] = "Social Media Trends.txt";
    array[38] = "Cultural Heritage.txt";
    array[39] = "Literature.txt";
    array[40] = "Art and Music.txt";
    array[41] = "Literature.txt";
    array[42] = "Human Psychology.txt";
    array[43] = "Socialogy.txt";
    array[44] = "Political Science.txt";





    for (int i = 0; i < max_size; ++i) {
        myfile[i].open(array[i]);
        if (!myfile[i]) {
            //cerr << "Unable to open file: " << array[i] << endl;
        }
    }

    
}

void Search::search(std::string w) {
    std::transform(w.begin(), w.end(), w.begin(), ::tolower);
    std::vector<std::string> words = split_words(w);
    string result;
    string w1 = "";
    for (auto word : words)
    {

        w1 += word;
    }
    if (my_map.find(w1) != my_map.end()) {
       // std::cout << "The word \"" << w << "\" has already been searched." << std::endl;


    }
    else
    {
        std::string substring = "and";

        // Use std::find_if to find the first occurrence of the substring
        auto it = std::find_if(words.begin(), words.end(), [&substring](const std::string& str) {
            return str==substring;
            });



        if (it == words.end())
        {

            for (int count = 0; count < max_size; ++count) {
                if (!myfile[count].is_open()) {
                   // std::cerr << "File " << count << " is not open!" << std::endl;
                    continue;
                }

                int sum = 0; // Reset sum for each file
                for (const auto& word : words) {
                    //std::cout << word << "    ";
                    int a = frequency(word, myfile[count]);
                    //  std::cout << "a : " << a << std::endl;
                    sum += a;
                    // std::cout << "sum : " << sum << std::endl;
                }

               
                my_map[w1][array[count]] = sum;
            }

        }

        else
        {

            for (int count = 0; count < max_size; ++count) {
                if (!myfile[count].is_open()) {
                   // std::cerr << "File " << count << " is not open!" << std::endl;
                    continue;
                }

                int sum = 0; // Reset sum for each file
                int check = 0;
                for (const auto& word : words) {
                    // std::cout << word << "    ";

                    if (word != "and")
                    {
                        int a = frequency(word, myfile[count]);
                        if (a == 0)
                        {
                            check = 1;
                            break;
                        }
                        sum += a;

                    }
                    // std::cout << "sum : " << sum << std::endl;
                }

                // Assuming array[count] gives a relevant identifier for the file
                if (check == 1)
                {
                    my_map[w1][array[count]] = 0;
                }
                else
                {
                    my_map[w1][array[count]] = sum;
                }
            }







        }

    }

   
    arrange_files(w1);
    
     /*for (auto link : links)
    {
        if (link.freq > 0)
        {
            cout << link.filename;
            cout << endl;
        }
    }*/
    
    //return links;


}




int Search::frequency(const std::string w, std::ifstream& file) {
    int count = 0;
    std::string word;


   
    file.clear();
    file.seekg(0, std::ios::beg);

    while (file >> word) {
        if (word == w) {
            ++count;
        }
    }
    file.clear();
    return count;





}

void Search::arrange_files(string& w)
{

    //vector<file_freq> links;
    links.clear();
    auto it = my_map.find(w);
    int count = 0;
    while (count != max_size)
    {
       // cout << "count  " << my_map[w][array[count]] << endl;
        file_freq node(array[count], my_map[w][array[count]]);
        ++count;
        links.push_back(node);
    }
    auto compareFreq = [](file_freq& a, file_freq& b)
        {
            return a.freq > b.freq;
        };

    sort(links.begin(), links.end(), compareFreq);

    //return links;

}




std::vector<std::string> Search::split_words(const std::string& phrase) {
    std::istringstream iss(phrase);
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) {

        if (st.Find(word) == 1)
        {
            // cout << word << endl; 
            words.push_back(word);
        }

    }

    return words;
}


inline void Search::SearchHistory(string w)
{



    auto now = std::chrono::system_clock::now();

    // Convert the time point to a time_t, which represents the system time in seconds since epoch
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t to a tm struct for local time using localtime_s
    std::tm now_tm;
    localtime_s(&now_tm, &now_time_t); // Use localtime_s for thread safety

    // Print the date and time in a readable format manually

    cout << (now_tm.tm_year + 1900) << '-'
        << std::setw(2) << std::setfill('0') << (now_tm.tm_mon + 1) << '-'
        << std::setw(2) << std::setfill('0') << now_tm.tm_mday << ' '
        << std::setw(2) << std::setfill('0') << now_tm.tm_hour << ':'
        << std::setw(2) << std::setfill('0') << now_tm.tm_min << ':'
        << std::setw(2) << std::setfill('0') << now_tm.tm_sec << "   " << w
        << '\n';

    std::ofstream history_file("History.txt");
    if (history_file.is_open()) {
        // Write the formatted string to the file
        history_file << (now_tm.tm_year + 1900) << '-'
            << std::setw(2) << std::setfill('0') << (now_tm.tm_mon + 1) << '-'
            << std::setw(2) << std::setfill('0') << now_tm.tm_mday << ' '
            << std::setw(2) << std::setfill('0') << now_tm.tm_hour << ':'
            << std::setw(2) << std::setfill('0') << now_tm.tm_min << ':'
            << std::setw(2) << std::setfill('0') << now_tm.tm_sec << "   " << w
            << '\n';
        // Close the file
        history_file.close();
    }
    else {
        std::cerr << "Unable to open file for writing.\n";
    }

}