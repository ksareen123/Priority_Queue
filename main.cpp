#include <iostream>

#include "PriorityQueue.h"

int main() {
    // PriorityQueue<int> max;
    // for(int i = 0; i <10; i++) {
    //     std::cout << "pushing " << i << std::endl;
    //     max.push(i % 2 ? -i : i);
    // }
    // max.pop();
    // std::cout << max.top() << std::endl;
    PriorityQueue<int> max_pq;
    PriorityQueue<int, std::vector<int>, std::greater<int>> min_pq;

    for (int i = 0; i < 10; ++i) {
        max_pq.push(i);
        min_pq.push(i);
        // max_pq.push(i % 2 ? -i : i);
        // min_pq.push(i % 2 ? -i : i);
    }

    std::cout << "Max Priority Queue:" << std::endl;
    while (!max_pq.empty()) {
        std::cout << max_pq.top() << ' ' << std::endl;
        max_pq.pop();
    }
    std::cout << "is sorted descending?" << std::endl;

    std::cout << "Min Priority Queue:" << std::endl;
    while (!min_pq.empty()) {
        std::cout << min_pq.top() << ' ';
        min_pq.pop();
    }
    std::cout << "is sorted ascending?" << std::endl;
}