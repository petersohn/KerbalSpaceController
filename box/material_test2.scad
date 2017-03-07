length = 94;
width = 160;
gap = 10;
spike_width = 25;
spike_height = 2;
spike_intersect = 0.5;
spike_distance = 50;

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

spiked_plate(length, width, 3);

translate([length + gap, 0, 0])
spiked_plate(length, width, 4);
