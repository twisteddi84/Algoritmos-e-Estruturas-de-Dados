
Dados_solve_5=load("ficheiro_solve_tomas.txt");
Tempos_5 = Dados_solve_5(:,4);
Posicoes_5 = Dados_solve_5(:,1);

plot(Posicoes_5,Tempos_5,'.-')

xlabel('Posições(20 a 20)')
ylabel('Tempo(s)')
xticks(0:20:800)
grid on
legend('Solução 5 (slow while)')
title('Grafico soluçao 5 (slow while)')