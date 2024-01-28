<!--
GS
Jan. 2024

1. https://stackoverflow.com/q/15292391/4561887
2. https://stackoverflow.com/q/7151311/4561887
3. [most views. so answer here!] https://stackoverflow.com/q/2928584/4561887 
-->

This is the only answer here which performs _multi-process_ (like multi-threaded) search in order to dramatically speed up big `git grep` searches. I'll also cover a variety of tools and scenarios not covered in any other answer here. 

_This should work in Windows, Mac, and Linux. Tested on Windows 11 in Git Bash, and on Linux Ubuntu 22.04._

For Windows, [use](https://github.com/BurntSushi/ripgrep/issues/411#issuecomment-1917413008) the Git Bash Linux-like terminal that comes with [Git for Windows](https://gitforwindows.org/). You can also use the MSYS2 terminal. 

Here are my installation instructions for those terminals in Windows:
1. [Installing Git for Windows](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/issues/27#issue-1950880578)
2. [Stack Overflow: Installing & setting up MSYS2 from scratch, including adding all 7 profiles to Windows Terminal](https://stackoverflow.com/a/77407282/4561887)


## All about searching (via `grep` or similar) in your git repositories


## 1. Search the tips of all branches in a git repository

This answers [the main question here](https://stackoverflow.com/q/15292391/4561887): 

> Is it possible to perform a 'grep search' in all the branches of a Git project?

Here are the answers on how to search for `'my regex search'` in all branches. Note that the `time` command in the front is just to time how long it takes. You can optionally remove that part. Here are the solutions:

```bash
# ---------------------------------------------
# 1. Search all local branches
# ---------------------------------------------

# Search all files and folders in all local branches
time git branch | awk '{print $NF}' \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {}

# Search only these files and folders in all local branches
time git branch | awk '{print $NF}' \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {} \
    -- "path/to/my_file.c" "path/to/my_folder"

# ---------------------------------------------
# 2. Search all remote branches of all remotes
# ---------------------------------------------

# A. Fetch all remote branches of `--all` remote repositories, to ensure that 
# your locally-stored remote-tracking branches are all up-to-date.
git fetch --all  

# B. Now perform the search

# Search all files and folders in all remote branches
time git branch -r | awk '{print $NF}' \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {}

# Search only these files and folders in all remote branches
time git branch -r | awk '{print $NF}' \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {} \
    -- "path/to/my_file.c" "path/to/my_folder"

# ---------------------------------------------
# 3. Search all local **and** remote branches
# ---------------------------------------------

# A. Fetch all remote branches of `--all` remote repositories, to ensure that
# your locally-stored remote-tracking branches are all up-to-date.
git fetch --all

# B. Now perform the search

# Search all files and folders in all local and remote branches
time git branch -a | awk '{print $NF}' \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {}

# Search only these files and folders in all local and remote branches
time git branch -a | awk '{print $NF}' \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {} \
    -- "path/to/my_file.c" "path/to/my_folder"
```

The output of the above commands is in this form:
```
branch_name:path/to/file:line_number:line of text containing the match in it
```

Example:
```
main:some_file.c:123:    myFunction();
```


#### Explanation of the commands above

1. `git branch` lists all local branches
1. `git branch -r` lists all locally-stored, remote-tracking branches
1. `git branch -a` lists all local and remote branches
1. `awk '{print $NF}'` prints only the last field (column) of each line, which is the branch name. `$NF` means "Number of Fields", so this grabs the last field (column). This removes the leading spaces before the branch names, as well as the `*` character in front of the current branch name.
1. `xargs -P "$(nproc)" -I {}` runs the command command following it in parallel, with 1 argument (branch name, in this case) per process, and with the number of processes allowed to run at once equal to the number of processors on your machine (`-P "$(nproc)"`). This is the key to speeding up the search. 

    The `-I {}` option tells `xargs` to replace `{}` in the `git --no-pager grep -n 'my regex search' {}` command which follows with the argument (branch name, in this case) passed to `xargs` from `git branch`. 

    The `--` part after `git grep` is how you tell `git grep` that all of the following arguments after that point are file or folder paths, and not more options.

    To show that using parallel processing via `-P "$(nproc)"` speeds up `git grep`, I ran a test search in a medium-sized repository (\~100 MB in the .git dir) both with and without parallelization, and here are the results. I was searching for the fixed string (`-F`) `STATIC_ASSERT(`:

    ```bash
    # 0.440 sec on Linux Ubuntu 22.04       0.564 sec on Windows 11 in Git Bash
    # With parallelization (I have 20 logical cores on my Dell Precision 
    # 5570 laptop):
    time git branch | awk '{print $NF}' \
        | xargs -P "$(nproc)" -I {} git --no-pager grep -n -F 'STATIC_ASSERT(' {}

    # 1.840 sec on Linux Ubuntu 22.04       1.316 sec on Windows 11 in Git Bash
    # No parallelization: 
    time git branch | awk '{print $NF}' \
        | xargs -I {} git --no-pager grep -n -F 'STATIC_ASSERT(' {}
    ```

1. `git --no-pager grep -n 'my regex search' {}` searches for the regex (regular expression) `'my regex search'` in the branch name which comes from the output of `git branch | awk '{print $NF}'` and is inserted (by `xargs`) into the `git grep` command in place of the `{}` characters. 

    Ie: `xargs` swaps out the `{}` chars for the branch name there. 

    The `-n` option tells `git grep` to print the line number of each match.
    
    The `--no-pager` option is used to prevent the `less` pager from being used, which otherwise disables echo in your terminal and causes it to no longer display characters you type. See my question and this answer by @wjandrea here: [Git Grep sometimes makes terminal stop showing typed commands](https://stackoverflow.com/a/77904031/4561887)


## 2. Search in all commits of a git repository

`git rev-list --all`, as shown [in the main answer by @VonC](https://stackoverflow.com/a/15293283/4561887), lists all commits reachable from any branch or tag in the whole repository. To search _all_ commits, therefore, not just the head commit at the tip of each branch name, we will use `git rev-list --all` instead of `git branch`:

```bash
# Search all commits (reachable from any branch or tag) in the whole repository
time git rev-list --all \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {}

# Search only these files and folders in all commits (reachable from any branch 
# or tag) in the whole repository
time git rev-list --all \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {} \
    -- "path/to/my_file.c" "path/to/my_folder"
```

Speed tests: 

Performing this search in the same \~100 MB repository as above, which has `git log --oneline | wc -l` = 154 commits, by the way, I get the following speed test results with and without parallelization:
```bash
# With parallelization.
# 12.835 sec on Linux Ubuntu 22.04      35.808 sec on Windows 11 in Git Bash
time git rev-list --all \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'STATIC_ASSERT' {}

# No parallelization.
# 58.482 sec on Linux Ubuntu 22.04      1min 53.929sec on Windows 11 in Git Bash 
time git rev-list --all \
    | xargs -I {} git --no-pager grep -n 'STATIC_ASSERT' {}
```


## 3. Search in just a specified list of branches or commits

```bash
# ---------------------------------------------
# 1. Search in branch/commit HEAD, which is all checked-in and committed changes 
#    in the current branch
# ---------------------------------------------

# Search all files and folders of the committed contents of the current branch
git grep -n 'my regex search'

# Search only these files and folders
git grep -n 'my regex search' -- "path/to/my_file.c" "path/to/my_folder"

# ---------------------------------------------
# 2. Search in a specified list of branches or commits
# ---------------------------------------------

# Search all files and folders just in branch `my_branch` and `commit1` and 
# `commit2`
git grep -n 'my regex search' my_branch commit1 commit2

# Search only these files and folders
git grep -n 'my regex search' my_branch commit1 commit2 \
    -- "path/to/my_file.c" "path/to/my_folder"

# ---------------------------------------------
# 3. Search in this range of commits
# ---------------------------------------------

# Search all commits over the range `commit_start` to `commit_end`, 
# NOT including `commit_start`, but including `commit_end`
time git rev-list commit_start..commit_end \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {}

# Search all commits over the range `commit_start` to `commit_end`, 
# including both `commit_start` and `commit_end`
time git rev-list commit_start~..commit_end \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {}

# Search only these files and folders in this range of commits
time git rev-list commit_start~..commit_end \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {} \
    -- "path/to/my_file.c" "path/to/my_folder"
```


## 4. Search just the current file-system / checked-out branch

To search just in the current file system, but *not* in the git history, here are the best techniques. The "current file system" includes the current branch plus any changes or new files not yet committed, but none of the other branches or past commits. 

First, [install ripgrep (`rg`)](https://github.com/BurntSushi/ripgrep?tab=readme-ov-file#installation), which is the world's fastest grep:
1. For Windows: see my Q&A: [How to install ripgrep on Windows?](https://stackoverflow.com/a/76666895/4561887)
1. For Linux Ubuntu or similar: 
    1. Get the latest release URL here: https://github.com/BurntSushi/ripgrep/releases
    1. Use that URL below:
        ```bash
        curl -LO https://github.com/BurntSushi/ripgrep/releases/download/14.1.0/ripgrep_14.1.0-1_amd64.deb
        sudo dpkg -i ripgrep_14.1.0-1_amd64.deb
        ```

Now, here are some techniques:

```bash
# ----------------------------------------------------------
# Search all files and folders in the current file system
# ----------------------------------------------------------

# Fastest: ripgrep
time rg 'my regex search'               # regular expression search
time rg -F 'my fixed string'            # fixed string search

# Slowest
time grep -rn 'my regex search'         # regular expression search
time grep -rnF 'my fixed string'        # fixed string search

# ----------------------------------------------------------
# Search only these files and folders in the current file system
# ----------------------------------------------------------

# Fastest: ripgrep

# regular expression search
time rg 'my regex search' -- "path/to/my_file.c" "path/to/my_folder"
# fixed string search
time rg -F 'my fixed string' -- "path/to/my_file.c" "path/to/my_folder"

# Slowest

# regular expression search
time grep -rn 'my regex search' -- "path/to/my_file.c" "path/to/my_folder"
# fixed string search
time grep -rnF 'my fixed string' -- "path/to/my_file.c" "path/to/my_folder"
```

Note that the following is *not* a technique to search the current file-system! `git grep`, rather, searches the _git history_, _not_ the current file system:
```bash
# git grep: searches over all **committed** changes in HEAD
time git grep -n 'my regex search'      # regular expression search
time git grep -nF 'my fixed string'     # fixed string search
```

Speed tests on Linux Ubuntu 22.04 in my \~100 MB repository:
```bash
# Fastest: ripgrep
# 0.014 sec avg.
time rg -F 'STATIC_ASSERT('

# git grep [not quite the same thing; see above; but shown here for 
# speed comparison]
# Next fastest. 
# 0.013 sec avg.
time git grep -nF 'STATIC_ASSERT('

# Slowest
# 0.027 sec avg.
time grep -rnF 'STATIC_ASSERT('
```


## 5. Find only where a certain string _changed_, not just where it is present

See [the "pickaxe" answer by @VonC](https://stackoverflow.com/a/2928721/4561887).


## 6. Alternative forms, and additional explanations

This:
```bash
# works
time git rev-list --all \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {}
```

Can also be done like this:
```bash
# works; same as above
time git rev-list --all \
    | xargs -n 1 -P "$(nproc)" git --no-pager grep 'my regex search'
```

But, there's a big problem there with expanding from the last one. If you add `-- "path/to/my_file.c" "path/to/my_folder"` to the end of the last command above, it does *not* work! This is because the last form above automatically sticks one (due to `-n 1`) commit hash from the `git rev-list --all` output onto the end of the `git --no-pager grep 'my regex search'` command, meaning that it will be tacked on _after_ the `-- "path/to/my_file.c" "path/to/my_folder"` part.

So, this:
```bash
# Does NOT work!
time git rev-list --all \
    | xargs -n 1 -P "$(nproc)" git --no-pager grep 'my regex search' \
    -- "path/to/my_file.c" "path/to/my_folder"
```
turns the `git grep` command into this:

```bash
git --no-pager grep 'my regex search' \
    -- "path/to/my_file.c" "path/to/my_folder" commit_hash
```

And now the `commit_hash` part is tacked onto the end in the wrong spot! It should be before the `--` part, but instead `xargs` shoves it on after, and now the `git grep` command is broken!

So the solution is this: 
```bash
# works (best)
time git rev-list --all \
    | xargs -P "$(nproc)" -I {} git --no-pager grep -n 'my regex search' {} \
    -- "path/to/my_file.c" "path/to/my_folder"
```

...or even this, which is much hackier I think, but also works:
```bash
# also works
time git rev-list --all \
    | xargs -n 1 -P "$(nproc)" \
    sh -c 'git --no-pager grep "STATIC_ASSERT" "$0" -- my_file.c'
```

In the last example just above, the `sh -c` command is used to run a shell command, and the `"$0"` is used to pass the first argument from `xargs`, which is a single (due to `-n 1`) commit hash from `git rev-list --all`, to the shell command. And again, same as before in every other example above, the `--` is used to tell `git grep` that all of the arguments after that point are file or folder paths, and not more options to `git grep`.


## References

1. A ton of my own testing and research.
1. GitHub Copilot AI in VSCode. I had a lot of chats with the GitHub Copilot AI in VSCode while figuring out all of the above. This answer is my own content and wording and I've tested and studied each command here to understand all parts.
1. [Is it possible to perform a 'grep search' in all the branches of a Git project?](https://stackoverflow.com/q/15292391/4561887)
1. [Using Git, how could I search for a string across all branches?](https://stackoverflow.com/q/7151311/4561887)


## See also

1. My answer: [`git grep` by file extensions](https://stackoverflow.com/a/77909714/4561887)

