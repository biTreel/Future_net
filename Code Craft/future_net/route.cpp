
#include "route.h"


//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    //意思是把最优路径放在数组result里头就可以了，其他的不要管
    //unsigned short result[] = {2, 6, 3};//示例中的一个解
    //for (int i = 0; i < 3; i++)
    //    record_result(result[i]);
    //printf("in search_route\n");

    
    int* topo_i[5000];
    strtoInt(topo_i,topo,edge_num);
    size_t* demand_i;
    demand_i=(size_t*)malloc((strlen(demand)/2+1)*sizeof(size_t));
    int demanSize=strtoInt(demand_i,demand);
    //test
    /*
    cout<<"\ndemand_i:"<<endl;
    for(int i=0;i!=demanSize;++i)
        cout<<demand_i[i]<<" ";
    cout<<endl;
    */
   /*
      for(int i=0;i!=size;++i)
        printf("%d ",demand_i[i]);
    */
    
    vector<table> adjVec[vertexNum+1];
    int vn=insertAdjVec(adjVec,topo_i,edge_num);
    //printAdjVec(adjVec,vn);
    //cout<<"\nvn= "<<vn<<endl;
    int choice=(vn<=100)? 1 :2;//1: DFS, 2: GA
    //bool isDFS=(vn<=100);
    switch(choice)
    {
        case 1:
        {
            // ***********case1: DFS************
            list<table> chrom[chromNum];
            int pathsNum=
                printallPaths(adjVec,demand_i,demanSize,chrom);
           // cout<<"pathSNum: "<<pathsNum<<endl;
            size_t weight_sum[chromNum];
            sum_weight(chrom,weight_sum,chromNum);
            size_t minWeight=weight_sum[0];
            int index=0; //the subset of min weight paths
            for(int i=1;i!=pathsNum;++i)
            {
                if(weight_sum[i]<minWeight)
                {
                    minWeight=weight_sum[i];
                    index=i;
                }
            }
            //cout<<"the result:"<<endl;
            for(list<table>::iterator iter=chrom[index].begin();
                    iter!=chrom[index].end();++iter)
            {
                //cout<<(*iter)->linkID<<" ";
               record_result((unsigned short)(*iter)->linkID);
            }
            break;
        }

        case 2:
        {
            /*****case2: GA***************/
            int populationNum=int(3*demanSize);
            vector<table> population[populationNum];
            generatePopulation(adjVec,populationNum,demand_i,demanSize,
                    vn,population);
           //test
            /*  
            cout<<"populations: "<<endl;
            for(int i=0;i!=populationNum;++i)
            {   
             vector<table>::iterator iter=population[i].begin();
                for(;iter!=population[i].end();++iter)
                    cout<<(*iter)->vertex<<" ";
                //cout<<"\tpathWeight: "<<population[i].pathWeight
                    cout<<endl;
            }
           */

	        Individual *population_temp=trans_population(population,
                    populationNum);
            //cout<<"\noffset: 1"<<endl;
	        Individual *newPopulation = evolvePopulation(demand_i,
                    demanSize,population_temp,vn,populationNum,adjVec);
	        for(int i = 1; i < Generation; ++i) 
	        {
               // cout<<"\noffset: "<<i+1<<endl;
        		newPopulation = evolvePopulation(demand_i,demanSize,
                        newPopulation,vn,populationNum,adjVec);
            }
	        //vector<int>::iterator iter=newPopulation[0].chromosome.begin();
	        //for(;iter!=newPopulation[0].chromosome.end();++iter)
            //	cout<<*iter<<" ";
            vector<table> result_GA=
	         k_bestSolution(adjVec,demand_i,demanSize,newPopulation,
                     populationNum);
            //vector<table> result_GA(*temp_GA);
            vector<table>::iterator it_GA=result_GA.begin();
            for(; it_GA!=result_GA.end();++it_GA)
            {
                //cout<<(*it_GA)->linkID<<" ";
                size_t linkID=0;
                //cout<<(*iter)->linkID<<" ";
                if((*it_GA)->linkID==0)
                {
                    do
                    {
                        srand((unsigned int)clock());
                        linkID=(size_t)random(edge_num);
                    }
                    while(result_GA.end()!=_find(result_GA.begin(),
                                result_GA.end(),linkID));
                    (*it_GA)->linkID=linkID;
                }
                  

                record_result((unsigned short)(*it_GA)->linkID);
            }
            //cout<<endl;
	        delete [] newPopulation;
	        /*for(int i=0;i<populationNum;i++)
	        {
        		cout<<population_temp[i].cost<<" ";
	        }
        	vector<int>::iterator iter=population_temp[0].chromosome.begin();
        	for(;iter!=population_temp[0].chromosome.end();++iter)
            	cout<<*iter<<" ";
        	*/
            //break;
        }
        default:
        {
            //cout<<"^_^"<<endl;
            break;
        }

    }

}


void strtoInt(int* topo_i[],char* topo[],int edge_num)
{
    int i;
    for(i=0;i!=edge_num;++i)
    {
        topo_i[i]=(int*)malloc(4*sizeof(int));
        sscanf(topo[i],"%d,%d,%d,%d",&topo_i[i][0],&topo_i[i][1],
                &topo_i[i][2],&topo_i[i][3]);
    }   
}

int strtoInt(size_t* demand_i,char* demand)
{
    char* pch;
    int i=0;
    pch=strtok(demand,", |");
    while(pch!=NULL)
    {
        demand_i[i]=(size_t)atoi(pch);
        pch=strtok(NULL,", |");
        ++i;
    }
    return i;
}




