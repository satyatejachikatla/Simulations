#!/bin/bash

export LD_LIBRARY_PATH="."
cd install
./game-of-life $@
