// Uncomment before rendering and exporting
//$fa = 0.01;
//$fs = 0.25;

// Configurable values
GRID_SIZE = [3, 3];
HOLE_DIAMETER = 16;
HOLE_DISTANCE = 5;
WALL_WIDTH = 2.5;
INTERNAL_HEIGHT = 20;
USB_PORT_WIDTH = 8;
USB_PORT_HEIGHT = 4;

// Calculated values
HOLE_DIAMETER_WITH_TOLERANCE = HOLE_DIAMETER + 0.5;
WIDTH_TOP = GRID_SIZE[0] * (HOLE_DIAMETER_WITH_TOLERANCE + HOLE_DISTANCE);
WIDTH_TOP_WITH_TOLERANCE = WIDTH_TOP + 0.5;
LENTGH_TOP = GRID_SIZE[1] * (HOLE_DIAMETER_WITH_TOLERANCE + HOLE_DISTANCE);
LENTGH_TOP_WITH_TOLERANCE = LENTGH_TOP + 0.5;
INTERNAL_HEIGHT_WITH_TOLERANCE = INTERNAL_HEIGHT + 0.5;
USB_PORT_WIDTH_WITH_TOLERANCE = USB_PORT_WIDTH + 0.5;
USB_PORT_HEIGHT_WITH_TOLERANCE = USB_PORT_HEIGHT + 0.5;

// Module for creating the top plate
module top(args) {
    difference() {
        // Base plate
        cube(size = [WIDTH_TOP, LENTGH_TOP, WALL_WIDTH]);
        // Hole cutout
        for (i = [0:GRID_SIZE[1] - 1]) {
            for (j = [0:GRID_SIZE[0] - 1]) {
                translate([(HOLE_DISTANCE / 2) + (HOLE_DISTANCE * j) + (HOLE_DIAMETER_WITH_TOLERANCE * j), (HOLE_DISTANCE / 2) + (HOLE_DISTANCE * i) + (HOLE_DIAMETER_WITH_TOLERANCE * i), 0]) {
                    translate([HOLE_DIAMETER_WITH_TOLERANCE / 2, HOLE_DIAMETER_WITH_TOLERANCE / 2, -1]) {
                        cylinder(d = HOLE_DIAMETER_WITH_TOLERANCE, h = WALL_WIDTH + 2);
                    }
                }
            }
        }
    }
}

// Module for creating the base box
module base(args) {
    difference() {
        // Base shape
        cube([WIDTH_TOP_WITH_TOLERANCE + (WALL_WIDTH * 2), LENTGH_TOP_WITH_TOLERANCE + (WALL_WIDTH * 2), INTERNAL_HEIGHT_WITH_TOLERANCE + (WALL_WIDTH * 2)]);
        // Top cutout
        translate([WALL_WIDTH, WALL_WIDTH, INTERNAL_HEIGHT + WALL_WIDTH]) {
            cube(size = [WIDTH_TOP_WITH_TOLERANCE, LENTGH_TOP_WITH_TOLERANCE, WALL_WIDTH + 1.5]);
        }
        // Internal cutout
        translate([WALL_WIDTH + 1, WALL_WIDTH + 1, WALL_WIDTH]) {
            cube(size = [WIDTH_TOP_WITH_TOLERANCE - 2, LENTGH_TOP_WITH_TOLERANCE - 2, INTERNAL_HEIGHT_WITH_TOLERANCE + WALL_WIDTH + 1]);
        }
        // USB port cutout
        translate([((WIDTH_TOP_WITH_TOLERANCE + (WALL_WIDTH * 2)) / 2) - (USB_PORT_WIDTH_WITH_TOLERANCE / 2), -1, WALL_WIDTH]) {
            cube(size = [USB_PORT_WIDTH_WITH_TOLERANCE, WALL_WIDTH + 3, USB_PORT_HEIGHT_WITH_TOLERANCE]);
        }
    }
}

// Using both modules
top();
translate([WIDTH_TOP + 10, 0, 0]) {
    base();
}
