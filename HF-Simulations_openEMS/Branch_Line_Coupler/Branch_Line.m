
% Branch_Line
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
CSX = AddBox(CSX,"Copper", 1, [-40,18.5,1.5],[40,21.5,1.5]);  %Lane Port 1 to 2
CSX = AddBox(CSX,"Copper", 10,[-20,17,1.5],[20,23,1.5]);  %Lane Port 1 to 2 lamda/4
CSX = AddBox(CSX,"Copper", 1,[-40,-18.5,1.5],[40,-21.5,1.5]);  %Lane Port 3 to 4
CSX = AddBox(CSX,"Copper", 10,[-20,-17,1.5],[20,-23,1.5]);  %Lane Port 3 to 4 lamda/4
CSX = AddBox(CSX,"Copper", 1, [-18.5,20,1.5],[-21.5,-20,1.5]);  %Lane Port 1 to 4
CSX = AddBox(CSX,"Copper", 1, [18.5,20,1.5],[21.5,-20,1.5]);  %Lane Port 2 to 3

%define mesh
mesh.x = SmoothMeshLines([-60 -40 -21.5 -18.5 0 18.5 21.5 40 60], resolution, 1.3);
mesh.y = SmoothMeshLines([-40 -23 -20 -17 0 17 20 23 40], resolution, 1.3);
mesh.z = SmoothMeshLines([-5 -1.5 0 1.5 10], resolution, 1.5);

CSX = DefineRectGrid( CSX, 1e-3, mesh );

%define Ports
[CSX,port{1}]=AddMSLPort(CSX, 9, 1, "Copper",[-40,18.5,1.5],[-35,21.5,0],"x", [0 0 -1],"ExcitePort", true,"Feed_R", 50 );
[CSX,port{2}]=AddMSLPort(CSX, 9, 2, "Copper",[40,18.5,1.5],[35,21.5,0],"x", [0 0 -1],"ExcitePort", false,"Feed_R", 50 );
[CSX,port{4}]=AddMSLPort(CSX, 9, 4, "Copper",[-40,-18.5,1.5],[-35,-21.5,0],"x", [0 0 -1],"ExcitePort", false,"Feed_R", 50 );
[CSX,port{3}]=AddMSLPort(CSX, 9, 3, "Copper",[40,-18.5,1.5],[35,-21.5,0],"x", [0 0 -1],"ExcitePort", false,"Feed_R", 50 );
F0 = 3e9;
Fc = 3e9;
FDTD = InitFDTD("NRTS",3e5, "EndCriteria",1e-4);
FDTD = SetGaussExcite(FDTD,F0,Fc);
FDTD = SetBoundaryCond(FDTD, {'PML_8' 'PML_8' 'MUR' 'MUR' 'PEC' 'MUR'})

%Save Data
WriteOpenEMS("temp/Branch_Line.xml",FDTD, CSX);

%model Display
CSXGeomPlot("temp/Branch_Line.xml");

%run simulation
RunOpenEMS( "temp", "Branch_Line.xml" );

% Display simulation
close all
f = linspace( 0.5e9, 1.5e9, 400);

port = calcPort( port, "temp", f, 'RefImpedance', 50);

s11 = port{1}.uf.ref ./ port{1}.uf.inc;
s21 = port{2}.uf.ref ./ port{1}.uf.inc;
s31 = port{3}.uf.ref ./ port{1}.uf.inc;
s41 = port{4}.uf.ref ./ port{1}.uf.inc;

% Plotten
%S-Parameter
figure;
plot(f/1e9, 20*log10(abs(s11)), 'k-', 'LineWidth', 1.5); hold on;
plot(f/1e9, 20*log10(abs(s21)), 'r--', 'LineWidth', 1.5);
plot(f/1e9, 20*log10(abs(s31)), 'b-.', 'LineWidth', 1.5);
plot(f/1e9, 20*log10(abs(s41)), 'g:', 'LineWidth', 1.5);

hold on;
grid on;
grid minor;
plot(f/1e9,20*log10(abs(s21)),'r--','LineWidth',1);
title('Microstrip S-Parameters Simulation', 'FontSize', 18);
hLeg = legend('S_{11}', 'S_{21}', 'S_{31}', 'S_{41}','FontSize', 12);
set(hLeg, 'Box', 'off', 'Location', 'northeastoutside');
ylabel('S-Parameter (dB)','FontSize',16);
xlabel('frequency (GHz) \rightarrow','FontSize',16);
xlim([0.5 1.5]);
%Phase
phase_s21 = angle(s21) * 180/pi;
phase_s31 = angle(s31) * 180/pi;
phase_diff = unwrap((phase_s21 - phase_s31) * pi/180) * 180/pi;

figure('Name', 'Phase Analysis', 'Color', 'w');
plot(f/1e9, phase_diff, 'm-', 'LineWidth', 2);
hold on;

grid on;
grid minor;
title('Phase Difference (Port 2 vs Port 3)', 'FontSize', 14);
ylabel('Phase (Degrees)', 'FontSize', 12);
xlabel('Frequency (GHz)', 'FontSize', 12);
xlim([0.5 1.5]);
