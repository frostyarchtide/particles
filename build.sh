#!/bin/bash

PROJECT_NAME=particles

catnip -T 3ds &&\
3dslink -a "$1" "build/main.release/${PROJECT_NAME}.3dsx"
