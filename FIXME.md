# FIXME

* Fix building on Debian: linker fails with `cannot find -lcursesw`.
  Changing the linker to use `-lncursesw` fixes this, however the compiler
  still cannot find wide character functions such as `waddwstr`.
  `ncursesw/curses.h` contains the necessary definitions on both Debian and
  Fedora, so changing `<curses.h>` includes to `<ncursesw/curses.h>` fixes this.
  Compilation on Fedora links against `libncursesw.so.6` by default, however
  Debian has `libncursesw.so.5` as the latest ncursesw shared object.
  For compilation on Fedora to be backwards compatible, `libncursesw.so.5` must
  be linked against. The package `ncurses-compat-libs` provides this.
