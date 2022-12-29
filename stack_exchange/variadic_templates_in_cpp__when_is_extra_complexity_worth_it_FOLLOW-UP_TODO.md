<!--
https://stackoverflow.com/q/73904873/4561887

GS
Sept. to Oct. 2022
-->

Add an entirely new answer to this question: https://stackoverflow.com/q/73904873/4561887

Study and then emphasize and teach when the more-complicated answer (https://stackoverflow.com/a/73904962/4561887) is worth it, and what benefits it adds. 

Here are some notes and quotes to get me started:


=====

NEW, FOLLOW-UP QUESTION I SHOULD PROBABLY ADD/ASK:
- Note: one who can answer this question is at a professional staff-level (L6) software engineer skill level in C++.

GS:

to call an inner func from an outer func, you can use variadic templates (parameter packs), like this:

```cpp
template<typename FuncType, typename... FuncArgs>
void OuterFunc(FuncType innerFunc, FuncArgs... args) {
    innerFunc(args...);
}

int main() {
    OuterFunc(print1, 100);
    OuterFunc(print2, 99.1234, 77);
    OuterFunc(print3, 123, 10.55, "hey you!");

    return 0;
}
```
See my *public Stack Overflow* answer here: [https://stackoverflow.com/a/73904874/4561887](https://stackoverflow.com/a/73904874/4561887). I like it. It's super easy to use and read.

But [this significantly more-complicated and hard-to-read answer](https://stackoverflow.com/a/73904962/4561887) proposes this:

```
template <typename F, typename ...P>
void foo(F &&func, P &&... args)
{
    std::invoke(std::forward<F>(func), std::forward<P>(args)...);
}
```
Can someone walk me through the virtues of the harder answer over my easier answer, and give me your opinion on whether or not the extra complexity of the harder answer is really worth it? Namely:

1. `&&`
2. `std::invoke()`
3. `std::forward<>()`
It is **significantly** harder to understand, and I don't understand the nuances of why it would or should or must be chosen under certain circumstances.

The one thing I see is that passing by *universal reference* (`&&`) can allow non-copyable objects to be passed to the `OuterFunc()`, but beyond that I'm at a loss.

=====











