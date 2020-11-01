
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Purpose

The purpose of these programs is to learn more about how floating point (`float` or `double`) error propagates, increases, and changes under different scenarios and circumstances. 

Ex: what happens if you have a `double time_sec` value that you add 1 nanosecond (`1e-9` sec) to repeatedly? At what point will you have introduced 1 nanosecond or more of error, just by repeatedly adding 1 nanosecond? The problem is that floating point cannot perfectly represent base-10 numbers, so it has to truncate at some point, meaning that each time you add a perfect base-10 number to a `float` or `double`, which are stored in a binary base-2 number system, you get an _imperfect_ base-2 number which introduces error. 


# Instructions

The data produced by these programs is rather large (dozens to hundreds of megabytes), so it will be stored in this other repo instead: [eRCaGuy_hello_world_data](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world_data). 

In order for the _symbolically-linked_ [data](data) folder here to properly work, be sure to clone the **eRCaGuy_hello_world_data** repository into the same directory as you have this **eRCaGuy_hello_world** repo. They should be at the same level in your file system.
