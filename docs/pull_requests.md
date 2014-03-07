# Pull Request Process

## NOTA BENE!

ALL CONTRIBUTIONS TO STIGDB REQUIRE A SIGNED [CONTRIBUTOR LICENSING AGREEMENT](https://github.com/StigDB/stigdb/blob/master/docs/Stig_CLA_Process.md).

We will not be able to merge in any contributions until you have a signed CLA on file with us.

## General Guidelines

* _All work happens in git and GitHub._ This means that you must have a [GitHub account](https://github.com/join) in order to contribute to Stig.
* _No one ever commits directly to the stigdb master branch._ All work happens in forks, branches, and pull requests. New commits are merged into the master from these.
* _We aim to assign/review all pull requests within a week._ Ideally we'll at least assign it to a reviewer within a day, but definitely within a week.
* _Ideally, all pull requests are closed within a month._ If they're not yet closed, they must still be under active discussion. We aim to have **No Zombie Pull Requests**.

## The Process

The Stig team uses the [Fork & Pull](https://help.github.com/articles/using-pull-requests) model for their code. You can read more about it at that link, but the steps are detailed below.

### Fork the stigdb repository

Your work should be performed on your own copy of the [stigdb repository](http://github.com/StigDB/stigdb). To fork the repo, click the [fork button](http://github.com/StigDB/stigdb/fork) button on the [GitHub](http://github.com) web interface.

### Clone the repository to your local machine

The easiest way to work with your forked repo code is from your local machine. That's accomplished by running a `git clone` command:

```
git clone git://github.com/StigDB/stigdb.git
```

### Perform your desired changes in your local repository

Within your own forked and cloned repository, you are free to handle the code however you wish. Fork it, tag it, commit it. "Whatever works best for you" is the right answer to "What's the process?" when you're in your own local repository.

### Push your changes to your cloned repository

Once you like how your changes are functioning in your locally cloned repo, it's time to [push them back up](https://help.github.com/articles/pushing-to-a-remote) to your cloned repo on GitHub. Without this step you will be unable to submit your changes to the Stig project.

### Create a pull request to the stigdb master branch

While this might feel like you're _pushing_ your changes up to Stig for them to be merged, from the git perspective what you're really doing is asking for someone to review your changes and then _pull_ them into the main repository. Hence: pull request.

GitHub has [good documentation](https://help.github.com/articles/using-pull-requests) on how to submit a pull request. Please review and use it when submitting contributions to Stig.

When submitting your request, please always provide **ample** pull request notes so we know not only what your request is trying to accomplish but also why you're trying to accomplish it. This will make things much easier for everyone. If you are working to fix an [issue](https://github.com/StigDB/stigdb/issues), please include the issue number in your pull request note.

### A stigdb core team member will assign and/or review your pull request

The Stig core team aims to have all pull requests reviewed within a week. If that's not possible, in that timeframe they'll at least have assigned your pull request to one of the core team for review.
