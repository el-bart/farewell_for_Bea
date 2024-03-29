include <detail/unicorn_config.scad>
use <unicorn_bottom.scad>

offset = -15;
size_ext = [80, 30+50, 30];
size_int = [22, size_ext[1], 18];
usb_port_size = [7, 9, 4];
display = true;

module button_mock()
{
  // core
  cylinder(d=9.6, h=10.25);
  translate([0, 0, 10.25])
  {
    // thread
    cylinder(d=6.7, h=5.9);
    // button
    translate([0, 0, 5.9])
    {
      cylinder(d=3, h=5);
      translate([0, 0, 5])
        cylinder(d=5.8, h=2.5);
    }
  }
  // contacts
  for(dx=[-1, +1])
    translate([dx*4.4/2-0.5/2, -3/2, -6])
      cube([0.5, 3, 6]);
}

module screw_holes(dh=0)
{
  edge = 5;
  for(dx=[-1,+1])
    for(dz=[-1,+1])
      translate([dx*(size_ext[0]-edge)/2, 0, dz*(size_ext[2]-edge)/2])
        translate([0, -eps, size_ext[2]/2])
          rotate([-90, 0, 0])
            cylinder(d=2.2+0.1, h=6.5+eps, $fn=30);
}

module pcb_stub()
{
  size = [26, 34, 2];
  translate([-size[0]/2, 0, 0])
  {
    cube(size);
    uc_size = [20, 28, 4];
    // wifi part
    translate([(size[0]-uc_size[0])/2, 0, size[2]])
      cube(uc_size);
    // USB port
    translate([(size[0]-usb_port_size[0])/2, (size[1]-usb_port_size[1]), -usb_port_size[2]])
      cube(usb_port_size);
  }
}

module unicorn_medal_placeholder(dh)
{
  cylinder(d=main_d, h=main_h+wall+dh, $fn=200);
}

module base_core()
{
  module shell()
  {
    difference()
    {
      translate([-size_ext[0]/2, offset, 0])
        cube(size_ext);
      // cable slot
      translate([0, 0, 10/2+wall])
        rotate([-90, 0, 0])
          cylinder(d=10, h=14, $fn=30);
      // electronics compartment
      translate([-size_int[0]/2, 10+2*wall, 2*wall])
        cube(size_int);
      // PCB slide-in slot
      translate([-28/2, 30+eps, 8])
        cube([28, 35, 3.5]);
      translate([0, 59, 0])
        screw_holes();
    }
    if(display)
      %translate([0, 30, 8])
        pcb_stub();
  }

  intersection()
  {
    shell();
    // front rounding
    d = 400;
    translate([0, d/2+offset, 0])
      cylinder(d=d, h=50, $fn=200);
  }
}


module base()
{
  module location()
  {
    rotate([90-base_angle, 0, 0])
      translate([0, main_d/2+wall, 0])
        children();
  }
  difference()
  {
    base_core();
    location()
      unicorn_medal_placeholder(20);
    translate([25, 58.5+eps, 17])
    {
      translate([0, 0, 9+eps])
        cylinder(d=6.5+0.5, h=5.5-1.5, $fn=50);
      translate(-13/2*[1,1,0] + [0, 0, -7.7-6])
      {
        cube([13, 13, 18+6]);
        translate([-10, 13-4-2, 0])
          cube([13+10, 4, 4]);
      }
      if(display)
        %button_mock();
    }
  }

  // display
  if(display)
  {
    %location()
    {
      if(1)
        unicorn_medal_placeholder(0);
      else
        unicorn_bottom();
    }
    %translate([0, 65, 0])
      cover();
  }
}

module cover()
{
  difference()
  {
    translate([-80/2, 0, 0])
    {
      difference()
      {
        cube([80, 2, 30]);
        // USB port slot
        port_hole = usb_port_size + 2*[1.5,0,1];
        translate([80/2-port_hole[0]/2, -port_hole[1]/2, 3])
          cube(port_hole);
      }
    }
    screw_holes();
  }
}


base();

translate([0, 100, 0])
  rotate([90, 0, 0])
    cover();
