##close all
##clear
##clc
addpath('C:\openEMS\matlab');
%init "CSX" 3D CAD data structure (coordinate system: 0 -> Cartesian)
CSX = InitCSX();

%define Materials
CSX = AddMetal(CSX, "copper");                          % Material für MicrostripLine and GND
CSX = AddMaterial(CSX, "FR4");
CSX = SetMaterialProperty( CSX, 'FR4', 'Epsilon', 4.2); % FR4 Epsilon

%define geometry
CSX = AddBox(CSX, "FR4",0 ,[-50, -30, 0],[50, 30, 1.5]); %FR4
CSX = AddBox(CSX, "copper",1 ,[-50, -30, 0],[50, 30, -0.035]); %GND
CSX = AddBox(CSX, "copper",1 ,[-50, 10, 1.5],[50, 13, 1.535]); %Microstrip

%define Ports
[CSX, port{1}]=AddLumpedPort(CSX, 1, 1, 50, [-50, 9, -0.1], [-50, 14, 1.635], [0, 0, 1], true);
[CSX, port{2}]=AddLumpedPort(CSX, 1, 2, 50, [50, 9, -0.1], [50, 14, 1.635], [0, 0, 1], false);

%mesh
mesh = DetectEdges(CSX);
%mesh dimension
mesh.x =[mesh.x -65 65];
mesh.y =[mesh.y -45 45];
mesh.z =[mesh.z -10 10];
%max_res~lambda/10, ratio~1.2 for stable computing
a=1
mesh =SmoothMesh(mesh,1.5 ,1.2);


%define Grid
%mash in mm (FDTD)
CSX = DefineRectGrid( CSX, 1e-3, mesh );


%FDTD 0 GHz - 3 GHz
F0=1.75e9;
Fc=1.25e9;
%%init with 3e5 max. timesteps and -40dB end-criteria
FDTD = InitFDTD('NrTS', 3e5, 'EndCriteria', 1e-4);
FDTD = SetGaussExcite(FDTD,F0,Fc);
FDTD = SetBoundaryCond(FDTD, {'PML_8' 'PML_8' 'PML_8' 'PML_8' 'PML_8' 'PML_8'});

%Save Data
WriteOpenEMS("temp/Microstrip.xml", FDTD, CSX);

%model Display
CSXGeomPlot("temp/Microstrip.xml");

%run simulation
RunOpenEMS( "temp", "Microstrip.xml" );

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
