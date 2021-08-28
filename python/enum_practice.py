#!/usr/bin/python3

"""
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Aug. 2021

Demonstrate how to use Enums (Enum class objects) in Python.

References:
1. [Official Python3 documentation] https://docs.python.org/3/library/enum.html

Run command:

    ./enum_practice.py

  OR:

    python3 enum_practice.py


"""

from enum import Enum, IntEnum

# ==============================
print("======= EXAMPLE 1: enum basics, incl. member attributes =======\n")

# Create an enum class called "Fruit", with the following enum **names** and **values**
# inside of it.
class Fruit(Enum):
    APPLE = 1
    PEAR = 2
    BANANA = 3
    KIWI = "kiwi"
    LEMON = "lemon"

# Note: the `.value` member variable contains the enum's assigned value, which can be an integer,
# string, etc. The official documentation (link above) states:
#
# """
# Note: Enum member values
#
# Member values can be anything: int, str, etc.. If the exact value is unimportant you may use auto
# instances and an appropriate value will be chosen for you. Care must be taken if you mix auto with
# other values.
# """

# Note: for the % print notation in Python, follow the C & C++ `printf()` documentation here:
# http://www.cplusplus.com/reference/cstdio/printf/

fruit = Fruit.APPLE
print("enum scoped name = %-15s enum name = %-10s enum value = %s" % (fruit, fruit.name, fruit.value))

fruit = Fruit.PEAR
print("enum scoped name = %-15s enum name = %-10s enum value = %s" % (fruit, fruit.name, fruit.value))

fruit = Fruit.BANANA
print("enum scoped name = %-15s enum name = %-10s enum value = %s" % (fruit, fruit.name, fruit.value))

fruit = Fruit.KIWI
print("enum scoped name = %-15s enum name = %-10s enum value = %s" % (fruit, fruit.name, fruit.value))

fruit = Fruit.LEMON
print("enum scoped name = %-15s enum name = %-10s enum value = %s" % (fruit, fruit.name, fruit.value))

print()
print(fruit.__dict__) # see what all is inside of the fruit **Enum class**.
print("---")
print(fruit._value_)
print(fruit.value) # same as above, but more-commonly-used
print(fruit._name_)
print(fruit.name)  # same as above, but more-commonly-used
print(fruit.__objclass__)
print("---")
print(fruit._value_ is fruit.value)  # See if these "values" truly are the same type
print(fruit._value_ == fruit.value)  # See if these "values" represent the same values
print("---")
print(fruit)
print(str(fruit))  # same as above

print()
print(fruit.__objclass__)
print(Fruit)        # same as above
print(type(fruit))  # same as above in this case
print()

# ==============================
print("======= EXAMPLE 2: enum multi-class inheritance, and iteration =======\n")

# Note: just like with any class, your custom Enum class can inherit from other class types too,
# such as `int` or `str`, in addition to `Enum`. If you inherit from `str` as well, it forces
# all of your "values" in the enum to be of type `str`, even when they look like integers.
class StrEnum(str, Enum):
    ENUM1 = "hey"
    ENUM2 = "how"
    ENUM3 = "are"
    ENUM4 = "you?"
    # NB!: since this Enum class also inherits from the `str` class, this value gets stored as the
    # **string** "1234" even though it looks like an integer!
    ENUM5 = 1234

strEnum = StrEnum.ENUM5
print(strEnum.value*2) # prints the **string** "1234" twice in a row, so you will see "12341234"

# How to **iterate over an entire enum class** (let's also prove the values are strings too):

print()
for enum in StrEnum:
    print("%-15s %8s = %-8s type(enum.value) is str? %s" % (enum, enum.name, enum.value,
        type(enum.value) is str))

print()
for enum in Fruit:
    print("%-15s %8s = %-8s type(enum.value) is str? %s" % (enum, enum.name, enum.value,
        type(enum.value) is str))
print()

# And, a few more prints for good measure. Here are 2 ways to access the enum:

# 1. Access the enum **via a variable** (`fruit`) which is of this type
fruit = Fruit.APPLE
print("%-15s %8s = %-8s type(fruit.value) is str?       %s" % (fruit, fruit.name, fruit.value,
    type(fruit.value) is str))

# OR 2. Access an enum **directly via its scoped class name** (ex: `Fruit.APPLE`).
# The output is the same as above!
print("%-15s %8s = %-8s type(Fruit.APPLE.value) is str? %s" % (Fruit.APPLE, Fruit.APPLE.name,
    Fruit.APPLE.value, type(Fruit.APPLE.value) is str))

print()

# ==============================
print("======= EXAMPLE 3: enum comparisons, with regular enums, string enums, and integer " +
      "enums =======\n")

# REGULAR ENUMS:
# Regular enums are Enum types, NOT string types, so they are NOT equal to enums or strings.
#
# STRING ENUMS:
# However, when you inherit from both the `str` AND `Enum` classes you get the `str` implementation
# of `__eq__`(), which means `strEnum.COLOR1 == "red"` returns True, instead of False like it would
# do for regular enums.
#
# INTEGER ENUMS:
# Similar behavior exists for the `IntEnum` class, which is the same as inheriting from both the
# `int` and `Enum` classes. Therefore `intEnum` types can act like both enums AND integers, kind of
# like enums in C, but NOT enum classes in C++ (unless cast to `int`s).
# - See also: https://docs.python.org/3/library/enum.html#intenum

# A regular enum: inherits from the `Enum` class
class regularEnum(Enum):
    COLOR1 = "red"   # value "red" is of type `str`
    COLOR2 = "blue"  # value "blue" is of type `str`
    COLOR3 = 7       # value 7 is of type `int`

# A string enum: inherits from the `str` and `Enum` classes
class strEnum(str, Enum):
    COLOR1 = "red"   # value "red" is of type `str`
    COLOR2 = "blue"  # value "blue" is of type `str`
    COLOR3 = 7       # value 7 is of type `str`  <==== NOTICE THIS ONE IS A str TOO!


# An integer enum: inherits from the `int` and `Enum` classes
class intEnum1(int, Enum):
    # COLOR1 = "red"   # ValueError: invalid literal for int() with base 10: 'red'
    COLOR1 = 9
    COLOR2 = 8
    COLOR3 = 7

# OR (same thing as above, I think) an integer enum inherits from the `intEnum` class
class intEnum2(IntEnum):
    # COLOR1 = "red"   # ValueError: invalid literal for int() with base 10: 'red'
    COLOR1 = 9
    COLOR2 = 8
    COLOR3 = 7

print("Enums themselves are NOT strings or integers! They are of type enum!")
print(type(regularEnum.COLOR1) is str) # False
print(type(regularEnum.COLOR2) is str) # False
print(type(regularEnum.COLOR3) is int) # False
print(type(regularEnum.COLOR1))
print(type(regularEnum.COLOR2))
print(type(regularEnum.COLOR3))
print()

print("However, their **values** can be `str` or `int` types")
print(type(regularEnum.COLOR1.value) is str) # True, its value is a string
print(type(regularEnum.COLOR2.value) is str) # True, its value is a string
print(type(regularEnum.COLOR3.value) is int) # True, its value is an integer
print("types of their values can be `str` or `int`")
print(type(regularEnum.COLOR1.value))
print(type(regularEnum.COLOR2.value))
print(type(regularEnum.COLOR3.value))
print("types of their names are `str`")
print(type(regularEnum.COLOR1.name))
print(type(regularEnum.COLOR2.name))
print(type(regularEnum.COLOR3.name))
print()

print("Therefore, since regular enums are enums, NOT strings or ints, the following are all False")
print(regularEnum.COLOR1 == "red")   # False
print(regularEnum.COLOR2 == "blue")  # False
print(regularEnum.COLOR3 == 7)       # False
print()

print("BUT, the strEnum is different! Only the last one is False")
print(strEnum.COLOR1 == "red")   # True
print(strEnum.COLOR2 == "blue")  # True
print(strEnum.COLOR3 == 7)       # False
print("...and this is True")
print(strEnum.COLOR3 == "7")     # True
print()

print("And, integer enums can compare as integers too, as shown here")
print("intEnum1:")
print(intEnum1.COLOR1 == 9)   # True
print(intEnum1.COLOR2 == 8)   # True
print(intEnum1.COLOR3 == 7)   # True
print("intEnum2:")
print(intEnum2.COLOR1 == 9)   # True
print(intEnum2.COLOR2 == 8)   # True
print(intEnum2.COLOR3 == 7)   # True
print("intEnum1 compared to intEnum2:")
print(intEnum1.COLOR1 == intEnum2.COLOR1)     # True
print(intEnum1.COLOR2 == intEnum2.COLOR2)     # True
print(intEnum1.COLOR3 == intEnum2.COLOR3)     # True
print("BUT, regular enums do NOT compare as integers even when they store integer values, so " +
      "this is False!")
print(regularEnum.COLOR3 == intEnum2.COLOR3)  # False! Even though both of these have integer values
                                              # equal to 7, this is False because a regular enum
                                              # is an enum type, NOT an integer type.
print("...these are all True though (both of their integer values are 7)")
print(regularEnum.COLOR3.value == intEnum2.COLOR3.value)  # True
print(regularEnum.COLOR3.value == 7)                      # True
print(intEnum2.COLOR3.value == 7)                         # True
print()

print("type information (just for general awareness):")
print(type(intEnum1.COLOR1))
print(type(intEnum2.COLOR1))
print(type(intEnum1))
print(type(intEnum2))
print()


"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./enum_practice.py
    ======= EXAMPLE 1: enum basics, incl. member attributes =======

    enum scoped name = Fruit.APPLE     enum name = APPLE      enum value = 1
    enum scoped name = Fruit.PEAR      enum name = PEAR       enum value = 2
    enum scoped name = Fruit.BANANA    enum name = BANANA     enum value = 3
    enum scoped name = Fruit.KIWI      enum name = KIWI       enum value = kiwi
    enum scoped name = Fruit.LEMON     enum name = LEMON      enum value = lemon

    {'_value_': 'lemon', '_name_': 'LEMON', '__objclass__': <enum 'Fruit'>}
    ---
    lemon
    lemon
    LEMON
    LEMON
    <enum 'Fruit'>
    ---
    True
    True
    ---
    Fruit.LEMON
    Fruit.LEMON

    <enum 'Fruit'>
    <enum 'Fruit'>
    <enum 'Fruit'>

    ======= EXAMPLE 2: enum multi-class inheritance, and iteration =======

    12341234

    StrEnum.ENUM1      ENUM1 = hey      type(enum.value) is str? True
    StrEnum.ENUM2      ENUM2 = how      type(enum.value) is str? True
    StrEnum.ENUM3      ENUM3 = are      type(enum.value) is str? True
    StrEnum.ENUM4      ENUM4 = you?     type(enum.value) is str? True
    StrEnum.ENUM5      ENUM5 = 1234     type(enum.value) is str? True

    Fruit.APPLE        APPLE = 1        type(enum.value) is str? False
    Fruit.PEAR          PEAR = 2        type(enum.value) is str? False
    Fruit.BANANA      BANANA = 3        type(enum.value) is str? False
    Fruit.KIWI          KIWI = kiwi     type(enum.value) is str? True
    Fruit.LEMON        LEMON = lemon    type(enum.value) is str? True

    Fruit.APPLE        APPLE = 1        type(fruit.value) is str?       False
    Fruit.APPLE        APPLE = 1        type(Fruit.APPLE.value) is str? False

    ======= EXAMPLE 3: enum comparisons, with regular enums, string enums, and integer enums =======

    Enums themselves are NOT strings or integers! They are of type enum!
    False
    False
    False
    <enum 'regularEnum'>
    <enum 'regularEnum'>
    <enum 'regularEnum'>

    However, their **values** can be `str` or `int` types
    True
    True
    True
    types of their values can be `str` or `int`
    <class 'str'>
    <class 'str'>
    <class 'int'>
    types of their names are `str`
    <class 'str'>
    <class 'str'>
    <class 'str'>

    Therefore, since regular enums are enums, NOT strings or ints, the following are all False
    False
    False
    False

    BUT, the strEnum is different! Only the last one is False
    True
    True
    False
    ...and this is True
    True

    And, integer enums can compare as integers too, as shown here
    intEnum1:
    True
    True
    True
    intEnum2:
    True
    True
    True
    intEnum1 compared to intEnum2:
    True
    True
    True
    BUT, regular enums do NOT compare as integers even when they store integer values, so this is False!
    False
    ...these are all True though (both of their integer values are 7)
    True
    True
    True

    type information (just for general awareness):
    <enum 'intEnum1'>
    <enum 'intEnum2'>
    <class 'enum.EnumMeta'>
    <class 'enum.EnumMeta'>

"""
