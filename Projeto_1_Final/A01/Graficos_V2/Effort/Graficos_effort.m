
Dados_solve_Inicial = load("ficheiro_solve_1.txt");
Dados_solve_Inicial_Melhorada = load("ficheiro_solve_2.txt");
Dados_solve_Dinamica = load("ficheiro_solve_4.txt");


Effort_solve_inicial = Dados_solve_Inicial(1:10,3);
Posicoes_solve_inicial = Dados_solve_Inicial(1:10,1);

Effort_solve_inicial_melhorada = Dados_solve_Inicial_Melhorada(1:70,3);
Posicoes_solve_inicial_melhorada = Dados_solve_Inicial_Melhorada(1:70,1);

Effort_solve_dinamica = Dados_solve_Dinamica(1:70,3);
Posicoes_solve_dinamica = Dados_solve_Dinamica(1:70,1);


plot(Posicoes_solve_inicial,Effort_solve_inicial,'.-')
hold on
plot(Posicoes_solve_inicial_melhorada,Effort_solve_inicial_melhorada,'.-')
plot(Posicoes_solve_dinamica,Effort_solve_dinamica,'.-')

xlabel('Posições(5 a 5)')
ylabel('Entradas na função')
xticks(0:5:200)
yticks(0:5:140)
ylim([1 140])
grid on
legend('Solução Inicial','Solução 2 Inicial Melhorada','Solução 4 dinamica')
title('Graficos Effort Recursivas')
