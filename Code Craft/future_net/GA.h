#ifndef __GA_H__
#define __GA_H__
#include <iostream>
#include <vector>
#include <algorithm>
#include "adjVect.h"
#include <ctime>
#include <cstdlib>
#include <memory.h>
#include <utility>      //pair

//new add
#define Max 100
#define Elitism true
#define tournamentSize 5
#define Generation 100
#define mutationRate 0.015
#define K 1

using namespace std;

#define random(x) rand()%x


struct Individual 
{
    size_t cost;
    vector<size_t> chromosome;
    Individual(): cost(0) {}
    Individual(size_t a, vector<size_t> b): cost(a), chromosome(b) {}
};

Individual * trans_population(vector<table>* population,int populationNum);

void createIndividual(size_t* demand,vector<size_t>& individual,
        int insertNum,int demandSize,int vn);

bool isDesignated(size_t* demand_i,int demandSize,size_t vertex);

void generatePopulation(vector<table>* adj,int populationNum,
        size_t* demand_i,int demandSize,
        int vn,vector<table>* population);


double getFitness(size_t cost) ;
//void printIndividual(Individual& obj) ;
//size_t getDistance(const Individual& indv);
Individual getFittest(const Individual *Population, int Size) ;

//bool mutateUtil(Individual& indv, int u, int &dest, int pathLength);
//void mutate(Individual& indv) ;
Individual crossover(vector<table>* adj,size_t* demand_i,int demandSize,
        const Individual& parent1, const Individual& parent2);

Individual tournamentSelection(const Individual* pop,int populationNum);

Individual* evolvePopulation(size_t* demand_i,
        int demandSize,const Individual* Pop,int vn,
        int populationNum,vector<table>*adj);

int compare(const void *vI1, const void *vI2) ;
vector<table> k_bestSolution(vector<table>* adj,size_t* demand_i,
        int demandSize,Individual* pop,int populationNum);

void toVectTable(vector<table>*adj,size_t* demand_i,int demandSize,
        vector<size_t> chrom,vector<table>& chrom_t);


#endif

