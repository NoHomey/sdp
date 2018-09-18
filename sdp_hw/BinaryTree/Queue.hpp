#pragma once

#include <utility>
#include <cassert>

template<typename T>
class Queue {
public:
    Queue(std::size_t capacity = 0)
    : queue{nullptr}, queueSize{0}, queueCapacity{capacity}, queueHead{0}, queueTail{0} {
        if(capacity) {
            queue = new T[capacity];
        }    
    }

    ~Queue() noexcept {
        delete[] queue;
    }

public:
    std::size_t size() const noexcept {
        return queueSize;
    }

    std::size_t capacity() const noexcept {
        return queueCapacity;
    }

    bool isEmpty() const noexcept {
        return queueSize == 0;
    }

    bool isFull() const noexcept {
        return queueSize == queueCapacity;
    }

public:
    void swap(Queue& other) {
        std::swap(queue, other.queue);
        std::swap(queueSize, other.queueSize);
        std::swap(queueCapacity, other.queueCapacity);
        std::swap(queueHead, other.queueHead);
        std::swap(queueTail, other.queueTail);
    }

    void enqueue(const T& data) {
        if(!queueCapacity) {
            queue = new T[1];
            queue[0] = data;
            queueSize = 1;
            queueCapacity = 1;
            queueTail = 1;
            return;
        }
        if(isFull()) {
            Queue tmp{queueCapacity * 2};
            for(std::size_t i = 0; i < queueCapacity; ++i) {
                tmp.enqueue(dequeue());
            }
            swap(tmp);
        }
        queue[queueTail] = data;
        queueTail = advance(queueTail);
        ++queueSize;
    }

    void removeFirst() {
        assert(!isEmpty());
        queueHead = advance(queueHead);
        --queueSize;
    }

    T dequeue() {
        assert(!isEmpty());
        std::size_t first = queueHead;
        removeFirst();
        return queue[first];
    }

private:
    std::size_t advance(std::size_t pos) const noexcept {
        assert(queueCapacity);
        return (pos + 1) % queueCapacity;
    }

private:
    T* queue;
    std::size_t queueSize;
    std::size_t queueCapacity;
    std::size_t queueHead;
    std::size_t queueTail;
};
