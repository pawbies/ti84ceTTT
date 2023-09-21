# ----------------------------
# Makefile Options
# ----------------------------

NAME = ttt
ICON = icon.png
DESCRIPTION = "tic tac toe for my calculator"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
