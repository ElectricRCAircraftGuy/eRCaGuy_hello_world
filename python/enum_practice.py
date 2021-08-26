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

from enum import Enum

# ==============================
print("======= EXAMPLE 1 =======\n")

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
print("======= EXAMPLE 2 =======\n")

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


"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/enum_practice.py
    ======= EXAMPLE 1 =======

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

    ======= EXAMPLE 2 =======

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

"""
