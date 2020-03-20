/*
hello_world
 - a brief practice file
Gabriel Staples
11 Jan. 2018

References:
  - http://www.cplusplus.com/doc/tutorial/program_structure/
  - C++ standards available in gcc/g++: http://gcc.gnu.org/onlinedocs/gcc/Standards.html
  - Basic C compiling & running: http://www.network-theory.co.uk/docs/gccintro/gccintro_9.html 
  - Basic C++ compiling & running: http://www.network-theory.co.uk/docs/gccintro/gccintro_54.html

To compile and run:
  `g++ -Wall -std=c++11 hello_world.cpp -o hello_world`
  `./hello_world`

To get the intermediate files along with the executable:
(Source: https://www.geeksforgeeks.org/compiling-a-c-program-behind-the-scenes/)
ie: 1) .hh, .cpp C++ files --[preprocessing]--> 
    2) .ii preprocessed C++ files --[compiling]--> 
    3) .s assembly language files --[assembly]-->
    4) .o object (machine code) files --[linking]-->
    #) executable (machine code) file [Done!]
  `g++ -Wall -std=c++11 -save-temps hello_world.cpp -o hello_world`

COMPILE AND RUN ALL IN ONE! <========== EASIEST
    g++ -Wall -std=c++11 -save-temps hello_world.cpp -o hello_world && ./hello_world
COMPILE AND RUN ALL IN ONE, OUTPUTTING EVERYTHING TO ./bin/ <========== MY FAVORITE
    mkdir -p bin && g++ -Wall -std=c++11 -save-temps=obj hello_world.cpp -o ./bin/hello_world && ./bin/hello_world
    - For meaning of -save-temps=obj, see: https://stackoverflow.com/a/46256372/4561887
    - basically, it tells the temp objects to go to the same location as the -o setting!

For multiple files:
  `g++ -Wall -std=c++11 hello_world.cpp file2.cpp file3.cpp -o hello_world`
  `./hello_world`

*/

#include <iostream>


// using namespace std;

int main()
{
    std::cout << "Hello world! ~GS" << std::endl;
    std::cout << "End.\n\n";
}

/*
Sample Output:

Easiest (all intermediate files are generated in same dir as the .cpp source file):

    $ g++ -Wall -std=c++11 -save-temps hello_world.cpp -o hello_world && ./hello_world
    Hello world! ~GS
    End.

My Favorite (all intermediate build files are generated in a "bin" sub-directory):

    $ mkdir -p bin && g++ -Wall -std=c++11 -save-temps=obj hello_world.cpp -o ./bin/hello_world && ./bin/hello_world
    Hello world! ~GS
    End.




*/





