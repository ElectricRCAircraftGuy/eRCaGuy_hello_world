<!--
GS: 
https://unix.stackexchange.com/a/119485/114401

I passed the following as an edit suggestion on 13 Oct. 2022. Hopefully it gets approved!
-->


`cat` concatenates files given as arguments on the command line and prints the concatenated output to standard output. It reads bytes one-at-a-time and by default does not perform any interpretation of the bytes it reads.

In your first example, you are redirecting stdout to a file, which is why you get a new file.

In your second example, the bytes are written to the terminal, and it is _the terminal_ which is interpreting sequences of characters as control sequences for the terminal. This is why you get unusual behaviour on your terminal. It has nothing to do with `cat` per se. `cat` doesn't know what you are going to do with its output. You might be sending it through a pipe to another program to interpret/process/print it or which passes it to an audio driver to play "Singing in the rain".

So, following the Unix philosophy: 

> do one thing, do one thing only, but do it well

`cat` should not attempt to guess or interpret what you are trying to do.

---

From [@Kiwy's comment below](https://unix.stackexchange.com/questions/119480/why-and-how-did-using-cat-on-binary-files-mess-up-the-terminal/119485#comment187518_119485) (fixed for grammar):

> does this mean that if you `cat` a binary file which contains in plain-text instructions like `rm -rf`, this could be interpreted?

Yes and no. Let me explain:

No: if you `cat` to a terminal, because it (the terminal software) is sending the output to your screen, or interpreting control sequences (it is emulating an old piece of hardware ie. *a teletype device*).

_but_:

Yes: if you `cat` to a pipe and the program receiving can interpret the characters as commands.

Look at this for example: 

```bash
cat anyOldShellScript | bash
``` 

In this example, `bash` will interpret what it gets as commands, and therefore run the characters `rm -rf` if they exist in that content passed to the pipe by `cat`. 
