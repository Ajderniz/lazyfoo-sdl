#!/bin/bash
ctags -R --kinds-c=demptu $(sdl2-config --prefix)/include/SDL2 include
