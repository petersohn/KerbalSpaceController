include <common.scad>

length = 90;
width = 160;
gap = 5;

spiked_plate(length, width, 3);

translate([length + gap, 0, 0])
spiked_plate(length, width, 4);
