<!--
https://stackoverflow.com/q/24793069/4561887
GS
7 Oct. 2022
-->

> What does `&>` do in bash?

Regarding the erroneous `git status 2&>1 > /dev/null`...

> Can someone clarify the man page and explain exactly what is happening with this syntax?

Yes, I can. I'm also trying to understand a variety of behaviors and bits of bash syntax too, so let's go through the statement in question, and some examples in order to gain a better understanding.

## Quick Summary

1. If you just want to **understand the full meaning of the odd/erroneous syntax in question:** `git status 2&>1 > /dev/null`, jump straight to **section 1** below.
1. If you're here just based on the **_title_ of the question itself**: "What does &> do in bash?", jump straight down to **section 2** below. 
1. If you want to have a **quick-reference summary of proper redirection usage in bash**, such as redirecting stderr to stdout via `2>&1`, or redirecting stdout to a file via `>file` or `1>file`, or redirecting stderr to a file via `2>file`, or redirecting _both_ stdout _and_ stderr to a file via `&>file` or `>file 2>&1`, look just at **section 3** below: "3. Summary of proper redirection in bash".
1. If you just want to test your bash knowledge on weird, redundant, overriding, or otherwise non-standard usages of redirection, look at **section 4** below.


## 1. Breakdown of the statement `git status 2&>1 > /dev/null`

In the statement
```bash
git status 2&>1 > /dev/null
```

there are 3 separate parts that break out like this (even though this is not intuitive nor obvious, especially considering that there is no space between the `2` and `&>1` in `2&>1`):
```bash
git status 2    # statement 1
&>1             # statement 2
> /dev/null     # statement 3
```

If you had the following, however, they are all very different than the above. We'll talk about these later in this answer: 
```bash
# separates into **two separate statements**: `2` and `&>1`
2&>1  # `2` is NOT part of `&>1`

# these are all **single statements**, but mean very different things (more on
# these below)
2>&1
2>1
```

1. **Statement 1** (`git status 2`) runs `git status 2`. Here, `2` is a parameter passed to `git status`. Since it's not a valid option, `git status` assumes it to be a path, which can be a file or directory. So, git returns the status of all files named `2`, or of all files within a directory named `2`. As `man git status` shows, a better way to specify paths is to separate options from paths with `--`, like this:
    ```bash
    git status -- 2  # 2 is a file or folder here
    ```

    Obviously, that's not what you're trying to do. :)

1. **Statement 2** (`&>1`) redirects stdout and stderr to a file named `1`. This is also obviously not what you are trying to do. :) The `&>file` syntax redirects all stdout and stderr to `file`. You can read about this [in the bash manual online here](https://www.gnu.org/software/bash/manual/bash.html#Redirecting-Standard-Output-and-Standard-Error), or by running `man bash` and and searching for the section named "Redirecting Standard Output and Standard Error". We'll go over this section of the manual more later. 

    Note that `&>1` (written as `2&>1`--two separate statements: `2` and `&>1`, in your question) is *not* the same syntax nor concept as `2>&1`. The latter, `2>&1`, redirects file descriptor `2` (stderr) to file descriptor `1` (stdout), where the 3 primary file descriptors are:

    1. `0` = `stdin`
    1. `1` = `stdout`
    1. `2` = `stderr`

1. **Statement 3** (`> /dev/null`): this is where it starts to get tricky. This can also be written without the space, as `>/dev/null`. It redirects stdout (file descriptor `1`) to the `/dev/null` Linux pseudofile, which discards any output written to it. Writing `>/dev/null` is exactly identical to `1>/dev/null`, as _file descriptor `1` (stdout) is implied as the default option if not specified,_ as the bash manual states. Read more about it in the ["Redirecting Output" section of the bash manual here](https://www.gnu.org/software/bash/manual/bash.html#Redirecting-Output).

    It starts to get tricky here for two reasons:

    1. First, because the `1` means two different things: in `&>1` the one is a _file_ named "1". This is likely a mistake on the user's part, but that's what it is. In `>/dev/null` there is an implied 1 as in `1>/dev/null`, and that refers to _file descriptor_ 1, which is `stdout`. 
    1. Second, it is tricky because you have redirection overrides going on, where the last one sticks. `&>1` redirects both stdout _and_ stderr to a file named "1", but `1>/dev/null` then redirects stdout to the "/dev/null" file. The latter redirection of stdout overrides the former, so the end result is that `stderr` is redirected to a file named "1" and `stdout` is redirected to the "/dev/null" file. This could have also been written as:
        ```bash
        # redirect stderr to a file named "1", and redirect stdout to the file
        # named "/dev/null" to discard it.
        2>1 1>/dev/null

        # same thing
        &>1 > /dev/null
        ```

The above information is begging for more explanation, so let's explain `&>` more and then give a detailed summary of how to correctly do redirection in bash.


## 2. Just addressing the title of this question: "What does `&>` do in bash?"

As @Casey Jones implies [in his (unfortunately) deleted answer here](https://stackoverflow.com/a/69488994/4561887), I think the bash manual explains it best: https://www.gnu.org/software/bash/manual/bash.html#Redirecting-Standard-Output-and-Standard-Error

From it we learn that all 4 of these syntaxes are nearly identical, with the 1st being recommended over the 2nd, and the 3rd being the more-universal way to do it outside of bash:

```bash
# 4 ways in bash to redirect both stdout and stderr to `file`

# 1. recommended in bash
&>file
# 2. works, but `file` may NOT expand to a number or to `-`. 
>&file

# 3. the universal way to do it in or outside of bash: first redirect stdout to
# file, and then redirect stderr to stdout
>file 2>&1
# 4. exact same as 3 above
1>file 2>&1
``` 

So, `&>file` means "redirect _both_ `stdout` _and_ `stderr` to `file`."

Here is [how the manual phrases it](https://www.gnu.org/software/bash/manual/bash.html#Redirecting-Standard-Output-and-Standard-Error):

> ### 3.6.4 Redirecting Standard Output and Standard Error
>
> This construct allows both the standard output (file descriptor 1) and the standard error output (file descriptor 2) to be redirected to the file whose name is the expansion of _word._
> 
> There are two formats for redirecting standard output and standard error:
> 
> ```bash
> &>word
> ```
>
> and
>
> ```bash 
> >&word
> ```
>
> Of the two forms, the first is preferred. This is semantically equivalent to
>
> ```bash 
> >word 2>&1
> ```
>
> When using the second form, _word_ may not expand to a number or ‘-’. If it does, other redirection operators apply (see Duplicating File Descriptors below) for compatibility reasons.


## 3. Summary of proper redirection in bash

File descriptor reminder:
1. `0` = `stdin`
1. `1` = `stdout`
1. `2` = `stderr`

Good, proper-usage syntax you should use:

```bash
# 1. file descriptor redirection

# redirect stderr to stdout
2>&1
# redirect stdout to stderr
1>&2


# 2. redirection to a file

# 2.A. redirect stdout to `file`
>file
1>file  # (same thing; the 1 is implied above)

# 2.B. redirect stderr to `file`
2>file

# 2.C. redirect BOTH stdout and stderr to `file` (4 ways)
&>file       # recommended in bash      <===
>&file       # not recommended
>file 2>&1   # universal and fine       <===
1>file 2>&1  # exact same as just above <===
```

Examples:
```bash
# print "hey 2 " to stdout.
# - Note: the `"%s "` format specifier gets applied to each input argument
#   thereafter. So, calling `printf "%s " "hello" "world"` is as though you had
#   called `printf "%s %s " "hello" "world"`.
printf "%s " "hey" 2

# redirect stdout to `file`; "file" now contains "hey 2 "
printf "%s " "hey" 2 >file
printf "%s " "hey" 2 1>file  # (same thing)

# redirect stderr to `file`; "file" remains empty since no stderr was printed
printf "%s " "hey" 2 2>file

# redirect BOTH stdout and stderr to `file`
printf "%s " "hey" 2 &>file
printf "%s " "hey" 2&>file        # don't do this! (same thing in this case, 
                                  # but looks awkward without the space before 
                                  # the `&`)
printf "%s " "hey" 2 >file 2>&1   # (same thing)
printf "%s " "hey" 2 1>file 2>&1  # (same thing)
```


## 4. "Weird" examples that we will present as "puzzles" and to teach and test understanding

```bash
# print "hey 2 " to stdout, redirecting stdout to a file named "1", then to "2",
# then to "3", then to "4", then to "5". Ultimately, `>5` overrides all
# previous stdout redirections, resulting in 5 files being created
# (named "1", "2", "3", "4", and "5"), with **only file "5"** containing
# the "hey 2 " text, and all other files being empty. Read the contents of all 
# files all at once with `grep '' *`.
printf "%s " "hey" 2 >1 >2 >3 >4 >5
# OR, exact same thing:
printf "%s " "hey" 2 1>1 1>2 1>3 1>4 1>5

# read the contents of all files so you can see that only file "5" above has
# "hey 2 " in it
grep '' *

# print "hey " to a file named "5", while also creating empty files
# named "1", "2", "3", and "4". Note: `21>1` is a bit nonsensical in this case.
# It redirects file descriptor 21 to a file named "1". That doesn't really do
# anything. All the redirections thereafter redirect file descriptor 1 (stdout)
# to a file with a number for a name, as specified. 
printf "%s " "hey" 21>1 1>2 1>3 1>4 1>5

# print "hey " to a file named "5", while creating empty files
# named "1", "2", "3", and "4". stderr gets redirected to the file named "1",
# but it also ends up empty since no stderr output was produced by this command.
printf "%s " "hey" 2>1 1>2 1>3 1>4 1>5

# Print some error output to a file named "1", since stderr gets redirected to
# it. Stdout gets ultimately redirected to a file named "5", but no stdout
# output is printed since `--invalid_arg` is not a valid argument. The stderr
# error message printed to the file named "1" is:
#       bash: printf: --: invalid option
#       printf: usage: printf [-v var] format [arguments]
printf --invalid_arg "%s " "hey" 2>1 1>2 1>3 1>4 1>5

# print "hey 2 " to a file named "5", while also creating empty files
# named "1", "2", "3", and "4". Initially, both stdout and stderr get
# redirected to the file named "1", via `&>1`, but then the stdout redirection
# gets overridden repeatedly until the last one that "sticks" is the stdout
# redirection to the file named "5" via `1>5`.
printf "%s " "hey" 2 &>1 1>2 1>3 1>4 1>5
printf "%s " "hey" 2&>1 1>2 1>3 1>4 1>5     # (same as above, but even more
                                            # awkward-looking)
printf "%s " "hey" 2&>1 >2 >3 >4 >5         # (same as above)
printf "%s " "hey" 2 &>1 >2 >3 >4 >5        # (same as above)
printf "%s " "hey" 2 >1 2>&1 >2 >3 >4 >5    # (same as above)
printf "%s " "hey" 2 1>1 2>&1 >2 >3 >4 >5   # (same as above; reminder: `1>1` 
        # redirects stdout (file descriptor 1) to a file named "1", whereas
        # `2>&1` redirects stderr (file descriptor 2) to stdout 
        # (file descriptor 1); make sure you understand that by now)

# (NOT the same as above! See this example & description previously a few
# examples up)
printf "%s " "hey" 2>1 1>2 1>3 1>4 1>5
```
