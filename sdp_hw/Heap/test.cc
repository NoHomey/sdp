#include <iostream>
#include "Heap.thd"

bool isLess(const int& a, const int& b) {
    return a < b;
}

int main() {
    Heap<int, isLess> heap{8};

    heap.insert(2);
    heap.insert(9);
    heap.insert(-1);
    heap.insert(-111);

    std::cout << heap.extract() << std::endl;
    std::cout << heap.extract() << std::endl;
    std::cout << heap.extract() << std::endl;
    std::cout << "is empty: " << (heap.isEmpty() ? "yes" : "no") << std::endl;

    {
        const std::size_t size = 11;
        int array[size] = {1, 5, -1, 0, 9, 3, 2,  2, 7, 4, 5};
        Heap<int, isLess>::sort(array, size);
        for(std::size_t i = 0; i < size; ++i) {
            std::cout << array[i] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}