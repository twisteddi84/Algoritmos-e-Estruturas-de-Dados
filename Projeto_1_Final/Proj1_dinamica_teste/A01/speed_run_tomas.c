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
}
solution_t;


//
// the (very inefficient) recursive solution given to the students
//

static solution_t solution_1,solution_1_best;
static double solution_1_elapsed_time; // time it took to solve the problem
static unsigned long solution_1_count; // effort dispended solving the problem

static void solution_1_recursion(int move_number,int position,int speed,int final_position)
{
  int i,new_speed;

  // record move
  solution_1_count++;
  solution_1.positions[move_number] = position;
  // // is it a solution?
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
  for(new_speed = speed + 1;new_speed >= speed - 1;new_speed--)
    if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
    {
      for(i = 0;i <=new_speed && new_speed <= max_road_speed[position + i];i++)
        ;
      if(i > new_speed)
        solution_1_recursion(move_number + 1,position + new_speed,new_speed,final_position);
    }



}


//Solução menos nesga

static int descida(int nr){
  int sum=0;
  for (int i = nr; i >=1; i--)
  {
    sum = sum + i;
  }
  return sum;
}

static void solve_2_Minha(int final_position){

  int move_number = 0;
  int position = 0;
  int speed = 0;

  solution_1.positions[move_number] = position;
  while (position <= final_position)
  {
    int valAumenta = 1;
    int valDiminui = 0;

    if (position == final_position && speed == 1)
    {
      solution_1_best = solution_1;
      solution_1_best.n_moves = move_number;
      break;
    }
    
    

    if (descida(speed+1) <= final_position-position && speed+1<10)/*position< final_position - position && (position +speed+1) */
    {
      //--------------------------ZONA AUMENTAR (qd sem max)---------------------------------

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
        if (max_road_speed[i]<manter_speed && i<=position + descida(speed)+1 )
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
        //Para verificar se pode manter 
        if ( i == manter_posi+manter_speed && i<=position + descida(speed)+1)
        {
          manter_speed--;
          manter_posi = manter_posi + manter_speed+1;
        }
      }
      
      
      if (valAumenta == 1)
      {
        speed++;
        //printf("\nAum Speed1: %d\n", speed);
      }else if (valDiminui == 1)
      {
        speed--;
        //printf("\nDimi Speed1: %d\n", speed);
      }else
      {
        speed=speed;
        //printf("\nMant Speed1: %d\n", speed);
      }

      //---------------------max speed----------------------
     
      //speed++;
      
      //printf("aumenta-\n");
     
    }
    else
    {
      if ((final_position - position) >= descida(speed))
      {
        //--------------------------ZONA MANTER (qd sem max)---------------------------------

        //---------------------max speed----------------------
    
        int new_speed = speed;
        int new_position = position;
        //printf("descida: %d; speed: %d; position:%d\n", descida(new_speed), new_speed, position);
        for (int i = position; i <= position + descida(speed); i++)
        {
          //printf("\nPosi:%d  new_speed:%d  max_speed:%d\n", i, new_speed, max_road_speed[i]);
          
          if (max_road_speed[i]<new_speed)
          {
            valDiminui = 1;
            break;
          }


          if ( i == new_position+new_speed)
          {
            new_speed--;
            new_position = new_position + new_speed+1;
          }
        }
        
        if (valDiminui == 1)
        {
          speed--;
          //printf("\nDim Speed3: %d\n", speed);
        }
        else
        {
          //printf("\nMant Speed3: %d\n", speed);
          speed=speed;
        }
   
        //---------------------max speed----------------------

        //printf("\nmantem- Speed3: %d\n", speed);

      }
      else
      {
        //--------------------------ZONA DIMINUIR (qd sem max)---------------------------------
        speed--;
        //printf("\nDim Speed4: %d\n",speed);
      }
    }

    //printf("%d", speed);
    position = position + speed;
    move_number++;
    solution_1.positions[move_number] = position;
    solution_1_count++;
  }

  //printf("\nmove nr:%d", move_number);
}

static void solve_2(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_1: bad final_position\n");
    exit(1);
  }
  solution_1_elapsed_time = cpu_time();
  solution_1_count = 0ul;
  solution_1_best.n_moves = final_position + 100;
  //solution_1_recursion(0,0,0,final_position);
  solve_2_Minha(final_position);
  solution_1_elapsed_time = cpu_time() - solution_1_elapsed_time;
}

//Solução menos nesga




static void solve_1(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_2: bad final_position\n");
    exit(1);
  }
  solution_1_elapsed_time = cpu_time();
  solution_1_count = 0ul;
  solution_1_best.n_moves = final_position + 100;
  solution_1_recursion(0,0,0,final_position);
  solution_1_elapsed_time = cpu_time() - solution_1_elapsed_time;
}



//
// example of the slides
//

static void example(void)
{
  int i,final_position;

  srandom(0xAED2022);
  init_road_speeds();
  final_position = 9;
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

//Solução nesga
int boll;
int size=0;

void bollchange(int *boll){
  *boll = 1;
}


void sizeUpdate(int *size, int n){
  *size = n;
}
void findNDigitNumsUtil(int n, int sum, char* speeds,  int index, int max_road[], int j)
{
    // Base case
    if ((index > n || sum < 0) && boll == 0)
        return;

    // If number becomes N-digit
    if (index == n-1 && boll == 0)
    {
        // if sum of its digits is equal to given sum,
        // print it
        if(sum == 0 && (speeds[index-1]-'0'==1 || speeds[index-1]-'0'==2 ))
        {
          speeds[n] = '\0';
                //printf("%d;;", boll);
          printf("%s <-- %d\n", speeds, n);
                //printf("%d\n",n);
          sizeUpdate(&size, n);
          bollchange(&boll);

        }

        return;
    }
    // else
    // {

    //   speeds[n] = '\0';
    //   printf("speed:%s , boll:%d \n", speeds, boll);

    // }

    if(boll==0){
      for (int i = speeds[index-1]-'0' -1; i <= speeds[index-1]-'0'+1 && i<= max_road[j]; i++)
      {
        // append current digit to number


        if (i>=1 && i<=9)
        {

          speeds[index] = i + '0';
            // recurse for next digit with reduced sum
          findNDigitNumsUtil(n, sum-i, speeds, index + 1, max_road, j + speeds[index]-'0');
        }
      }
    }



}

// This is mainly a wrapper over findNDigitNumsUtil.
// It explicitly handles leading digit

void findNDigitNums(int n, int sum, int max_road[])
{
    // output array to store N-digit numbers
    if (boll == 0)
    {



    char speeds[n + 1];


    // fill 1st position by every digit from 1 to 9 and
    // calls findNDigitNumsUtil() for remaining positions


    speeds[n-1] = 1+ '0';
        // append current digit to number
    speeds[0] = 1+ '0';
    int j =1;
    findNDigitNumsUtil(n, sum - 2, speeds, 1, max_road, j);

    }

}

void BestCombinacao(int n, int max_road[]){
    for (int i = size; i <= size+3; i++)
    {
        if(boll==0){
          printf("\n");
          findNDigitNums(i, n, max_road);


        }else{
          break;
        }

    }

}
//Solução nesga


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
  // printf("    + --- ---------------- --------- +\n");
  // printf("    |                plain recursion |\n");
  // printf("--- + --- ---------------- --------- +\n");
  // printf("  n | sol            count  cpu time |\n");
  // printf("--- + --- ---------------- --------- +\n");
  // printf("\n");
  // final_position =100;
  while(final_position <=800 )/* && final_position <= 20*/
  {
    print_this_one = (final_position == 10 || final_position == 20 || final_position == 40 || final_position == 50 || final_position == 100 || final_position == 200 || final_position == 400 || final_position == 800) ? 1 : 0;
    printf("%3d",final_position);

    // first solution method (very bad)

    if(solution_1_elapsed_time < _time_limit_)
    {
      solve_2(final_position);
      if(print_this_one != 0)
      {
        sprintf(file_name,"%03d_1.pdf",final_position);
        make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_1_best.n_moves,&solution_1_best.positions[0],solution_1_elapsed_time,solution_1_count,"Plain recursion");
      }
      printf(" %3d %16lu %9.3e",solution_1_best.n_moves,solution_1_count,solution_1_elapsed_time);
    }
    else
    {
      solution_1_best.n_moves = -1;
      //printf("                                |");
    }
    // printf("\n");
    // solve_2_Minha(final_position);



    // second solution method (less bad)
    // ...


    // boll = 0;
    // BestCombinacao(final_position, max_road_speed);



    //printf("-----------------------------------------\n");


    // done
    printf("\n");
    fflush(stdout);
    //new final_position
    if(final_position < 50)
      final_position += 1;
    else if(final_position < 100)
      final_position += 5;
    else if(final_position < 200)
      final_position += 10;
    else
      final_position += 20;
  }
  //printf("--- + --- ---------------- --------- +\n");
  return 0;
# undef _time_limit_
}
