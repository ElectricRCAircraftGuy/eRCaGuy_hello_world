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

"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./enum_practice.py
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

"""
