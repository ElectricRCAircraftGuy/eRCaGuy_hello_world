This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


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
