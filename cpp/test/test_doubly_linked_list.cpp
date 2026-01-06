#include "../src/doubly_linked_list.h"
#include <chrono>
#include <iostream>
#include <list>

int main() {
    constexpr int N = 1000;
    // Create a list containing integers
    std::list<int> l{};

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        l.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "std::list took " << duration.count() << " ms\n";

    // my own impl
    auto start2 = std::chrono::high_resolution_clock::now();
    V1::DoublyLinkedList<int> dll{};
    for (int i = 0; i < N; ++i) {
        dll.append(i);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration2 = end2 - start2;
    std::cout << "my list took " << duration2.count() << " ms\n";

    return 0;
}
