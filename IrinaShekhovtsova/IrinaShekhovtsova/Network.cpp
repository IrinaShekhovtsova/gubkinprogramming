#include "Pipeline.h"
#include "utils.h"
#include "Network.h"

Network::Network()
{
    Active = false;
}

std::vector<std::vector<int>> Network::AdjencyMatrix(std::unordered_map <int,Pipeline> pipes, std::vector<int>& Station_Connection)
{
    std::set <int> Graph_Pipes;
    std::set <int> Graph_Stations;
    for (const auto& pair : pipes)
        if (pair.second.in != -1 && pair.second.out != -1)
        {
            Graph_Pipes.insert(pair.first);
            Graph_Stations.insert(pair.second.in);
            Graph_Stations.insert(pair.second.out);
        }
    std::set <int> ::iterator it1 = Graph_Pipes.begin();
    std::set <int> ::iterator it2 = Graph_Stations.begin();
    for (unsigned int i = 0; i < Graph_Stations.size(); i++)
    {
        Station_Connection.push_back(*it2);
        it2++;
    }
    std::vector <std::vector <int>> graph(Station_Connection.size(), std::vector <int>(Station_Connection.size()));
    for (unsigned int i = 0; i < Graph_Pipes.size(); i++)
    {
        int ID_in = pipes[*it1].in;
        int ID_out = pipes[*it1].out;
        int ind_in = SelectbyID(Station_Connection, ID_in);
        int ind_out = SelectbyID(Station_Connection, ID_out);
        graph[ind_in][ind_out] = 1;
        it1++;
    }
    return graph;
}

void Network::ViewNetwork(const std::vector<std::vector<int>>& graph, const std::vector<int>& Station_Connection)
{
    std::cout << std::setw(10) << "*";
    for (unsigned int i = 0; i < Station_Connection.size(); i++)
        std::cout << std::setw(10) << Station_Connection[i];
    std::cout << std::endl;
    for (unsigned int i = 0; i < Station_Connection.size(); i++)
    {
        std::cout << std::setw(10) << Station_Connection[i];
        for (unsigned int j = 0; j < Station_Connection.size(); j++)
            std::cout << std::setw(10) << graph[i][j];
        std::cout << std::endl;
    }
}

bool Network::cycle_exists(int start, std::vector <std::vector <int>> g, std::vector <int>& visit)
{
    visit[start] = 1; // 1 - не вышли из вершины
    for (unsigned int j = 0; j < g[start].size(); j++) 
        if (g[start][j] != 0) {
            if (visit[j] == 0) {
                if (cycle_exists(j, g, visit)) return true;
            }
            else if (visit[j] == 1)
                return true;
        }
        visit[start] = 2; // 2 - вышли из вершины
    return false;
}
void Network::dfs(int start, std::vector <std::vector <int>> g, std::vector <bool>& visited, std::stack <int>& stack)
{
    visited[start] = true;
    for (unsigned int j = 0; j < g[start].size(); j++)
        if (g[start][j] != 0 && !visited[j])
            dfs(j, g, visited, stack);
    stack.push(start);
}
void Network::topological_sort(unsigned int n, std::vector <std::vector <int>> g, const std::vector<int>& Station_Connection)
{
    std::vector <int> visit(n, 0);
    for (int i = 0; i < n; i++)
        if (cycle_exists(i, g, visit)) {
            std::cout << "There is a cycle in the network" << std::endl;
            return;
        }
        else {
            std::stack <int> sort;
            std::vector <bool> visited(n, false);
            for (int i = 0; i < n; i++)
                if (!visited[i])
                    dfs(i, g, visited, sort);
            while (sort.empty() == false)
            {
                std::cout << Station_Connection[sort.top()] << " ";
                sort.pop();
            }
            std::cout << std::endl;
            return;
        }
}
