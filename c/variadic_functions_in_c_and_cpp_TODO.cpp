/*

GS
gabrielstaples.com
Sept-Oct. 2022

TODO: teach and practice various ways to use and pass variadic functions and their parameters in C
and C++. Borrow from some of my work here: https://stackoverflow.com/a/74542788/4561887

The below is just some scratch work to conceptualize and prototype various ideas.
See also my answer using variadic templates in C++ here:
https://stackoverflow.com/a/73904874/4561887

---------------------------------
In C, you have a few options.
---------------------------------

One is to pass an inner function and its parameters to an outer function via an enum `Func`, as
shown below. The outer func can accept a ton of different args as `void*` so as to be able to cast
them to *anything*.

When passing args to the outer func, unused or unneeded args for a given Func which takes fewer args
can be passed to the outer func as `NULL`. That, for course, indicates unused args when passing by
`void*`.

To make a function take literally **any** number of args, you can pass an array of `void*` args as
one parameter, and the size of the array as another parameter. This would, again, allow dynamic
interpretation of the args per the type of Func.

Instead of passing the func as a `Func` enum, you could also potentially pass the func to the outer
func as a function ptr to a `void* (*func_t)(void*)` function (ie: a func which accepts `void*` and
returns `void*`). Or, you could have it receive an array of `void*` and the size of the array, as
mentioned above.

You could also use variadic arguments via `...` and a `va_list` of args, interpreting them via
the `va_args()` func. See here: https://en.cppreference.com/w/c/variadic

---------------------------------
In C++, you have all of the above options, plus more
---------------------------------

In C++ you can do all of the above, plus pass functions as `std::function<>`.

You can also use variadic templates. See my answer here:
https://stackoverflow.com/a/73904874/4561887

Note: consider unions (or `std::variant<>` in C++) and `std::optional<>` potentially as well.


References:
1. [my ans] https://stackoverflow.com/a/74542788/4561887
1. [my ans] https://stackoverflow.com/a/73904874/4561887
1. https://en.cppreference.com/w/c/variadic
1. Multiple typename arguments in c++ template? - https://stackoverflow.com/a/19923558/4561887



*/


///////////
// save and document this
// originally started while helping someone on 28 Sept. 2022

struct Data
{
    int var1;
    float var2;
    std::string var3;
    double var4;
}

void foo(const Data& data)
{
    // foo calls a bunch of funcs with their params
    bar(data.var1, data.var4);
    bar2(data.var2);
    bar3(data.var3);
}



enum class Func
{
    A = 0,
    B,
    C,
}

/// 1 arg case
void outer(Func func, void* arg1)
{

}

/// 2 arg case
void outer(Func func, void* arg1, void* arg2)
{

}

/// 3 arg case
void outer(Func func, void* arg1, void* arg2)
{

}

////////////// POST THIS TO STACK OVERFLOW!--add a runnable example to my hello_world repo first! //////////////////
// try `std::optional<std::variant<>>` as well, instead of `void*`.
// do <func> as a template parameter to the function, instead of as the first argument to the function
//...thereby also eliminating the run-time switch block
// - see variadic templates: https://stackoverflow.com/questions/19923353/multiple-typename-arguments-in-c-template/19923558#19923558


enum class Func
{
    A = 0,
    B,
    C,
}


void outer_func(Func func, void* arg1, void* arg2 = nullptr, void* arg3 = nullptr, void* arg4 = nullptr)
{
    switch (func)
    {
        case Func::A:
        {
            // func_a requires only the first arg
            int* arg1_ = (int*)arg1;
            func_a(*arg1);
            break;
        }
        case Func::B:
        {
            // func_b requires 2 args
            double* arg1_ = (double*)arg1;
            float* arg2 = (float*)arg2;
            func_b(*arg1,*arg2);
            break;
        }
        case Func::C:
        {
            // func_c requires all 4 args

            break;
        }
    }
}

void outer(std:: func, void* arg1, void* arg2, void* arg3, void* arg4)
{
    switch (func)
    {
        case F:
        int* arg1_ = (int*)arg1;
        a(*arg1);
    }
}

int foo(int i)
{
    return i*2;
}


typedef int (*func_ptr_t)(int);

int (*func_ptr)(int) = foo;
func_ptr_t func_ptr = foo;

std::function<int (int)> func_ptr = foo;

typedef void* (*func_ptr_t)(void*);


void outer()

int main()
{

    outer(Func::A, 7, NULL, NULL, NULL);
    outer(Func::B, 7, "hello", NULL, NULL);
    outer(Func::C, 7, "hello", 1.234, -1);

    // more intuitive
    outer(Func::A, 7);
    outer(Func::B, 7, "hello");
    outer(Func::C, 7, "hello", 1.234, -1);

    outer(func1, 7);
    outer(func2, 7, "hello");
    outer(func3, 7, "hello", 1.234, -1);

    outer(func1, &struct1);
    outer(func2, &struct2);
    outer(func3, &struct3);

    // outer(func2, 7, "hello");
    // outer(func3, 7, "hello", 1.234, -1);


    my_struct_t my_struct = {
        .var1 = 7,
        .var2 = -1,
        .var3 = "hey",
    };
    outer(func1, &my_struct);


    outer(func1, {7, -1, "hey"});




    return 0;
}
