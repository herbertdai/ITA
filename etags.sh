#!/bin/bash

find . -name *.[ch] -exec etags -a {} \;

ls -l TAGS