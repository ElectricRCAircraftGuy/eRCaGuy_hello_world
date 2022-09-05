1. This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world  
1. https://stackoverflow.com/a/63418267/4561887

I'm in the middle of adding sections on how to delete branches and stuff.

---


## Various ways to create a branch in git from another branch:

This answer adds some additional insight, not already present in the existing answers, regarding just the _title_ of the question itself (**Create a branch in Git from another branch**), but does _not_ address the more narrow specifics of the question which already have sufficient answers here.

I'm adding this because I really needed to know how to do #1 below just now (create a new branch from a branch I do NOT have checked out), and it wasn't obvious how to do it, and Google searches led to here as a top search result. So, I'll share my findings here. This isn't touched upon well, if at all, by any other answer here. 

While I'm at it, I'll also add my other most-common `git branch` commands I use in my regular workflow, below.


## 1. To create a new branch from a branch you do NOT have checked out:

Create `branch2` from `branch1` while you have any branch whatsoever checked out (ex: let's say you have `main` checked out):

```bash
git branch branch2 branch1
```

The general format is:

```bash
git branch <new_branch> [from_branch]
```

`man git branch` shows it as follows. What I call `<new_branch>` is what they call `<branchname>`, and what I call `[from_branch]` is what they call `[<start-point>]`:

>     git branch [--track | --no-track] [-l] [-f] <branchname> [<start-point>]


## 2. To create a new branch from the branch you DO have checked out:

```bash
git branch new_branch
```

This is great for making backups before rebasing, squashing, hard resetting, etc.--before doing anything which could mess up your branch badly.

Ex: I'm on `feature_branch1`, and I'm about to squash 20 commits into 1 using `git rebase -i main`. In case I ever want to "undo" this, let's back up this branch first! I do this **ALL...THE...TIME** and find it super helpful and comforting to know I can always _easily_ go back to this backup branch and re-branch off of it to try again in case I mess up `feature_branch1` in the process:

```bash
git branch feature_branch1_BAK_20200814-1320hrs_about_to_squash
```

The `20200814-1320hrs` part is the date and time in format `YYYYMMDD-HHMMhrs`, so that would be 13:20hrs (1:20pm) on 14 Aug. 2020. This way I have an easy way to find my backup branches until I'm sure I'm ready to delete them. If you don't do this and you mess up badly, you have to use `git reflog` to go find your branch prior to messing it up, which is much harder, more stressful, and more error-prone.


## 3. To create _and check out_ a new branch from the branch you DO have checked out:

```bash
git checkout -b new_branch
```

To make it obvious what is happening there, know that this one command above is equivalent to these _two_ separate commands:

```bash
git branch new_branch
git checkout new_branch
```


## 4. To create _and check out_ a new branch from a branch you do NOT have checked out:

```bash
git checkout -b new_branch from_branch
```

To make it obvious what is happening there, know that this one command above is equivalent to these _three_ separate commands:

```bash
git checkout from_branch
git branch new_branch
git checkout new_branch
```


## 5. To rename a branch

### A. That you do NOT have checked out:

Just like renaming a regular file or folder in the terminal, `git` considered "renaming" to be more like a 'm'ove command, so you use `git branch -m` to rename a branch. Here's the general format:

```bash
git branch -m <old_name> <new_name>
```

`man git branch` shows it like this:

>     git branch (-m | -M) [<oldbranch>] <newbranch>

Example: let's rename `branch_1` to `branch_1.5`:

```bash
git branch -m branch_1 branch_1.5
```

### B. That you DO have checked out:

OR, if you already have `branch_1` checked out, you can rename the _currently-checked-out branch_ to `branch_1.5` like this:

```bash
git branch -m branch_1.5
```


## 6. To delete a branch

Source: [EXCELLENT READ! Study this answer. Also see my comments below the answer] [How do I delete a Git branch locally and remotely?](https://stackoverflow.com/a/23961231/4561887)

### A. If your repo is on your local computer only...

...and your branch has never been pushed to any remote server, then you only have **_one branch to delete_**: your local branch. 

Here is the **"safe delete" command**. It only deletes the branch if it is fully merged into its upstream branch, or, if no upstream branch is set, if it is fully merged into the branch you currently have checked out at the time you run the delete command. This ensures you never lose the changes from this branch:

```bash
git checkout some_other_branch

git branch --delete branch_to_delete  # long form
git branch -d branch_to_delete        # short form
```

Here is the **"force delete" command.** It deletes the branch no matter what, so long as you're checked-out on a different branch at the time you run the command. This is the command I use the most often:

```bash
git checkout some_other_branch

git branch --delete --force branch_to_delete  # long form
git branch -D branch_to_delete                # short form [what I use most]
```

### B. If your repo is also on a remote server named `origin`...

...and your branch named `branch1` HAS been pushed to that remote server, then you have **_three branches to delete!_**: 
1. your **local branch**: `branch1`
1. your **_locally-stored_ remote-tracking branch**: `origin/branch1`
    1. This is what gets updated whenever you run `git fetch`.
1. your **_remote_ branch**, actually stored on the remote server: `branch1`

To help orient you, if you have branch `branch1` checked out, then 


## 7. To undelete a branch

If you ever want to **undelete a branch or commit** you have deleted, you can do so for at least 2 weeks if you are using default git settings for.


<!--
TODO!:
1. To delete a merged commit or branch
1. To forcefully delete an unmerged commit or branch

3 branches to delete: 1) local, 2) locally-stored remote-tracking, 3) remote
-->
