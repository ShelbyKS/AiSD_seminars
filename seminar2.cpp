#include <iostream>
#include <vector>
#include <math.h>

template <typename T>
struct DefaultComparator {
    bool operator()(const T& l, const T& r) const {
        return l < r;
    }
};


template <typename T, typename Comparator = DefaultComparator<T>>
class Heap {
public:
    Heap(Comparator comp = Comparator()) : comp(comp) //,......
    {
    }
    Heap(const T& arr, size_t arr_size, Comparator comp = Comparator()) : comp(comp) //,......
    {

    }
    ~Heap();

    const T& top();
    void pop();
    void push(const T&);

    bool is_empty() const { return heap_size == 0; }
    size_t size() const { return heap_size; }

private:
    void heapify();
    void sift_up();
    void sift_down();

    Comparator comp;

    T* buf;
    size_t buf_size;
    size_t heap_size;
};








template <typename T, typename Comparator = DefaultComparator<T>>
void sort(T* arr, size_t size, Comparator comp = Comparator()) {
    size_t l = 0;
    size_t r = size;

    for (size_t i = l; i < r; ++i ) {
        for (size_t j = l; j < r - 1; ++j) {

            if (comp(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template <typename T>
void sort_simple(T* arr, size_t size, bool (*comp)(const T& l, const T& r)) {
    size_t l = 0;
    size_t r = size;

    for (size_t i = l; i < r; ++i ) {
        for (size_t j = l; j < r - 1; ++j) {

            if (comp(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

struct Point {
    int x;
    int y;

    bool operator< (const Point& r) const {
        return this->x < r.x;
    }
};

template <typename T>
bool is_less(const T& l, const T& r) {
    return l < r;
}

bool is_less_points(const Point& l, const Point& r) {
    return l.x < r.x;
}

bool is_less_points_by_y(const Point& l, const Point& r) {
    return l.y < r.y;
}


struct ComparatorPoint {
    Point base_point;
    int* compare_count;

    ComparatorPoint(const Point& bp, int* compare_count) : base_point(bp), compare_count(compare_count) {

    }

    bool operator()(const Point& l, const Point& r)  {
        (*compare_count)++;
        return abs(base_point.x - l.x) < abs(base_point.x - r.x);
    }
};

int main() {
    std::vector<int> arr = {5,4,3,2,7,11,100,-100,80,0};
    //int*
    sort(&arr[0], arr.size(), is_less<int>);

    for (int c : arr) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    int counter = 0;
    ComparatorPoint comp_points(Point({0,0}), &counter);

    std::vector<Point> arr_points = { {0,0}, {1,1}, {10,0}, {0, 20} };
    sort(&arr_points[0], arr_points.size());

    for (Point c : arr_points) {
        std::cout << "{" << c.x << "," << c.y << "} ";
    }
    std::cout << std::endl;

    std::cout << *comp_points.compare_count << std::endl;
}
