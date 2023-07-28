<!--
GS
2023

My answer: https://stackoverflow.com/a/61618255/4561887
-->

As of Aug. 2021, also see here: https://stackoverflow.com/questions/29136057/can-i-search-github-labels-with-logical-operator-or/68621781#68621781 and: https://github.blog/changelog/2021-08-02-search-issues-by-label-using-logical-or/.

---

Ideally, GitHub search would support parenthesis for nesting and grouping, and logical `AND`, `OR`, and `NOT` operators. What I would like is for them to support something like this:

    is:open AND is:pr AND (review-requested:ElectricRCAircraftGuy OR 
    assignee:ElectricRCAircraftGuy) AND NOT(review-requested:"team:ORGNAME/team-1") AND 
    archived:false AND (author:my-teammate-1 OR author:my-teammate-2 OR 
    author:my-teammate-3)

Instead, their search is much more limiting, and also pretty convoluted since it has VERY DIFFERENT behavior depending on *where* you type your search. Since the above search style is not supported, let's consider this more limited search attempt instead:

----

**My search:**

    is:open is:pr review-requested:ElectricRCAircraftGuy archived:false 
    author:my-teammate-1 author:my-teammate-2 author:my-teammate-3

----

The behavior I WANT is this:

    is:open AND is:pr AND review-requested:ElectricRCAircraftGuy AND archived:false AND 
    (author:my-teammate-1 OR author:my-teammate-2 OR author:my-teammate-3)

But depending on _where_ you do this search, you will get _two very different behaviors_. If I go to https://github.com/ --> **Pull requests** (at top) and type the search into this search bar highlighted in yellow here:

[![enter image description here][1]][1]

...then I get this search behavior:

    is:open AND is:pr AND review-requested:ElectricRCAircraftGuy AND archived:false AND author:my-teammate-3

Notice that all `author` fields *except for* the last one were DELETED. You can only search for ONE OF A GIVEN FIELD AT A TIME! This is sooo limiting! It is as though I had done this search:

    is:open is:pr review-requested:ElectricRCAircraftGuy archived:false 
    author:my-teammate-3

However, if I use the global search bar, highlighted below, which is available pretty much anywhere on https://github.com/, and copy and paste **My search** into this search bar:

[![enter image description here][2]][2]

...then I get this search behavior, which is exactly what I want in this case:

    is:open AND is:pr AND review-requested:ElectricRCAircraftGuy AND archived:false AND 
    (author:my-teammate-1 OR author:my-teammate-2 OR author:my-teammate-3)

This means that in the global search bar, each search term is joined with `AND` under the hood, unless there are multiples of a given field, and then each of those is joined with `OR` under the hood, as shown above. In the local Pull Request search bar, however, each search term is joined with `AND` under the hood, and if there are multiples of a given field, all of the multiples are deleted *except for the last one*, which is retained. This is what I call "convoluted" search behavior, since the results are 1) confusing, 2) different, depending on which search bar you use, and 3) limiting: even if you knew everything about GitHub search it still impossible to obtain the search results you might want. It's very hard to understand what's happening without extensive research and trial and error, which is exactly what I had to do. :(

So, what are your options if you want to see a list of all "Review requests" by my-teammate-1 OR my-teammate-2 OR my-teammate-3? Well, you can do and bookmark a single global search, like this:

    is:open is:pr review-requested:ElectricRCAircraftGuy archived:false 
    author:my-teammate-1 author:my-teammate-2 author:my-teammate-3

OR you can do and bookmark 3 separate Pull Request searches, like this:

1. Open, non-archived PRs requesting my review AND by `my-teammate-1`
    ```
    is:open is:pr review-requested:ElectricRCAircraftGuy archived:false 
    author:my-teammate-1
    ```
1. Open, non-archived PRs requesting my review AND by `my-teammate-2`
    ``` 
    is:open is:pr review-requested:ElectricRCAircraftGuy archived:false 
    author:my-teammate-2
    ```
1. Open, non-archived PRs requesting my review AND by `my-teammate-3`
    ```
    is:open is:pr review-requested:ElectricRCAircraftGuy archived:false 
    author:my-teammate-3
    ```

The display results of the Pull Request searches are displayed in a nicer format, so even though doing and bookmarking the 3 Pull Request searches is more of a pain than doing and bookmarking a single global search of the same thing, it might be what you prefer to do. 

And if you want to do something more complicated, such as get this behavior:

    is:open AND is:pr AND (review-requested:ElectricRCAircraftGuy OR 
    assignee:ElectricRCAircraftGuy) AND NOT(review-requested:"team:ORGNAME/team-1") AND 
    archived:false AND (author:my-teammate-1 OR author:my-teammate-2 OR 
    author:my-teammate-3)

...sorry, it's not currently possible. You'll have to create multiple sub-searches taking advantage of the search bar behavior that works for you, and using the `-` sign where necessary to exclude results. But, you can request that GitHub implement this more advanced search behavior by opening an issue [here (not affiliated with GitHub--just a place to track issues)](https://github.com/isaacs/github) and then [sending them a message here](https://support.github.com/contact) and giving them the links to your issue and to this Stack Overflow answer.

# GitHub search quick-reference cheat sheet:
Reminder: [read here](https://webapps.stackexchange.com/questions/57933/how-to-search-with-logic-operators-on-github/142071#142071) for a quick refresher/summary of what to expect when using the GitHub global search bar versus the GitHub Pull Request search bar.

## DEFAULT GITHUB PULL REQUEST (PR) SEARCHES:
1. All **open PRs created by me**: 
    1. https://github.com --> click "Pull requests" at the *very top*. 
    1. Direct link: https://github.com/pulls
1. All **open PRs assigned to me**: 
    1. https://github.com --> "Pull requests" --> "Assigned".
    1. Direct link: https://github.com/pulls/assigned
1. All **open PRs which mention me in a comment** (via @my-username): 
    1. https://github.com --> "Pull requests" --> "Mentioned".
    1. Direct link: https://github.com/pulls/mentioned
1. All **open PRs for which my review is requested**:
    1. https://github.com --> "Pull requests" --> "Review requests".
    1. Direct link: https://github.com/pulls/review-requested

## CUSTOM GITHUB PULL REQUEST (PR) SEARCHES:
1. **ALL PRS OPEN, BY AUTHOR:**
    1. Using the **Pull request search bar**:
        1. https://github.com --> click "Pull requests" at the *very top*. 
        1. Direct link: https://github.com/pulls
        1. Now use the search bar at the top-center/top-right.
        1. _Note that this search bar is limited to only one author at a time:_

                is:open is:pr archived:false author:username-1
                is:open is:pr archived:false author:username-2 
                is:open is:pr archived:false author:username-3 
                is:open is:pr archived:false author:username-4

        1. Here is a sample URL for the first of the 4 searches just above: https://github.com/pulls?q=is%3Aopen+is%3Apr+archived%3Afalse+author%3Ausername-1

    1. **[BEST]** Using the **GitHub global search bar (main search bar at top-left of any GitHub page)**:
        - This search bar allows multiple authors at once, but displays slightly differently than (doesn't look as good as) the Pull request search above:

                is:open is:pr archived:false author:username-1 author:username-2 author:username-3 author:username-4

        - Here is what the URL looks like after performing this search in the GitHub global search bar: https://github.com/search?q=is%3Aopen+is%3Apr+archived%3Afalse+author%3Ausername-1+author%3Ausername-2+author%3Ausername-3+author%3Ausername-4

1. **REVIEWS REQUESTED OF ME BY OTHERS:**
    1. Using the **Pull request search bar**:
        - Note that this search bar is limited to only one author at a time: 

                is:open is:pr archived:false review-requested:my-username author:username-1
                is:open is:pr archived:false review-requested:my-username author:username-2
                is:open is:pr archived:false review-requested:my-username author:username-3
                is:open is:pr archived:false review-requested:my-username author:username-4

        - Here is a sample URL for the first search above: https://github.com/pulls?q=is%3Aopen+is%3Apr+archived%3Afalse+review-requested%3Amy-username+author%3Ausername-1

    1. **[BEST]** Using the **GitHub global search bar (main search bar at top-left of any GitHub page)**:
        - This search bar allows multiple authors at once, but displays slightly differently than (doesn't look as good as) the Pull request search above:

                is:open is:pr archived:false review-requested:my-username author:username-1 author:username-2 author:username-3 author:username-4

        - URL produced by the above global search: https://github.com/search?q=is%3Aopen+is%3Apr+archived%3Afalse+review-requested%3Amy-username+author%3Ausername-1+author%3Ausername-2+author%3Ausername-3+author%3Ausername-4

# See also:
1. My answer here on how to search for PRs by "to branch", by "from branch", and by author, _including_ doing this using custom Chrome search engines you can quickly trigger in your search bar: 
https://stackoverflow.com/questions/20547198/how-can-i-filter-all-github-pull-requests-for-a-specific-target-branch/66287268#66287268.

# References:
1. https://webapps.stackexchange.com/questions/57933/how-to-search-with-logic-operators-on-github/111246#111246
1. See also my shorter answer here: https://webapps.stackexchange.com/questions/57933/how-to-search-with-logic-operators-on-github/142071#142071
1. [Getting started with searching on GitHub](https://help.github.com/en/github/searching-for-information-on-github/getting-started-with-searching-on-github)
    1. [About searching on GitHub](https://help.github.com/en/github/searching-for-information-on-github/about-searching-on-github)
    1. [Searching issues and pull requests](https://help.github.com/en/github/searching-for-information-on-github/searching-issues-and-pull-requests#search-by-team-mention)
    1. [Using search to filter issues and pull requests](https://help.github.com/en/github/managing-your-work-on-github/using-search-to-filter-issues-and-pull-requests)
    1. [Understanding the search syntax](https://help.github.com/en/github/searching-for-information-on-github/understanding-the-search-syntax)
    1. [Troubleshooting search queries](https://help.github.com/en/github/searching-for-information-on-github/troubleshooting-search-queries) - here they mention `AND`, `OR`, and `NOT` operators, but they don't seem to actually have these implemented, so this page must be out-of-date :(.
1. https://github.com/isaacs/github/issues/660

  [1]: https://i.stack.imgur.com/bpFPb.png
  [2]: https://i.stack.imgur.com/3KEOZ.png
