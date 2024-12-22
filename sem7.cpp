#include <iostream>
#include <queue>
#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    explicit ListGraph(int vertices_count) {
        graph.resize(vertices_count);
        prev_graph.resize(vertices_count);
    }
    ListGraph(const IGraph &); // реализовать в рамках ДЗ

    virtual ~ListGraph() {};

    void AddEdge(int from, int to) override {
        graph[from].push_back(to);
        prev_graph[to].push_back(from);
    }

    int VerticesCount() const override {
        return graph.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        return std::vector<int>(graph[vertex].begin(), graph[vertex].end());
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        return std::vector<int>(prev_graph[vertex].begin(), prev_graph[vertex].end());
        // std::vector<int> result;
        // for (int i = 0; i < graph.size(); ++i) {
        //     for (int j = 0; j < graph[i].size(); ++j) {
        //         if (graph[i][j] == vertex) {
        //             result.push_back(i);
        //         }
        //     }
        // }
        // return result;
    }

private:
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>> prev_graph;
};

void dfs_aux(const IGraph &graph, std::vector<bool> &visited, int vertex, void (*callback)(int v)) {
    visited[vertex] = true;
    callback(vertex);
    for (int child_vertex : graph.GetNextVertices(vertex)) {
        if (!visited[child_vertex]) {
            dfs_aux(graph, visited, child_vertex, callback);
        }
    }
}

void dfs(const IGraph &graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            dfs_aux(graph, visited, i, callback);
        }
    }
}

void bfs_aux(const IGraph &graph, std::vector<bool> &visited, int vertex, void (*callback)(int v)) {
    std::queue<int> q;
    visited[vertex] = true;

    q.push(vertex);
    while (!q.empty()) {
        int current_vertex = q.front();
        q.pop();
        callback(current_vertex);
        for (int child_vertex : graph.GetNextVertices(current_vertex)) {
            if (!visited[child_vertex]) {
                visited[child_vertex] = true;
                bfs_aux(graph, visited, child_vertex, callback);
            }
        }
    }
}

void bfs(const IGraph &graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            bfs_aux(graph, visited, i, callback);
        }
    }
}

int main() {
    ListGraph graph(5);
    graph.AddEdge(0, 2);
    graph.AddEdge(2, 1);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 4);
    graph.AddEdge(2, 4);

    std::cout << "======= DFS =======" << std::endl;
    dfs(graph, [](int v) {
        std::cout << "v: " << v << std::endl;
    });

    std::cout << "======= BFS =======" << std::endl;
    bfs(graph, [](int v) {
        std::cout << "v: " << v << std::endl;
    });
    std::cout << "OK" << std::endl;
}
