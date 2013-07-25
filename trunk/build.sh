#!/bin/sh

# author : avi sengupta
# desc   : toplevel build script
#

TYPE=$1
TARGET=$2

DIR="fibheap_lib fibheap_driver"
OUTPUTDIR=`pwd`/output

for i in $DIR
do
    echo "********* Building $i "
    cd $i/work
    make BLDTYPE=$TYPE $TARGET
    cd -
done
