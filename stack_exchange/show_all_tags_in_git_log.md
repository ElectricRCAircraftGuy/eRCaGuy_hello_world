<!--
https://stackoverflow.com/a/69275540/4561887
-->

Note: I am just addressing the _subject_ of the question: 

> show all tags in git log

..._not_ the specific details of the question.

## Show the full `git log` (in color!) for each tagged commit:

I really think this is the most-useful and most-beautiful form:

```bash
git log --no-walk --tags
```

It shows the full `git log` output for every single commit which has a tag attached to it. Very handy!

And if you'd like to filter out just tags which match a certain string search pattern, do this instead: 

```bash
git log --no-walk --tags=*some_string*
```

Example:
```bash
git log --no-walk --tags=*release/my_board*
```

## Show a 1-line `git log` summary (in color!) for each tagged commit:

If you'd like to just see one line per tagged commit, do this instead. Note: this is modified from [Coderwall's beautiful `git lg` alias][1]: 

```bash
git log --color --no-walk --tags --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit
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


  [1]: https://coderwall.com/p/euwpig/a-better-git-log
  [2]: https://stackoverflow.com/a/25777221/4561887
