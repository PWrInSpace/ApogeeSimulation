clear all;

t = 0:0.1:25;

normal = fopen('data_sim_przed.txt','r');
noAir = fopen('data_sim_po.txt','r');
energy = fopen('data_sim_nowy_alg.txt','r');

formatSpec = '%f';
A = fscanf(normal,formatSpec);
B = fscanf(noAir,formatSpec);
C = fscanf(energy,formatSpec);

figure();
plot(A, 'r');
hold on;
plot(B, 'g');
hold on;
plot(C, 'b');
hold on;
leg = {'zwykly'; 'bez oporu powietrza'; 'rownanie energii'};
legend(leg);