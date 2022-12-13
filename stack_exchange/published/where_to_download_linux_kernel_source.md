<!--
GS
9 Dec. 2022

https://unix.stackexchange.com/q/46077/114401
My answer: https://unix.stackexchange.com/a/728275/114401
-->

## All about _where_ and _how_ to get the official Linux kernel source code

## Quick summary

The official code location for the Linux kernel source is https://kernel.org/. 

#### Option 1: manually download just the kernel version tar file of interest

Go here to navigate and download just your version of interest: https://mirrors.edge.kernel.org/pub/linux/kernel/. 

Ex: the OP's v2.6.32.2 is on this page here: https://mirrors.edge.kernel.org/pub/linux/kernel/v2.6/. I recommend downloading the `.tar.xz` version of the file, since it is the smallest: [linux-2.6.36.2.tar.xz](https://mirrors.edge.kernel.org/pub/linux/kernel/v2.6/linux-2.6.36.2.tar.xz). The `.sign` file next to it contains the cryptographic PGP signature to verify the downloaded file's authenticity and integrity. Read more about that here, including seeing commands to verify the signature: https://kernel.org/category/signatures.html.

It's also really easy to download the files from the command-line. Here's what that might look like: 

```bash
# Download the file, showing a progress bar; this file is 56 MB
wget https://mirrors.edge.kernel.org/pub/linux/kernel/v2.6/linux-2.6.36.2.tar.xz
# extract it; on a fast computer this takes ~4 sec.; the extracted 
# "linux-2.6.36.2" dir is ~400 MB when done
time tar -xvf linux-2.6.36.2.tar.xz
```

#### Option 2 (recommended): use git to download _all_ versions and check out _any_ version

```bash
# clone the latest Stable and Longterm release tree (git repo)
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
# cd into it
cd linux
# view all tags, which contain the many many version numbers
# - see my answer here: https://stackoverflow.com/a/69275540/4561887
git log --no-walk --tags --oneline
# Once you identify the one of interest (ex: 2.6.36.2), check out the commit
# with that tag
git checkout v2.6.36.2
```


## Details

The official Linux kernel source code is at The Linux Kernel Archives at https://kernel.org/. 

Choose the git repository "tree" you wish to clone:

_These quotes just below are from this page: https://kernel.org/category/releases.html. I've also added my words in square brackets ([])._

> **Prepatch**  
> Prepatch or "RC" [Release Candidate] kernels are mainline kernel pre-releases that are mostly aimed at other kernel developers and Linux enthusiasts. They must be compiled from source and usually contain new features that must be tested before they can be put into a stable release. Prepatch kernels are maintained and released by Linus Torvalds. [Their versions end in `-rcX`, where `X` is a number.]
> 
> **Mainline**  
> Mainline tree is maintained by Linus Torvalds. It's the tree where all new features are introduced and where all the exciting new development happens. New mainline kernels are released every 9-10 weeks.
> 
> **Stable**  
> After each mainline kernel is released, it is considered "stable." Any bug fixes for a stable kernel are backported from the mainline tree and applied by a designated stable kernel maintainer. There are usually only a few bugfix kernel releases until next mainline kernel becomes available -- unless it is designated a "longterm maintenance kernel." Stable kernel updates are released on as-needed basis, usually once a week.
> 
> **Longterm**  
> There are usually several "longterm maintenance" kernel releases provided for the purposes of backporting bugfixes for older kernel trees. Only important bugfixes are applied to such kernels and they don't usually see very frequent releases, especially for older trees. [See a table of all of the long-term releases here: https://kernel.org/category/releases.html. Most of them are supported for up to 6 years.]

#### `git clone` URLs

Clone the repo you want. Note that if there are multiple clone URLs, any are usable, but I prefer the first one in each list below:

1. For Prepatch ("Release Candidate", or `-rc`) and Mainline (the main working tree) releases: 
    ```bash
    # From kernel.org directly
    # See: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/
    git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
    git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
    git clone https://kernel.googlesource.com/pub/scm/linux/kernel/git/torvalds/linux.git

    # Or, an exact mirror on GitHub
    # See: https://github.com/torvalds/linux
    git clone https://github.com/torvalds/linux
    ```
1. For Stable and Longterm releases:
    ```bash
    # From kernel.org directly
    # See: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/
    git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
    git clone https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
    git clone https://kernel.googlesource.com/pub/scm/linux/kernel/git/stable/linux.git

    # Note: This URL still works as of Dec. 2022, and has the exact same content
    # as the URLs above, but is no longer listed in the list of **all**
    # repos/trees here (https://git.kernel.org/), and so it appears to be
    # deprecated. Use the URLs above instead.
    git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git
    ```
1. For "Linux-Next" (I'm not sure what this means) releases:
    ```bash
    # From kernel.org directly
    # See: https://git.kernel.org/pub/scm/linux/kernel/git/next/linux-next.git/
    git clone git://git.kernel.org/pub/scm/linux/kernel/git/next/linux-next.git
    git clone https://git.kernel.org/pub/scm/linux/kernel/git/next/linux-next.git
    git clone https://kernel.googlesource.com/pub/scm/linux/kernel/git/next/linux-next.git
    ```

If you're developing in the kernel or want to see the latest, you'll probably want the Mainline git tree:
```bash
git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
# or on GitHub
git clone https://github.com/torvalds/linux
```

If you're just trying to download a given stable or longterm release number, such as in the question (v2.6.36.2), then clone the Stable and Longterm release tree instead, and `cd` into it:
```bash
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
cd linux  # cd into the newly-cloned dir
```

You can then view all version number tags ([see my answer for details and more commands](https://stackoverflow.com/a/69275540/4561887)), and check out the one of interest:
```bash
git log --no-walk --tags --oneline
git checkout v2.6.36.2
```


## How did I find the kernel.org `git clone` URLs above? 

Go to the main page at https://kernel.org/ and click the "browse" links:

[![enter image description here][1]][1]

Then click the "summary" column header at the top, and look for the "Clone" links at the bottom:

[![enter image description here][2]][2]


## References

1. https://kernel.org/category/signatures.html - I learned how to verify the PGP signatures and find the download URLs for individual tar files from this page.
1. My answer: [show all tags in `git log`](https://stackoverflow.com/a/69275540/4561887)
1. https://linuxize.com/post/how-to-extract-unzip-tar-xz-file/


  [1]: https://i.stack.imgur.com/emDrd.png
  [2]: https://i.stack.imgur.com/4rgwC.png
