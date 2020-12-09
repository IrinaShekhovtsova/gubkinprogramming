#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <unordered_map>
#include <stack>

class Network
{
public:
	bool Active;
	Network();
	std::vector<std::vector<int>> AdjencyMatrix(std::unordered_map <int, Pipeline> pipes, std::vector<int>& Station_Connection);
	void ViewNetwork(const std::vector <std::vector <int>>& g, const std::vector<int>& Station_Connection);
	bool cycle_exists(int start, std::vector <std::vector <int>> g, std::vector <int>& visit);
	void dfs(int start, std::vector <std::vector <int>> g, std::vector <bool>& visited, std::stack <int>& stack);
	void topological_sort(unsigned int n, std::vector <std::vector <int>> g, const std::vector<int>& Station_Connection);
};

