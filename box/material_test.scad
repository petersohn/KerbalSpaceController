length = 100;
width = 25;
distance = 30;
spike_length = 5;
spike_height = 2;
spike_intersect = 0.5;

module spike() {
    x = spike_intersect * width / 2 / spike_height;
    echo(x);
    translate([0, width/2, 0])
    rotate([90, 0, 90])
    linear_extrude(height=length)
    polygon([
        [-x, -spike_intersect],
        [x, -spike_intersect],
        [0, spike_height]]);
}

cube([length, width, 1]);

translate([0, distance, 0])
cube([length, width, 2]);

translate([0, 2*distance, 0]) {
    union() {
        cube([length, width, 1]);
        translate([0, 0, 1]) spike();
    }
}

translate([0, 3*distance, 0]) {
    union() {
        cube([length, width, 2]);
        translate([0, 0, 2]) spike();
    }
}
