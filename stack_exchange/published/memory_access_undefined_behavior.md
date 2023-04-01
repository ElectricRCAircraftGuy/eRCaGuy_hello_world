<!--
GS
1 Apr. 2023
My answer: https://stackoverflow.com/a/75903325/4561887
-->


## Undefined behavior: memory usage in C, when it _is_ or is _not_ undefined behavior

### 1st, some background study: let us understand what is and is not undefined behavior when managing memory in C

As is frequently the case in programming, there are a lot of _nuances_ to discuss. So, let me try to address the edits to your question.

> My question was a bit unclear and misleading. It's not the cast itself that I think is UB, but dereferencing `pChild` after it was cast from `pInstance`.

In C, I believe _casting_ is *never* undefined behavior. _Dereferencing_ is undefined behavior if: 
1. you are dereferencing out-of-bounds memory that is *unowned* by your program/object, or 
1. you are reading *uninitialized* memory/values (even if your program *does* properly own that memory)

Consider the following examples:

1. Example 1: pointing to memory our program does _not_ own is undefined behavior
    1. Undefined behavior: on any machine
        ```c
        // arbitrarily point to some address in memory, and assume it's an 8-bit
        // unsigned integer
        uint8_t * p = (uint8_t*)0x1234; // not undefined behavior

        // now dereference this pointer and assign a value to this integer
        *p = 1; // undefined behavior (whether reading OR writing here) because
                // you are accessing memory that your program does not own nor
                // control!
        ```
    1. NOT undefined behavior: on an ATmega328 8-bit microcontroller (ex: Arduino Uno)

        ```c
        uint8_t * p = (uint8_t*)0x23; // not undefined behavior

        // now dereference this pointer and assign a value to this integer
        *p = 1; // NOT undefined behavior because the ATmega328 datasheet 
                // (https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/40001906C.pdf)
                // indicates on p445 that address 0x23 is the PINB hardware
                // register, which allows you to read from or toggle IO pins.
                // Writing a 1 here actually toggles the output of GPIO pin B0. 
        ```

        Note that the proper way to do the above is this (example file: "/Arduino 1.8.13/hardware/tools/avr/avr/include/avr/[iom328pb.h](https://github.com/amoehl/uino-atmega328pb/blob/master/src/tools/include/avr/iom328pb.h#L51-L59)"):
        ```c
        #define PINB    (*(volatile uint8_t *)(0x23))
        #define PINB7   7
        #define PINB6   6
        #define PINB5   5
        #define PINB4   4
        #define PINB3   3
        #define PINB2   2
        #define PINB1   1
        #define PINB0   0

        PINB = 1 << PINB0;
        ```

1. Example 2: using memory we don't own, and/or that is uninitialized, is undefined behavior
    1. Undefined behavior: on any machine
        ```c
        uint32_t * pu32 = (uint32_t*)0x1234; // ok
        uint32_t u1;

        u1 = *pu32; // Undefined behavior! Reading memory our program doesn't 
                    // own

        *pu32 = 0;  // Undefined behavior! Writing to memory our program doesn't
                    // own

        pu32 = &u1; // ok: pointing our pointer to valid memory our program owns

        uint32_t u2;
        u2 = u1;    // Undefined behavior! Reading an undefined value from u1.
        *pu32 = u1; // Undefined behavior! Reading an undefined value from u1.

        u1 = *pu32; // Undefined behavior! Our program DOES own this memory 
                    // that pu32 points to now, but the value stored there is
                    // undefined/uninitialized.
        ```
    1. NOT undefined behavior: on any machine
        ```c
        uint32_t * pu32;
        uint32_t u1;
        pu32 = &u1; // ok: our ptr now points to valid memory
        *pu32 = 7;  // set u1 to 7
        u1 = 8;     // set u1 to 8
        uint32_t u2 = u1;     // set u2 to 8
        uint32_t u3 = *pu32;  // set u3 to 8 (since pu32 points to u1)
        ```

1. Example 3: using a memory pool our program *does* own is _not_ undefined behavior
    1. NOT undefined behavior: on any machine
        ```c
        uint8_t memory_pool_of_bytes[4]; // ok
        // ok: pointing our uint32_t* pointer to use this memory pool of bytes
        uint32_t * pu32 = (uint32_t *)memory_pool_of_bytes; 

        *pu32 = 1000000; // ok; our program owns this memory!
        ```

### Now, with the above knowledge learned, let's look back at your question: 

> My question was a bit unclear and misleading. It's not the cast itself that I think is UB, but dereferencing `pChild` after it was cast from `pInstance`.

The answer to this is: **"it depends on whether or not you dereferencing _valid_ (owned, and already-initialized if reading it) vs _invalid_ (not owned, _or_ not initialized) memory.**

Consider the following:
```c
// create a base
S_Base base;
Child_DoAwesomeStuff(&base); // Undefined behavior inside this func??? Maybe!

// vs:

// create a child
S_Child child; 
Child_DoAwesomeStuff((S_Base*)&child); // Undefined behavior inside this func??? 
                                       // No! This is fine. 
```

Let's go deeper to explore the 1st case where there is *maybe* undefined behavior.
```c
S_Base base;            // ok: statically allocate a chunk of memory large 
                        // enough to hold an `S_Base` type.
S_Base* pBase = &base;  // ok: create a pointer to point to our memory above.
S_Child* pChild = (S_Child*)pBase; // **technically** ok, but a very bad idea 
                                   // because it **could lead to** undefined
                                   // behavior later! `pChild` does NOT point
                                   // to a "valid complete object of the target
                                   // type".
pChild->BaseClass.AwesomeValue = 7; // fine, because this is owned memory!
pChild->EvenAwesomerValue; // UNDEFINED BEHAVIOR! This is NOT owned memory! We
                           // just read outside the memory we statically 
                           // allocated in the first line above!
```

So, is *the `(S_Child*)pBase;` cast* undefined behavior? No! But it is _dangerous_! Is accessing owned memory within `pChild` undefined behavior? No! We own it. Our program allocated it. But, is accessing memory *outside* what our program owns (ex: `pChild->EvenAwesomerValue`) undefined behavior? Yes! We do *not* own that memory. It is similar to the many undefined cases I went through above. 

C++ has solved the _dangerous_ behavior above by having the `dynamic_cast<>()` conversion which will allow casting a parent type to a child type. It will then *dynamically*, at run-time, check to see if the resulting object ["is a valid complete object of the target type"](https://cplusplus.com/doc/tutorial/typecasting/). If it discovers it is _not_, it sets the resulting pointer to `nullptr` to notify you of that. In C, you have to just track these things manually yourself. 


## "What mechanics need to be in place so that it is ensured that `S_Base` (parent) and `S_Child` are correctly aligned?"

This one's easy: just put your `S_Base` struct at the _very beginning_ of your `S_Child` struct and they are automatically aligned. Now, a pointer to your `S_Child` object points to the _exact same address_ as a pointer to the `S_Base` object within it, since the child _contains_ the base object. 

They are automatically aligned so long as you don't use any alignment or padding keywords or compiler extensions to change things. Padding is automatically added by the compiler _after_ struct members, as needed, never before the first member. See more on that here: [Structure padding and packing](https://stackoverflow.com/q/4306186/4561887).

Simple example (with*out* any virtual table polymorphism function stuff):
```c
typedef struct parent_s
{
    int i;
    float f;
} parent_t;

typedef struct child_s 
{
    parent_t parent; // parent (base) member MUST be 1st within the child
                     // to be properly aligned with the start of the child!
    int i;
    float f;
} child_t;

child_t child;
parent_t parent;

parent_t* p_parent = &child; // ok; p_parent IS a "valid complete object of the
                             // target [parent] type", since the child's
                             // allocated memory blob does indeed encompass the
                             // parent's
child_t* p_child = &child; // ok; p_child is a "valid complete object of 
                           // the target [child] type"
child_t* p_child = (child_t*)&parent; // DANGEROUS! Technically this cast is 
                                      // *not* undefined behavior *yet*, but it
                                      // could lead to it if you try to access
                                      // child members outside the memory blob 
                                      // created for the parent. 
                                      // 
                                      // p_child is NOT a "valid complete object
                                      // of the target [child] type".
```

For the last (dangerous) cast above, C++ would allow you to have a dynamic cast which would fail at runtime if and only if you called it with C++ dynamic_cast syntax, _and_ checked for errors, like this: 
```cpp
child_t* p_child = dynamic_cast<child_t*>(&parent);
if (p_child == nullptr)
{
    printf("Error: dynamic cast failed. p_child is NOT a \"valid complete "
           "object of the target [child_t] type.\"");
    // do error handling here
}
```

**Key takeaway:** 

Once you first get alignment by putting the parent right at the beginning inside the child, basically just think of each object as a memory blob, or memory pool. If the memory pool you have (are pointing to) is *larger than* the expected size based on the pointer type pointing to it, you're fine! Your program owns that memory. But, if the memory pool you have (are pointing to) is *smaller than* the expected size based on the pointer type pointint to it, you're not fine! Accessing memory outside your allocated memory blob is _undefined behavior_. 

In the case of OOP and parent/child relationships, the child object must always be larger than the parent object because _it contains_ a parent object within it. So, casting a child to a parent type is fine, since the child type is larger than the parent type and the child type holds the parent type *first* in its memory, but casting a parent type to a child type is *not* fine unless the memory blob being pointed to was created initially as a child of that child type. 

Now, let's look at this in C++ and compare to your C example.


## Inheritance and parent <--> child type casting in C++ and C

So long as the `pInstance` pointer being passed to `Child_DoAwesomeStuff()` was actually constructed initially as an `S_Child` object, then casting the pointer back to an `S_Child` pointer (`S_Child*`) is _not_ undefined behavior. It would only be undefined behavior if you attempt to cast a pointer to an object that was constructed originally as a `struct BaseTag` (aka `S_Base`) type to a child pointer type. 

This is how C++ works too, with `dynamic_cast<>()` (which I mention [in my answer here](https://stackoverflow.com/a/75838664/4561887)). 

Example C++ code from https://cplusplus.com/doc/tutorial/typecasting/ under the "dynamic_cast" section is below. 

In the C++ code below, notice that both `pba` _and_ `pbb` are pointers to the base type (`Base *`), yet, `pba` is actually _constructed_ as a `Derived` (child) type via `new Derived`, whereas `pbb` is actually _constructed_ as a `Base` (base, or parent) type via `new Base`. 

Therefore, casting _`pba`_ to `Derived*` is perfectly valid, since it truly is that type, but casting _`pbb`_ to `Derived*` is _not_ valid, since it is _not_ truly that type. C++'s `dynamic_cast<Derived*>(pbb)` call catches this undefined behavior at run-time, detecting that the returned type is not a fully-formed `Derived` type, and returns a `nullptr`, which is equal to `0`, so you get the print that says `Null pointer on second type-cast.` 

Here is that C++ code:

```cpp
// dynamic_cast
#include <iostream>
#include <exception>
using namespace std;

class Base { virtual void dummy() {} };
class Derived: public Base { int a; };

int main () {
  try {
    Base * pba = new Derived;
    Base * pbb = new Base;
    Derived * pd;

    pd = dynamic_cast<Derived*>(pba);
    if (pd==0) cout << "Null pointer on first type-cast.\n";

    pd = dynamic_cast<Derived*>(pbb);
    if (pd==0) cout << "Null pointer on second type-cast.\n";

  } catch (exception& e) {cout << "Exception: " << e.what();}
  return 0;
}
```

Output:
```
Null pointer on second type-cast.
```

Similarly, your C code has the same behavior. 

Doing this is valid:
```c
// create a child
S_Child child; 
// treat it like a base (ok since `S_Base` is at the beginning of it--since the
// child contains a base object)
S_Base* pBase = (S_Base*)&child;
// Now obtain the child back from the base pointer
S_Child* pChild = (S_Child*)pBase; // ok, since pBase really points to a 
                                   // child object
```

But doing this is _not_ ok:
```c
// create a base
S_Base base;
// Get a pointer to it
S_Base* pBase = &base;
// Now try to magically obtain a child from a base object
S_Child* pChild = (S_Child*)pBase; // NOT ok! **May lead to** undefined behavior 
                                   // when dereferencing, since pBase really
                                   // points to a base object!
```

So, for your specific function:
```c
// Note: I replaced `struct BaseTag*` with `S_Base*` for readability
int Child_DoAwesomeStuff(S_Base* pInstance) {
    S_Child* pChild = (S_Child*) pInstance;
    return pChild->EvenAwesomerValue;
}
```

This is fine:
```c
// create a child
S_Child child; 

Child_DoAwesomeStuff((S_Base*)&child); // ok
```

But this is _not_!:
```c
// create a base
S_Base base;

Child_DoAwesomeStuff(&base); // NOT ok! **May lead to** undefined behavior 
                             // inside this func!
```


## My thoughts on enforcing OoP (Object Oriented Programming) and inheritance in C

Just a warning though: passing around pointers and storing pointers to vtables and functions and things inside C structs will make tracing your code and trying to understand it _very_ difficult! No indexer that I am aware of (Eclipse included, and Eclipse has the best indexer I've ever seen), can trace back to which function or type was assigned to a pointer in your code. Unless you're doing this stuff just for a learning exercise, or to bootstrap your own C++ language from scratch in C (again, for learning), I recommend against these patterns. 

If you want "object-_oriented_" C with inheritance and all, don't do it. If you want "object-_based_" C, via opaque pointers/structs for basic private-member encapsulation and data hiding, that's just fine! Here's how I prefer to do that: [Option 1.5 ("Object-based" C Architecture)](https://stackoverflow.com/a/54488289/4561887).

Last note: you probably know more about virtual tables (vtables) than I do. At the end of the day, it's your code, so do whichever architecture you want, but I don't want to be working in that code base :).


## See also

1. https://cplusplus.com/doc/tutorial/typecasting/ - **excellent** article on typecasting! See in particular the "dynamic_cast" section, and the code snippet therein.
1. [Structure padding and packing](https://stackoverflow.com/q/4306186/4561887)
1. [my answer] [When should static_cast, dynamic_cast, const_cast, and reinterpret_cast be used?](https://stackoverflow.com/a/75838664/4561887)
1. https://en.wikipedia.org/wiki/Undefined_behavior
