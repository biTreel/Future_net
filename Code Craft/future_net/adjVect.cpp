#include "adjVect.h"

table makeEmpty()
{
    table temp=new Table;
    if(!temp)
        cout<<"ERROR in makeEmpty!"
            <<endl;
    return temp;
}

int insertAdjVec(vector<table>adjVec[],int** const buff,int edgeNum)
{
     int i,j,vn=0;
     for(i=0;i!=edgeNum;++i)
     {
        for(j=0;j!=edgeNum;++j)
        {
            if(buff[j][1]!=i)
                continue;
            table temp=makeEmpty();

            temp->linkID=(size_t)buff[j][0];
            temp->vertex=(size_t)buff[j][2];
            temp->weight=(size_t)buff[j][3];
            adjVec[i].push_back(temp);
            if(vn<i)
                vn=i;//the large sub of adjVec equal verter_num-1
            //delete temp;
        }
     }
     return ++vn;//vertex number
}
void printAdjVec(const vector<table>*av,int vn)
{
    int i;
    //table temp;
    cout<<"\nprintAdjVec:"<<endl;
    for(i=0;i!=vn;++i)
    {
        vector<table>::const_iterator iter=av[i].begin();
        for(;iter!=av[i].end();++iter)
            cout<<(*iter)->linkID<<" "
                <<i<<" "    //current vertex
                <<(*iter)->vertex<<" "
                <<(*iter)->weight
                <<endl;
       // cout<<endl;
    }
}

vector<table>::iterator _find(vector<table>::iterator bg,
        vector<table>::iterator en,size_t val)
{
    while(bg!=en)
    {
        if((*bg)->vertex==val)
            return bg;
        ++bg;
    }
    return en;
}
