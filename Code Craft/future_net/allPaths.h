/* */
#ifndef __ALLPATHS_H
#define __ALLPATHS_H

#include <stdio.h>
#include <stdlib.h>
//#include "adjTable.h"
#include "adjVect.h"

#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

#define vertexNum 600

//#define _getArrLen(arr) (sizeof(arr)/sizeof(arr[0]))

int printallPaths(vector<table>* adj,size_t* demand_i,
        int demanSize,list<table> chrom[]);

void printallPathsUtil(vector<table>* adj,size_t v,size_t w,bool visited[],
        size_t path[],int& pathIndex,size_t* demand_i,int demanSize,
        int& pathsNum,list<table> chrom[]);

int designated(size_t* demand_i,int demanSize,size_t path);
void  sum_weight(list<table> chrom[],size_t *weight_sum,int chromNum);
#endif


