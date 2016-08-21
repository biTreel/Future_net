#ifndef __ADJVECT_H__
#define __ADJVECT_H__

#include <iostream>
#include <vector>
#include <cmath>

#define INF (size_t)pow(2,10)

using namespace std;

#define vertexNum 600

struct Table;
typedef struct Table* table;

struct Table
{
    size_t linkID;
    size_t vertex;
    size_t weight;

/*    Table(size_t b):linkID(-1), weight(INF),
        vertex(b){} //not a adjcent
    Table(size_t a,size_t b,size_t c):
        linkID(a),vertex(b),weight(c){} // a adjcent
*/
};

//vector<table> adjVec[vertexNum+1];

table makeEmpty();
int insertAdjVec(vector<table> adjVec[],int** const buff,int edgeNum);
void printAdjVec(const vector<table>* av,int vn);

vector<table>::iterator _find(vector<table>::iterator bg,
        vector<table>::iterator en,size_t val);





#endif

