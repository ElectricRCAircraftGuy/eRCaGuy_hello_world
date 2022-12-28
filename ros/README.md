This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# ROS (Robot Operating System)

https://www.ros.org/

You can think about the concept of ROS as an adhoc network of processes communicating with each other over a TCP loopback network within the same computer.
A physical analogy would be a ton of microprocessors (ECUs) in a car on a CAN bus. Even though they are many separate processors and microcontrollers, collectively you can consider them holistically as the car's "computer".
This multi-process node network is in contrast to a single executable for your robot. The benefit is software modularity. You can just rebuild an individual "node" or process which has a dedicated task rather than rebuilding an entire massive executable, when you make a change.
So: multi-process vs multi-threaded. Distributed application vs single executable.
That's ROS in a nutshell.

NOT real-time...is simply a means of easily creating a distributed application.

[WIP]...TODO: finish writing me
