#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

By Gabriel Staples and George
Written 11 March 2022 12:21:56 PM MST

Description:
Print "Hey George", with the index number first, 10 times.

Contributed to my code repository 8 Apr. 2022 in memory of my wife's grandpa, George, who married
and sealed us. He died 23 March 2022, just 12 days after he and I wrote this code together. At the
time he died he was 88 years old, just 2 days before his 89th birthday. We went to visit him in Los
Alamos, NM, and he asked what I do. He knows virtually nothing about computers and technology, not
even what the internet is really nor what a router is. He can hardly use email with assistance, and
he still has a flip phone.

I talked briefly about programming and said, "You know what! Let me just show you." He and I then
sat down together in some chairs in his master bedroom, with him in a white button up dress shirt
and nice jeans, and on oxygen with tubes in his nose, and we wrote this code together and I talked
about programming, "for" loops, and how all computers and technology are built up in chunks of code
and building blocks, just like nails and boards in a house. I said, "the problem with programming
and software architecture, however, is that sometimes when building your house of software, you
need a nail that doesn't exist yet, and you have to pause to go make the 'nail'. But then you
realize you need the raw iron to make the nail, and a forge to melt the iron to make the nail, and
the wood to heat it, and you need to go find, borrow, or make all of those things too. Something
that seems so simple on the outside to the untrained observer can take weeks or months or more to
build up a little at a time in code." He was in the construction business in his life, so I think
he could understand the analogy of building software to building a house.

His mind was blown. He asked if I thought self-driving cars were really coming (I work as a senior
embedded software engineer on self-driving cars at Cruise right now; see:
https://www.getcruise.com/), and I said "yes". He said, "I'd never trust one of those things to
drive me around", and I said, "I know, but they're coming. Just as surely as the horse and buggy
were replaced by cars, regular cars will be replaced by self-driving cars." I said, "that doesn't
mean all self-driving cars won't have a steering wheel. I think most cars will continue to have a
steering wheel, at least for the next 100 years or so, to allow drivers to drive them manually when
they want to feel in control, or when they want to go off-roading or just have fun with them, but
most if not all cars will be self-driving within 100 years." Again, his mind was blown. He said he
didn't think he'd get in one. We agreed that some people would just need to die off to make this
happen, as older generations passing away is all part of the process of progression.

I mentioned that I saw a presentation once at AFRL (Air Force Research Laboratory) that when the
automobile was first invented, they were limited to a max speed of 5 mph in New York City, and a
flag person had to walk before the automobile saying, "An automobile is coming! An automobile is
coming." A second flag bearer had to walk behind the car as well, for "safety", to protect the
horses and buggies from this unruly beast of a machine which certainly could not be trusted because
it didn't eat nor drink nor have a mind of its own. It was **dangerous!** Anyway, similar opinions
and inhibitions sometimes exist about the self-driving car today. But, they will pass. Electric
charge stations will be build. Infrastructure will be built, and even in 30 years self-driving cars
will be fairly common-place in many large cities throughout the world.

Grandpa George said he was ready to pass away, and looked forward to dying. He wanted to be with his
wife again. He was ready to go. I put my computer away and we had a nice visit. We had printed "Hey
George" 10 times to the computer screen in Python. May he rest in peace and find love in the arms
of his wife, and his Savior, Jesus Christ, who he probably has not seen yet, but certainly will see
at some point in the future.

Enjoy watching "Hey George" print 10 times.

Disclaimer: nothing in this article is from Cruise. These are my own beliefs, opinions, and words
and are not endorsed by nor supported by my employer. This is my own personal code repository and
is not owned by Cruise, nor affiliated with Cruise in any way.


Run command:
```bash
./hello_george.py
# OR
python3 hello_george.py
```


References:
1. Python f-strings / f-format strings: https://realpython.com/python-f-strings/

"""

for i in range(10):
    print(f"{i}: Hey George")


"""

Sample output:

    eRCaGuy_hello_world/python$ ./hello_george.py
    0: Hey George
    1: Hey George
    2: Hey George
    3: Hey George
    4: Hey George
    5: Hey George
    6: Hey George
    7: Hey George
    8: Hey George
    9: Hey George
"""
