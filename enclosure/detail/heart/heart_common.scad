size_heart = [100, 0, 20];
base_thickness = 2;
border = 5;
gap = 20;

module heart(size, offset_z) {
    $fn = 500;
    base = size[0] * 2.0 / 3.0;
    radius = size[0] / 3.0;
    
    translate([-size[0] * 0.43, -size[0] * 0.43, offset_z]) {
        linear_extrude(size[2]) {
          square(base);

          translate([radius, base, 0])
          circle(radius);

          translate([base, radius, 0])
          circle(radius);
        }
    }
}

module heart_box(size, base_thickness, border, gap) {
    hole_radius = 2;
    hole_radius_button = 1.5;
    hole_radius_back = 6;

    offset_hole_back = -gap * sqrt(2) + hole_radius_back;

    difference() {
        union() {
            difference() {
                heart(size, 0);
                heart([size[0] - border, size[1], size[2]], base_thickness);
            }

            difference() {
                heart([size[0] - border - gap, size[1], size[2] - base_thickness], 0);
                heart([size[0] - 2 * border - gap, size[1], size[2] - base_thickness], base_thickness);
            }
        }
        
        translate([18, 18, base_thickness + hole_radius]) {
            rotate([90, 0, -45]) {
                cylinder(h = 5, r = hole_radius, center = true, $fn = 100);
            }
        }
        
        translate([offset_hole_back, offset_hole_back, 0]) {
            cylinder(h = 4 * base_thickness, r = hole_radius_back, center = true, $fn = 100);
        }
        
        translate([offset_hole_back / 2, offset_hole_back / 2, 0]) {
            cylinder(h = 4 * base_thickness, r = hole_radius_button, center = true, $fn = 100);
        }
    }
}
