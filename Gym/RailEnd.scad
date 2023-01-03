/**
* Plastic insert to snap into the end offset* the
* drawer slide for Ninda's Gym
**/


$fn=100;

hole_dia = 5.25;
hole_edge_from_end = 16.5;
rail_width = 11.5;
rail_width_inner = 6.5;
rail_depth = 6;
rail_thickness = 1.4;

cap_dia = rail_width;

cap_inner_length = hole_edge_from_end + 2*hole_dia;
cap_length = cap_inner_length + cap_dia / 2;

hole_spacing = 14.15 - hole_dia;

module half_circle(dia, thickness) {

difference() {
cylinder(h = thickness, d = dia);

translate([-(dia+1)/2,-dia,-thickness/2])
cube([dia+1, dia, thickness*2]);

}

}


module rail_inner() {
scale([6.5/10.7,1,1])
linear_extrude(height = cap_inner_length)
polygon([
[0,0],
[0,0.7],
[0,1.4],
[0.3,1.5],
[0.6,1.6],
[0.75,1.75],
[0.9,1.9],
[1,2.1],
[1.1,2.3],
[1.1,2.55],
[1.1,2.8],
[1,2.95],
[0.9,3.1],
[0.8,3.3],
[0.8,4.25],
[0.8,5.2],
[1.1,5.6],
[1.4,5.8],
[2,6],
[2.5,6.1],
[3.1,6.1],
[3.4,6],
[4.6,5.4],
[7.2,5.4],
[7.8,5.5],
[8.8,6.1],
[9.05,6.15],
[9.3,6.2],
[9.9,6.2],
[10.1,6.15],
[10.3,6.1],
[10.4,6],
[10.55,5.75],
[10.7,5.5],
[10.6,0.1],
[9.3,0.1],
[9.3,3.78],
[9.25,4.03],
[8.95,4.34],
[8.7,4.4],
[4.6,4.4],
[2.9,4.65],
[2.5,4.7],
[2.2,4.5],
[2.1,3.3],
[2.3,2.9],
[2.3,2.5],
[2.2,1.9],
[1.4,1.2],
[1.4,0.1],
[0.7,0.05],
[0,0]]);

translate([rail_width/2 - 2,rail_depth - rail_thickness - 0.4,cap_inner_length - hole_dia/2 - hole_edge_from_end - 0.5])
rotate([-90,0,0])
cylinder(h=2 * rail_thickness, d=hole_dia - 0.5);

// now stick a half-circle on the top on a square base
translate([ - 2 * rail_thickness,0,cap_inner_length - 0.4]){
cube([rail_width, rail_depth + 3 * rail_thickness, rail_thickness]);

translate([0,rail_depth + rail_thickness+0.5,-2 * rail_thickness+0.4])
cube([rail_width, rail_thickness*1.5,rail_thickness*2]);
}

translate([3 ,rail_depth,cap_inner_length+rail_thickness-0.4])
rotate([90,0,0])
half_circle(rail_width, rail_thickness);
}

module end_stop() {
// three snap-ins with a rod sticking out

cylinder(h=3 * rail_thickness, d = hole_dia);
translate([hole_spacing,0,0])
cylinder(h=3 * rail_thickness, d = hole_dia);
translate([2 * hole_spacing,0,0])
cylinder(h=3 * rail_thickness, d = hole_dia);

translate([-hole_spacing/2,-0.75 * hole_dia,0])
cube([3 * hole_spacing, 1.5 * hole_dia, rail_thickness]);

// sticky-out bit
translate([2 * hole_spacing - hole_dia/2,-0.75 * hole_dia,0])
cube([5,30,rail_thickness]);

translate([2 * hole_spacing - hole_dia/2 + 1,16,0])
cube([3,10,10 *rail_thickness]);
}

module microswitch_mount() {
w = 12.7;
d = 5.6;
h = 6.5;
terminal_length = 6;
mount_to_roller = 20;
hole_dia = 2;
hole_spacing = 6;
// Flat base which can be glued on
cube([w,w,2]);
//side panel with sticky out bits to snap the switch on to
cube([w,2,20]);
//sticky out bit

translate([w/2,-0.4,12])
rotate([90,0,0])
cylinder(h=d + 3, d=hole_dia - 0.3);

translate([w/2, -0.4, 12 + hole_spacing])
rotate([90,0,0])
cylinder(h=d + 3, d=hole_dia - 0.3);
}


microswitch_mount();

//rail_inner();

//translate([20,0,0])end_stop();

//half_circle(rail_width, rail_thickness);
