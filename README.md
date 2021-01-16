# dpd
![tests](https://github.com/smoldoom/dpd/workflows/tests/badge.svg)

`dpd` is a small tool that tries to do one thing well - namely converting PNG images into a `PLAYPAL.lmp` [file](https://doomwiki.org/wiki/PLAYPAL).

## Usage 

In order to create a DOOM palette called `playpal.lmp` from a PNG called `palette.png`: 

``dpd palette.png playpal.lmp``

Note that input PNGs must contain one pixel per color, so a 256 color PNG palette would have 256 pixels, with a resolution of 16x16.

## License

This software is licensed under the GNU GPLv3 . See ``LICENSE.md`` for information.
    
