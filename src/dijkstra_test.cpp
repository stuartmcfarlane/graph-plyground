#include <iostream>
#include <string>
#include <vector>

#include "utils.h"

using namespace std;

void dijkstra(vector<string> input)
{
    cout << "do dijkstra on input";
}
void dijkstra_test()
{
    vector<string> input = readFileLines("data/day01.txt");
    dijkstra(input);
}
