
GS  
26 Sept. 2020  

See: my code here: [function_overloading_on_input_param_array_size](https://onlinegdb.com/Sk3bw8aHD)


Let's see how using a regular function with an array ptr and size as input params, vs template magic which statically knows the array's size, affects program size.

I hypothesize that using the template magic is a bad idea and will result in programs which explode in size if the function is called on a ton of different array sizes, whereas the regular function will be fine, even if inlined, since at some large call quantity to that function, the compiler will decide not to inline. Let's see.

Results:

See the bottom of "regular_func.cpp".

Running the code on 10 different arrays of increasing sizes has a total program footprint of 2759 bytes. Increasing it to 100000 arrays still has a program footprint of only 2759 bytes. 

Inlining the function *decreases* this footprint, oddly enough, to 2695 bytes for any array size. 


See the bottom of "template_func.cpp" too.

This code is much harder to use, since it must know the array size at compile time, and can NOT accept any size at run-time, unlike the regular_func.cpp version. Also, running the code on 10 different arrays has a total program footprint of 2879 bytes, but increasing to even just 100 arrays increases that to 5039 bytes, for a total increase of (5039 - 2879)/90 added = 24 bytes per new (array size) function call. This means every new array size requires the template to create a brand-new function definition to statically handle an array of that new size. This results in major unneccessary code bloat and usage complexity, while having the sole benefit of not having to pass in the array size as an extra parameter. 

I strongly recommend using a regular function over this function template version which overloads on input parameter array length.

Note also that the `inline` version of the regular function had a smaller memory footprint than the non-inline version, so I recommend it as well in this particular case. You will have to do your own checks on the effect of `inline`, however, for your own functions of different complexity.
