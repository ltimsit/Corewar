#!/bin/sh

gcc init_display.c hook.c -I ../include display.h mlx.h libmlx.a -framework OpenGL -framework AppKit
