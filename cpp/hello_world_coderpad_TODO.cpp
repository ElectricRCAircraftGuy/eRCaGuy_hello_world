/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
~July 2022

Write a bit about how to use coderpad. Also, explain the default C++ "hello world" code which comes
up in coderpad whenever you open it, as the `auto` word really throws off the fact that `auto
words` is actually `std::initializer_list<std::string> words`!

STATUS: wip/todo

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
1. See my answer here: https://stackoverflow.com/a/75656629/4561887

*/




https://coderpad.io/languages/cpp/ - scroll to bottom

```cpp
#include <iostream>
using namespace std;

// To execute C++, please define "int main()"
int main() {
  auto words = { "Hello, ", "World!", "\n" };
  for (const string& word : words) {
    cout << word;
  }
  return 0;
}

```


// The meaning of `auto words = { "Hello, ", "World!", "\n" };` is
// `std::initializer_list<std::string> words = { "Hello, ", "World!", "\n" };`
// So do this instead!:

```cpp
#include <iostream>
using namespace std;

// To execute C++, please define "int main()"
int main() {
  std::initializer_list<std::string> words = { "Hello, ", "World!", "\n" };
  for (const string& word : words) {
    cout << word;
  }
  return 0;
}

```





/*
Also, from the "Info" button at the top of Coderpad:
(make this a readme!):
hello_world_coderpad_README.md



C++
Running GCC 9.4 (C++20) - IntelliSense is enabled
We run your C++ code with GCC 8. You should define an int main() entrypoint. The gcc compiler is invoked with the following args:

g++ -Wall -fsanitize=address -std=c++17 -pthread \
-lboost_date_time -lboost_regex -lboost_system -lboost_thread -lboost_timer -lboost_filesystem \
-lssl -lcrypto -lmysqlcppconn
Which results in:

Use the C++17 standard
Turn on all warning messages
Compile in debug mode
Warn on memory use-after-free bugs and other memory issues with ASan. If you see an unusual message or segfault, it’s likely ASan picking up a use-after-free or use of uninitialized memory bug in your code.
Link the pthread library
Link a few static boost libraries
We also provide a few libraries:

Boost is provided, with most of its header-only libraries working straight out of the box. Of its statically compiled components, we link to DateTime, Regex, System, Thread, and Timer. If you need more than those, please let us know!

nlohmann/json, a convenient and simple JSON library. To use it on CoderPad, just include "json.hpp" and go nuts:

#include "json.hpp"
#include <iostream>

int main() {
  nlohmann::json j2 = {
    {"hello", "world"}
  };
  std::cout << j2;
}
Catch, a C++ testing library. Catch is a single-header library and very easy to get started with. To use it on CoderPad, simply define a macro and include the header like so:
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? 1 : Factorial(number - 1) * number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
If you do so, you should not define your own main method. You can also read more about Catch’s macros for testing.

Eigen, a library for linear algebra. We provide all of the Eigen modules and header files to the environment. To use it on CoderPad, just include the header that you want and instantiate an object:
#include <iostream>
#include "Eigen/Dense"

using Eigen::MatrixXd;

int main()
{
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;
}
Are there any libraries or settings we missed? Feel free to email us with suggestions!

*/
