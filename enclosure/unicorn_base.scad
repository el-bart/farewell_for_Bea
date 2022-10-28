include <detail/config.scad>
use <detail/unicorn.scad>
use <unicorn_top.scad>
use <unicorn_bottom.scad>

module unicorn_medal_placeholder(dh)
{
  cylinder(d=main_d, h=main_h+wall+dh, $fn=200);
}


unicorn_medal_placeholder(0.75);
