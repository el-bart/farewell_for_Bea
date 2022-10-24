include <detail/config.scad>
use <detail/unicorn.scad>
use <unicorn_top.scad>

module unicorn_bottom()
{
  module unicorn_head()
  {
    linear_extrude(height=main_h)
      unicorn();
  }
  module unicorn_head_slot()
  {
    linear_extrude(height=main_h)
      offset(r=main_hole)
        unicorn();
  }
  module cable_slot()
  {
    translate([0, -60, main_h/2])
    {
      rotate([90, 0, 0])
        cylinder(d=7, h=20);
      translate([0, -12, -main_h+5])
        cylinder(d=10, h=10);
    }
  }

  difference()
  {
    cylinder(d=main_d, h=main_h, $fn=200);
    translate([0,0,wall])
      unicorn_head_slot();
    cable_slot();
  }
  translate([0,0,wall])
    unicorn_head();
}


unicorn_bottom();

%translate([0, 0, main_h+wall+eps])
  rotate([0, 180, 0])
    unicorn_top();
