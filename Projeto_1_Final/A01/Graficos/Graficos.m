Dados_solve_5 = load("ficheiro_solve_tomas.txt");
Tempos_5 = Dados_solve_5(:,4);
Posicoes_5 = Dados_solve_5(:,1);

Dados_solve_2 = load("ficheiro_solve2.txt");
Tempos_2 = Dados_solve_2(:,4);
Posicoes_2 = Dados_solve_2(:,1);

Dados_solve_3 = load("ficheiro_solve3.txt");
Tempos_3 = Dados_solve_3(:,4);
Posicoes_3 = Dados_solve_3(:,1);

Dados_solve_4 = load("ficheiro_solve4.txt");
Tempos_4 = Dados_solve_4(:,4);
Posicoes_4 = Dados_solve_4(:,1);


figure(1)
plot(Posicoes_2,Tempos_2,'.-')

hold on

plot(Posicoes_3,Tempos_3,'.-')

plot(Posicoes_4,Tempos_4,'.-')

plot(Posicoes_5,Tempos_5,'.-')

hold off
xlabel('Posições(20 a 20)')
ylabel('Tempo(s)')
xticks(0:20:800)
grid on
legend('Solução 2 recursiva','Solução 3 não recursiva','Solução 4 dinamica','Solução 5 não recursiva mais lenta')
title('Graficos soluções melhoradas')
