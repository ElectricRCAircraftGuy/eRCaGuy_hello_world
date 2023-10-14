<!--
https://stackoverflow.com/q/7197937/4561887

GS
14 Oct. 2023
-->

> On GitHub, can I fork just a wiki?

Yes, but it requires using `git` from the command-line. If on Windows, you will need the Git Bash terminal which comes with [Git for Windows](https://gitforwindows.org/), to run `git` commands at the command-line. On Mac or Linux, use your regular terminal. 

Below, I present three options to fork a wiki.

_The following concepts apply to any of the major git-based hosting platforms, including GitHub and Atlassian BitBucket. My tests and screenshots are from GitHub. I imagine that the same concepts would also apply to GitLab, but I have not tested it._


## Background knowledge

Don't skip this part. You need to understand some things.

#### Git vs GitHub; branches and repos:

Just like every git branch is actually made up of up to 3 branches, which confuses the heck out of everybody (see [my comment here](https://stackoverflow.com/questions/2003505/how-do-i-delete-a-git-branch-locally-and-remotely/23961231#comment107954274_23961231), and the answer above it), every GitHub repository is actually made up of **up to 2 _git_ repositories**, which also confuses the heck out of everybody. Remember: GitHub is *not* git! Git is a command-line version control tool. GitHub simply *uses* git. GitHub can do whatever the heck they want. They could store 1000 git repositories for every GitHub repository if they wanted. 

So, the two underlying _git_ repositories in a single _GitHub_ repository are:

1. The main git repository you generally push and pull to, and fork.
1. The secondary git repository used to store _the wiki pages only, _so long as_ you have created at least one page on the wiki. 

#### Example

Here is an example. We will reference this image:
[![enter image description here][1]][1]

1. The **main GitHub repo:** https://github.com/nicolargo/glances
    1. Click the green "Code" button shown in the image above to view the _git_ URLs to it. 
    1. **Git URLs:**
        1. HTTPS: `https://github.com/nicolargo/glances.git`
        1. SSH: `git@github.com:nicolargo/glances.git`
        1. These Git URLS are _not_ intended to be accessed in your browser! They are not webpages. They are intended to be used only at the command-line with `git` commands. They are the git _remote_ server URLs.
1. The main GitHub repo's **corresponding wiki repo,** which exists since this _GitHub_ repo has at least one wiki page: go to https://github.com/nicolargo/glances --> click the "Wiki" tab at the top, as shown in the image above.
    1. Direct link to the wiki: https://github.com/nicolargo/glances/wiki
    1. In the bottom-right of the wiki page, see the "Clone this wiki locally" section to view the _git_ HTTPS URL to it: 
        1. [![enter image description here][2]][2]
    1. **Git URLs:**
        1. HTTPS: `https://github.com/nicolargo/glances.wiki.git`
        1. SSH: `git@github.com:nicolargo/glances.wiki.git`  
            1. **Important!** 
                1. This URL is not shown in the image just above, but it does work and exist. All you do is take your main git repo URL, remove the `.git` extension, and replace it with `.wiki.git`. 
                1. Prefer the HTTPS git URLs for read-only access to someone else's git repos, and prefer the SSH URLs for read/write access to _your own_ git repos.
        1. Again, these Git URLs are _not_ webpages! They are for use only at the command-line with `git` commands. They are the git _remote_ server URLs to these git repositories, for use from the command-line.

#### Git limitations

**None**. A git repository is a git repository is a git repository. You have *two* git repositories above. Their HTTPS URLs are `https://github.com/nicolargo/glances.git` and `https://github.com/nicolargo/glances.wiki.git`. You can do *anything you want* to it via `git` commands at the command-line. Again, in Windows, use the Git Bash Linux-emulation terminal, and on Linux or Mac, use your regular terminal.

#### GitHub limitations

GitHub only supports forking the main repository (at git remote server HTTPS URL `https://github.com/nicolargo/glances.git`, in this case). It does _not_ support forking the wiki repository. It also only supports Issues, branch protections, pull requests, etc., on the _main repository._ It does not support them on the wiki repository. For the wiki repository, just editing a wiki page in the GitHub web editor online creates a commit and pushes automatically. There is no pull request, no branch protection, no Issues, etc.

If you want all of those features, you need to put your wiki pages *into* the main repository as markdown pages within it. That's fine, but then you have a more cumbersome process for community members to update the wiki pages, because now your "wiki" pages will be in the main, highly-regulated git repository, rather than in the unregulated wiki git repository. GitHub _intentionally_ makes the wiki repository easy to modify, but also unprotected.

#### Let's define some terms

1. Let's call `https://github.com/nicolargo/glances.git` the _"main git repository"_. 
1. Let's call `https://github.com/nicolargo/glances.wiki.git` the _"accompanying wiki git repository"_.
1. If you move the contents of `https://github.com/nicolargo/glances.wiki.git` into `https://github.com/nicolargo/glances.git`, which you can do via git at the command-line by the way, let's call that concept _"wiki pages in your main git repository"_, or _"markdown pages in your main git repository"_.
1. If you delete `https://github.com/nicolargo/glances.wiki.git` and move it into its own stand-alone main GitHub repository, then you will now have the ability to fork it, create Issues, have pull requests, etc. Let's call that concept a _"main git repository which is used as a wiki"_.

In my answer below, I will cover forking 1, 2, and 4 above in 3 separate ways:
1. [most common] How to fork the _"main git repository"_ and its _"accompanying wiki git repository"_.
1. How to copy an _"accompanying wiki git repository"_ into a new _"main git repository"_ to create a _"main git repository which is used as a wiki"_.
1. How to fork an _"accompanying wiki git repository"_ into the _"accompanying wiki git repository"_ of any other _"main git repository"_.

Here we go:


## Option 1 [most common]: fork the _"main git repository"_ and its _"accompanying wiki git repository"_

Let's fork the `glances` repository and its accompanying wiki repository. 

1. In a web browser, log into GitHub.
1. Go here: https://github.com/nicolargo/glances
1. Click the "Fork" button at the top: 
    
    [![enter image description here][3]][3]

    On the page that opens, click "Create fork". 

    My username is [ElectricRCAircraftGuy](https://github.com/ElectricRCAircraftGuy). 

    I now have this fork of glances, with my username in the webpage URL: https://github.com/ElectricRCAircraftGuy/glances

    If I click the green "Code" button --> "SSH" tab, I can see my git SSH URL: `git@github.com:ElectricRCAircraftGuy/glances.git`. My HTTPS URL is `https://github.com/ElectricRCAircraftGuy/glances.git`. 

    In my terminal on my computer, I can clone the repo:
    ```bash
    # What I will run to clone my own repo with read/write permissions
    git clone git@github.com:ElectricRCAircraftGuy/glances.git

    # What others can run to clone my repo with read-only permissions
    git clone https://github.com/ElectricRCAircraftGuy/glances.git
    ```

    [x] Forking the _"main git repository"_ is now done. But, forking the _"accompanying wiki git repository"_ is not done yet.

1. Try to clone the _"accompanying wiki git repository"_ to prove it does _not_ exist yet. 

    I know from experience that GitHub does not fork the wiki repository when you fork the main repository. I also know that the _"accompanying wiki git repository's"_ git URLs will be as follows. Simply remove `.git` from your _"main git repository's"_ git URLs, and add `.wiki.git` instead:

    _"accompanying wiki git repository"_ git URLs:

    ```bash
    # What I will run to clone my own accompanying wiki git repo with 
    # read/write permissions
    git clone git@github.com:ElectricRCAircraftGuy/glances.wiki.git

    # What others can run to clone my accompanying wiki git repo with 
    # read-only permissions
    git clone https://github.com/ElectricRCAircraftGuy/glances.wiki.git
    ```

    So, if I run `git clone git@github.com:ElectricRCAircraftGuy/glances.wiki.git`, I'll get this error, as expected, since my forked repo does not have an _"accompanying wiki git repository"_ yet:

    ```bash
    $ git clone git@github.com:ElectricRCAircraftGuy/glances.wiki.git
    Cloning into 'glances.wiki'...
    ERROR: Repository not found.
    fatal: Could not read from remote repository.

    Please make sure you have the correct access rights
    and the repository exists.
    ```

1. Click the "Wiki" link at the top of your new, forked repo. You'll see this:

    [![enter image description here][4]][4]

    Click the "Create the first page" button. In the web editor that opens, just click "Save page" in the bottom right:

    [![enter image description here][5]][5]

    I now see this, and the "Clone this wiki locally" section is now visible in the bottom-right:

    [![enter image description here][6]][6]

    GitHub has now created a nearly empty _"accompanying wiki git repository"_ which we can work with.

1. Clone your empty _"accompanying wiki git repository"_:

    ```bash
    # What I will run to clone my own accompanying wiki git repo with 
    # read/write permissions
    git clone git@github.com:ElectricRCAircraftGuy/glances.wiki.git

    # What others can run to clone my accompanying wiki git repo with 
    # read-only permissions
    git clone https://github.com/ElectricRCAircraftGuy/glances.wiki.git
    ```

    This works fine now. I run:
    ```bash
    git clone git@github.com:ElectricRCAircraftGuy/glances.wiki.git
    ```

    This creates a new `glances.wiki` folder on my computer, with the `.git` folder in it, of course, plus a single `Home.md` markdown file in it, which contains the Wiki home page you see online at https://github.com/ElectricRCAircraftGuy/glances/wiki. 

1. Command-line work: fork the original glances _"accompanying wiki git repository"_ into your new, empty _"accompanying wiki git repository"_

    ```bash
    # cd into your new, empty accompanying wiki git repo
    cd glances.wiki

    # view your git remotes; the "origin" one is the one you just cloned
    # from your own new _"accompanying wiki git repository"_
    git remote -v

    # Add the original glances repo as a remote repo, and call it "upstream"; 
    # use the HTTP git URL for read-only access
    git remote add upstream https://github.com/nicolargo/glances.wiki.git
    
    # prove you've added it
    git remote -v

    # fetch the upstream _"accompanying wiki git repository"_ you just added
    git fetch upstream

    # view your remote git branches you just fetched, and make note of the 
    # "upstream" one. I see the following:
    #       origin/HEAD -> origin/master
    #       origin/master
    #       upstream/master      <==== the upstream branch we need later
    git branch -r

    # Ensure `git status` is clean, and that you don't have any local, 
    # uncommitted changes to your _"accompanying wiki git repository"_. 
    # It should say: "nothing to commit, working tree clean".
    git status

    # back up your branch in case you royally screw this up
    git branch my_backup_branch

    # hard reset your branch to the upstream you just fetched, which is called
    # "upstream/master" in my case, as shown above
    git reset --hard upstream/master

    # List files to see you now have all pages from the upstream wiki
    ls

    # Force push it to yoru own _"accompanying wiki git repository"_
    git push -f  # see WARNING WARNING WARNING below; never do this again on
                 # your _"accompanying wiki git repository"_.
    ```

1. Go back to your wiki page and refresh the page: https://github.com/ElectricRCAircraftGuy/glances/wiki

    And voila! I now see this: 

    [![enter image description here][7]][7]

    ...just like the upstream wiki page, here: https://github.com/nicolargo/glances/wiki

1. Done. I hope you thoroughly understand now that a GitHub _"accompanying wiki git repository"_ is just another regular git repo like any other git repo! Just use the command-line. 

    Note: I use the command-line to write and edit my wiki pages too. Then I push them. I hardly use the online wiki editor on GitHub. 

    WARNING WARNING WARNING: **never** ever force push `git push -f` again, or else you permanently wipe other peoples' changes that they make via the web interface, and since people editing the wiki via the web interface don't have the "_accompanying wiki git repository_" cloned locally, they can't recover their changes, ever. You will erase their work forever.

    So, if you edit the wiki via the command line, and `git push` fails, NEVER use `-f`. Instead, pull the latest changes, merge them with yours, and `git push` again cleanly.


## Option 2: copy an _"accompanying wiki git repository"_ into a new _"main git repository"_ to create a _"main git repository which is used as a wiki"_

_I'm not going to include so many details from this point forward. The above instructions should be enough to get you going as a beginner._

This option is most useful if you want to have a professional wiki page with branch protections, Issues, pull requests, etc. This is what I use at work to create wikis for my team. In this case, the "wiki" is just a regular git repo which we use as a wiki by storing a ton of linked markdown files in it.

1. Go to GitHub in a browser and make a new repo. I'll call mine `glances_wiki`. It's here: https://github.com/ElectricRCAircraftGuy/glances_wiki
1. Now do everything locally from the terminal:
    ```bash
    # Clone it locally, using the SSH git URL
    git clone git@github.com:ElectricRCAircraftGuy/glances_wiki.git
    
    # cd into it
    cd glances_wiki

    # add the original _"accompanying wiki git repository"_ of the glances repo
    # as an upstream to your new _"main git repository"_
    git remote add upstream https://github.com/nicolargo/glances.wiki.git

    # fetch the upstream _"accompanying wiki git repository"_ you just added
    git fetch upstream

    # hard reset onto it; WARNING WARNING: hard reset will wipe local changes
    git reset --hard upstream/master

    # force push it to your own _"main git repository"_; WARNING WARNING: 
    # this permanently wipes changes in your remote "origin" on github
    # for this repo
    git push -f
    ```
1. Done. Check it out: https://github.com/ElectricRCAircraftGuy/glances_wiki

    The "Home.md" page is now the main page of this _"main git repository which is used as a wiki"_. Rename that file to "README.md" if you want it to show up automatically on the website when you view the repo in a browser on GitHub. 

    Ironically enough, my _"main git repository which is used as a wiki"_ also now has a wiki page, so _technically_ you can have a wiki of your wiki. Here is that page. It's empty: https://github.com/ElectricRCAircraftGuy/glances_wiki/wiki


## Option 3: fork an _"accompanying wiki git repository"_ into the _"accompanying wiki git repository"_ of any other _"main git repository"_

This option is most useful if you just want to copy the _"accompanying wiki git repository"_ of one repo into the _"accompanying wiki git repository"_ of another repo, while keeping the their corresponding _"main git repositories"_ separate and distinct.

1. For this demo, I'm creating a nearly-empty repo called `wiki_copy_demo`, here: https://github.com/ElectricRCAircraftGuy/wiki_copy_demo
    This is basically just Option 1 again, but into a different GitHub repo instead of the forked one.

1. Add at least one page to your destination Wiki--same as before in Option 1. Here's mine: https://github.com/ElectricRCAircraftGuy/wiki_copy_demo/wiki. 

1. Now, let's copy the glances upstream _"accompanying wiki git repository"_ into the _"accompanying wiki git repository"_ of this new `wiki_copy_demo` repo:

    ```bash
    # Clone your new _"accompanying wiki git repository"_ locally, using the 
    # SSH git URL
    git clone git@github.com:ElectricRCAircraftGuy/wiki_copy_demo.wiki.git
    # cd into it
    cd wiki_copy_demo.wiki

    # add the original _"accompanying wiki git repository"_ of the glances repo
    # as an upstream to your new _"accompanying wiki git repository"_
    git remote add upstream https://github.com/nicolargo/glances.wiki.git

    # fetch the upstream _"accompanying wiki git repository"_ you just added
    git fetch upstream

    # hard reset onto it; WARNING WARNING: hard reset will wipe local changes
    git reset --hard upstream/master

    # force push it to your own _"accompanying wiki git repository"_; 
    # WARNING WARNING: this permanently wipes changes in your remote 
    # "origin" on github for this repo
    git push -f
    ```

1. Done. The Glances wiki is copied into mine. See here: https://github.com/ElectricRCAircraftGuy/wiki_copy_demo/wiki



  [1]: https://i.stack.imgur.com/M8GCs.png
  [2]: https://i.stack.imgur.com/wwdJE.png
  [3]: https://i.stack.imgur.com/d8SzH.png
  [4]: https://i.stack.imgur.com/Rez1F.png
  [5]: https://i.stack.imgur.com/ICnTh.png
  [6]: https://i.stack.imgur.com/l87eW.png
  [7]: https://i.stack.imgur.com/Zv1qi.jpg
