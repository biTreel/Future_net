
#include "allPaths.h"

//print all paths from src to target
int printallPaths(vector<table>* adj,size_t* demand_i,int demanSize,
        list<table> chrom[])
{
    size_t src=demand_i[0];
    size_t dst=demand_i[1];
    int pathsNum=0;
    //int sumWeight=0;

    //mark all the vertices as not visited
    bool *visited=(bool*)malloc((vertexNum+1)*sizeof(bool));
    //create an array to store paths
    size_t* path= (size_t*)malloc((vertexNum+1)*sizeof(size_t));

    int pathIndex=0;
    for(int i=0;i!=vertexNum;++i)
        visited[i]=false;
    //cout<<"\nbefore printUtil"<<endl;
    printallPathsUtil(adj,src,dst,visited,path,pathIndex,demand_i,
            demanSize,pathsNum,chrom);
    //cout<<"\nafter printUtil"<<endl;
    return pathsNum;
}

/* recuresive function to print all paths from the current v to d
 * visited[] keeps track of vertices in current path.
 * path[] stores actual vertices and pathIndex is current index in 
 *path[].by the way, pathIndex use reference(&).
 */
void printallPathsUtil(vector<table> *adj,size_t v,size_t d,bool visited[],
        size_t path[],int& pathIndex,size_t* demand_i,int demanSize,
        int& pathsNum,list<table> chrom[] )
{
    vector<table>::iterator iter=adj[v].begin();//the first adjcent v point
    visited[v]=true;
    path[pathIndex]=v;
    ++pathIndex;
    //if current v is same as dst,and the number of vertex is large than
    // demand size+2, them print curent path[]
    if((v==d) && (pathIndex >= demanSize))
    {
        //cout<<"\nand here?"<<endl;
        int cnt=0;
        for(int i=0;i!=pathIndex;++i)
        {
            cnt+=designated(demand_i,demanSize,path[i]);
        }
        if(cnt==demanSize-2)
        {
            //cout<<"\nwell done here?"<<endl;
            //chrom[pathsNum].push_back(adj[path[0]]);
            vector<table>::iterator it;
            vector<table> temp_t;
            for(int i=0;i!=pathIndex-1;++i)
            {
                /*
                adjTable temp1=adj[path[i]];
                while(temp1)
                {
                    if(temp1->next->vertex==(size_t)path[i+1])
                    {
                         chrom[pathsNum].push_back(temp1->next);
                         break;
                    }
                    temp1=temp1->next;
                 }
                 */
                temp_t=adj[path[i]];
                it= _find(temp_t.begin(),temp_t.end(),path[i+1]);
                if(it==temp_t.end())
                {
                    cout<<"ERROR: NOT A ADJCENT"<<endl;
                    continue;
                }
                chrom[pathsNum].push_back(*it);
            }
            /* for test*/
            //for(int i=0;i!=pathIndex;++i)
            //    cout<<path[i]<<" ";
            ++pathsNum;
            //cout<<endl;
        }
    }
    
    else
    {
       // cout<<"\nbefore recuresive in printUtil"<<endl;
        //recuresive for all the vertices adjacent to current vertex
        while(iter!=adj[v].end())
        {
            if(!visited[(*iter)->vertex])
                printallPathsUtil(adj,(*iter)->vertex,d,
                        visited,path,pathIndex,demand_i,
                        demanSize,pathsNum,chrom);
            //temp=temp->next;
            ++iter;
        }
    }
    //remove current vertex from path[] and mark it as unvisited.
    --pathIndex;
    visited[v]=false;
}

int designated(size_t* demand_i,int demanSize,size_t path)
{
    int cnt=0;
    for(int i=2;i!=demanSize;++i)
        if(demand_i[i]==path)
            cnt=1;
    return cnt;
}
void sum_weight(list<table>chrom[],size_t* weight_sum,int chromNum)
{
    
    for(int i=0;i<chromNum;i++)
    {
        weight_sum[i]=0;
     for(list<table>::iterator iter=chrom[i].begin();
        iter!=chrom[i].end();++iter)

        weight_sum[i]+=(*iter)->weight;
    }
}
