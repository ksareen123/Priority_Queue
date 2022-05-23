#pragma once

#include <functional>
#include <utility>
#include <vector>

template <class T, class Container = std::vector<T>, class Compare = std::less<T>>
class PriorityQueue {
public:
    using value_compare = Compare;
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;

private:
    Container c;
    value_compare comp;

    size_type parent(size_type index) { return (index - 1) / 2; }
    size_type left_child(size_type index) { return 2 * index + 1; }
    size_type right_child(size_type index) { return 2 * (index + 1); }
    bool is_internal(size_t index) { return left_child(index) < c.size(); }
    bool is_leaf(size_t index) { return left_child(index) >= c.size(); }

    
    /**
     * @brief Recursively (or Iteratively) swap the value at index up the heap until it is in the correct position.
     * 
     * @note This is a max heap, so assume Compare is less, but promote the larger value.
     * 
     * Used by push
     * 
     * O(log(size()))
     * 
     * @param index the current position to swap upwards
     */
    void upheap(size_type index) {
        if (index == 0) {
            return;
        }
        else {
            if (comp(c[parent(index)], c[index])) {
                auto temp = std::move(c[parent(index)]);
                c[parent(index)] = std::move(c[index]);
                c[index] = std::move(temp);
                return upheap(parent(index));
            }
        }
    }
    
    /**
     * @brief Recursively swap the value at index down the heap until it is in the correct position.
     * 
     * @note This is a max heap, so assume Compare is less, so promote the larger value.
     * 
     * Used by pop
     * 
     * O(log(size()))
     * 
     * @param index the current position to swap downwards
     */
    void swap(size_type a, size_type b) {
        auto temp = std::move(c[a]);
        c[a] = std::move(c[b]);
        c[b] = std::move(temp);
    }

    void downheap(size_type index) {
        size_t lchild = left_child(index);
        size_t rchild = right_child(index);

        if (is_leaf(index)) {
            return;
        }
        if (right_child(index) >= size()) {
            if(comp(c[index], c[lchild])) {
                swap(index, lchild);
                downheap(lchild);
            }
            return;
        }
        if (comp(c[rchild], c[index]) && comp(c[lchild], c[index])) {
            return;
        }
        if (comp(c[rchild], c[lchild])) {
            swap(index, lchild);
            downheap(lchild);
        }
        else {
            swap(index, rchild);
            downheap(rchild);
        }
    }

public:
    PriorityQueue() = default;
    PriorityQueue( const PriorityQueue& other ) = default;
    PriorityQueue( PriorityQueue&& other ) = default;
    ~PriorityQueue() = default;
    PriorityQueue& operator=( const PriorityQueue& other ) = default;
    PriorityQueue& operator=( PriorityQueue&& other ) = default;

    /**
     * @brief Return a const reference to the element at the top of the heap.
     * 
     * O(1)
     * 
     * @return const_reference to the element at the top of the heap.
     */
    const_reference top() const { return c[0]; }

    /**
     * @brief Return whether the heap is empty. This is the same as whether the underlying container, c, is empty.
     * 
     * O(1)
     * 
     * @return true c is empty
     * @return false c is not empty
     */
    bool empty() const { return (c.size() == 0); }

    /**
     * @brief Return the number of elements in the heap. This is the same as the number of elements in the underlying container, c.
     * 
     * O(1)
     * 
     * @return size_type of the number of elements in the heap
     */
    size_type size() const { return c.size(); }
	
    /**
     * @brief Inserts element and sorts the underlying container, c.
     * 
     * Uses upheap
     * 
     * O(log(size())) 
     * 
     * @param value inserted by copying into c 
     */
    void push( const value_type& value ) {
        c.push_back(value);
        upheap(c.size()-1);
    }

    /**
     * @brief Inserts element and sorts the underlying container, c.
     * 
     * Uses upheap
     * 
     * O(log(size())) 
     * 
     * @param value inserted by moving into c 
     */
	void push( value_type&& value ) {
        c.push_back(std::move(value));
        upheap(size() - 1);
    }

    /**
     * @brief Removes the top element.
     * 
     * Uses downheap
     * 
     * O(log(size())) 
     * 
     */
    void pop() {
        std::cout << "replacing " << c[0] << " with " << c[c.size() - 1] << std::endl;
        swap(0, c.size() - 1);
        // std::cout << c[0] << std::endl;
        // std::cout << c[c.size() - 1] << std::endl;
        c.pop_back();
        downheap(0);
        std::cout << "downheap finished" << std::endl;
    }
};