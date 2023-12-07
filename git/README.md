This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Useful Git References
...including many answers I've written myself:

1. My answer: [Various ways to create a branch in Git from another branch](https://stackoverflow.com/a/63418267/4561887)
1. My answer: [All about checking out files or directories in git](https://stackoverflow.com/a/65258783/4561887)
1. My answer: [How to cherry-pick a single commit, multiple commits, or a range of commits](https://stackoverflow.com/a/69472178/4561887)
1. Official Git documentation: https://git-scm.com/docs/gitrevisions - mentions git commit 3 dot (`...`) vs 2 dot range syntax, `^commit` ("not" `commit`), `commit^` (the parent of `commit`), etc.
1. [What are the differences between double-dot ".." and triple-dot "..." in Git diff commit ranges?](https://stackoverflow.com/a/7252067/4561887)
1. My answer: [Who is "us" and who is "them" according to Git?](https://stackoverflow.com/a/63911630/4561887)
1. My answer: [How to use `git diff` filters via `--diff-filter=`](https://stackoverflow.com/a/66649684/4561887)
1. My answer: [How to use `git lfs` as a basic user: What is the difference between `git lfs fetch`, `git lfs fetch --all`, and `git lfs pull`?](https://stackoverflow.com/a/72610495/4561887)
1. My Q&A: [How to view a linear `git log` (exclude feature commits), showing only commits to `main` or merges to `main`](https://stackoverflow.com/a/76625396/4561887)
1. My Q&A: [In a `git merge`-style workflow, show only the unique commits someone had in their PR (Pull Request) before merging](https://stackoverflow.com/a/77617437/4561887)
    > You might think of this as showing only the "right-hand parent" or "right-parent" commits, or as a type of `git log --second-parent` (which doesn't exist) command.
1. My answer: [How can I push a local Git branch to a remote with a different name easily?](https://stackoverflow.com/a/70302053/4561887)
1. My Q&A: [How to change the owner of a PR on GitHub / How to commandeer an open GitHub PR](https://stackoverflow.com/q/66539231/4561887)
1. My A: [Adding custom `git` hooks, such as pre-`git status` and post-`git status`](https://stackoverflow.com/a/77294994/4561887)


# Standard git workflow

```bash
git status
git checkout main
git pull
# IMPORTANT: useful branch name format: <your_username>_<issue_number>_<description>
git checkout -b gstaples_AB-999_description_of_my_new_feature
# Set the upstream branch to the same name as the local branch; required the **first push** only
git push -u origin gstaples_AB-999_description_of_my_new_feature
# future pushes are simple; verify that the upstream was set correctly:
git push

# REPEAT THE FOLLOWING STEPS AS MANY TIMES AS NEEDED
# ... do work ...
git status
git add -A  # commit all changes
git add .   # commit all changes in the current directory or lower (not the same thing as above)
git status
git commit
git push
# ... write commit message ...
# ... save and close commit message ...

# When ready for a pull request, open GitHub, BitBucket, Gitlab, etc, and open a pull request
# through the web interface. Then, merge the pull request through the web interface. 

# Then, pull the commit you just merged into main, and clean up your local and remote branches:

git status
git checkout main
git pull
# delete the branch locally now that we are done with it
git branch -d gstaples_AB-999_description_of_my_new_feature
# delete the branch remotely now that we are done with it
git push origin --delete gstaples_AB-999_description_of_my_new_feature
```


# Renaming a local and remote branch

Do *not* create new branches in the web interface, unless it lets you *manually* specify the branch name so you can follow the useful `<your_username>_<issue_number>_<description>` convention above. **Putting your username first is especially important to help your colleagues identify who owns each branch.**

If you do create a branch in the web interface, you cannot rename it easily. You probably cannot rename it in the web interface at all. Instead, you'll have to rename it locally at the command-line with the correct name, set the new upstream and push it to the remote, and then delete the old branch from the remote server, as follows. 

Imagine you mistakenly used the web interface to create a new branch that it named `feature/some_description`. Here's how to fix it to rename it to `gstaples_AB-999_some_description` instead, both locally and remotely:

```bash
git status
git fetch
git checkout feature/some_description
git pull
git branch -m gstaples_AB-999_some_description       # rename the local branch by 'm'oving it
git push origin -u gstaples_AB-999_some_description  # push it to the new remote branch
git push origin --delete feature/some_description    # delete the old remote branch
```
