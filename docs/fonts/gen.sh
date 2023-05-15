#!/bin/bash


echo "You need https://github.com/shellixyz/hd_fpv_osd_font_tool";
echo "And you need montage from imagemagick";



echo "converting";
find ../../fonts -iname '*.bin' | cut -d '/' -f 4 | cut -d '.' -f 1 | xargs -I '%' ~/.cargo/bin/hd_fpv_osd_font_tool convert djibin:../../fonts/%.bin tiledir:dir_%;

echo "montaging";
find ../../fonts -iname '*.bin' | cut -d '/' -f 4 | cut -d '.' -f 1 | xargs -I '{}' montage 'dir_{}/*.png'  -tile 16x -geometry 24x36+1+1 {}.png;

echo "cleaning";
rm -rf ./dir_font*


echo "Finished"