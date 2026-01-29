
% WilkinsonPowerDividers
close all
clear
clc
%add path for openEMS
addpath('C:\openEMS\matlab');

c0=3e8;
f_max=3e9;
unit = 1e-3;
resolution = c0/(f_max*sqrt(4.2))/unit/60;

%init CSX Datastructure for openEMS
CSX = InitCSX();

%define materials8
CSX = AddMaterial(CSX,"FR4");
CSX = SetMaterialProperty(CSX, "FR4", "Epsilon", 4.2);
CSX = AddMetal(CSX,"Copper")

%define geometry (make the transmissionline shorter for faster Simulation)
CSX = AddBox(CSX,"FR4",0,[-40, -40, 0],[40, 40, 1.5]); %FR4
CSX = AddBox(CSX,"Copper",1,[-40, -40, 0],[40, 40, 0]);  %GND
CSX = AddBox(CSX,"Copper", 1, [-40,20,1.5],[40,23,1.5]);  %Lane Port 3 to 4
CSX = AddBox(CSX,"Copper", 1,[-20,20,1.5],[20,26.1,1.5]);  %Lane Port 3 to 4 lamda/4
CSX = AddBox(CSX,"Copper", 1,[-40,-20,1.5],[40,-23,1.5]);  %Lane Port 1 to 2
CSX = AddBox(CSX,"Copper", 1,[-20,-20,1.5],[20,-26.1,1.5]);  %Lane Port 1 to 2 lamda/4
CSX = AddBox(CSX,"Copper", 1, [-20,20,1.5],[-23,-20,1.5]);  %Lane Port 3 to 2
CSX = AddBox(CSX,"Copper", 1, [20,-20,1.5],[23,20,1.5]);  %Lane Port 1 to 4

%define mesh
mesh.x = SmoothMeshLines([-60 -50 0 50 60], resolution, 1.3);
mesh.y = SmoothMeshLines([-40 -30 10 13 30 40 ], resolution, 1.3);
mesh.z = SmoothMeshLines([-5 -1.5 0 1.5 10], resolution, 1.5);

CSX = DefineRectGrid( CSX, 1e-3, mesh );

F0 = 3e9;
Fc = 3e9;
FDTD = InitFDTD("NRTS",3e5, "EndCriteria",1e-4);
FDTD = SetGaussExcite(FDTD,F0,Fc);
FDTD = SetBoundaryCond(FDTD, {'PML_8' 'PML_8' 'MUR' 'MUR' 'PEC' 'MUR'})

%Save Data
WriteOpenEMS("temp/Branch_Line.xml",FDTD, CSX);

%model Display
CSXGeomPlot("temp/Branch_Line.xml");



