#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define pcross 0.4     //The probiblity of crossover
#define pmutate 0.05   //The probability of mutation
#define code_length 16 //The length of gene code
#define N 500          //The number of individuals
#define genmax 500     //The maximum of generations
using namespace std;

struct unit
{
    int code[code_length]; //Gene code
    double cost;           //Fitness score
};

double getCost(unit &p);
double getNum(unit &p);
void initial_gen(unit group[N]);
void evolve(unit group[N]);
void choose(unit group[N]);
void cross(unit &u1, unit &u2);
void mutate(unit &u);
int getBest(unit group[N]);

unit group[N];
unit temp[N];

//Convert gene code to vaiable x
double getNum(unit &p)
{
    double Num = 0;
    int weight = 3;
    for (int i = 0; i < code_length; ++i)
    {
        Num += p.code[i] * pow(2, weight);
        --weight;
    }
    Num--;
    return Num;
}

//Calculate fitness score of an individual
double getCost(unit &p)
{
    double Num = getNum(p);
    p.cost = -Num * sin(Num) + 15;
    return (p.cost);
}

//Initialize the gene of the whole group
void initial_gen(unit group[N])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < code_length; ++j)
        {
            group[i].code[j] = rand() % 2;
        }
        getCost(group[i]);
    }
}

void copy_unit(unit &u1, unit &u2)
{
    int i;
    for (i = 0; i < code_length; ++i)
    {
        u1.code[i] = u2.code[i];
    }
    u1.cost = u2.cost;
}

//Simulate the evolution process
void evolve(unit group[N])
{
    int id = getBest(group);
    //Parent generation
    cout << "the best fitness score of parent generation is: " << getCost(group[id]) << ". The individual x is: " << getNum(group[id]) << endl;
    for (int i = 0; i < genmax; ++i) //gen_max generations
    {                           
        choose(group);               //natural choose
        for (int j = 0; j < N; ++j)  //crossover 
        {                       
            double randn = double(rand()) / double(RAND_MAX);
            if (randn < pcross)
            {
                int randn2 = rand() % N;
                cross(group[j], group[randn2]);
            }
        }
        for (int j = 0; j < N; ++j)  //multation
        {                       
            double randn = double(rand()) / double(RAND_MAX);
            if (randn < pmutate)
            {
                mutate(group[j]);
            }
        }
        int bestId = getBest(group);
        cout << "the best fitness score of " << i + 1 << "th generation is: " << getCost(group[bestId]) << ". The individual x is: " << getNum(group[bestId]) << endl;
    }
}

//Simulate the natural choosing process
void choose(unit group[N])
{
    double cost[N];
    double sum = 0;
    for (int i = 0; i < N; ++i)
    {
        copy_unit(temp[i], group[i]);
    }
    cost[0] = temp[0].cost;
    for (int i = 1; i < N; ++i)
    {
        cost[i] = temp[i].cost + cost[i - 1];
    }
    for (int i = 0; i < N; ++i)
    {
        cost[i] /= cost[N - 1];
    }
    for (int i = 0; i < N; ++i)
    {
        double randn = double(rand()) / double(RAND_MAX);
        for (int j = 0; j < N; ++j)
        {
            if (randn <= cost[j])
            {
                copy_unit(group[i], temp[j]);
                break;
            }
        }
    }
}

//Simulate the crossover process
void cross(unit &u1, unit &u2)
{
    int temp;
    int cross_point = rand() % code_length;
    for (int i = cross_point; i < code_length; i++)
    {
        temp = u1.code[i];
        u1.code[i] = u2.code[i];
        u2.code[i] = temp;
    }
    getCost(u1);
    getCost(u2);
}

//Simulate the multation process
void mutate(unit &u)
{
    int mutate_point = rand() % code_length;
    u.code[mutate_point] = !u.code[mutate_point];
    getCost(u);
}

//Find the id of the best fitting individual
int getBest(unit group[N])
{
    double best = 0;
    int bestId = 0;
    for (int i = 0; i < N; ++i)
    {
        if (best <= group[i].cost)
        {
            best = group[i].cost;
            bestId = i;
        }
    }
    return bestId;
}

int main()
{
    srand(time(NULL));
    initial_gen(group);
    evolve(group);
    return 0;
}