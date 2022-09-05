1. This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world  
1. https://stackoverflow.com/a/73564212/4561887

I was adding a section at the bottom about `T()`, but instead I should add that as its own answer to my question here: [What is a call to `char()` as a function in C++?](https://stackoverflow.com/q/72367123/4561887), then I should link this answer below to my answer I'll add to that question there.

---


## What is the colon syntax (`:`) in the class constructor and what does passing an integer to a `std::vector<>` do?

I'd like to explain the below example from [this question](https://stackoverflow.com/q/73563851/4561887):

```cpp
class UnionFind {
    public:
        UnionFind(int sz) : root(sz) {
            for (int i = 0; i < sz; i++) {
                root[i] = i;
            }
        }
    private:
        vector<int> root;
    };
    
    
    int main() {
        
       
        UnionFind uf(10);
    }
```

The colon (`:`) signifies the start of an initialization list, which initializes each variable to the value in parenthesis. So, `: root(sz)` initializes the `root` variable with an `int sz`, which is like doing `vector<int> root(sz);`. Doing it like this, however, allows `sz` to get passed in to the `UnionFind` class constructor.

Initializing a vector with a size like that is constructor #3 here (https://en.cppreference.com/w/cpp/container/vector/vector):

```cpp
// Constructor (3) as shown at
// https://en.cppreference.com/w/cpp/container/vector/vector
explicit vector( size_type count,
                 const T& value = T(),
                 const Allocator& alloc = Allocator());
```

It constructs `count` (`sz` in the example above) number of elements into the vector, each with value `T()`, which means `int()` in this case since `root` is a `vector<int>`. `int()` looks like a function call but is basically an integer default constructor to value zero (`0`). It is called ["value initialization"](https://en.cppreference.com/w/cpp/language/value_initialization). Think of it like calling an "integer constructor", if integers were objects and had constructors. See also my question here: [What is a call to `char()` as a function in C++?](https://stackoverflow.com/q/72367123/4561887)

So, let's recap: `: root(sz)` in the constructor is like constructing `vector<int> root(sz);`, which creates `sz` number of elements in the `root` vector, each with initial value `int()`, which is the syntax for ["value initialization"](https://en.cppreference.com/w/cpp/language/value_initialization) of an `int` to zero. 

Note also that the `count` parameter passed to constructor #3 shown above really should be a `size_type`, which can be written as `std::vector::size_type`, and is usually `size_t` (see the "Member types" section [here](https://en.cppreference.com/w/cpp/container/vector)). So, it would be better to change `int sz` to `size_t sz` instead. Therefore, change this constructor line: `UnionFind(int sz) : root(sz) {` to this instead: `UnionFind(size_t sz) : root(sz) {`.


## More on the weird `T()` (ex: `int()`) syntax

See also my question here: [What is a call to `char()` as a function in C++?](https://stackoverflow.com/q/72367123/4561887)

See also [https://en.cppreference.com/w/cpp/language/zero_initialization]


means a zero which is an integer., which is literally `int()` in this case, since `sz` is an int. Even though `int()` looks super weird, that is actually valid C++, which means to default-initialize an `int` with value zero. So, it is like writing `int `
