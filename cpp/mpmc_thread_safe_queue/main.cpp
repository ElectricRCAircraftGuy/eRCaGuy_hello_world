/*
GS
May 2025

MPMC thread-safe queue

Learned by me through interview prep and interviewing (as both the receiver and the giver), 
and improved over time. 

File started: ~Sep. 2022
Estimated knowledge span of this work: ~2020~2025
My personal (NON-public) notes on this: 
https://github.com/ElectricRCAircraftGuy/PRIVATE_interview_questions/issues/6#issuecomment-1289756376

Goal: 
Create a multi-producer multi-consumer (MPMC) thread-safe, concurrent, FIFO queue class.
 - Use modern C++ (C++11 or later) with STL container types. 
 - Ensure locking and concurrency are handled correctly.
 - The queue class's interface should be easy to use.

References:
1. https://cplusplus.com/doc/oldtutorial/templates/
1. https://en.cppreference.com/w/cpp/thread/condition_variable
1. https://gabrielstaples.com/cpp-mutexes-and-locks/#gsc.tab=0
1. https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-160
1. 

*/


#include <chrono>
// https://en.cppreference.com/w/cpp/thread/condition_variable
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

static bool run_producer = true;
static bool run_consumer = true;

static std::mutex cout_mutex;

template <typename T>
class ThreadSafeQueue
{
private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;

public:
    ThreadSafeQueue() {}
    ~ThreadSafeQueue() {}

    // Add an element to the queue
    void add(T element) 
    {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(element);
        lock.unlock();
        cv_.notify_one();
    }

    // Remove and return by copy the oldest element from the queue
    T remove() 
    {
        std::unique_lock<std::mutex> lock(mutex_);
        // NB: capture the `this` ptr by value to get access to the `queue_` member variable. 
        cv_.wait(lock, [this]() {
            // This is the predicate lambda function to the condition variable. 
            // - If the predicate returns false, it means the condition variable had a spurious 
            //   wakeup, and we need the thread to go back to sleep and wait again. 
            bool dataIsAvailable = queue_.size() > 0;
            return dataIsAvailable; 
        });
        T element = queue_.front();
        queue_.pop();
        return element;
    }
};

// Producer function/thread
template <typename T>
void producer(ThreadSafeQueue<T> *threadSafeQueue)
{
    while (run_producer)
    {
        int value = std::rand() % 100;
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Adding value " << value << std::endl;
        }
        threadSafeQueue->add(value);

        int numBetween0And500 = std::rand() % 500;
        std::this_thread::sleep_for(std::chrono::milliseconds(numBetween0And500));
    }
}

// Consumer function/thread
template <typename T>
void consumer(ThreadSafeQueue<T> *threadSafeQueue)
{
    while (run_consumer)
    {
        T value = threadSafeQueue->remove();
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "  Removing value " << value << std::endl;
        }
    }
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    // Make a single thread-safe queue object which will store elements of type `int`
    ThreadSafeQueue threadSafeQueue = ThreadSafeQueue<int>();

    // Spawn some producer and consumer threads

    constexpr size_t NUM_PRODUCERS = 20;
    constexpr size_t NUM_CONSUMERS = 20;

    std::thread producers[NUM_PRODUCERS];
    std::thread consumers[NUM_CONSUMERS];

    for (size_t i = 0; i < NUM_PRODUCERS; i++)
    {
        std::thread producerThread(producer<int>, &threadSafeQueue);
        producers[i] = std::move(producerThread);
    }

    for (size_t i = 0; i < NUM_CONSUMERS; i++)
    {
        std::thread consumerThread(consumer<int>, &threadSafeQueue);
        consumers[i] = std::move(consumerThread);
    }

    // Let it run for a short time
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Kill the threads
    run_consumer = false;
    // give the consumers time to receive another produced item and then detect the stop boolean
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    run_producer = false;  // stop the producers
    
    // Wait for all threads to finish
    for (size_t i = 0; i < NUM_PRODUCERS; i++)
    {
        producers[i].join();
    }
    for (size_t i = 0; i < NUM_CONSUMERS; i++)
    {
        consumers[i].join();
    }
}
