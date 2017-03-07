wallWidth = 1;
$fs = 1;

module cylinder_outer(height, diameter, fs) {
   radius = diameter / 2;
   fn = floor(360 / acos(1 - (fs*fs) / (2*radius*radius)));
   fudge = 1/cos(180/fn);
   cylinder(h=height, d=diameter*fudge, $fn=fn);
}

module rail(length) {
    rotate([90,0,90])
    linear_extrude(height=length) {
        difference() {
            width = 10;
            holeWidth = 3;
            holeX = (width - holeWidth) / 2;

            height = 20;
            holeHeight = 10;
            holeY = height - holeHeight;

            archRadius = 8;
            archX = archRadius + wallWidth;
            archY = 0;

            square([width, height]);
            translate([holeX, holeY]) {
                square([holeWidth, holeHeight + 1]);
            }
            translate([archX, archY]) {
                circle(archRadius);
            }

        }
    }
}

module rail_corner() {
}

rail(length=100);
translate([0, 100, 0])
rotate([0, 0, -90])
rail(length=100);
