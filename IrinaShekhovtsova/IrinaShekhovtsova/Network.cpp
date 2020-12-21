#include "Pipeline.h"
#include "utils.h"
#include "Network.h"
#include <queue>
#include <stdlib.h>

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
    for (unsigned int i = 0; i < Graph_Pipes.size(); i++) //auto
    {
        int ID_in = pipes[*it1].in;
        int ID_out = pipes[*it1].out;
        int ind_in = SelectbyID(Station_Connection, ID_in);
        int ind_out = SelectbyID(Station_Connection, ID_out);
        graph[ind_in][ind_out] = pipes[*it1].GetWeight();
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

bool Network::cycle_exists(int start, const std::vector <std::vector <int>>& g, std::vector <int>& visit)
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
void Network::dfs(int start, const std::vector <std::vector <int>>& g, std::vector <bool>& visited, std::stack <int>& stack)
{
    visited[start] = true;
    for (unsigned int j = 0; j < g[start].size(); j++)
        if (g[start][j] != 0 && !visited[j])
            dfs(j, g, visited, stack);
    stack.push(start);
}
void Network::topological_sort(unsigned int n, const std::vector <std::vector <int>>& g, const std::vector<int>& Station_Connection)
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

void Network::Floyd(int start, int finish, const std::vector<std::vector<int>>& g, const std::vector<int>& Station_Connection)
{
    int INF = 10e9;
    std::vector <std::vector <int>> f(Station_Connection.size(), std::vector <int>(Station_Connection.size()));
    std::vector <std::vector <int>> prev(Station_Connection.size(), std::vector <int>(Station_Connection.size()));
    for (size_t i = 0; i < Station_Connection.size(); i++)
        for (size_t j = 0; j < Station_Connection.size(); j++) {
            if (g[i][j] != 0) {
                f[i][j] = g[i][j];
                if (f[i][j] < INF) prev[i][j] = i;
            }
            else {
                f[i][j] = INF; //если труба в ремонте?
                prev[i][j] = -1;
            }
        }
    for (size_t k = 0; k < Station_Connection.size(); k++)
        for (size_t i = 0; i < Station_Connection.size(); i++)
            for (size_t j = 0; j < Station_Connection.size(); j++)
                if (f[i][k] < INF && f[k][j] < INF && f[i][k] + f[k][j] < f[i][j])
                {
                    f[i][j] = f[i][k] + f[k][j];
                    prev[i][j] = prev[k][j];
                }
    std::vector <int> path;
    int vertex_start = SelectbyID(Station_Connection, start);
    int vertex_finish = SelectbyID(Station_Connection, finish);
    int curr = vertex_finish;
    bool path_found = false;
    while (curr != -1)
    {
        path.push_back(curr);
        if (curr == vertex_start) path_found = true;
        curr = prev[vertex_start][curr];
    }
    reverse(path.begin(), path.end());
    if (path_found) {
        for (auto vertex : path)
            std::cout << Station_Connection[vertex] << " ";
        std::cout << std::endl;
    }
    else std::cout << "There is no route" << std::endl;
}

std::vector<std::vector<int>> Network::AdjencyList(std::unordered_map <int, Pipeline> pipes, std::vector<int>& Station_Connection)
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
    //for (unsigned int i = 0; i < Graph_Stations.size(); i++)
    for(auto elem: Graph_Stations)
    {
        Station_Connection.push_back(*it2);
        it2++;
    }
    std::vector <std::vector <int>> adj_list(Station_Connection.size(), std::vector <int>(Station_Connection.size()));
    //for (unsigned int i = 0; i < Graph_Pipes.size(); i++) //auto
    for(auto elem: Graph_Pipes)
    {
        int ID_in = pipes[*it1].in;
        int ID_out = pipes[*it1].out;
        int ind_in = SelectbyID(Station_Connection, ID_in);
        int ind_out = SelectbyID(Station_Connection, ID_out);
        adj_list[ind_in].push_back(ind_out);
        adj_list[ind_out].push_back(ind_in);
        it1++;
    }
    return adj_list;
}

std::vector<std::vector<int>> Network::PerformanceMatrix(std::unordered_map <int, Pipeline> pipes, std::vector<int>& Station_Connection)
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
    for(auto elem : Graph_Stations)
    {
        Station_Connection.push_back(*it2);
        it2++;
    }
    std::vector <std::vector <int>> perf_graph(Station_Connection.size(), std::vector <int>(Station_Connection.size()));
    for(auto elem : Graph_Pipes)
    {
        int ID_in = pipes[*it1].in;
        int ID_out = pipes[*it1].out;
        int ind_in = SelectbyID(Station_Connection, ID_in);
        int ind_out = SelectbyID(Station_Connection, ID_out);
        perf_graph[ind_in][ind_out] = pipes[*it1].GetPerformance();
        it1++;
    }
    return perf_graph;
}

int Network::bfs(int start, int finish, std::vector<int>& prev, const std::vector<std::vector<int>>& g, const std::vector<std::vector<int>>& capacity)
{
    const int INF = 10e9;
    for (auto& elem : prev)
        elem = -1;
    prev[start] = -2;
    std::queue<std::pair<int, int>> q;
    q.push({ start,INF });

    while (!q.empty()) {
        int curr = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int vertex : g[curr]) {
            if (prev[vertex] == -1 && capacity[curr][vertex]) {
                prev[vertex] = curr;
                int new_flow = std::min(flow, capacity[curr][vertex]);
                if (vertex == finish)
                    return new_flow;
                q.push({ vertex,new_flow });
            }
        }
    }

    return 0;
}

// prying about flow: https://cp-algorithms.com/graph/edmonds_karp.html 

int Network::MaxFlow(int start, int finish, const std::vector<std::vector<int>>& g, std::vector<std::vector<int>> capacity, const std::vector<int>& Station_Connection)
{
    int flow = 0;
    int start_ind = SelectbyID(Station_Connection, start);
    int finish_ind = SelectbyID(Station_Connection, finish);
    std::vector<int>prev(Station_Connection.size());
    
    while (int new_flow = bfs(start_ind, finish_ind, prev, g,capacity)) {
        flow += new_flow;
        int curr = finish_ind;
        while (curr != start_ind) {
            int vert = prev[curr];
            capacity[vert][curr] -= new_flow;
            capacity[curr][vert] += new_flow;
            curr = vert;
        }
    }
    return flow;

}
