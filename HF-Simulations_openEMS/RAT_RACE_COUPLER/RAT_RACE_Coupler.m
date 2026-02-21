%Rat Race Coupler

close all
clear
clc

% Add OpenEMS to MATLAB Environment
addpath('C:\openEMS\matlab');

%define variables
c0=3e8;
F0=1e9;
FC=0.5e9;


unit = 1e-3; % all length in mm
length = 80;
width = 80;
hight=1.5;
MSL_width_50OHm=3;
MSL_width_ring=1.5;
lamda_4_length=36.6;
radius=34.9;

resolution = c0/(F0*sqrt(4.2))/unit/60;

%init CSX Datastructure
CSX=InitCSX();

%define materials
CSX = AddMaterial(CSX,"FR4");
CSX = SetMaterialProperty(CSX,"FR4","Epsilon",4.2);
CSX = AddMetal(CSX,"Copper");

%define geometry
%%FR4
CSX = AddBox(CSX, "FR4", 0, [-length/2, -width/2, 0], [length/2, width/2, hight]);
CSX = AddBox(CSX, "Copper", 0, [-length/2, -width/2, 0],[length/2, width/2, 0]);
CSX = AddCylindricalShell(CSX,'Copper',10,[0 0 hight],[0 0 hight+0.035],radius-0.75, 1.5);






%define mesh
mesh.x = SmoothMeshLines([-40 -21.5 -18.5 0 18.5 21.5 40], resolution, 1.3);
mesh.y = SmoothMeshLines([-40 -23 -20 -17 0 17 20 23 40], resolution, 1.3);
mesh.z = SmoothMeshLines([-5 -1.5 0 1.5 10], resolution, 1.5);

CSX = DefineRectGrid( CSX, 1e-3, mesh );


FDTD = InitFDTD("NRTS",3e5, "EndCriteria",1e-4);

%Save Data
WriteOpenEMS("temp/RAT_RACE_coupler.xml", FDTD, CSX);
%model Display
CSXGeomPlot("temp/RAT_RACE_coupler.xml");
