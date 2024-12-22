#include <iostream>

#include <array>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <assert.h>

static const size_t LINE_SIZE = 4;
static const size_t FIELD_SIZE = LINE_SIZE * LINE_SIZE;

using FieldArray = std::array<uint8_t, FIELD_SIZE>; // uint8_t a[FIELD_SIZE];

const FieldArray EMPTY_STATE = {
    0, 0, 0,0,
    0, 0, 0,0,
    0, 0, 0,0,
    0, 0, 0,0
};

const FieldArray GOAL_STATE = {
    1,2,3,4,
    5,6,7,8,
    9,10,11,12,
    13,14,15,0
};

class FieldState {
public:
    FieldState(const FieldArray &a) : zero_pos(0) {
        for (int i = 0; i < a.size(); ++i) {
            arr[i] = a[i];
            if (arr[i] == 0) {
                zero_pos = i;
            }
        }
    }

    FieldState(const FieldState &a) : arr(a.arr), zero_pos(a.zero_pos) {
    }

    std::vector<FieldState> GetNextVertices() const {
        std::vector<FieldState> result;
        if ((zero_pos + 1) % LINE_SIZE != 0) { // right
            FieldState st(*this);
            st.moveRight();
            result.push_back(st);
        }
        if (zero_pos % LINE_SIZE != 0) { // left
            FieldState st(*this);
            st.moveLeft();
            result.push_back(st);
        }
        if (zero_pos < FIELD_SIZE - LINE_SIZE) { // down
            FieldState st(*this);
            st.moveDown();
            result.push_back(st);
        }
        if (zero_pos >= LINE_SIZE) { // up
            FieldState st(*this);
            st.moveUp();
            result.push_back(st);
        }
        return result;
    }

    bool operator==(const FieldState& r) const {
        return arr == r.arr;
    }

    bool operator<(const FieldState& r) const {
        return arr < r.arr;
    }

    void print() const {
        std::cout << std::endl << "--------" << std::endl;
        for (int i = 0; i < arr.size(); ++i) {
            if (i % LINE_SIZE == 0) {
                std::cout << std::endl;
            }
            std::cout << (int)arr[i] << " ";
        }
    }

private:
    void moveDown() {
        size_t new_zero_pos = zero_pos + LINE_SIZE;
        std::swap(arr[zero_pos], arr[new_zero_pos]);
        zero_pos = new_zero_pos;
    }

    void moveUp() {
        size_t new_zero_pos = zero_pos - LINE_SIZE;
        std::swap(arr[zero_pos], arr[new_zero_pos]);
        zero_pos = new_zero_pos;
    }

    void moveLeft() {
        size_t new_zero_pos = zero_pos - 1;
        std::swap(arr[zero_pos], arr[new_zero_pos]);
        zero_pos = new_zero_pos;
    }

    void moveRight() {
        size_t new_zero_pos = zero_pos + 1;
        std::swap(arr[zero_pos], arr[new_zero_pos]);
        zero_pos = new_zero_pos;
    }

    FieldArray arr;
    size_t zero_pos;
};


void bfs(const FieldState& start) {
    FieldState goal_state(GOAL_STATE);
    FieldState empty_state(EMPTY_STATE);

    std::map<FieldState, FieldState> parents;
    std::queue<FieldState> q;

    parents.insert({start, empty_state});
    q.push(start);

    FieldState cur_state(EMPTY_STATE);
    bool found = false;
    while (!q.empty()) {
        cur_state = q.front();
        q.pop();
        if (parents.size() % 1000 == 0) {
            std::cout << "parents.size()=" << parents.size() << std::endl;
        }
        // cur_state.print();

        if (cur_state == goal_state) {
            found = true;
            break;
        }

        for (auto& child : cur_state.GetNextVertices()) {
            auto it = parents.find(child);
            if (it == parents.end()) {
                parents.insert({child, cur_state});
                q.push(child);
            }
        }
    }

    if (found) {
        int steps_count = 0;
        while (cur_state != empty_state) {
            steps_count++;
            cur_state.print();
            auto it = parents.find(cur_state);
            assert(it != parents.end());
            cur_state = it->second;
        }
        std::cout << "Solution found. steps_count=" << steps_count << std::endl;
    } else {
        std::cout << "Solution not found. vertices_count=" << parents.size() << std::endl;
    }
}

int main() {
    FieldState st({1, 0, 3, 4,
                   5, 2, 6, 8,
                   9, 10, 7, 12,
                   13, 14, 15, 11});
    bfs(st);
    std::cout << "----" << std::endl;
    return 0;
}
