
Dados_solve_4 = load("ficheiro_solve_4.txt");
Tempos_solve_4 = Dados_solve_4(:,4);
Posicoes_solve_4 = Dados_solve_4(:,1);


plot(Posicoes_solve_4,Tempos_solve_4,'.-')

legend('Solução 4 Dynamic')
xlabel('Posições')
ylabel('Tempos(s)')
grid on
title('Gráfico Tempo Solução 4 (Dynamic)')
xticks(0:20:800)

