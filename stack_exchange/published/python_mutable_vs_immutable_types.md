<!--
GS
23 Sep. 2023

https://stackoverflow.com/q/8056130/4561887
-->


Mutable vs immutable types in Python


## 1. Summary

1. [_Mutable_](https://www.wordreference.com/definition/mutable) in plain English means _changeable._ Think: "mutation".
1. [_Immutable_](https://www.wordreference.com/definition/immutable) means _unchangeable_.
1. Python has no concept of constants. _Immutable_ vs _mutable_ does *not* mean _constant_ vs _not constant_, respectively. Rather, it means immutable --> _shared memory (a single underlying object in memory via dynamic memory allocation, for a given literal value assigned to variables)_ vs mutable --> _not shared memory (multiple underlying objects in memory via dynamic memory allocation, for a given literal value assigned to variables)_, respectively. I have more on this below, as this is quite nuanced.
    1. This, as a consequence, also means _pass by reference_ (mutable) vs _pass by value_ (immutable), since objects which are capable of maintaining their own unique underlying objects in memory can pass those mutable memory chunks by reference so that they can be mutated. 
1. Everything in Python is an object. Even numbers, integers, float, etc. are objects. All variables are objects.
1. The mutable vs immutable objects types in Python are listed below.

1. **_Mutable_ types are passed _by reference_, and cause _side effects_.**
    1. If you do `my_dict3 = my_dict2 = my_dict1 = {}`, then change `my_dict3`, it *does* also change `my_dict2` *and* `my_dict1`. This is a _side effect._ It is because each variable points to *the same* underlying object (memory blob).
    1. Again, if you _chain-assign_ mutable types, each mutable variable points to *the same* underlying object in memory, since the value is passed from one variable to the next _by reference_:
        ```py
        my_dict1 = {"key": "value"}
        # Copy **by reference**, so all variables point to the same 
        # underlying object.
        my_dict2 = my_dict1
        my_dict3 = my_dict2
        ```
        
        Therefore, the following are *all* `True`:
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
    1. If you _independently assign_ the same literal value to mutable types, however, each mutable variable points to *its own* underlying object in memory, since it is expected to be able to independently mutate the memory it points to:
        ```py
        # **Mutable type:** each variable has an **independent underlying 
        # object**, even though each of those underlying objects has the same
        # value.
        my_dict1 = {"key": "value"}
        my_dict2 = {"key": "value"}
        my_dict3 = {"key": "value"}
        # Therefore, each of these is False because the underlying objects 
        # differ.
        print(my_dict3 is my_dict2)    # False
        print(my_dict2 is my_dict1)    # False
        print(my_dict3 is my_dict1)    # False
        # But, each of these is True because all variables have the same value.
        print(my_dict3 == my_dict2)    # True
        print(my_dict2 == my_dict1)    # True
        print(my_dict3 == my_dict1)    # True
        ```
    1. If you pass a _mutable_ variable to a function, and that function modifies it, the modification will automatically be seen outside the function. This is a _side effect_:
        ```py
        def modify_dict(my_dict):
            my_dict["new_key"] = "new_value"

        my_dict1 = {"key": "value"}
        modify_dict(my_dict1)
        print(my_dict1)  # prints: {"key": "value", "new_key": "new_value"}
        ```
    1. To force a _mutable_ type to be passed _by value_ instead of _by reference_, you can call the `.copy()` method to force a copy of the underlying object to be made. 
        ```py
        my_dict1 = {"key": "value"}
        # Force-copy **by value**, so each variable has its own underlying 
        # object. The `.copy()` method makes an entirely new copy of the 
        # underlying object.
        my_dict2 = my_dict1.copy()
        my_dict3 = my_dict2.copy()
        # Therefore, each of these is False because the underlying objects 
        # differ.
        print(my_dict3 is my_dict2)    # False
        print(my_dict2 is my_dict1)    # False
        print(my_dict3 is my_dict1)    # False
        # But, each of these is True because all variables have the same value.
        print(my_dict3 == my_dict2)    # True
        print(my_dict2 == my_dict1)    # True
        print(my_dict3 == my_dict1)    # True
        ```

1. **_Immutable_ types are passed _by copy_, and do _not_ cause _side effects_.**
    1. If you do `my_int3 = my_int2 = my_int1 = 1`, then change `my_int3`, it does *not* change `my_int2` or `my_int1`, because that would be a side effect. It has no _side effects._
    1. However, if you assign the same value to multiple immutable variables, whether by _chain assignment_ _or_ _independent literal assignment_, the variables are both equal (`var1 == var2` is `True`) _and_ they are the same (`var1 is var2` is `True`), as shown here:
        ```py
        ## **Immutable types:** each variable apparently has the **same 
        # underlying object**, but side effects are not allowed
        my_int1 = 7
        my_int2 = 7
        my_int3 = 7
        # Therefore, each of these is True because the underlying objects are 
        # the same.
        print(my_int3 is my_int2)      # True
        print(my_int2 is my_int1)      # True
        print(my_int3 is my_int1)      # True
        # And, each of these is also True because all variables have the 
        # same value.
        print(my_int3 == my_int2)      # True
        print(my_int2 == my_int1)      # True
        print(my_int3 == my_int1)      # True
        
        # Try the test again, this time like this
        my_int1 = 7
        my_int2 = my_int1
        my_int3 = my_int2
        # Same as above: same underlying object, so each of these is True
        print(my_int3 is my_int2)      # True
        print(my_int2 is my_int1)      # True
        print(my_int3 is my_int1)      # True
        # Same as above: same value, so each of these is True
        print(my_int3 == my_int2)      # True
        print(my_int2 == my_int1)      # True
        print(my_int3 == my_int1)      # True
        print()
        ```

        That's a bit confusing, but the immutability and lack of side effects holds true.
    1. If you pass an _immutable_ variable to a function, and that function modifies it, the modification will _not_ be seen outside the function. There are no side effects. Rather, if you want to see the change outside the function, you must return the modified variable from the function, and reassign it outside the function.
        ```py
        def modify_int(my_int):
            my_int += 1
            return my_int

        my_int1 = 7
        # reassign the returned value to obtain the change from inside the
        # function
        my_int1 = modify_int(my_int1)  
        print(my_int1)  # prints: 8
        ```
    1. To force an _immutable_ type to be passed _by reference_ instead of _by copy_, you can simply wrap the immutable type inside of a mutable type, such as a list, and then pass the mutable wrapper to a function. This way, it gets passed by reference, and the side effect of modifying its contents is automatically visible outside the function:
        ```py
        def modify_immutable_type_hack(var_list):
            var_list[0] += 1  # increment the number inside the first element

        my_int = 10
        my_int_list = [my_int]
        print(my_int_list[0])  # 10
        # Force an immutable type to act mutable by passing it inside a list,
        # which is a mutable type, into a function. This way, the "side effect"
        # of the change to the list being visible outside the function is still
        # seen. This is because the list gets passed **by reference** instead
        # of **by value.**
        modify_immutable_type_hack(my_int_list)
        print(my_int_list[0])  # 11
        print(my_int)          # 10
        ```

        For single numbers, however, it's clearer to just use the return value method above, instead: `my_int1 = modify_int(my_int1)`.

1. You can write a program to automatically identify whether a type is _mutable_ or _immutable_ by looking for and identifying _side effects_. I do this below.
1. Python is _not_ an easy programming language. It has tons of nuances like this. It's just popular, different, and very high level.

All of the test code for the above learning is below.


## 2. List of mutable vs immutable objects in Python

Here's a list of the most common mutable and immutable objects in Python. This list can be obtained by 1) painstakingly searching [Python's official "Built-in Types" reference page](https://docs.python.org/3/library/stdtypes.html) for the words "mutable" and "immutable", _or_ by 2) asking GitHub Copilot (or BingAI or ChatGPT) for it. I did both. The latter is, of course, way faster, and perhaps less error-prone in this case. I verified and updated the list below based on my own findings, and added all quotes, mostly from the official documentation.

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

---

**Stop here if you like. The above is the most important.**

---


## 3. Reassignment

All variables can be reassigned in Python, whether they were previously assigned to mutable or immutable types. However, the behavior of reassignment is different for mutable and immutable types, and cannot be thought of purely in traditional C and C++-like memory terms and understanding. Python is Python, and Python is different.

Coming from C and C++ as my primary languages, the concept of "mutability" in Python is quite confusing. For this and other reasons, I do *not* consider Python to be an "easy" or "beginner" language. It is simply a very powerful "extra high-level" language, is all. It has a *ton* of very nuanced and confusing points. C is more straight-forward and concrete in this regard. (And [C++ is just nuts](https://stackoverflow.com/questions/47002799/what-does-the-ampersand-at-the-end-of-member-function-signature-mean/47003980#comment109357350_47003980)).

In C and C++, my mental model of each variable is that it is a chunk of bytes in memory. When you do this:
```cpp
int var = 0;  // statically allocate bytes for `var`, and mutate them into a 0
var = 7;      // mutate the bits in `var` into a 7 now instead of a 0
```

...you are changing the bytes in `var`'s chunk of memory from bits storing a `0`, to bits storing a `7`. You have "mutated" the memory allocated by that variable, meaning: the chunk of memory which is set apart for it. The _type_ of the variable simply specifies the _"lens"_ (think: looking through a magic glass lens that interprets bits into numbers, letters, etc.), or _interpretation algorithm_, through which you will interpret those bits (ex: `float`, `int`, `char`, etc.).

In Python, however, that is *not* the mental model you should have for variables. **In Python, think of variables as _objects containing pointers to other objects_,** where _everything is an object_, and each object contains a bit specifying whether it is _mutable_ or _immutable_, and _mutable_ variables are passed _by reference_ whereas _immutable_ variables are _passed by value_. Note also that an object is a _very sophisticated dynamically-allocated instance of a class, which manages its own state and chunk of memory_, kind of like a [std container](https://en.cppreference.com/w/cpp/container) in C++.

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
# in it is now "orphaned" and I suspect will be garbage collected, but that 
# level of understanding is beyond me.
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

So, as long as you know the summary in section 1 above, and the list of mutable vs immutable objects in Python in section 2 above, you are good.


## 4. Pass _by reference_ vs pass _by copy_, and _side effects_

What a good Python programmer *does* need to know, however, is whether or not their particular variable type will be passed _by reference_ or _by copy_ when passed to a function. This is a very important distinction, as passing _by reference_ causes _side effects_, which means that changes to the variable in one place will result to changes to that or other variables in other places, such as inside vs outside a function. This is a very important concept in Python, and to me is the main reason why the distinction between mutable and immutable types is important. I don't really care how they work under the hood otherwise.

Again:
1. Passing a **mutable** type to a function causes _side effects_, which means modifications to that variable inside the function _will_ be seen outside the function.
1. Passing an **immutable** type to a function does not cause side effects, which means modifications to that variable inside the function will _not_ be seen outside the function.


## 5. `is` vs `==`

The operator `==` tests for equality of values stored within a variable. The operator `is`, I think, is used to test if two variables refer to the same object in memory. Again, the nuances of how Python does this under-the-hood are beyond me. See my section 1 summary, however, for a bunch of nuanced cases of `is` vs `==`. 

The official Python documentation describes the `is` and `is not` operators under the "Identity comparisons" section of its documentation here: https://docs.python.org/3/reference/expressions.html#is-not: 

> The operators `is` and `is not` test for an object’s identity: `x is y` is true if and only if `x` and `y` are the same object. An Object’s identity is determined using the `id()` function. `x is not y` yields the inverse truth value.

The `id()` function says: https://docs.python.org/3/library/functions.html#id:

> Return the “identity” of an object. This is an integer which is guaranteed to be unique and constant for this object during its lifetime. Two objects with non-overlapping lifetimes may have the same `id()` value.

So, I interpret this to mean that the `id()` is a unique dynamic memory address, or index into a map to one, which is assigned to each object at object creation. When you do `my_int3 = my_int2 = my_int1 = 7`, the `id()` of all 4 of those parts is the same:
```py
my_int3 = my_int2 = my_int1 = 7
print(id(my_int1))  # 140201501393328
print(id(my_int2))  # 140201501393328
print(id(my_int3))  # 140201501393328
print(id(7))        # 140201501393328
```

So, they all appear to be the same underlying object, or blob of memory. 


## 6. Some test code

Here's my test code. Nearly all of the behaviors in my test code were unpredictable to me, since Python is such a dramatically different language from C and C++, and I was unable guess the results of most of these tests prior to running them and doing this learning. I had just about everything wrong. 

[**mutable_vs_immutable_types.py**](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/python/mutable_vs_immutable_types.py) from my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/) repo. 

Note: the test code is too long to paste in this answer, as the Stack Overflow limit is 30000 chars. So, see it at the link above. 

**Sample run and output:**
```none
eRCaGuy_hello_world$ python/mutable_vs_immutable_types.py 
var before modification: True
var is a bool
var after modification:  False

var before modification: 1.0
var is a float
var after modification:  2.0

var before modification: 7
var is an int
var after modification:  8

var before modification: some words
var is a str (string)
var after modification:  some words; some more words

var before modification: [7, 8, 9]
var is a list
var after modification:  [7, 8, 9, 1]

var before modification: {'key1': 'value1', 'key2': 'value2'}
var is a dict
var after modification:  {'key1': 'value1', 'key2': 'value2', 'new_key': 'new_value'}

var before modification: (7, 8, 9)
var is a tuple
var after modification:  (1, 2, 3)

is_mutable(my_bool, True)                                    -->  immutable
is_mutable(my_float, 1.0)                                    -->  immutable
is_mutable(my_int, 7)                                        -->  immutable
is_mutable(my_str, "some words")                             -->  immutable
is_mutable(my_list, [7, 8, 9])                               -->  mutable
is_mutable(my_dict, {"key1": "value1", "key2": "value2"})    -->  mutable
is_mutable(my_tuple, (7, 8, 9))                              -->  immutable

int is immutable
list is mutable

MUTABLE TYPES
False
False
False
True
True
True

IMMUTABLE TYPES
True
True
True
True
True
True

integer types again
True
True
True
True
True
True

True
True
True
True
True
True

False
False
False
True
True
True

How to update immutable vs mutable variables in a function:

7
8

[7, 8, 9]
[7, 8, 9, 1]

10
11
10
```


## References

1. Nearly all of the references are my links and test code above. 
1. This is my own work, but for anyone curious, here's in introductory conversation I had with GitHub Copilot to get me started: 
