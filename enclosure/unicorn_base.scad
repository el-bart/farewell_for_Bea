include <detail/config.scad>
use <detail/unicorn.scad>
use <unicorn_top.scad>
use <unicorn_bottom.scad>

module unicorn_medal_placeholder()
{
  cylinder(d=main_d, h=main_h+wall, $fn=200);
}


unicorn_medal_placeholder();
