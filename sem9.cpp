#include <iostream>
#include <vector>
#include <algorithm>

struct Edge
{
    int from;
    int to;
    int weight;
};

class DSU {
public:
    explicit DSU(size_t size) {
        parent.resize(size, 0);
        rank.resize(size, 1);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }
    ~DSU() = default;

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_set(int v, int u) {
        int v_set = find_set(v);
        int u_set = find_set(u);

        int rank_v_set = rank[v_set];
        int rank_u_set = rank[u_set];

        if (rank_v_set > rank_u_set) {
            parent[u_set] = v_set;
            rank[v_set] += rank[u_set];
        } else {
            parent[v_set] = u_set;
            rank[u_set] += rank[v_set];
        }
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};


void kruskal(std::vector<Edge>& edges, int vertices_count, void (*callback)(const Edge& edge)) {
    std::sort(edges.begin(), edges.end(), [](const Edge& l, const Edge& r) {
        return l.weight < r.weight;
    });

    DSU dsu(vertices_count);
    for (auto& e : edges) {
        int from_set = dsu.find_set(e.from);
        int to_set = dsu.find_set(e.to);

        if (from_set != to_set) {
            dsu.union_set(from_set, to_set);
            callback(e);
        }
    }
}


int main() {
    std::vector <Edge> edges = {
        { 2, 3, 3 },
        { 1, 6, 4 },
        { 5, 7, 5 },
        { 6, 8, 5 },
        { 7, 8, 5 },
        { 2, 4, 1 },
        { 3, 4, 1 },
        { 1, 3, 2 },
        { 0, 3, 6 },
        { 4, 7, 6 },
        { 3, 6, 7 },
        { 0, 1, 9 },
        { 3, 5, 9 },
        { 5, 6, 1 },
        { 5, 8, 1 },
        { 0, 2, 2 }
    };
    kruskal(edges, 9, [](const Edge& e) {
        std::cout << "[" << e.from << ", " << e.to << "]=" << e.weight << std::endl;
    });
    std::cout << "OK" << std::endl;
    return 0;
}
