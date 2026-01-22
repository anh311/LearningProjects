
% Lambda/4 short 2x
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
CSX = AddBox(CSX,"FR4",0,[-50, -30, 0],[50, 30, 1.5]);         %FR4
CSX = AddBox(CSX,"Copper",1,[-50, -30, 0],[50, 30, 0]);  %GND
CSX = AddBox(CSX,"Copper", 1,[-50, 10, 1.5],[50, 13, 1.5]); %Line
CSX = AddBox(CSX,"Copper", 1,[-1.5,-30,1.5], [1.5,11, 1.5]); %Lambda/4
CSX = AddBox(CSX,"Copper", 1,[-1.5,-30,-0],[1.5,-29,1.5]); %short
CSX = AddBox(CSX,"Copper", 1,[5.5,-30,1.5], [8.5,11, 1.5]); %Lambda/4
CSX = AddBox(CSX,"Copper", 1,[5.5,-30,-0],[8.5,-29,1.5]); %short
%define mesh
mesh.x = SmoothMeshLines([-60 -50 0 50 60], resolution, 1.3);
mesh.y = SmoothMeshLines([-40 -30 10 13 30 40 ], resolution, 1.3);
mesh.z = SmoothMeshLines([-5 -1.5 0 1.5 10], resolution, 1.5);


%define Grid
%mash in mm (FDTD)
CSX = DefineRectGrid( CSX, 1e-3, mesh );

%define Ports
[CSX,port{1}] = AddMSLPort( CSX, 9, 1, 'Copper', [-50 10 1.5], [0 13 0], 0, [0 0 -1], 'ExcitePort', true,'FeedShift', 10*resolution,"Feed_R",50);
[CSX,port{2}] = AddMSLPort( CSX, 9, 2, 'Copper', [50 10 1.5], [0 13 0], 0, [0 0 -1],'ExcitePort', false,"Feed_R",50);


%FDTD 0 GHz - 3 GHz
##F0 = 1.75e9;
##Fc = 1.25e9;
F0 = 3e9;
Fc = 3e9;
FDTD = InitFDTD("NRTS",3e5, "EndCriteria",1e-4);
FDTD = SetGaussExcite(FDTD,F0,Fc);
FDTD = SetBoundaryCond(FDTD, {'PML_8' 'PML_8' 'MUR' 'MUR' 'PEC' 'MUR'})


%Save Data
WriteOpenEMS("temp/Microstrip_lamba4_short.xml",FDTD, CSX);

%model Display
CSXGeomPlot("temp/Microstrip_lamba4_short.xml");

%run simulation
RunOpenEMS( "temp", "Microstrip_lamba4_short.xml" );

% Display simulation
close all
f = linspace( 0.5e9, 3e9, 400);

port = calcPort( port, "temp", f, 'RefImpedance', 50);
s11 = port{1}.uf.ref./ port{1}.uf.inc;
s21 = port{2}.uf.ref./ port{1}.uf.inc;

plot(f/1e9,20*log10(abs(s11)),'k-','LineWidth',1);
hold on;
grid on;
grid minor;
plot(f/1e9,20*log10(abs(s21)),'r--','LineWidth',1);
title('Microstrip S-Parameters Simulation', 'FontSize', 18);
hLeg = legend('S_{11}', 'S_{21}','FontSize', 12);
set(hLeg, 'Box', 'off', 'Location', 'northeastoutside');
ylabel('S-Parameter (dB)','FontSize',16);
xlabel('frequency (GHz) \rightarrow','FontSize',16);
ylim([-40 2]);
