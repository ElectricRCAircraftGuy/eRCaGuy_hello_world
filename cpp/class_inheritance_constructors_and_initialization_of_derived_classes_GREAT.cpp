///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
9 Mar. 2023

Practice using constructors in a child class which call constructors in a parent class.
STATUS: done and works! GREAT DEMO

My content herein will be modified and originally learned from Alex's content, here:
https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
1. *****+ https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/

*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
// None

class Base
{
private:
    int _id;

public:
    // constructor
    Base(int id = 0)
        : _id{id}
    {
    }

    int getId() const
    {
        return _id;
    }
};

class Derived: public Base
{
private:
    double _cost;

public:
    // constructor
    Derived(double cost = 0.0, int id = 0)
        : Base{id} // call `Base(int)` constructor with value `id`!
        , _cost{cost}
    {
    }

    double getCost() const
    {
        return _cost;
    }
};

int main()
{
    Derived derived1{1.3, 5}; // calls the `Derived(double, int)` constructor
    std::cout << "Cost: " << derived1.getCost() << '\n';
    std::cout << "Id:   " << derived1.getId() << "\n\n";

    Derived derived2{100.04, 1234}; // calls the `Derived(double, int)` constructor
    std::cout << "Cost: " << derived2.getCost() << '\n';
    std::cout << "Id:   " << derived2.getId() << "\n\n";

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ cpp/class_inheritance_constructors_and_initialization_of_derived_classes_GREAT.cpp
    Cost: 1.3
    Id:   5

    Cost: 100.04
    Id:   1234


*/
