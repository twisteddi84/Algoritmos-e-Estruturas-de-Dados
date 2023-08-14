 //
// AED, August 2022 (Tomás Oliveira e Silva)
//
// First practical assignement (speed run)
//
// Compile using either
//   cc -Wall -O2 -D_use_zlib_=0 solution_speed_run.c -lm
// or
//   cc -Wall -O2 -D_use_zlib_=1 solution_speed_run.c -lm -lz
//
// Place your student numbers and names here
//   N.Mec. XXXXXX  Name: XXXXXXX
//


//
// static configuration
//

#define _max_road_size_  800  // the maximum problem size
#define _min_road_speed_   2  // must not be smaller than 1, shouldnot be smaller than 2
#define _max_road_speed_   9  // must not be larger than 9 (only because of the PDF figure)


//
// include files --- as this is a small project, we include the PDF generation code directly from make_custom_pdf.c
//

#include <math.h>
#include <stdio.h>
#include "../P02/elapsed_time.h"
#include "make_custom_pdf.c"


//
// road stuff
//

static int max_road_speed[1 + _max_road_size_]; // positions 0.._max_road_size_

static void init_road_speeds(void)
{
  double speed;
  int i;

  for(i = 0;i <= _max_road_size_;i++)
  {
    speed = (double)_max_road_speed_ * (0.55 + 0.30 * sin(0.11 * (double)i) + 0.10 * sin(0.17 * (double)i + 1.0) + 0.15 * sin(0.19 * (double)i));
    max_road_speed[i] = (int)floor(0.5 + speed) + (int)((unsigned int)random() % 3u) - 1;
    if(max_road_speed[i] < _min_road_speed_)
      max_road_speed[i] = _min_road_speed_;
    if(max_road_speed[i] > _max_road_speed_)
      max_road_speed[i] = _max_road_speed_;
  }
}


//
// description of a solution
//

typedef struct
{
  int n_moves;                         // the number of moves (the number of positions is one more than the number of moves)
  int positions[1 + _max_road_size_];  // the positions (the first one must be zero)
  int ultimo_incremento[3]; //array para guardar o valor da posição, da velocidade e do n. de movimentos do ultimo incremento
}
solution_t;


//
// the (very inefficient) recursive solution given to the students
//

static solution_t solution_1,solution_1_best;
static double solution_1_elapsed_time; // time it took to solve the problem
static unsigned long solution_1_count; // effort dispended solving the problem

static solution_t solution_2,solution_2_best,solution_2_last;
static double solution_2_elapsed_time; // time it took to solve the problem
static unsigned long solution_2_count; // effort dispended solving the problem

static solution_t solution_3,solution_3_best;
static double solution_3_elapsed_time; // time it took to solve the problem
static unsigned long solution_3_count; // effort dispended solving the problem

static solution_t solution_4,solution_4_best;
static double solution_4_elapsed_time; // time it took to solve the problem
static unsigned long solution_4_count; // effort dispended solving the problem

static solution_t solution_5,solution_5_best;
static double solution_5_elapsed_time; // time it took to solve the problem
static unsigned long solution_5_count; // effort dispended solving the problem



static void solution_1_recursion(int move_number,int position,int speed,int final_position)
{
  int i,new_speed;

  // record move
  solution_1_count++;
  solution_1.positions[move_number] = position;
  // is it a solution?
  if(position == final_position && speed == 1)
  {
    // is it a better solution?
    if(move_number < solution_1_best.n_moves)
    {
      solution_1_best = solution_1;
      solution_1_best.n_moves = move_number;
    }
    return;
  }
  // no, try all legal speeds
  for(new_speed = speed - 1;new_speed <= speed + 1;new_speed++)
    if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
    {
      for(i = 0;i <= new_speed && new_speed <= max_road_speed[position + i];i++)
        ;
      if(i > new_speed)
        solution_1_recursion(move_number + 1,position + new_speed,new_speed,final_position);
    }
}

static void solve_1(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_1: bad final_position\n");
    exit(1);
  }
  solution_1_elapsed_time = cpu_time();
  solution_1_count = 0ul;
  solution_1_best.n_moves = final_position + 100;
  solution_1_recursion(0,0,0,final_position);
  solution_1_elapsed_time = cpu_time() - solution_1_elapsed_time;
}



//Solve 2 (1 melhorada)
static int solution_2_recursion(int move_number,int position,int speed,int final_position)
{
  int i,new_speed;

  // record move
  solution_2_count++;
  solution_2.positions[move_number] = position;
  // is it a solution?
  if(position == final_position && speed == 1)
  {
    // is it a better solution?
    if(move_number < solution_2_best.n_moves)
    {
      solution_2_best = solution_2;
      solution_2_best.n_moves = move_number;
      solution_2_last = solution_2_best;
    }
    return 1;
  }
  if(solution_2_best.positions[move_number] > solution_2.positions[move_number]){
	return 0;
	}
  // no, try all legal speeds
  for(new_speed = speed + 1;new_speed >= speed - 1;new_speed--) {
    if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
    {
      for(i = 0;i <= new_speed && new_speed <= max_road_speed[position + i];i++)
        ;
      if(i > new_speed){
      int verify = solution_2_recursion(move_number + 1,position + new_speed,new_speed,final_position);
      if (new_speed - speed == 1){
        solution_2_last.ultimo_incremento[0] = move_number + 1;
        solution_2_last.ultimo_incremento[1] = position + new_speed;
        solution_2_last.ultimo_incremento[2] = new_speed;      
       }
      if (verify == 1)
      {
        return 1;
      } 
    }
      }
    }
    return 0;
}


static void solve_2(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_1: bad final_position\n");
    exit(1);
  }
  solution_2_elapsed_time = cpu_time();
  solution_2_count = 0ul;
  solution_2_best.n_moves = final_position + 100;
  solution_2_recursion(solution_2_last.ultimo_incremento[0],solution_2_last.ultimo_incremento[1],solution_2_last.ultimo_incremento[2],final_position);
  solution_2_elapsed_time = cpu_time() - solution_2_elapsed_time;
}


//Solve 3 (while)
static void solution_3_while_dynamic(int move_number,int position,int speed,int final_position)
{

  int new_speed = solution_3.ultimo_incremento[2];
  int new_speed_test;
  int position_test;
  int variavel_teste;
  int position_test_anterior; 
  int teste_max_speed;
  int moves = solution_3.ultimo_incremento[0];
  position = solution_3.ultimo_incremento[1];
  speed = solution_3.ultimo_incremento[2];
  
 


  while(position<final_position){ // Executa enquanto a posição não for a final_position

    solution_3_count++; // Conta o número de iterações
    speed = new_speed; // Atribui a speed o valor de new_speed
    variavel_teste = 1; // Variável que controla a entrada nos if's seguintes
    position_test = position; // Atribui a position_test o valor de position

    teste_max_speed = 1; // Variável que controla se a speed ultrapassa o max_road_speed

    
    
    if(final_position==1){
      moves = 1;
      solution_3.positions[moves] = 1;
      solution_3_best.positions[moves] = 1;
      solution_3.ultimo_incremento[0] = moves;
      solution_3.ultimo_incremento[1] = 1;
      solution_3.ultimo_incremento[2] = 1;
      
      break;
    }
    else{
    if(variavel_teste == 1 && speed<_max_road_speed_){ // Se speed for menor que o max_road_speed
      position_test = position;
      for(new_speed_test = speed +1;new_speed_test >= 1; new_speed_test--){ //Loop desde speed+1 até 1
        position_test_anterior = position_test; //Atribui a position_test_anterior o valor de position_test
        position_test = position_test + new_speed_test; //Atribui a position_test o valor de position_test + new_speed_test
        for(int i = position_test_anterior; i <= position_test; i++){ //Testa max_speed desde posiçao inicial+1 ate posiçao depois do incremento de velocidade
          if(max_road_speed[i]<new_speed_test){ //Se max_speed for menor que new_speed
            teste_max_speed = 0;  //Pode dar break;
            break;
          }
        }
        if(teste_max_speed == 0){break;} //Se max_speed for menor que new_speed pode dar break no loop
      }
      if(position_test<=final_position && teste_max_speed == 1){ //Se a posição for menor que a final_position e se max_speed for maior que new_speed
        new_speed = speed +1; //Atribui a new_speed o valor de speed +1
        moves ++; //Incrementa o número de movimentos
        variavel_teste = 0; //Pode começar uma nova iteração no while
        solution_3.ultimo_incremento[0] = moves; //Atribui a solution_3.ultimo_incremento[0] o valor de moves
        solution_3.ultimo_incremento[1] = position + new_speed; //Atribui a solution_3.ultimo_incremento[1] o valor de position + new_speed
        solution_3.ultimo_incremento[2] = new_speed; //Atribui a solution_3.ultimo_incremento[2] o valor de new_speed
      }
    }

    teste_max_speed = 1; //Variável que controla se a speed ultrapassa o max_road_speed

    if(variavel_teste==1 && speed<=_max_road_speed_){
      position_test = position;
      for(new_speed_test = speed;new_speed_test >= 1; new_speed_test--){ //Loop desde speed até 1 (Manter speed)
        position_test_anterior = position_test;
        position_test = position_test + new_speed_test;
        for(int i = position_test_anterior; i <= position_test; i++){ //Testa max_speed no intervalo das posições
          if(max_road_speed[i]<new_speed_test){
            teste_max_speed = 0;  //Pode dar break;
            break;
          }
        }
        if(teste_max_speed == 0){break;}
      }
      if (teste_max_speed == 0) //Caso não possa manter o speed a única opção é decrementar o speed
      {
        new_speed = speed - 1;
        moves ++;
        variavel_teste = 0;
      }
      else if(position_test<=final_position && teste_max_speed == 1){
        new_speed = speed;
        moves++;
        variavel_teste = 0;
      }
    }

    
    if(variavel_teste==1){
      position_test = position;
      for(new_speed_test = speed-1;new_speed_test >= 1; new_speed_test--){ //Desce speed
        position_test = position_test + new_speed_test;
      }
      new_speed = speed -1;
      moves ++;
      variavel_teste = 0;   
    }
    
    
    if(new_speed == 0){
      position = position + speed;
    }else{
      position = position + new_speed;
      solution_3.positions[moves] = position;
      solution_3_best.positions[moves] = position;
    }
    }
  }
  solution_3_best.n_moves = moves ;
}

static void solve_3(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_2: bad final_position\n");
    exit(1);
  }
  solution_3_elapsed_time = cpu_time();
  solution_3_count = 0ul;
  solution_3_best.n_moves = final_position + 100;
  solution_3_while_dynamic(solution_3.ultimo_incremento[0],solution_3.ultimo_incremento[1],solution_3.ultimo_incremento[2],final_position);//Move_number,position,speed
  solution_3_elapsed_time = cpu_time() - solution_3_elapsed_time;
}



//Solve 4 (dynamic programing)

//Utilizando array externo e ponteiros
// int useful[3];
// void ultimo_incremento_Update(int *useful,int move,int position, int speed){
//   useful[0] = move;
//   useful[1] = position;
//   useful[2] = speed;
// }

static void solution_4_dynamic(int move_number,int position,int speed,int final_position)
{
  int position_teste,position_anterior; //Variáveis que irão receber valores de posições para testar se a speed é válida
  int acabou = 0; //Variável de controlo
  int speed_valido=1; //Variável de controlo para saber se a speed é válida
  solution_4_count++;
  position_teste = position;
  solution_4.positions[move_number] = position;
  solution_4_best.positions[move_number] = position;
  
  if(position==final_position){
    solution_4_best.n_moves = move_number;
    return;
  }
  else{
    for(int new_speed = speed + 1; new_speed >= speed - 1; new_speed--){ //3 possibilidades de speed, incrementa, mantém ou decrementa
      speed_valido = 1; //Variável de controlo para saber se a speed é válida
      if(new_speed<=_max_road_speed_){ //Testa se a speed é válida
        position_teste = position; //Reinicia a posição de teste
        for(int new_speed_teste = new_speed;new_speed_teste >= 1; new_speed_teste--){ //Loop desde new_speed até 1
          position_anterior = position_teste; //Guarda a posição anterior
          position_teste = position_teste + new_speed_teste; //Incrementa a posição de teste

          for(int i = position_anterior;i<=position_teste;i++){ //Testa max speed 
            if(max_road_speed[i]<new_speed_teste){
              speed_valido = 0;
              break;
            }
          }

          if(position_teste>final_position || acabou == 1 || speed_valido == 0){break;}

          if(new_speed_teste == 1 && position_teste<=final_position && speed_valido == 1){ //Speed válida entra na funçao com novo speed e nova posiçao
            acabou = 1;
            if(new_speed - speed == 1){ // Deu incremento no speed
              // ultimo_incremento_Update(&useful,move_number + 1,position + new_speed, new_speed); //Com Array externo
              solution_4.ultimo_incremento[0] = move_number + 1;
              solution_4.ultimo_incremento[1] = position + new_speed;
              solution_4.ultimo_incremento[2] = new_speed;
            }
            solution_4_dynamic(move_number + 1,position + new_speed, new_speed,final_position);
          }
        }
      }
    } 
  } 
}

static void solve_4(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_4: bad final_position\n");
    exit(1);
  }
  solution_4_elapsed_time = cpu_time();
  solution_4_count = 0ul;
  solution_4_best.n_moves = final_position + 100;
  //solution_4_dynamic(useful[0],useful[1],useful[2],final_position); //Com Array externo
  solution_4_dynamic(solution_4.ultimo_incremento[0],solution_4.ultimo_incremento[1],solution_4.ultimo_incremento[2],final_position);
  solution_4_elapsed_time = cpu_time() - solution_4_elapsed_time;
}

//Solve 5 (while less efficient)
static int descida(int nr){
  int sum=0;
  for (int i = nr; i >=1; i--)
  {
    sum = sum + i;
  }
  return sum;
}

static void solve_5_while(int final_position){

  int move_number = 0;
  int position = 0;
  int speed = 0;

  solution_5.positions[move_number] = position;
  while (position <= final_position)
  {
    int valAumenta = 1;
    int valDiminui = 0;

    if (position == final_position && speed == 1)
    {
      solution_5_best = solution_5;
      solution_5_best.n_moves = move_number;
      break;
    }
    
    

    if (descida(speed+1) <= final_position-position && speed+1<10)
    {
      //---------------------max speed----------------------

      int manter_speed = speed;
      int manter_posi = position;
      int new_speed = speed+1;
      int new_position = position;

      for (int i = position; i <= position + descida(speed+1); i++)
      {
        if (max_road_speed[i]<new_speed)
        {
          valAumenta = 0;
        }
        if (max_road_speed[i]<manter_speed && i<=position + descida(speed))
        {
          valDiminui = 1;
          valAumenta = 0;
          break;
        }


        if ( i == new_position+new_speed)
        {
          new_speed--;
          new_position = new_position + new_speed+1;
        }
        if ( i == manter_posi+manter_speed && i<=position + descida(speed))
        {
          
          manter_posi = manter_posi + manter_speed;
          manter_speed--;
        }
      }
      
      
      if (valAumenta == 1)
      {
        speed++;
        
      }else if (valDiminui == 1)
      {
        speed--;
      }else
      {
        speed=speed;
      }

      //---------------------max speed----------------------
     
     
     
    }
    else
    {
      if ((final_position - position) >= descida(speed))
      {
        
        //---------------------max speed----------------------
    
        int new_speed = speed;
        int new_position = position;
        for (int i = position; i <= position + descida(speed); i++)
        {
          
          if (max_road_speed[i]<new_speed)
          {
            valDiminui = 1;
            break;
          }


          if ( i == new_position+new_speed)
          {
            
            new_position = new_position + new_speed;
            new_speed--;
          }
        }
        
        if (valDiminui == 1)
        {
          speed--;
        }
        else
        {
          speed=speed;
        }
   
        //---------------------max speed----------------------

      }
      else
      {
        speed--;
      }
    }

    //printf("%d", speed);
    position = position + speed;
    move_number++;
    solution_5.positions[move_number] = position;
    solution_5_count++;
  }

  //printf("\nmove nr:%d", move_number);
}

static void solve_5(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_1: bad final_position\n");
    exit(1);
  }
  solution_5_elapsed_time = cpu_time();
  solution_5_count = 0ul;
  solution_5_best.n_moves = final_position + 100;
  solve_5_while(final_position);
  solution_5_elapsed_time = cpu_time() - solution_5_elapsed_time;
}

//
// example of the slides
//

static void example(void)
{
  int i,final_position;

  srandom(0xAED2022);
  init_road_speeds();
  final_position = 30;
  solve_1(final_position);
  make_custom_pdf_file("example.pdf",final_position,&max_road_speed[0],solution_1_best.n_moves,&solution_1_best.positions[0],solution_1_elapsed_time,solution_1_count,"Plain recursion");
  printf("mad road speeds:");
  for(i = 0;i <= final_position;i++)
    printf(" %d",max_road_speed[i]);
  printf("\n");
  printf("positions:");
  for(i = 0;i <= solution_1_best.n_moves;i++)
    printf(" %d",solution_1_best.positions[i]);
  printf("\n");
}


//
// main program
//

int main(int argc,char *argv[argc + 1])
{
# define _time_limit_  3600.0
  int n_mec,final_position,print_this_one;
  char file_name[64];

  // generate the example data
  if(argc == 2 && argv[1][0] == '-' && argv[1][1] == 'e' && argv[1][2] == 'x')
  {
    example();
    return 0;
  }
  // initialization
  n_mec = (argc < 2) ? 0xAED2022 : atoi(argv[1]);
  srandom((unsigned int)n_mec);
  init_road_speeds();
  // run all solution methods for all interesting sizes of the problem
  final_position = 1;
  solution_1_elapsed_time = 0.0;
  printf("    + --- ---------------- --------- +\n");
  printf("    |                plain recursion |\n");
  printf("--- + --- ---------------- --------- +\n");
  printf("  n | sol            count  cpu time |\n");
  printf("--- + --- ---------------- --------- +\n");
  while(final_position <= _max_road_size_/* && final_position <= 20*/)
  {
    print_this_one = (final_position == 10 || final_position == 20 || final_position == 50 || final_position == 100 || final_position == 200 || final_position == 400 || final_position == 800) ? 1 : 0;
    printf("%3d ",final_position);
    // first solution method (very bad)
    // if(solution_1_elapsed_time < _time_limit_)
    // {
    //   solve_1(final_position);
    //   if(print_this_one != 0)
    //   {
    //     sprintf(file_name,"%03d_1.pdf",final_position);
    //     make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_1_best.n_moves,&solution_1_best.positions[0],solution_1_elapsed_time,solution_1_count,"Plain recursion");
    //   }
    //   printf(" %3d %16lu %9.3e",solution_1_best.n_moves,solution_1_count,solution_1_elapsed_time);
    // }
    // else
    // {
    //   solution_1_best.n_moves = -1;
    //   //printf("                                |");
    // }


    // second solution method (less bad)
    // if(solution_2_elapsed_time < _time_limit_)
    // {
    //   solve_2(final_position);
    //   if(print_this_one != 0)
    //   {
    //     sprintf(file_name,"%03d_2.pdf",final_position);
    //     make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_2_best.n_moves,&solution_2_best.positions[0],solution_2_elapsed_time,solution_2_count,"Plain recursion");
    //   }
    //   printf(" %3d %16lu %9.3e ",solution_2_best.n_moves,solution_2_count,solution_2_elapsed_time);
    // }
    // else
    // {
    //   solution_2_best.n_moves = -1;
    //   // printf("                                |");
    // }


    //third solution method (less bad without recursive)
    // if(solution_3_elapsed_time < _time_limit_)
    // {
    //   solve_3(final_position);
    //   if(print_this_one != 0)
    //   {
    //     sprintf(file_name,"%03d_3.pdf",final_position);
    //     make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_3_best.n_moves,&solution_3_best.positions[0],solution_3_elapsed_time,solution_3_count,"Plain recursion");
    //   }
    //   printf(" %3d %16lu %9.3e ",solution_3_best.n_moves,solution_3_count,solution_3_elapsed_time);
    // }
    // else
    // {
    //   solution_3_best.n_moves = -1;
    //   // printf("                                |");
    // }


    //fourth solution method (good with dynamic)
    // if(solution_4_elapsed_time < _time_limit_)
    // {
    //   solve_4(final_position);
    //   if(print_this_one != 0)
    //   {
    //     sprintf(file_name,"%03d_4.pdf",final_position);
    //     make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_4_best.n_moves,&solution_4_best.positions[0],solution_4_elapsed_time,solution_4_count,"Plain recursion");
    //   }
    //   printf(" %3d %16lu %9.3e ",solution_4_best.n_moves,solution_4_count,solution_4_elapsed_time);
    // }
    // else
    // {
    //   solution_4_best.n_moves = -1;
    //   // printf("                                |");
    // }

    //fifth solution method (while loop slow)
    // if(solution_5_elapsed_time < _time_limit_)
    // {
    //   solve_5(final_position);
    //   if(print_this_one != 0)
    //   {
    //     sprintf(file_name,"%03d_5.pdf",final_position);
    //     make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_5_best.n_moves,&solution_5_best.positions[0],solution_5_elapsed_time,solution_5_count,"Plain recursion");
    //   }
    //   printf(" %3d %16lu %9.3e ",solution_5_best.n_moves,solution_5_count,solution_5_elapsed_time);
    // }
    // else
    // {
    //   solution_5_best.n_moves = -1;
    //   // printf("                                |");
    // }

    // done

    printf("\n");
    fflush(stdout);
    // new final_position
    if(final_position < 50)
      final_position += 1;
    else if(final_position < 100)
      final_position += 5;
    else if(final_position < 200)
      final_position += 10;
    else
      final_position += 20;
  }
  printf("--- + --- ---------------- --------- +\n");
  return 0;
# undef _time_limit_
}
