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
CSX = AddBox(CSX,"FR4",0,[-50, -30, 0],[50, 30, 1.5]);         %FR4
CSX = AddBox(CSX,"Copper",1,[-50, -30, 0],[50, 30, 0]);  %GND
CSX = AddBox(CSX,"Copper", 1,[-50, 10, 1.5],[50, 13, 1.5]); %Line
CSX = AddBox(CSX,"Copper", 1,[-1.5,-30,1.5], [1.5,11, 1.5]); %Lambda/4
CSX = AddBox(CSX,"Copper", 1,[2.5,-30,1.5], [5.5,11, 1.5]); %Lambda/4
CSX = AddBox(CSX,"Copper", 1,[-1.5,-30,-0],[1.5,-29,1.5]); %short
CSX = AddBox(CSX,"Copper", 1,[2.5,-30,-0],[5.5,-29,1.5]); %short

%define Ports
[CSX, port{1}]=AddLumpedPort(CSX, 1, 1, 50, [-50, 9, -1], [-50, 14, 1.5], [0, 0, 1], true);
[CSX, port{2}]=AddLumpedPort(CSX, 1, 2, 50, [50, 9, -1], [50, 14, 1.5], [0, 0, 1], false);

%mesh
mesh = DetectEdges(CSX);

mesh.x =[mesh.x -60 60];
mesh.y =[mesh.y -45 45];
mesh.z =[mesh.z -10 10];
mesh =SmoothMesh(mesh,0.5,1.2);

%define Grid
CSX = DefineRectGrid( CSX, 1e-4, mesh );

%FDTD 0 GHz - 3 GHz
F0 = 1.75e9;
Fc = 1.25e9;
FDTD = InitFDTD("NRTS",3e5, "EndCriteria",1e-5);
FDTD = SetGaussExcite(FDTD,F0,Fc);
FDTD = SetBoundaryCond(FDTD, {'PML_8' 'PML_8' 'PML_8' 'PML_8' 'PML_8' 'PML_8'})


%Save Data
WriteOpenEMS("temp/Microstrip_lamba4_2xshort.xml",FDTD, CSX);

%model Display
CSXGeomPlot("temp/Microstrip_lamba4_2xshort.xml");

%run simulation
RunOpenEMS( "temp", "Microstrip_lamba4_2xshort.xml" );

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
