#!/bin/bash

export LD_PRELOAD=./libft_malloc.so
export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH

$@
