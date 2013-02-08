# guitar: libgit2 bindings for R

# GUITAR IS PRETTY MUCH NOT WORKING YET

Hi! You're now touring the [sausage factory]. This notice will disappear
once `guitar` is ready for public consumption.

## But I want to try it!

Ok. I'm developing it on a mac. I haven't tested it on Linux, so it's
very possibly not going to work there (but feel free to take a stab at
fixing it! start at guitar.cpp, and look for the dlopen calls there).
I have no idea how dynamic libraries work on Windows, and I currently
have no intention on porting `guitar` to Windows. Please feel free to
open an issue so we can discuss submitted patches.

# Intro

`guitar` gives you programmatic access to git in R, through the
combined magic of [libgit2](http://github.com/libgit2/libgit2/) and
[Rcpp](http://dirk.eddelbuettel.com/code/rcpp.html).

`guitar` is meant to be easy to use with simple classes, and methods
mapping pretty directly into libgit2. If you have a hard time with it,
please file documentation [issues](http://github.com/cscheid/guitar/issues) on github. If you really don't
like it, you can alternatively use the chorus to Cake's 
[homonymous song](http://www.lyricsfreak.com/c/cake/guitar_20026676.html) for
inspiration :)

# Dependencies

You'll need to install libgit2 with shared library support (possibly
the default).
