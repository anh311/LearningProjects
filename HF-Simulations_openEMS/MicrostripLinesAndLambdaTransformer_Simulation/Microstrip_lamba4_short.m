% Lambda/4 short
close all
clear
clc
%add path for openEMS
addpath('C:\openEMS\matlab');

%init CSX Datastructure for openEMS
CSX = InitCSX();

%define materials8
CSX = AddMaterial(CSX,"FR4");
CSX = SetMaterialProperty(CSX, "FR4", "Epsilon", 4.2);
CSX = AddMetal(CSX,"Copper")

%define geometry (make the transmissionline shorter for faster Simulation)
CSX = AddBox(CSX,"FR4",0,[-30, -30, 0],[30, 30, 1.5]);         %FR4
CSX = AddBox(CSX,"Copper",0,[-30, -30, 0],[30, 30, -0.035]);  %GND
CSX = AddBox(CSX,"Copper", 0,[-30, 10, 1.5],[30, 13, 1.535]); %Line
CSX = AddBox(CSX,"Copper", 1,[-1.5,-30,1.5], [1.5,11, 1.535]); %Lambda/4
%CSX = AddBox(CSX,"Copper", 2,[-1.5,-30,-0.35],[1.5,-29,1.535]); %short

%mesh
mesh = DetectEdges(CSX);
mesh.x =[mesh.x -45 45];
mesh.y =[mesh.y -45 45];
mesh.z =[mesh.z -10 10];
mesh =SmoothMesh(mesh,2.5,1.2);

%define Grid
CSX = DefineRectGrid( CSX, 1e-3, mesh );

%define Ports
[CSX, port{1}]=AddLumpedPort(CSX, 1, 1, 50, [-30, 7, 0.5], [-30, 16, 4.535], [0, 0, 1], true);
[CSX, port{2}]=AddLumpedPort(CSX, 1, 2, 50, [30, 7, 0.5], [30, 16, 4.535], [0, 0, 1], false);

%FDTD 0 GHz - 3 GHz
F0 = 1.75e9;
Fc = 1.25e9;
FDTD = InitFDTD("NRTS",1e6, "EndCriteria",1e-4);
FDTD = SetGaussExcite(FDTD,F0,Fc);
FDTD = SetBoundaryCond(FDTD, {'PML_8' 'PML_8' 'PML_8' 'PML_8' 'PML_8' 'PML_8'})


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
ylim([-80 2]);
