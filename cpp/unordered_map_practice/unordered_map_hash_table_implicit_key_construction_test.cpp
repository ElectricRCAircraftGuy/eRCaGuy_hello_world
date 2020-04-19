/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

GS 
17 Apr. 2020 
Filename: "unordered_map_hash_table_implicit_key_construction_test.cpp"

WORKS!

Run online: https://onlinegdb.com/Hy3c1QYOU

Run locally:
    g++ -Wall -Werror -g3 -std=c++17 -o unordered_map_hash_table_implicit_key_construction_test \
    unordered_map_hash_table_implicit_key_construction_test.cpp && \
    ./unordered_map_hash_table_implicit_key_construction_test

=======
Result:
=======
This is *very insightful!* Attempting to access any key which doesn't already exist 
in a C++ hash table simply CREATES THE KEY AND A DEFAULT VALUE for you RIGHT ON THE SPOT WHERE 
YOU USE IT! This is even the case when you attempt to access a *member* of a value for a key 
which doesn't yet exist!--it will simply create and add the key and a default value right on 
the spot, dynamically, then access the member of the value as you specified. 
Ex: 
    struct myStruct 
    {
        int i1 = 100;
        int i2 = 200;
    };
    std::unordered_map<int, myStruct> numToStructMap; // map an int to a struct 
    numToStructMap[74].i1 = 30; // Creates a new key 74 with value i1 = 30 (set here) and i2 = 200 (default)

References:
1. *****http://www.cplusplus.com/reference/unordered_map/unordered_map/operator[]/
1. http://www.cplusplus.com/reference/unordered_map/unordered_map/find/ 

*******************************************************************************/
// unordered_map::operator[]
#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>

struct myStruct 
{
    int i1 = 100;
    int i2 = 200;
};

int main()
{
    printf("Hello World\n\n");
    
    std::unordered_map<std::string, std::string> mymap;

    mymap["Bakery"]="Barbara";  // new element inserted
    mymap["Seafood"]="Lisa";    // new element inserted
    mymap["Produce"]="John";    // new element inserted
    
    std::string name = mymap["Bakery"];   // existing element accessed (read); name contains "Barbara"
    mymap["Seafood"] = name;              // existing element accessed (written); "Seafood" is mapped to "Barbara"
    
    mymap["Bakery"] = mymap["Produce"];   // existing elements accessed (read/written); "Bakery" is mapped to "John"
    
    name = mymap["Deli"];      // non-existing element: new element "Deli" inserted! `name` should contain 
                               // empty string object since `mymap["Deli"]` has no corresponding value, so it's 
                               // created with a *default value*, which is an empty C++ string object in this 
                               // case!
    
    std::cout << "name = \"" << name << "\"\n";
    printf("name = \"%s\"\n", name.c_str());
    printf("name.empty() = %s\n", name.empty() ? "true" : "false");
    
    mymap["Produce"] = mymap["Gifts"];    // new element "Gifts" inserted, "Produce" written; since the "Gifts" 
                                          // key has no corresponding value, neither does "Produce"
    
    printf("mymap[\"Produce\"].empty() = %s\n", mymap["Produce"].empty() ? "true" : "false");
    printf("mymap[\"Gifts\"].empty() = %s\n", mymap["Gifts"].empty() ? "true" : "false");
    
    printf("\n`Key: value` pairs in mymap:\n"
             "----------------------------\n");
    for (auto& x : mymap) {
        std::cout << x.first << ": " << x.second << std::endl;
    }
    
    
    printf("\n====================\n\n");
    
    std::unordered_map<int, myStruct> numToStructMap; // map an int to a struct 
    
    numToStructMap[37]; // Add a new key with a default struct as its value (default struct contains i1 = 100 and i2 = 200)
    // expect 100 and 200 
    printf("numToStructMap[37].i1 = %i; numToStructMap[37].i2 = %i\n", numToStructMap[37].i1, numToStructMap[37].i2);

    numToStructMap[74].i1 = 30; // Creates a new key 74 with value i1 = 30 (set here) and i2 = 200 (default)
    // expect 30 and 200 
    printf("numToStructMap[74].i1 = %i; numToStructMap[74].i2 = %i\n", numToStructMap[74].i1, numToStructMap[74].i2);
    
    numToStructMap[74].i2 = 40; // Sets i2 of the existing struct of the existing key 74 to 40
    // expect 30 and 40 now 
    printf("numToStructMap[74].i1 = %i; numToStructMap[74].i2 = %i\n", numToStructMap[74].i1, numToStructMap[74].i2);
    

    return 0;
}

/*
EXAMPLE OUTPUT:

    Hello World

    name = ""
    name = ""
    name.empty() = true
    mymap["Produce"].empty() = true
    mymap["Gifts"].empty() = true

    `Key: value` pairs in mymap:
    ----------------------------
    Gifts: 
    Produce: 
    Bakery: John
    Deli: 
    Seafood: Barbara

    ====================

    numToStructMap[37].i1 = 100; numToStructMap[37].i2 = 200
    numToStructMap[74].i1 = 30; numToStructMap[74].i2 = 200
    numToStructMap[74].i1 = 30; numToStructMap[74].i2 = 40
*/




