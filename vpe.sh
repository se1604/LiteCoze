#!/bin/sh

for file in $(ls *.svg)
do
       sed -n '/Visual\ Paradigm\ Enterprise\ \[evaluation\ copy\]/p' $file |sed -i 's/Visual\ Paradigm\ Enterprise\ \[evaluation\ copy\]//g' $file
       sed -n '/fill-opacity="0"/p' $file |sed -i 's/fill-opacity="0"/fill-opacity="100"/g' $file
done
