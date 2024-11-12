#include <algorithm>
#include <iostream>

template <typename T>
struct DefaultComparator {
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
int partition(T *arr, int l, int r, Comparator comp = Comparator()) {
    int pivot_idx = l + (r - l) / 2;
    std::swap(arr[pivot_idx], arr[r - 1]);
    T &pivot = arr[r - 1];
    int i = l;
    int j = r - 1;
    while (i < j) {
        for (; comp(arr[i], pivot); ++i)
            ;
        // arr[i] >= pivot

        while (!comp(arr[j], pivot)) {
            j--;
        }
        // arr[j] < pivot

        if (i < j) {
            std::swap(arr[j], arr[i]);
            i++;
            j--;
        }
    }
    std::swap(arr[i], arr[r - 1]);
    return i;
}

template <typename T, typename Comparator = DefaultComparator<T>>
void kth_element(T *arr, int size, int k, Comparator comp = Comparator()) {
    int l = 0;
    int r = size;
    while (l < r) {
        int pivot_pos = partition(arr, l, r, comp);
        if (pivot_pos == k) {
            return;
        }
        if (k < pivot_pos) {
            r = pivot_pos;
        } else { // k > pivot_pos
            l = pivot_pos + 1;
        }
    }
}

bool testFunc(int *arr, int size, int k) {
    kth_element(arr, size, k);
    int kth_value = arr[k];

    std::sort(&arr[0], &arr[size - 1]);
    std::cout << "----- k=" << k << " ------" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl
              << "-----------" << std::endl;

    return arr[k] == kth_value;
}

struct Person {
    std::string name;
    int year;
};

void unstable_count_sort(int *arr, int size, int R) {
    int *counters = new int[R + 1];
    for (int i = 0; i < R + 1; ++i) {
        counters[i] = 0;
    }
    // std::fill(&counters[0], &counters[R + 1], 0);

    for (int i = 0; i < size; ++i) {
        counters[arr[i]]++;
    }
    int arr_idx = 0;
    for (int i = 0; i < R + 1; ++i) {
        while (counters[i] > 0) {
            arr[arr_idx++] = i;
            counters[i]--;
        }
    }
    delete[] counters;
}

void stable_count_sort(int *arr, int size, int R) {
    int *counters = new int[R + 1];
    std::fill(&counters[0], &counters[R + 2], 0);

    for (int i = 0; i < size; ++i) {
        counters[arr[i]]++;
    }
    for (int i = 0; i < size - 1; ++i) {
        counters[i + 1] += counters[i];
    }

    int *temp_arr = new int[size];
    for (int i = size - 1; i >= 0; --i) {
        temp_arr[--counters[arr[i]]] = arr[i];
    }
    std::copy(&temp_arr[0], &temp_arr[size], &arr[0]);

    delete[] temp_arr;
    delete[] counters;
}

template <typename T>
void count_sort(T *arr, int size, int R, size_t (*key)(const T &)) {
    int counters_size = R + 1;
    int *counters = new int[counters_size];
    std::fill(&counters[0], &counters[counters_size], 0);

    for (int i = 0; i < size; ++i) {
        counters[key(arr[i])]++;
    }
    for (int i = 0; i < counters_size - 1; ++i) {
        counters[i + 1] += counters[i];
    }
    // 0..counters[0]; counters[0]..counters[1]
    // count_sort(arr, counters[0], counters[1])

    T *temp_arr = new T[size];
    for (int i = size - 1; i >= 0; --i) {
        size_t k = key(arr[i]);
        counters[k]--;
        size_t counters_idx = counters[k];
        temp_arr[counters_idx] = arr[i];

    }
    for (int i = 0; i < size; ++i) {
        std::cout << "key=" << key(temp_arr[i]) << " " << temp_arr[i].year << std::endl;
    }
    std::copy(&temp_arr[0], &temp_arr[size], &arr[0]);

    delete[] temp_arr;
    delete[] counters;
}

int main() {
    {
        std::vector<int> v = {1, 3, -1, 0, 2, 1};
        testFunc(&v[0], v.size(), 0);
    }
    {
        std::vector<int> v = {1, 3, -1, 0, 2, 1};
        testFunc(&v[0], v.size(), v.size() - 1);
    }
    {
        std::vector<int> v = {1};
        testFunc(&v[0], v.size(), 0);
    }

    {
        std::vector<int> v = {1, 3, 1, 0, 2, 1};
        unstable_count_sort(&v[0], v.size(), 3);
        for (auto &c : v) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> v = {1, 3, 1, 0, 2, 1};
        stable_count_sort(&v[0], v.size(), 3);
        for (auto &c : v) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    {
        std::vector<Person> v = {{"Ivan", 2000}, {"Oleg", 2020}};
        count_sort<Person>(&v[0], v.size(), 2020, [](const Person &p) {
            return (size_t)p.year;
        });
        for (auto &c : v) {
            std::cout << c.year << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "test OK" << std::endl;
}
