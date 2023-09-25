<!--
GS
23 Sep. 2023

https://stackoverflow.com/q/8056130/4561887
-->


## Mutable vs immutable types in Python: quick summary

1. [_Mutable_](https://www.wordreference.com/definition/mutable) in plain English means _changeable._ Think: "mutation".
1. [_Immutable_](https://www.wordreference.com/definition/immutable) means _unchangeable_.
1. Python has no concept of constants. _Immutable_ vs _mutable_ does *not* mean _constant_ vs _not constant_, respectively. Rather, it means _shared memory (a single underlying object in memory via dynamic memory allocation)_ vs _not shared memory (multiple underlying objects in memory via dynamic memory allocation)_, respectively. 
    1. This, as a consequence, also means _pass by reference_ (mutable) vs _pass by value_ (immutable), since objects which maintain their own unique underlying objects in memory pass those mutable memory chunks by reference so that they can be mutated. 
1. Everything in Python is an object. Even numbers, integers, float, etc. are objects. All variables are objects.
1. The mutable vs immutable objects types in Python are listed below.
1. _Mutable_ types are passed _by reference_, and cause _side effects_.
    1. If you do `my_dict3 = my_dict2 = my_dict1 = {}`, then change `my_dict3`, it *does* also change `my_dict2` *and* `my_dict1`. This is a _side effect._ It is because each variable points to *the same* underlying object.
    1. If you do this, each mutable variable points to *the same* underlying object in memory, since the value is passed from one variable to the next _by reference_:
        ```py
        my_dict1 = {"key": "value"}
        my_dict2 = my_dict1
        my_dict3 = my_dict2
        ```
    1. Therefore, the following are *all* `True`:
        ```py
        # Each of these is True because the underlying object is the same
        # blob of memory.
        print(my_dict3 is my_dict2)    # True
        print(my_dict2 is my_dict1)    # True
        print(my_dict3 is my_dict1)    # True
        # And each of these is True because all variables have the same value.
        print(my_dict3 == my_dict2)    # True
        print(my_dict2 == my_dict1)    # True
        print(my_dict3 == my_dict1)    # True
        ```
1. _Immutable_ types are passed _by copy_, and do _not_ cause _side effects_.
    1. If you do `my_int3 = my_int2 = my_int1 = 1`, then change `my_int3`, it does *not* change `my_int2` or `my_int1`, because each variable points to *its own* underlying object. It has no _side effects._
1. Python is not an easy programming language. It has tons of nuances like this. It's just popular, different, and very high level.


###### func example; multi-assign example


## 1. Mutable vs immutable objects in Python

Here's a list of the most common mutable and immutable objects in Python. This list can be obtained by 1) painstakingly searching [Python's official "Built-in Types" reference page](https://docs.python.org/3/library/stdtypes.html) for the words "mutable" and "immutable", _or_ by 2) asking GitHub Copilot (or BingAI or ChatGPT) for it. I did both. The latter is, of course, way faster, and perhaps less error-prone in this case. I updated the list below based on my own findings, and added all quotes, mostly from the official documentation.

**Mutable objects:**
- [list](https://docs.python.org/3/library/stdtypes.html#lists) - "Lists are mutable sequences"
- [set](https://docs.python.org/3/library/stdtypes.html#set-types-set-frozenset) - "The set type is mutable"
- [dict](https://docs.python.org/3/library/stdtypes.html#dict) - "A mapping object maps hashable values to arbitrary objects. Mappings are mutable objects. There is currently only one standard mapping type, the _dictionary_."
- [bytearray](https://docs.python.org/3/library/stdtypes.html#bytearray)
    - "As bytearray objects are mutable, they support the mutable sequence operations in addition to the common bytes and bytearray operations"
    - "bytearray objects are mutable and have an efficient overallocation mechanism"
    - "bytearray objects are a mutable counterpart to bytes objects."

**Immutable objects:**
- All [numeric types](https://docs.python.org/3/library/stdtypes.html#numeric-types-int-float-complex). The official Python docs say nothing about their immutability, but every source and AI I find confirms they are immutable, as does my personal testing below. From [RealPython.com:](https://realpython.com/python-mutable-vs-immutable-types/#immutable-built-in-data-types-in-python) "Numeric types...are immutable."
    - int
    - float
    - complex
    - bool
- [str](https://docs.python.org/3/library/stdtypes.html#text-sequence-type-str) - "Strings are immutable sequences of Unicode code points."
- [bytes](https://docs.python.org/3/library/stdtypes.html#bytes-objects) - "Bytes objects are immutable sequences of single bytes."
- [tuple](https://docs.python.org/3/library/stdtypes.html#tuples) - "Tuples are immutable sequences, typically used to store collections of heterogeneous data"
- [frozenset](https://docs.python.org/3/library/stdtypes.html#set-types-set-frozenset) - "The frozenset type is immutable and hashable"
- [range](https://docs.python.org/3/library/stdtypes.html#ranges) - "The range type represents an immutable sequence of numbers and is commonly used for looping a specific number of times in for loops."


## 2. Reassignment

#### Summary

All variables can be reassigned in Python, whether they were previously assigned to mutable or immutable types. However, the behavior of reassignment is different for mutable and immutable types. For **immutable** types, reassignment is equivalent to creating (dynamically allocating) a new underlying type object with the new value, and making the already-existing variable object point to this new underlying type object. For **mutable** types, reassignment is equivalent to mutating the underlying object that the variable points to, modifying the underlying object's value in place.

#### Details

Coming from C and C++ as my primary languages, the concept of "mutability" in Python is quite confusing. For this and other reasons, I do *not* consider Python to be an "easy" or "beginner" language. It is simply a very powerful "extra high-level" language, is all. It has a *ton* of very nuanced and confusing points. C is more straight-forward and concrete in this regard. (And [C++ is just nuts](https://stackoverflow.com/questions/47002799/what-does-the-ampersand-at-the-end-of-member-function-signature-mean/47003980#comment109357350_47003980)).

In C and C++, my mental model of each variable is that it is a chunk of bytes in memory. When you do this:
```cpp
int var = 0;  // statically allocate bytes for `var`, and mutate them into a 0
var = 7;      // mutate the bits in `var` into a 7 now instead of a 0
```

...you are changing the bytes in `var`'s chunk of memory from bits storing a `0`, to bits storing a `7`. You have "mutated" the memory allocated by that variable, meaning: the chunk of memory which is set apart for it. The _type_ of the variable simply specifies the "lens" (think: looking through a magic glass lens that interprets bits into numbers, letters, etc.), or interpretation algorithm, through which you will interpret those bits (ex: `float`, `int`, `char`, etc.).

In Python, however, that is *not* the mental model you should have for variables. **In Python, think of variables as _objects containing pointers to other objects_,** where _everything is an object_. So, when you create a variable with a value, you create a variable object which points to another underlying object. When you update a variable, if the underlying object being pointed to is updated in place, then that type is considered **"mutable"**. However, if updating the variable causes a new underlying object to be dynamically allocated, and the variable object simply updates its pointer to point to that new underlying object, then that underlying type is considered **"immutable"**. Note also that an object is a _very sophisticated dynamically-allocated instance of a class, which manages its own state and chunk of memory_, kind of like a [std container](https://en.cppreference.com/w/cpp/container) in C++.

You can instantly see that types `int`, `bool`, `float`, etc. are all *classes* (objects) in Python, not just trivial types like they are in C and C++, by doing this:
```py
type(7)     # returns <class 'int'>
type(True)  # returns <class 'bool'>
type(1.0)   # returns <class 'float'>
```

So, in Python, when you do this:
```py
# dynamically allocate a pointer variable object named `var`, then
# dynamically allocate an integer object with a `0` in it, then point `var`
# to that int object which contains a `0`.
var = 0  # 0 is the value contained inside an immutable type `int` object

# dynamically allocate a new integer object with a `7` in it, then point `var`
# to that new, underlying int object which contains a `7`. Therefore,
# this simply re-assigns the variable `var` from pointing to the `0`
# object, to  pointing to the `7` object; the `int` object with a `0`
# in it is now "orphaned" and I suspect will be garbage collected
var = 7
```

In the case of mutable objects, the reassignment modifies its bytes in-place rather than dynamically creating a new object and pointing the variable to it. For example:

```py
my_dict = {}  # dynamically allocate a pointer variable named `my_dict`,
              # dynamically allocate a dict object, then point `my_dict` to
              # that dict object
my_dict["some_key"] = "some_value"  # mutate the dict object by adding a
                                    # key-value pair
```

The details of how that "immutable" vs "mutable" characteristic is carried out aren't really important to the Python programmer like they would be to a low-level embedded systems C and C++ programmer like myself. Rather, it's sort of "hand-wavy". The Python programmer is supposed to just blindly accept it and move on. Some high-level C++ programmers are this way too. It's a mindset thing.


## 3. References: passing by copy vs pass by reference, and _side effects_

What a good Python programmer *does* need to know, however, is whether or not their particular variable type will be passed _by reference_ or _by copy_ when passed to a function. This is a very important distinction, as passing _by reference_ causes _side effects_, which means that changes to the variable inside the function will be reflected outside the function. This is a very important concept in Python, and to me is the main reason why the distinction between mutable and immutable types is important. I don't really care how they work under the hood otherwise.

Again:
1. Passing a **mutable** type to a function causes _side effects_, which means modifications to that variable inside the function _will_ be seen outside the function.
1. Passing an **immutable** type to a function does not cause side effects, which means modifications to that variable inside the function will _not_ be seen outside the function.

Let's see this in action:

```py
def modify_variable(var):
    """
    Modifies the variable passed to it so that we can see later if the change to
    this variable can be seen outside the function.
    """
    print(f"var before modification = {var}")

    if type(var) is bool:
        print("var is a bool")
        var = not var  # flip it
    elif type(var) is float:
        print("var is a float")
        var += 1.0  # increment it
    elif type(var) is int:
        print("var is an int")
        var += 1  # increment it
    elif type(var) is str:
        print("var is a str (string)")
        var += "; some more words" # append some new words to it
    elif type(var) is list:
        print("var is a list")
        var.append(1)  # append a 1 to it
    elif type(var) is dict:
        print("var is a dict")
        var["new_key"] = "new_value"  # add a new key-value pair to it
    elif type(var) is tuple:
        print("var is a tuple")
        var = (1, 2, 3)  # reassign it to a new tuple

    print(f"var after modification = {var}")


def is_mutable(value_new, value_old):
    """
    Returns whether the variable is "mutable" or "immutable".

    This is identified simply by checking if `value_new` is the same as
    `value_old`. If it is, then it is immutable, since the update above
    was *not* seen outside the `modify_variable` function. If the two values
    are different, then it *is* mutable.
    """
    if value_new = value_old:
        return False
    else:
        return True

my_bool = True
my_float = 1.0
my_int = 7
my_str = "some words"
my_list = [7, 8, 9]
my_dict = {"key1": "value1", "key2": "value2"}
my_tuple = (7, 8, 9)

modify_variable(my_bool)
modify_variable(my_float)
modify_variable(my_int)
modify_variable(my_str)
modify_variable(my_list)
modify_variable(my_dict)
modify_variable(my_tuple)

print(f"is_mutable(my_bool, True) = {is_mutable(my_bool, True)}")
print(f"is_mutable(my_float, 1.0) = {is_mutable(my_float, 1.0)}")
print(f"is_mutable(my_int, 7) = {is_mutable(my_int, 7)}")
print(f"is_mutable(my_str, 'some words') = {is_mutable(my_str, 'some words')}")
print(f"is_mutable(my_list, [7, 8, 9]) = {is_mutable(my_list, [7, 8, 9])}")
print(f"is_mutable(my_dict, {{'key1': 'value1', 'key2': 'value2'}}) =
    {is_mutable(my_dict, {'key1': 'value1', 'key2': 'value2'})}")
print(f"is_mutable(my_tuple, (7, 8, 9)) = {is_mutable(my_tuple, (7, 8, 9))}")
```

Output:
```

```


## 4. `is` vs `==`

>>> {"key1":"val1"} == {"key1":"val1"}
True
>>> {"key1":"val1"} is {"key1":"val1"}
False
>>> d1 = {"key1":"val1"}
>>> d2 = d1
>>> d1 == d2
True
>>> d2 is d1
True
>>> d3 = {"key1":"val1"}
>>> d3 is d2
False
>>> d3 == d2
True
