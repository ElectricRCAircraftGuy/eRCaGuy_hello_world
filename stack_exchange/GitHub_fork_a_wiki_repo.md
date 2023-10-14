<!--
https://stackoverflow.com/q/7197937/4561887

GS
14 Oct. 2023
-->

> On GitHub, can I fork just a wiki?

Yes, but it requires using `git` from the command-line. If on Windows, you will need the Git Bash terminal which comes with [Git for Windows](https://gitforwindows.org/), to run `git` commands at the command-line. On Mac or Linux, use your regular terminal. 

Below, I present three options to fork a wiki.


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
        1. Git HTTPS: `https://github.com/nicolargo/glances.wiki.git`
        1. Again, this Git URL is _not_ a webpage! It is for use only at the command-line with `git` commands. It is the git _remote_ server URL to this git repository.

#### Git limitations

**None**. A git repository is a git repository is a git repository. You have *two* git repositories above. Their HTTPS URLs are `https://github.com/nicolargo/glances.git` and `https://github.com/nicolargo/glances.wiki.git`. You can do *anything you want* to it via `git` commands at the command-line. Again, in Windows, use the Git Bash Linux-emulation terminal, and on Linux or Mac, use your regular terminal.

#### GitHub limitations

GitHub only supports forking the main repository (at git remote server HTTPS URL `https://github.com/nicolargo/glances.git`, in this case). It does _not_ support forking the wiki repository. It also only supports Issues, branch protections, pull requests, etc., on the _main repository._ It does not support them on the wiki repository. For the wiki repository, just editing a wiki page in the GitHub web editor online creates a commit and pushes automatically. There is no pull request, no branch protection, no Issues, etc.

If you want all of those features, you need to put your wiki pages *into* the main repository as markdown pages within it. That's fine, but then you have a more cumbersome process for community members to update the wiki pages, because now your "wiki" pages will be in the main, highly-regulated git repository, rather than in the unregulated wiki git repository. GitHub _intentionally_ makes the wiki repository easy to modify, but also unprotected.

#### Let's define some terms

1. Let's call `https://github.com/nicolargo/glances.git` the _main git repository._ 
1. Let's call `https://github.com/nicolargo/glances.wiki.git` the _accompanying wiki git repository._
1. If you move the contents of `https://github.com/nicolargo/glances.wiki.git` into `https://github.com/nicolargo/glances.git`, which you can do via git at the command-line by the way, let's call that concept _wiki pages in your main git repository_, or _markdown pages in your main git repository._
1. If you delete `https://github.com/nicolargo/glances.wiki.git` and move it into its own stand-alone main GitHub repository, then you will now have the ability to fork it, create Issues, have pull requests, etc. Let's call that concept _a main git repository which is used as a wiki_.

In my answer below, I will cover forking 1, 2, and 4 above in 3 separate ways:
1. How to fork the _main git repository_ and its _accompanying wiki git repository_.
1. How to copy an _accompanying wiki git repository_ into a new _main git repository_.
1. How to fork an _accompanying wiki git repository_ into the _accompanying wiki git repository_ of a new, empty _main git repository_.

Here we go:


## Option 1: fork the _main git repository_ and its _accompanying wiki git repository_

Let's fork the `glances` repository and its accompanying wiki repository. 

1. In a web browser, log into GitHub.
1. Go here: https://github.com/nicolargo/glances
1. 
[![enter image description here][3]][3]


## Option 2: copy an _accompanying wiki git repository_ into a new _main git repository_


## Option 3: fork an _accompanying wiki git repository_ into the _accompanying wiki git repository_ of a new, empty _main git repository_


  [1]: https://i.stack.imgur.com/M8GCs.png
  [2]: https://i.stack.imgur.com/wwdJE.png
  [3]: https://i.stack.imgur.com/d8SzH.png
