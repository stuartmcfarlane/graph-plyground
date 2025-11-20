#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> readFileLines(const string filename)
{
    vector<string> lines;
    fstream file;

    file.open(filename, ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

vector<string> parseCommaSeparated(const string str)
{
    vector<string> v;

    stringstream ss(str);

    while (ss.good())
    {
        string substr;
        getline(ss, substr, ' ');
        v.push_back(substr);
    }
    return v;
}

vector<int> toInts(vector<string> ss)
{
    vector<int> is;
    for (auto it = ss.begin(); it != ss.end(); it++)
    {
        is.push_back(stoi(*it));
    }
    return is;
}