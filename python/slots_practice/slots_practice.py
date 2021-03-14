#!/usr/bin/python3

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

"""
GOAL:

Learn a little bit about the special Python `__slots__` list, class variables vs. instance
variables, private variables vs public variables, and internal Python variables surrounded by double
underscores (`__some_var__`). Also practice passing and using list args to a function (ex: as
`*args`), and keyword key:value dict args to a function as well (ex: as `**kwargs`).

PYTHON DEFINITIONS:

1. Variables prefixed with a single underscore (`_`) are user-specific **private variables**.
All other variables (NOT beginning with `_`) are therefore, by default, **public variables**.
Ex:
    ```
    _my_private_var = 123
    # vs:
    my_public_var = 123
    ```

1. Variables which begin and end with two underscores (`__some_name__`) are **internal Python
variables** used by the Python interpreter/language. Ex: `__slots__`, `__name__`, `__main__`.

1. Variables outside of all methods inside a class are **class variables**. They are shared among
all objects (instances) of a given class. You can access them inside the class definition in 2 ways:
    ```
    MyClass.class_var
    self.class_var
    ```
  ...and outside the class definition directly as well, so long as they are public, NOT private
  variables. Ex:
    ```
    myClass = MyClass()
    myClass.class_var
    ```

1. Variables inside any class method and which are prefixed with `self.` are **instance variables**.
They have unique values for each instance of a class. For classes which do NOT use the `__slots__`
internal variable shown below, these "instance variables" are stored via a key:value dict, with each
key being the name of the variable (stored and accessed as a _string_). When you use the special
`__slots__` variable manually, however, you can save run-time RAM by having Python store these
instance variable names in a list instead of in a dict!


RUN COMMAND:
    ./slots_practice.py
    # OR
    python3 slots_practice.py

REFERENCES:
1. Slots: https://book.pythontips.com/en/latest/__slots__magic.html
1. Class vs Instance variables: https://realpython.com/lessons/class-and-instance-attributes/
1. Official Python `__slots__` documentation:
   https://docs.python.org/3/reference/datamodel.html?highlight=__slots__#slots
1. [NEED TO STUDY AND READ STILL] https://stackoverflow.com/questions/472000/usage-of-slots


"""

class MyClass():

    # 1. Class variables (shared among all instances of this class--must be defined outside all other
    # class methods)

    # arbitrary variable I made up
    animal = "dragon"

    # special list of all string names of our instance variables
    # __slots__ = ['var1', 'var2']  # <======== does NOT work because it doesn't define 'var3' which we use and need below too!
    __slots__ = ['var1', 'var2', 'var3']  # <======== WORKS!

    # arbitrarily-named, private (prefixed with single `_`) list of the types (stored as strings)
    # for the instance variables specified above
    _slot_types = ['string', 'int', 'list of ints']


    def __init__(self, *args, **kwargs):
        """
        Constructor to create a new MyClass instance.

        Parameters:
            *args:          special syntax to capture a list of all list arguments
            **kwargs:       special syntax to capture a dict of all keyword arguments passed in as
                            key:value pairs (written as `someFunc(key1 = value1, key2 = value2)`
                            when you call the method).

        Returns:
            NA
        """

        # 2. Instance variables (begin with `self.`--these can be defined and/or accessed within ANY
        # method within a class!):
        self.var1 = kwargs['var1']
        self.var2 = kwargs['var2']
        self.var3 = kwargs['var3']

        print("Here are all the dictionary items you passed in!:")
        for key, value in kwargs.items():
            print("  {}: {}".format(key, value))


    def printVariables(self):
        """
        Print all class and instance variables for this class.
        """
        print("Class variables:")
        print("  animal (MyClass.animal) = {}".format(MyClass.animal))
        print("  animal (self.animal)    = {}".format(self.animal)) # alternative way

        print("Instance variables:")
        print("  self.var1               = {}".format(self.var1))
        print("  self.var2               = {}".format(self.var2))
        print("  self.var3               = {}".format(self.var3))


if __name__ == '__main__':
    """
    This runs only if you run this file directly, NOT if you import this file as a module into
    another Python program. That is what this `if` statement does for us here!
    """

    print("instance1:")
    instance1 = MyClass(var1 = "hello", var2 = 710, var3 = [1, 2, 3])
    instance1.printVariables()

    print()

    print("instance2:")
    instance2 = MyClass(var1 = "world", var2 = 18, var3 = [4, 5, 6])
    instance2.printVariables()


"""
SAMPLE OUTPUT:

    $ ./slots_practice.py
    instance1:
    Here are all the dictionary items you passed in!:
      var1: hello
      var2: 710
      var3: [1, 2, 3]
    Class variables:
      animal (MyClass.animal) = dragon
      animal (self.animal)    = dragon
    Instance variables:
      self.var1               = hello
      self.var2               = 710
      self.var3               = [1, 2, 3]

    instance2:
    Here are all the dictionary items you passed in!:
      var1: world
      var2: 18
      var3: [4, 5, 6]
    Class variables:
      animal (MyClass.animal) = dragon
      animal (self.animal)    = dragon
    Instance variables:
      self.var1               = world
      self.var2               = 18
      self.var3               = [4, 5, 6]

"""
