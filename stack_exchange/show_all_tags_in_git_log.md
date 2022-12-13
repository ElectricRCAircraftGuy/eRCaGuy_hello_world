<!--
https://stackoverflow.com/a/69275540/4561887
-->


Note: I am just addressing the _subject_ of the question (emphasis added): 

> **show all tags in `git log`**

..._not_ the specific details of the question.


## Show the full `git log` (in color!) for each tagged commit:

I really think this is the most-useful and most-beautiful form to **show all tags**:

```bash
# standard, multi-line `git log` output
git log --no-walk --tags

# concise, one-line `git log` output
git log --no-walk --tags --oneline
```

It shows the full `git log` output for every single commit which has a tag attached to it. Very handy! 

Trying to make sense of the option descriptions in `man git log`, I think that `--tags` causes `git log` to show all tags even if the tag is not on a commit otherwise in the `git log` ancestry tree, and `--no-walk` tell it to show _only_ the tags rather than walking the tree and showing all non-tagged commits too. The `--oneline` option, of course, is added to get a concise output of one line per commit (tag actually, in this case).

And if you'd like to **filter out just tags which match a certain string search pattern**, do this instead: 

```bash
# multi-line output
git log --no-walk --tags=*some_string*

# one-line output
git log --no-walk --tags=*some_string* --oneline
```

Example:
```bash
git log --no-walk --tags=*release/my_board*
```


## Alternative 1-line `git log` summary (in color!) for each tagged commit:

If you'd like to see a little more info. in your one-line-per-tagged-commit output, do this instead. Note: this is modified from [Coderwall's beautiful `git lg` alias][1]: 

```bash
# fancy one-line output
git log --color --no-walk --tags --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit

# vs regular one-line output
git log --no-walk --tags --oneline
```

Here is some sample output from the [official "Stable" version of the Linux kernel](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git):
1. "fancy" one-line command and output
    ```bash
    linux_stable$ git log --color --no-walk --tags --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit
    650093916eb3 - (tag: v6.0.12, origin/linux-6.0.y) Linux 6.0.12 (5 days ago) <Greg Kroah-Hartman>
    d9790301361c - (tag: v5.15.82, origin/linux-5.15.y) Linux 5.15.82 (5 days ago) <Greg Kroah-Hartman>
    592346d5dc9b - (tag: v5.10.158, origin/linux-5.10.y) Linux 5.10.158 (5 days ago) <Greg Kroah-Hartman>
    316cdfc48d4d - (tag: v5.4.226, origin/linux-5.4.y) Linux 5.4.226 (5 days ago) <Greg Kroah-Hartman>
    e8fff2341723 - (tag: v4.19.268, origin/linux-4.19.y) Linux 4.19.268 (5 days ago) <Greg Kroah-Hartman>
    65afe34ac33d - (tag: v4.14.301, origin/linux-4.14.y) Linux 4.14.301 (5 days ago) <Greg Kroah-Hartman>
    b6097015eea4 - (tag: v4.9.335, origin/linux-4.9.y) Linux 4.9.335 (5 days ago) <Greg Kroah-Hartman>
    76dcd734eca2 - (tag: v6.1-rc8) Linux 6.1-rc8 (8 days ago) <Linus Torvalds>
    31e4bdd2c25b - (tag: v6.0.11) Linux 6.0.11 (10 days ago) <Greg Kroah-Hartman>
    e4a7232c917c - (tag: v5.15.81) Linux 5.15.81 (10 days ago) <Greg Kroah-Hartman>
    ```
1. regular one-line command and output at the exact same point in time
    ```bash
    linux_stable$ git log --no-walk --tags --oneline
    650093916eb3 (tag: v6.0.12, origin/linux-6.0.y) Linux 6.0.12
    d9790301361c (tag: v5.15.82, origin/linux-5.15.y) Linux 5.15.82
    592346d5dc9b (tag: v5.10.158, origin/linux-5.10.y) Linux 5.10.158
    316cdfc48d4d (tag: v5.4.226, origin/linux-5.4.y) Linux 5.4.226
    e8fff2341723 (tag: v4.19.268, origin/linux-4.19.y) Linux 4.19.268
    65afe34ac33d (tag: v4.14.301, origin/linux-4.14.y) Linux 4.14.301
    b6097015eea4 (tag: v4.9.335, origin/linux-4.9.y) Linux 4.9.335
    76dcd734eca2 (tag: v6.1-rc8) Linux 6.1-rc8
    31e4bdd2c25b (tag: v6.0.11) Linux 6.0.11
    e4a7232c917c (tag: v5.15.81) Linux 5.15.81
    ```

And of course you can still filter on just certain tags you want using the `--tags=*some_string*` form instead:

```bash
git log --color --no-walk --tags=*some_string* --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit
```

Example:
```bash
git log --color --no-walk --tags=*release/my_board* --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit
```


## References:
1. The [answer by @Marcello de Sales][2] helped get me started.
1. [Coderwall's beautiful `git lg` alias][1]
1. `man git log`, and my own personal experimentation


  [1]: https://coderwall.com/p/euwpig/a-better-git-log
  [2]: https://stackoverflow.com/a/25777221/4561887
