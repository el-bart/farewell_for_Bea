include <unicorn_config.scad>

module unicorn()
{
  scale(0.6*[1,1])
    translate([-90, -190])
      import("unicorn.svg");
}


difference()
{
  circle(d=main_d);
  circle(d=main_d-2);
}
unicorn();
