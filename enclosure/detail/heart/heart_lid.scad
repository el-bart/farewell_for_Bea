include <heart_common.scad>

lid_gap = 0.2;

heart([size_heart[0] + border - gap, size_heart[1], base_thickness], 0);
heart([size_heart[0] - 2 * border - gap - lid_gap, size_heart[1], base_thickness], base_thickness);
