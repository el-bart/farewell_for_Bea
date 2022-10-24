include <detail/config.scad>
use <detail/unicorn.scad>
use <unicorn_top.scad>

module unicorn_top()
{
  module unicorn_head_slot()
  {
    linear_extrude(height=wall+2*eps)
      offset(r=main_hole_ext)
        mirror([1, 0]) // mirrored, so that glossy surface stays on top
          unicorn();
  }

  difference()
  {
    cylinder(d=main_d, h=wall, $fn=200);
    translate([0,0,-eps])
      unicorn_head_slot();
  }
}


unicorn_top();
