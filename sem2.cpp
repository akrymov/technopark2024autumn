#include <iostream>
#include <vector>
#include <string>



template<typename T>
struct DefaultComparator {
    bool operator()(const T& l, const T& r) const {
        return l < r;
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class Heap {
public:
    Heap(Comparator comp=Comparator());
    Heap(const Heap&)=delete;
    Heap(const Heap&&)=delete;

    Heap &operator=(const Heap &) = delete;
    Heap &operator=(Heap &&) = delete;

    ~Heap();

    const T& top() const;
    void pop();
    void push(const T&);

    size_t size() const;

// POD - plain old datatype
private:
    void sift_up();
    void sift_down();

    T* buffer;
    size_t size;
    size_t count;

    Comparator comp;
};

template <typename T, typename Comparator = DefaultComparator<T>>
void sort(T *arr, size_t size, Comparator comp = Comparator()) {
    int l = 0;
    int r = size;
    for (size_t i = l; i < r; ++i) {
        for (size_t j = l; j < r - 1; ++j ) {
            if (comp(arr[j + 1], arr[j])) {
                std::swap(arr[j + 1], arr[j]);
            }
        }
    }
}

bool int_less(const int &l, const int &r) {
    return l < r;
}
bool int_greater(const int &l, const int &r) {
    return !int_less(l, r);
}

bool ___dsoifhiksdhfviosdhvcjldfsjlvcdsbjhcbsdlkn(const int &l, const int &r) {
    return l < r;
}

struct Point {
    int x;
    int y;

    bool operator<(const Point& r) const {
        return this->x < r.x;
    }
};

// bool operator<(const Point& l, const Point& r) {
//     return l.x < r.x;
// }

//Point p1,p2;
//p1 < p2 -> p1.operator<(p2)

struct PointComparator {
    Point base_point;
    PointComparator(const Point& b) : base_point(b) {
    }

    bool operator()(const Point& l, Point& r) const {
        return base_point.x - l.x < base_point.x - r.x;
    }
};

struct TS {
    int x;
    TS() : x(0) {
        std::cout << "ctr" << std::endl;
    }
    TS(const TS&)=delete;
    ~TS() {
        std::cout << "~" << std::endl;
    }
};

int main() {

    TS t1;
    //TS t2 = t1;
    std::vector<int> v = {434,2,-1,0,333,1,23};
    int t = 0;
    sort(&v[0], v.size(), int_greater);
    sort(&v[0], v.size(), [&t](const int &l, const int &r) {
        t = 1;
        return l < r;
    });

    for (auto &i : v) {
        std::cout << i << " " << std::endl;
    }

    std::vector<std::string> s_vec = {"dfsdf", "asdasd", "123"};
    sort(&s_vec[0], s_vec.size());
    std::cout << "----" << std::endl;
    for (auto &i : s_vec) {
        std::cout << i << " " << std::endl;
    }


    std::vector<Point> p_vec = {{0,0}, {-1,1}, {1,1}};
    //PointComparator p_comp({0, 0});
    sort(&p_vec[0], p_vec.size());
}
