#ifndef __ROUTE_H__
#define __ROUTE_H__

#include <string.h>
#include "lib_record.h"
#include <stdio.h>
//#include "adjTable.h"//for DFS
#include <stdlib.h>
//#include "dijkstra.h"
//#include "binaryHeap.h"
#include "allPaths.h"
#include "adjVect.h"//for GA
#include <list>
#include <iostream>
#include "GA.h"
#include <vector>
#include <algorithm>

#define vertexNum 600
#define chromNum 5000

using namespace std;

/* strtoInt: convert string arry to in arry */
void strtoInt(int*topo_i[5000],char* topo[5000],int edge_num);
int strtoInt(size_t* demand_i,char* demand);
/* search_route:algorithm implementation */
void search_route(char *graph[5000], int edge_num, char *condition);

#endif
