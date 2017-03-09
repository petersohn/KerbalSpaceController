spike_width = 25;
spike_height = 2;
spike_intersect = 0.5;
spike_distance = 50;

wall_width = 2;
rail_width = 10;
rail_height = 20;
rail_hole_width = 3;
rail_hole_height = 8;
rail_arch_radius = 10;

module spike(length) {
    x = spike_intersect * spike_width / 2 / spike_height;
    echo(x);
    rotate([90, 0, 90])
    linear_extrude(height=length)
    polygon([
        [-x, -spike_intersect],
        [x, -spike_intersect],
        [0, spike_height]]);
}

module spike_mesh(length, width) {
   underhang = spike_width;
   spike_length_approx = width * 1.5 + underhang;
   intersection() {
      translate([0, 0, -spike_intersect])
      cube([length, width, spike_height + spike_intersect]);

      union() {
         for (x = [-width : spike_distance : length]) {
            translate([x, -underhang, 0])
            rotate([0, 0, 45])
            spike(spike_length_approx);
         }

         for (x = [0 : spike_distance : length + width]) {
            translate([x, -underhang, 0])
            rotate([0, 0, 135])
            spike(spike_length_approx);
         }
      }
   }
}

module spiked_plate(length, width, thickness) {
   union() {
      cube([length, width, thickness]);
      translate([0, 0, thickness])
      spike_mesh(length, width);
   }
}

module rail(length) {
    rotate([90, 0, 90])
    linear_extrude(height=length) {
        difference() {
            hole_x = (rail_width - rail_hole_width) / 2;

            hole_y = rail_height - rail_hole_height;

            arch_x = rail_arch_radius + wall_width;
            arch_y = 0;

            square([rail_width, rail_height]);
            translate([hole_x, hole_y]) {
                square([rail_hole_width, rail_hole_height + 1]);
            }
            translate([arch_x, arch_y]) {
                circle(rail_arch_radius);
            }

        }
    }
}

module cylinder_outer(height, diameter, fs) {
   radius = diameter / 2;
   fn = floor(360 / acos(1 - (fs*fs) / (2*radius*radius)));
   fudge = 1/cos(180/fn);
   cylinder(h=height, d=diameter*fudge, $fn=fn);
}

module rail_corner() {
    hole_position = (rail_width - rail_hole_width) / 2;
    hole_position_z = rail_height - rail_hole_height;
    length = rail_width + 1;
    render()
    difference() {
        union() {
            rail(length=length);
            translate([0, length, 0])
            rotate([0, 0, -90])
            rail(length=length);
        }
        translate([hole_position, hole_position, hole_position_z])
        cube([rail_width, rail_hole_width, rail_hole_height + 1]);
        translate([hole_position, hole_position, hole_position_z])
        cube([rail_hole_width, rail_width, rail_hole_height + 1]);
    }
}
