/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

Gabriel Staples
www.ElectricRCAircraftGuy.com
11 Sept. 2020

OnlineGDB Share code: https://onlinegdb.com/r1_kRct4v

Practice defining and using a custom copy constructor and assignment operator
(`operator=()` func).

This is required for any class, in particular, which manages its own memory, or,
in other words, in general, which has pointers instead of values.

"A user-defined copy constructor is generally needed when an object owns
pointers or non-shareable references, such as to a file, in which case a
destructor and an assignment operator should also be written (see Rule of
three)."
- https://en.wikipedia.org/wiki/Copy_constructor_(C%2B%2B)

Also:
    If your class needs any of

    a copy constructor,
    an assignment operator,
    or a destructor,
    defined explictly, then it is likely to need all three of them.
- https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three/4172961#4172961

Also be mindful of the Rule of 5 (Google this), and even the Rule of Zero (try
to never have to write any one of these, and when you do, encapsulate them).
- https://isocpp.org/blog/2012/11/rule-of-zero
*****+Rule of 0/3/5: https://stackoverflow.com/a/4172724/4561887

A final example of the Rule of 5, from the Stack Overflow link just above:

    class person
    {
        std::string name;
        int age;

    public:
        person(const std::string& name, int age);        // Ctor
        person(const person &) = default;                // 1/5: Copy Ctor
        person(person &&) noexcept = default;            // 4/5: Move Ctor
        person& operator=(const person &) = default;     // 2/5: Copy Assignment
        person& operator=(person &&) noexcept = default; // 5/5: Move Assignment
        ~person() noexcept = default;                    // 3/5: Dtor
    };

--------------------------------------------------------------------------------
RULE OF THUMB FOR THE RULE OF 5:
**If you manually declare at least one of them, then you should manually declare
ALL of them, even if that just means explicitly defaulting them all with
`= default;`.**
See last line of this answer: https://stackoverflow.com/a/63855203/4561887
--------------------------------------------------------------------------------

References:
1. Google search for "c++ Assignment operator and copy constructor":
   https://www.google.com/search?q=c%2B%2B+Assignment+operator+and+copy+constructor&oq=c%2B%2B+Assignment+operator+and+copy+constructor&aqs=chrome..69i57.14504j0j7&client=ms-android-google&sourceid=chrome-mobile&ie=UTF-8
2. *****+ https://www.geeksforgeeks.org/copy-constructor-vs-assignment-operator-in-c/:
   `t2 = t1;  // calls assignment operator, same as "t2.operator=(t1);"`
3. ***** https://www.geeksforgeeks.org/assignment-operator-overloading-in-c/
4. Cplusplus.com: Copy constructors, assignment operators, and exception safe assignment:
   https://www.cplusplus.com/articles/y8hv0pDG/
5. *****[VERY USEFUL TOO!]
   http://web.stanford.edu/class/archive/cs/cs106b/cs106b.1084/cs106l/handouts/170_Copy_Constructor_Assignment_Operator.pdf
6. *****+Rule of 0/3/5: https://stackoverflow.com/a/4172724/4561887
7. MY OWN Q: https://stackoverflow.com/questions/63855090/whats-the-purpose-of-typing-default-at-the-end-of-a-constructor-or-operator

*******************************************************************************/

#include <iostream>

#include <stdio.h>

// See references 3 and 2 above!
// Also Stanford #5 p12 for a "skeleton" example of all 3: (regular constructor)
// + 1) Copy Constructor, 2) Assignment Operator, 3) Destructor

// Mind the "Rule of Three"! 1) Copy Constructor, 2) Assignment Operator,
// 3) Destructor
// - see:
//   1. Stanford reference #5 above, p4, and
//   2. https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three/4172961#4172961
class Test
{
public:
    // Regular constructor
    Test(int i = 0)
    {
        // dynamically-allocated int with value initialized to i; see:
        // https://en.cppreference.com/w/cpp/language/new --> "Memory leaks"
        // section for an example there.
        printf("regular constructor; i = %i\n", i);
        ptr = new int(i);
    }

    // 1/5: Custom **copy constructor**
    Test(const Test &other)
    {
        printf("copy constructor\n");
        ptr = new int;
        copyFromOther(other);
    }

    // 4/5: Move constructor
    // **NEED TO RESEARCH AND STUDY THIS MORE!**
    // See my Q here: https://stackoverflow.com/questions/63855090/whats-the-purpose-of-typing-default-at-the-end-of-a-constructor-or-operator
    // Test(Test &&) noexcept = default; // explicitly default it
    Test(Test &&other)
    {
        printf("move constructor\n");
        moveFromOther(std::move(other));
    }

    // 2/5: Define a custom **assignment operator** function!
    // (operator overloading for the `=` operator)
    Test & operator=(const Test &other)
    {
        printf("assignment operator\n");

        // Check for, **and don't allow**, self assignment!
        if(this != &other)
        {
            // ie: only copy the contents of the pointer(s) from the other object
            // to this object if it is not the same object (ie: if it is not
            // self-assignment)!
            copyFromOther(other);
        }
        // the assignment function (`operator=()`) expects you to return the
        // contents of your own object (the left side), passed by reference, so
        // that constructs such as `test1 = test2 = test3;` are valid!
        // See reference #5, from Stanford, p11, above!:
        //      MyClass one, two, three;
        //      three = two = one;
        return *this;
    }

    // 5/5: Move assignment
    // **NEED TO RESEARCH AND STUDY THIS MORE!**
    // See my Q here: https://stackoverflow.com/questions/63855090/whats-the-purpose-of-typing-default-at-the-end-of-a-constructor-or-operator
    // Test & operator=(Test &&) noexcept = default; // explicitly default it
    Test & operator=(Test &&other)
    {
        printf("move assignment\n");
        if (this != &other)
        {
            // manually call destructor to free resources from this instance, to
            // prevent memory leaks since `this` will now get rid of its own
            // resources and own `other`'s resources instead!
            this->~Test();
            // give `this` ownership of `other`'s resources now!
            moveFromOther(std::move(other));
        }
        return *this;
    }

    // 3/5: (to prevent memory leaks since this class must manage its own
    // dynamically-allocated memory!) Define a custom **destructor**!
    ~Test()
    {
        printf("destructor\n");
        // We MUST ensure `ptr != nullptr` here since the old ptr is set to
        // `nullptr` in the move constructor and in the move assignment
        // function.
        if (ptr != nullptr)
        {
            delete ptr;
        }
    }


    // Other public methods

    void setValue(int i)
    {
        *ptr = i;
    }

    void print()
    {
        std::cout << *ptr << std::endl;
    }

private:
    int *ptr = nullptr;

    void copyFromOther(const Test& other)
    {
        *ptr = *(other.ptr);
    }

    // Give `this` ownership of `other`'s resources! To prevent memory leaks,
    // we should have already `delete`d `this`'s resources (to free them)
    // PRIOR to calling this function!
    void moveFromOther(Test && other)
    {
        // pass the ownership of this memory from other instance to this
        // instance
        ptr = other.ptr;
        // Instance `this` now has full control of `other`'s (dynamic memory)
        // resources!

        // now invalidate the other instance's ownership of that memory so its
        // destructor will NOT attempt to free this memory, since that object
        // no longer owns this memory! IT WILL NOW BE A RUNTIME ERROR TO TRY
        // TO CALL `other.print()`, for instance, since that will attempt to
        // dereference a nullptr!
        other.ptr = nullptr;
    }
};


int main()
{
    printf("Hello World\n");

    Test t1(5);
    Test t2;
    t2 = t1;            // assignment operator <=== 1 ===
    std::cout << "t1 = "; t1.print();
    t1.setValue(10);
    std::cout << "t1 = "; t1.print();
    std::cout << "t2 = "; t2.print();

    Test t3(t1);        // copy constructor <=== 2 ===
    std::cout << "t3 = "; t3.print();

    t2.setValue(75);
    Test t4 = t2;       // copy constructor <=== 3 ===
    std::cout << "t4 = "; t4.print();

    Test t5(std::move(t4)); // move constructor <=== 4 ===; calls: `t5(std::move(t4));`
    // If you run the next line, you'll get this:
    //      Segmentation fault (core dumped)
    // since it attempts to dereference t4.ptr (which is now a nullptr!) to
    // print its value! ONCE MOVED, YOU CAN NO LONGER USE THE MOVED OBJECT (t4
    // in this case) AS THE NEW OBJECT (t5 in this case) NOW OWNS ITS MEMORY
    // RESOURCES!
    // std::cout << "t4 = "; t4.print();
    std::cout << "t5 = "; t5.print();

    Test t6(6);
    Test t7(7);
    std::cout << "t6 = "; t6.print();
    std::cout << "t7 = "; t7.print();
    t7 = std::move(t6); // move assignment <=== 5 ===; calls: `t7.operator=(std::move(t6));`
    // segmentation fault; t6.ptr is now `nullptr`!
    // std::cout << "t6 = "; t6.print();
    std::cout << "t7 = "; t7.print();

    return 0;
}

/*

SAMPLE OUTPUT:

    Hello World
    regular constructor; i = 5
    regular constructor; i = 0
    assignment operator
    t1 = 5
    t1 = 10
    t2 = 5
    copy constructor
    t3 = 10
    copy constructor
    t4 = 75
    move constructor
    t5 = 75
    regular constructor; i = 6
    regular constructor; i = 7
    t6 = 6
    t7 = 7
    move assignment
    destructor
    t7 = 6
    destructor
    destructor
    destructor
    destructor
    destructor
    destructor
    destructor


*/


