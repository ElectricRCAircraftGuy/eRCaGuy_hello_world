This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples  
Sept. 2022

# Table of Contents
<!-- <details> -->
<!-- <summary><b>(click to expand)</b></summary> -->
<!-- MarkdownTOC -->

1. [C++ mutexes and locks: `std::mutex` vs \(`std::lock_guard` and `std::condition_variable`\) vs `std::unique_lock` vs \(`std::scoped_lock` and `std::lock(\)`)](#c-mutexes-and-locks-stdmutex-vs-stdlock_guard-and-stdcondition_variable-vs-stdunique_lock-vs-stdscoped_lock-and-stdlock)
    1. [1. `std::mutex` \(C++11\)](#1-stdmutex-c11)
    1. [2. `std::lock_guard` \(C++11\)](#2-stdlock_guard-c11)
    1. [3. `std::unique_lock` \(C++11\)](#3-stdunique_lock-c11)
    1. [4. `std::scoped_lock` \(C++17\) and `std::lock()` \(C++11\)](#4-stdscoped_lock-c17-and-stdlock-c11)
    1. [5. `std::condition_variable` \(C++11\)](#5-stdcondition_variable-c11)

<!-- /MarkdownTOC -->
<!-- </details> -->


<a id="c-mutexes-and-locks-stdmutex-vs-stdlock_guard-and-stdcondition_variable-vs-stdunique_lock-vs-stdscoped_lock-and-stdlock"></a>
# C++ mutexes and locks: `std::mutex` vs (`std::lock_guard` and `std::condition_variable`) vs `std::unique_lock` vs (`std::scoped_lock` and `std::lock()`)

About references: _both_ cppreference.com and cplusplus.com are _community wikis._ **You** can edit them, just like Wikipedia! Cppreference.com is generally _more pedantic_ and up-to-date (has documentation through C++20, for instance) and difficult to understand, and cplusplus.com is generally **significantly** easier to understand, and more useful in that sense, but is missing most documentation after C++11.  

General References:
1. Concurrency support library: https://en.cppreference.com/w/cpp/thread
1. Spurious wakeup: https://en.wikipedia.org/wiki/Spurious_wakeup


<a id="1-stdmutex-c11"></a>
## 1. `std::mutex` (C++11)

References:
1. https://en.cppreference.com/w/cpp/thread/mutex
1. https://cplusplus.com/reference/mutex/mutex/
    > A mutex is a lockable object that is designed to signal when critical sections of code need exclusive access, preventing other threads with the same protection from executing concurrently and access the same memory locations.

Features:
1. A `std::mutex` allows you to prevent race conditions between multiple threads by explicitly locking and unlocking access to a shared resource.

Sample code:
```cpp
#include <mutex>

std::mutex mutex;

mutex.lock(); 
// critical section here
mutex.unlock();
```


<a id="2-stdlock_guard-c11"></a>
## 2. `std::lock_guard` (C++11)

References:
1. https://en.cppreference.com/w/cpp/thread/lock_guard
1. https://cplusplus.com/reference/mutex/lock_guard/ 
    > A lock guard is an object that manages a mutex object by keeping it always locked.
    > 
    > On construction, the mutex object is locked by the calling thread, and on destruction, the mutex is unlocked. It is the simplest lock, and is specially useful as an object with automatic duration that lasts until the end of its context. In this way, it guarantees the mutex object is properly unlocked in case an exception is thrown.

Features:
1. A `std::lock_guard` wraps a mutex. 
1. At creation, it automatically locks the mutex. 
1. Upon destruction as it exits scope, it automatically unlocks the mutex. 
1. If using C++17 or later, it is recommended to use `std::scoped_lock` instead. 
1. Even in C++11, you can use the more feature-rich `std::unique_lock` as well, to do the exact same thing if needed.

Sample code:
```cpp
#include <mutex>

std::mutex mutex;

{
    // `mutex.lock()` is automatically called here at the construction of the 
    // `std::lock_guard`
    std::lock_guard<std::mutex> lock(mutex);
    
    // critical section here

}   // `mutex.unlock()` is automatically called here at the destruction of the 
    // `std::lock_guard` 
```


<a id="unique_lock"></a>
<a id="3-stdunique_lock-c11"></a>
## 3. `std::unique_lock` (C++11)

References:
1. https://en.cppreference.com/w/cpp/thread/unique_lock
1. https://cplusplus.com/reference/mutex/unique_lock/
    > A unique lock is an object that manages a mutex object with unique ownership in both states: locked and unlocked.
    > 
    > On construction (or by move-assigning to it), the object acquires a mutex object, for whose locking and unlocking operations becomes responsible.
    > 
    > This class guarantees an unlocked status on destruction (even if not called explicitly). Therefore it is especially useful as an object with automatic duration, as it guarantees the mutex object is properly unlocked in case an exception is thrown.

Features:
1. Wraps a mutex, but has more features than a `std::lock_guard`. 
    1. Unlike a `std::lock_guard`, a `std::unique_lock` can be explicitly locked and unlocked after creation.
1. At creation, by default, it automatically locks the mutex (same as a `std::lock_guard`), but this behavior can be modified by passing special values to the constructor.
1. Upon destruction as it exits scope, it automatically unlocks the mutex (same as a `std::lock_guard`).
1. Is required by the receiving side (the side which is notified) for use by a `std::condition_variable` in order to receive the notification. 
    1. The reason a `std::unique_lock` is required by a `std::condition_variable` is so that it can lock the underlying mutex each time the condition variable wakes up from a wait after a valid notification and runs a critical section of code, and unlock the underlying mutex each time A) the condition variable `wait()` call spuriously wakes up and it needs to wait again, and B) upon automatic destruction when the critical section runs and is over and the scope of the `std::unique_lock` is exited.
1. You can **always** use a `std::unique_lock` in place of a `std::lock_guard`, but not the other way around. 

Sample code:
```cpp
#include <mutex>

// A global, shared mutex to be used by **all** code and threads in all examples
// below!
std::mutex mutex;

// ------------------------------------------
// Example 1: basic lock guard type usage
// ------------------------------------------
{
    // `mutex.lock()` is automatically called here at the construction of the 
    // `std::unique_lock`
    std::unique_lock<std::mutex> lock(mutex);
    
    // critical section here

}   // `mutex.unlock()` is automatically called here at the destruction of the 
    // `std::unique_lock` 

// ------------------------------------------
// Example 2: multiple critical sections
// ------------------------------------------
{
    // `mutex.lock()` is automatically called here at the construction of the 
    // `std::unique_lock`
    std::unique_lock<std::mutex> lock(mutex);
    // critical section 1 here
    lock.unlock();

    // do non-critical stuff here

    lock.lock();
    // critical section 2 here
    lock.unlock();

    // do non-critical stuff here

}   // `mutex.unlock()` is automatically called here at the destruction of the 
    // `std::unique_lock` 

// ------------------------------------------
// Example 3: choose to NOT automatically lock at construction
// ------------------------------------------
{
    // `mutex.lock()` is NOT automatically called here at the construction of
    // the `std::unique_lock`
    std::unique_lock<std::mutex> lock(mutex, std::defer_lock);

    // do non-critical stuff here

    lock.lock();    
    // critical section here
    lock.unlock();

    // do non-critical stuff here

}   // `mutex.unlock()` is automatically called here at the destruction of the 
    // `std::unique_lock`
```

<a id="condition_variable"></a>
The `std::condition_variable` usage of the `std::unique_lock` is slightly more complex:

```cpp
#include <condition_variable>
#include <mutex>

// A global, shared mutex to be used by all code and threads below
std::mutex mutex;
// A global, shared condition variable to be used by all code and threads below
// in order to support one or more thread or threads to notify another thread
// or threads to trigger it or them to wake up and run.
// ie: a condition variable is a signal mechanism to get other threads to run
// when it is time for them to run.
std::condition_variable cv;

// ------------------------------------------
// Example 4: usage with `std::condition_variable`s to send a notification 
// from a producer thread to a consumer thread whenever it is time to wake up
// the consumer to let it work on what the producer has provided via a shared
// memory object.
// ------------------------------------------

// Container of data to share
struct Data
{
    // The producer will set this to true to indicate the data is new and has
    // not been read by a consumer yet. The consumer will reset it to false
    // once the data has been read.
    bool isNewData = false;
    int i1;
    int i2;
    int i3;
};

// shared data--to share between threads
Data sharedData; 

// - - - - - - - - - - - - - - - - - - - - -
// Thread 1: producer
// Write data to be read by any consumer thread.
// - - - - - - - - - - - - - - - - - - - - -
{
    // `mutex.lock()` is automatically called here at the construction of the 
    // `std::unique_lock`
    std::unique_lock<std::mutex> lock(mutex);
    
    // critical section here: have unique access via the underlying mutex to
    // atomically **write to** a shared data object
    sharedData.isNewData = true;
    sharedData.i1 = 7;
    sharedData.i2 = 8;
    sharedData.i3 = 9;

    // Now, immediately unlock the mutex since we are done with the critical
    // section, and notify a consumer thread **which is already waiting on 
    // the condition variable** to get it to wake up and run.
    lock.unlock();
    cv.notify_one(); // wake up just one waiting, consumer thread
}   // `mutex.unlock()` is automatically called here at the destruction of the 
    // `std::unique_lock` 

// Alternative form of Thread 1:
{
    mutex.lock();
    sharedData.isNewData = true;
    sharedData.i1 = 7;
    sharedData.i2 = 8;
    sharedData.i3 = 9;
    mutex.unlock();
    cv.notify_one(); // wake up just one waiting, consumer thread
}

// Another alternative form of Thread 1:
while (true)
{   
    {
        // `mutex.lock()` is automatically called here at construction of 
        // `std::lock_guard`
        std::lock_guard<std::mutex> lock(mutex);
        sharedData.isNewData = true;
        sharedData.i1 = 7;
        sharedData.i2 = 8;
        sharedData.i3 = 9;
    }   // `mutex.unlock()` is automatically called here at destruction of
        // `std::lock_guard
    cv.notify_one(); // wake up just one waiting, consumer thread
}

// - - - - - - - - - - - - - - - - - - - - -
// Thread 2: consumer
// Wake up and read data from any producer thread which has sent it a 
// notification via the condition variable.
// Call `cv.wait()` WITH the boolean predicate. 
// - - - - - - - - - - - - - - - - - - - - -
while (true)
{
    // The `std::condition_variable::wait()` function **requires** a 
    // `std::unique_lock<std::mutex>&` to operate on! See:
    // https://en.cppreference.com/w/cpp/thread/condition_variable/wait
    std::unique_lock<std::mutex> lock(mutex); // `mutex.lock()` is automatically 
                                              // called here at construction 
    
    // Wait, meaning sleep this thread, until it is notified by the condition
    // variable to wake up! The 2nd parameter passed to `wait()` is a callable
    // or lambda or boolean variable "predicate" which must be `true` in order
    // for this thread to stay awake and return from the `wait()` function. If
    // the predicate is false, then the `wait()` function assumes it was a 
    // [spurious wakeup](https://en.wikipedia.org/wiki/Spurious_wakeup) and 
    // automatically calls the underlying `lock.unlock()` and puts the thread
    // back to sleep to wait again. This wait loop goes on indefinitely until 
    // the predicate is true, at which point the `wait()` function will return. 
    // When `wait()` finally does return, the lock will have been already
    // automatically taken via `lock.lock()`, which of course is just a wrapper
    // around the underlying mutex, essentially calling `mutex.lock()`.  
    cv.wait(lock, []() { 
        return sharedData.isNewData; 
    });
    // at this point, after `wait()` returns, the underlying mutex has already
    // been taken via `mutex.lock()`
    
    // critical section here: have unique access via the underlying mutex to
    // atomically **read from (and/or also write to)** a shared data object
    sharedData.isNewData = false; // reset our boolean "predicate" variable
    // Quickly copy out the shared data to minimize time in the critical
    // section. See my answer here: https://stackoverflow.com/a/71625693/4561887
    Data sharedDataCopy = sharedData;

    // terminate the critical section by releasing the lock
    lock.unlock();

    // do whatever you want to with your copy of the data now; ex: print it:
    printf("sharedDataCopy: i1 = %i; i2 = %i; i3 = %i\n", 
        sharedDataCopy.i1, sharedDataCopy.i2, sharedDataCopy.i3);

}   // `mutex.unlock()` is automatically called here at the destruction of the 
    // `std::unique_lock` 

// Comment-free (minimal comment) form of Thread 2, for clarity:
while (true)
{
    std::unique_lock<std::mutex> lock(mutex); // `mutex.lock()` is automatically 
                                              // called here at construction 
    cv.wait(lock, []() { 
        return sharedData.isNewData; 
    });
    // `mutex.lock()` was called prior to `wait()` returning above too, even
    // though the mutex was necessarily **unlocked** during the sleeping/waiting
    // period
    sharedData.isNewData = false; // reset our boolean "predicate" variable
    Data sharedDataCopy = sharedData; // quickly copy out the shared data
    lock.unlock();

    printf("sharedDataCopy: i1 = %i; i2 = %i; i3 = %i\n", 
        sharedDataCopy.i1, sharedDataCopy.i2, sharedDataCopy.i3);
}

// Alternative form of Thread 2: call `cv.wait()` withOUT the boolean predicate,
// by using a simple `wait()` and a while loop to repeatedly check the
// predicate instead.
while (true)
{
    std::unique_lock<std::mutex> lock(mutex); // `mutex.lock()` is automatically 
                                              // called here at construction 
    while (sharedData.isNewData == false) // OR: `while (!sharedData.isNewData)`
    {
        cv.wait(lock);
    }

    // `mutex.lock()` was called prior to `wait()` returning above too, even
    // though the mutex was necessarily **unlocked** during the sleeping/waiting
    // period
    sharedData.isNewData = false; // reset our boolean "predicate" variable
    Data sharedDataCopy = sharedData; // quickly copy out the shared data
    lock.unlock();

    printf("sharedDataCopy: i1 = %i; i2 = %i; i3 = %i\n", 
        sharedDataCopy.i1, sharedDataCopy.i2, sharedDataCopy.i3);
}
```


<a id="4-stdscoped_lock-c17-and-stdlock-c11"></a>
## 4. `std::scoped_lock` (C++17) and `std::lock()` (C++11)

References:
1. `std::scoped_lock`: https://en.cppreference.com/w/cpp/thread/scoped_lock
1. `std::lock`: https://en.cppreference.com/w/cpp/thread/lock

Features:
1. `std::scoped_lock` is a very simple mechanism, like a C++11 `std::lock_guard`, except that the C++17 `std::scoped_lock` can be used on **multiple mutexes simultaneously!**
1. If using C++17 or later, it is recommended to use `std::scoped_lock` instead of the `std::lock_guard`. 
1. A `std::scoped_lock` wraps one or more mutexes, just like a `std::lock_guard`, except a `std::lock_guard` can only wrap ONE mutex at a time!
1. At creation, a `std::scoped_lock` automatically locks the mutex(es). 
1. Upon destruction as it exits scope, a `std::scoped_lock` automatically unlocks the mutex(es). 
1. Even in C++11, you can use the more feature-rich `std::unique_lock` as well, to do the exact same thing as a `std::scoped_lock`, but on a _single mutex at a time_. To do the same thing in C++11 on _multiple mutexes at once_, you must use a call to the `std::lock(mutex1, mutex2, mutexN)` function instead, thereby explicitly locking all mutexes at once. See examples below.

Sample code:
```cpp
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;
std::mutex mutex3;

// ------------------------------------------
// Example 1 (C++17): basic scoped lock usage on multiple mutexes at once
// ------------------------------------------
{
    // `mutex.lock()` is automatically simultaneously called on all mutexes here
    // at the construction of the `std::scoped_lock`
    std::scoped_lock lock(mutex1, mutex2, mutex3);
    
    // critical section here

}   // `mutex.unlock()` is automatically simultaneously called on all mutexes 
    // here at the destruction of the `std::scoped_lock`

// ------------------------------------------
// Example 2 (C++11): equivalent to the above, but C++11-compatible. See:
// 1. https://en.cppreference.com/w/cpp/thread/scoped_lock
// 2. https://en.cppreference.com/w/cpp/thread/lock_guard/lock_guard
// 3. https://en.cppreference.com/w/cpp/thread/lock_tag
// ------------------------------------------
{
    // 1. Explicitly lock all mutexes at once
    std::lock(mutex1, mutex2, mutex3);
    // 2. Now pass their ownership individually to `std::lock_guard` objects to
    // auto-unlock them at the termination of this scope. Creating a
    // `std::lock_guard` with the `std::adopt_lock` parameter "Acquires
    // ownership of the mutex `m` without attempting to lock it." See: 
    // https://en.cppreference.com/w/cpp/thread/lock_guard/lock_guard. 
    std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);
    std::lock_guard<std::mutex> lock3(mutex3, std::adopt_lock);

    // critical section here

}   // `mutex.unlock()` is automatically called on all mutexes 
    // here at the destruction of each `std::lock_guard`

// ------------------------------------------
// Example 3 (C++11): basic `std::lock()` function usage on multiple mutexes 
// at once. 
// ------------------------------------------
{
    // Explicitly lock all mutexes at once
    std::lock(mutex1, mutex2, mutex3);
    
    // critical section here

    // Unlock each mutex individually now
    mutex1.unlock();
    mutex2.unlock();
    mutex3.unlock();
}

// ------------------------------------------
// Example 4 (C++17): basic scoped lock usage on a single mutex.
// Remember: if using C++17 or later, it is recommended to use
// `std::scoped_lock` instead of the `std::lock_guard`, even when only locking
// a single mutex.
// ------------------------------------------
{
    // `mutex.lock()` is automatically called on the mutex(es) here
    // at the construction of the `std::scoped_lock`
    std::scoped_lock lock(mutex1);
    
    // critical section here

}   // `mutex.unlock()` is automatically called on the mutex(es) 
    // here at the destruction of the `std::scoped_lock`
```


<a id="5-stdcondition_variable-c11"></a>
## 5. `std::condition_variable` (C++11)

References:
1. https://en.cppreference.com/w/cpp/thread/condition_variable
    1. https://en.cppreference.com/w/cpp/thread/condition_variable/wait
1. https://cplusplus.com/reference/condition_variable/condition_variable/
    1. Quote:
        > A condition variable is an object able to block the calling thread until notified to resume.
        > 
        > It uses a `unique_lock` (over a `mutex`) to lock the thread when one of its `wait` functions is called. The thread remains blocked until woken up by another thread that calls a notification function on the same `condition_variable` object.
    1. https://cplusplus.com/reference/condition_variable/condition_variable/wait/
        > At the moment of blocking the thread, the function automatically calls `lck.unlock()`, allowing other locked threads to continue.
        > 
        > Once notified (explicitly, by some other thread), the function unblocks and calls `lck.lock()`, leaving `lck` in the same state as when the function was called. Then the function returns (notice that this last mutex locking may block again the thread before returning).
        >
        > Generally, the function is notified to wake up by a call in another thread either to member `notify_one` or to member `notify_all`. But certain implementations may produce spurious wake-up calls without any of these functions being called. Therefore, users of this function shall ensure their condition for resumption is met.

Features:
1. Allows one thread waking up another thread or threads to notify it or them that it's time for it or them to run.
1. The producer/notifying thread can lock the mutex like normal to write to or access the shared data.
1. The consumer/`wait()`ing thread _must_ use a `std::unique_lock` when waiting to be notified and woken up.

Sample code:  
_See above in the [`std::unique_lock`](#condition_variable) section!_
