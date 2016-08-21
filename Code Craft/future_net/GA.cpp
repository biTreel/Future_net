#include "GA.h"
/*
int N;
vector <int> adj[Max];
int dist[Max][Max];
bool taken[Max * Max];
*/
void createIndividual(size_t* demand_i,vector<size_t>& individual,
        int insertNum,int demandSize,int vn)
{
    int indexofDemand;
    vector<size_t> demand_v(demand_i+2,demand_i+demandSize);
    //test
    /*vector<size_t>::iterator iter=demand_v.begin();
    
    cout<<"\ndemand_v: "<<endl;
    for(;iter!=demand_v.end();++iter)
        cout<<*iter<<" ";
    cout<<endl;
    */
    
    /*insert the designated-points randomly*/
    int ds=demandSize-2;
    while(!demand_v.empty())
   {
        srand((unsigned int)clock());
        indexofDemand=random(ds--);
        if(individual.end()!=find(individual.begin(),
                    individual.end(),demand_v[indexofDemand]))
        {
            demand_v.erase(demand_v.begin()+indexofDemand);
            continue;
        } 
        individual.push_back(demand_v[indexofDemand]);
        demand_v.erase(demand_v.begin()+indexofDemand);

   }

    /*insert randVertex*/
    size_t randVertex;
    vector<size_t>::size_type subPos;
    while(insertNum > 0)
    {
        while(1)
        {
            srand((unsigned int)clock());
            randVertex=(size_t)random(vn);
            //cout<<"\nrandVertex: "<<randVertex<<endl;
            //randVertex should not in demand_i or individual.
            bool isindividual=(bool)(individual.end() !=
                    find(individual.begin(),individual.end(),randVertex));
            //cout<<"\nisindividual: "<<isindividual<<endl;
            if(isDesignated(demand_i,demandSize,randVertex) || isindividual)
                continue; 
            srand((unsigned int)clock());
            subPos=(size_t)random(individual.size());//not sero
            individual.insert(individual.begin()+subPos,randVertex);
            break;
        }
        --insertNum;
    }
    individual.insert(individual.begin(),demand_i[0]);//source
    individual.push_back(demand_i[1]);//destination
}

bool isDesignated(size_t* demand_i,int demandSize,size_t vertex)
{
    bool taken=false;
    for(int i=0;i!=demandSize;++i)
        if(demand_i[i]==vertex)
            taken=true;
    return taken;
}

void generatePopulation(vector<table>* adj,int populationNum,
        size_t* demand_i,int demandSize,
        int vn,vector<table>* population)
{
    int index=0;
    vector<size_t> temp_v;
    vector<table> temp_t;
    vector<size_t>::iterator iter_s;
    vector<table>::iterator iter_t;
    //table t=makeEmpty();

    int insertNum=(int)demandSize/2; //half of demandSize as initial.
    //cout<<"\ninsertNum before: "<<insertNum<<endl;
    while(index!=populationNum)
    {
        if(insertNum>vn-demandSize) //the case0 can not work because of this
            break;
        createIndividual(demand_i,temp_v,insertNum,demandSize,vn);
       /*turning size_t to table*/ 
        toVectTable(adj,demand_i,demandSize,temp_v,population[index]);
        insertNum = insertNum + (int)vn/populationNum;
        temp_v.clear();
        ++index;
        //cout<<"\nsize:"<<population[index].size()<<endl;
        //test
        /*
        vector<table>::iterator iter=population[index].begin();
        cout<<"\nindex "<<index<<" :"<<endl;
        for(;iter!=population[index].end();++iter)
            cout<<(*iter)->vertex<<" ";
        cout<<endl;
        */
        //cout<<"\ninsertNum after: "<<"v/p="<<vn/populationNum
        //    <<", ins="<<insertNum<<endl;
        //temp_v.clear();
        //++index;
    }
}


//转换成后面程序所需的数据结构
Individual * trans_population(vector<table>* population,int populationNum)
{
	Individual *population_temp=new Individual[populationNum];
	for(int i=0;i<populationNum;i++)
	{
		int cost=0;
		vector<table>::iterator iter=population[i].begin();
		for(;iter!=population[i].end();++iter)
        {
			cost+=(*iter)->weight;
			population_temp[i].chromosome.push_back((*iter)->vertex);
		}
		population_temp[i].cost=cost;
	}
	return population_temp;
}

double getFitness(size_t cost) 
{
    return (1.0 / (double)cost);
}
/*
void printIndividual( Individual& obj) 
{
   	vector<size_t>::iterator iter=obj.chromosome.begin();
	for(;iter!=obj.chromosome.end();++iter)
        	cout<<*iter<<"->";
    	cout<<"\ncost: "<<obj.cost<<endl;
}

size_t getDistance(const Individual& indv) 
{
    size_t cost = 0;
    for(int i = 0, n = indv.chromosome.size(); i < n - 1; ++i) 
	{
       // cost += dist[ indv.chromosome[i] ][ indv.chromosome[i + 1] ];
    }
    return cost;
}
*/
Individual getFittest(const Individual *Population, int Size) 
{
    int fittest = 0;
    double best = getFitness(Population[0].cost);
    for(int i = 1; i < Size; ++i)
	{
        double fitness = getFitness(Population[i].cost);
        //适应度函数是权值的倒数，适应度函数越小越好
        if(fitness < best) 
		{
            fittest = i;
            best = fitness;
        }
    }
    return Population[fittest];//返回适应度最小的那一代
}
/*
bool mutateUtil(Individual& indv, int u, int &dest, int pathLength) 
{
    taken[u] = true;
    indv.chromosome.push_back(u);
    if(u == dest) return true;
    if(pathLength == N) return false;

    int adjs = (int)adj[u].size();
    bool block = true;
    for(int i = 0; i < adjs; ++i)//当前点（即变异点）的邻接点全部被访问过则变异失败
	{
        if(!taken[adj[u][i]]) 
		{
            block = false;
            break;
        }
    }
    if(block) return false;
    int randomIdx, v;
    do 
	{
        randomIdx = rand() % adjs;
        v = adj[u][randomIdx];//从变异点开始进行迭代，重新找一条路径到达终点
    } while(taken[v]);//保证该邻接点之前不在路径中（避免成环）
    indv.cost += dist[u][v];
    return mutateUtil(indv, v, dest, pathLength + 1);//进行迭代，直至变异到终点为止
}
void mutate(Individual& indv) 
{
    double mutationProb = ((double) rand() / (RAND_MAX));
    if(mutationProb < mutationRate) //保证变异率在mutationRate范围以内
	{
        int n = (int)indv.chromosome.size();
        int mutationPoint = rand() % n;//选择变异的位置
        if(mutationPoint == n - 1) return;//如果变异的位置是终点的话则不变异
        memset(taken, false, sizeof(taken));
        int src = indv.chromosome[mutationPoint];//开始变异的位置
		int dest = indv.chromosome[n - 1];//变异结束的位置
        Individual newIndv;
        int cost = 0;
        for(int i = 0; i < mutationPoint; ++i) 
		{
            newIndv.chromosome.push_back(indv.chromosome[i]);//把要变异的染色体进行存储
            taken[indv.chromosome[i]] = true;//染色体变异节点前的每个节点都访问过，进行标记避免成环
            cost += dist[indv.chromosome[i]][indv.chromosome[i + 1]];
        }
        newIndv.cost = cost;
        bool success = mutateUtil(newIndv, src, dest, mutationPoint + 1);
        if(success) indv = newIndv;
    }
}
*/
Individual crossover(vector<table>* adj,size_t* demand_i,int demandSize,
        const Individual& parent1, const Individual& parent2) 
{
    Individual child1,child2;
    vector<table> chrom_t1,chrom_t2;
    int len1 = parent1.chromosome.size();
    int len2 = parent2.chromosome.size();
    //int flag_1=0;
    //int flag_2=0;
    vector< pair<int, int> > crossingSites;
    for(int i = 1; i < len1 - 1; ++i) 
	{
        for(int j = 1; j < len2 - 1; ++j) 
		{
            if(parent1.chromosome[i] == parent2.chromosome[j])//如果两个父代有相同的节点则将其位置存起来
                crossingSites.push_back( make_pair(i, j) );
        }
    }

    if(crossingSites.size() < 1)
        //如果没有相同节点则返回权值较大的那个
        return (parent1.cost >= parent2.cost ? parent1: parent2);
   // while(1)
   // {

        srand((unsigned int)clock());
        //随机取出相同点的位置对
        pair<int,int> randomCS=crossingSites[random( crossingSites.size())];
        for(int i = 0; i < randomCS.first; ++i) 
            //将父代1相同点之前的赋给子代,包括相同点
             child1.chromosome.push_back(parent1.chromosome[i]);
        for(int i = randomCS.second; i < len2; ++i)   
        //将父代2相同点之后的赋给子代,不包括相同点      
              child1.chromosome.push_back(parent2.chromosome[i]);
        int arr[vertexNum+1]={0};
        int arr2[vertexNum+1]={0};
        vector<size_t>::iterator iter=child1.chromosome.begin();
        for(;iter!=child1.chromosome.end();++iter)
        {
            arr[*iter]++;
            if(arr[*iter]>1)
            {
                arr[*iter]=1;
                child1.chromosome.erase(iter);
            }
        }
        for(int i=0;i<randomCS.second;++i)
            child2.chromosome.push_back(parent2.chromosome[i]);
        for(int i=randomCS.first;i<len1;++i)
            child2.chromosome.push_back(parent1.chromosome[i]);
        vector<size_t>::iterator iter2=child2.chromosome.begin();
        for(;iter2!=child2.chromosome.end();++iter2)
        {  
             arr2[*iter2]++;
             if(arr2[*iter2]>1)
             {
                 arr[*iter2]=1;
                 child2.chromosome.erase(iter2);
             }
        }
        /*
        if(flag_1&&flag_2)
        {
             flag_1=0;
             flag_2=0;
            continue;
        }
        else 
            break;
        */
        //cout<<"end of while"<<endl;
   // }
    // child.cost = getDistance(child);
   // if((!flag_1)&&(!flag_2))
   // {
        toVectTable(adj,demand_i,demandSize,child1.chromosome,chrom_t1);
        child1=*trans_population(&chrom_t1,1);
        toVectTable(adj,demand_i,demandSize,child2.chromosome,chrom_t2);
        child2=*trans_population(&chrom_t2,1);
        chrom_t1.clear();
        chrom_t2.clear();
        if(child1.cost >= child2.cost)
            return child1;
        else
            return child2;
    //}
    /*
    else if(!flag_1)
    {
        toVectTable(adj,demand_i,demandSize,child1.chromosome,chrom_t1);
        child1=*trans_population(&chrom_t1,1);
        chrom_t1.clear();
        return child1;
    }
    else
    {
        toVectTable(adj,demand_i,demandSize,child2.chromosome,chrom_t2);
        child2=*trans_population(&chrom_t2,1);
        chrom_t2.clear();
        return child2;
    }

    */
}
Individual tournamentSelection(const Individual* pop,int populationNum)
    //随机从初始种群里面选择5个父代然后返回适应度最高的那个
{
    Individual tournament[tournamentSize];
    for(int i = 0; i < tournamentSize; ++i) 
	{
        int randomID = rand() % populationNum;
        tournament[i] = pop[randomID];
    }
    return getFittest(tournament, tournamentSize);

}

Individual* evolvePopulation(size_t* demand_i,
        int demandSize,const Individual* Pop,int vn,
        int populationNum,vector<table>*adj) 
{
    int elitismOffset = 0;
    Individual *evolvePop = new Individual[populationNum];

    if(Elitism)
	{
        Individual best = getFittest(Pop, populationNum);
        evolvePop[0] = best;
        elitismOffset = 1;
    }
	//cout<<populationNum<<endl;
    for(int i = elitismOffset; i < populationNum; ++i) 
	{
        Individual parent1 = tournamentSelection(Pop,populationNum);
        Individual parent2 = tournamentSelection(Pop,populationNum);
        Individual child = crossover(adj,demand_i,demandSize,
                parent1, parent2);
        evolvePop[i] = child;
        //test
        /*
	    vector<size_t>::iterator iter=child.chromosome.begin();
	    for(;iter!=child.chromosome.end();++iter)
        	cout<<*iter<<" ";
	    cout<<endl;
        */
    }

    delete [] Pop;

  /*  for(int i = elitismOffset; i < Iteration; ++i) //从100个子代里面进行变异
	{
        mutate(evolvePop[i]);
    }
*/
    return evolvePop;
}

int compare(const void *vI1, const void *vI2) 
{
    Individual *I1 = (Individual *)vI1;
    Individual *I2 = (Individual *)vI2;

    return (*I1).cost < (*I2).cost;
}

vector<table> k_bestSolution(vector<table>* adj,size_t* demand_i,
        int demandSize,Individual* pop,int populationNum) 
{
    vector<table> bestChrom;
    qsort(&pop[0], populationNum, sizeof(Individual), compare);//利用函数指针进行排序
    toVectTable(adj,demand_i,demandSize,pop[0].chromosome,bestChrom);
    /*
    int k = min(populationNum, K);//找出最小的5条
    cout<<"Total Population:"<<populationNum<<endl;
    cout<<k<<" most optimal solutions:"<<endl;
    for(int i = 0; i < k; ++i) 
	{
        printIndividual(pop[i]);
    }
    */
    return bestChrom;
}

void toVectTable(vector<table>*adj,size_t* demand_i,int demandSize,
        vector<size_t>chrom,vector<table>& chrom_t)
{
    vector<size_t>::iterator iter_s=chrom.begin();
    vector<table>::iterator iter_t;
    for(; iter_s!=chrom.end()-1;)
    {
        vector<table> temp_t=adj[*iter_s];
        ++iter_s;
        iter_t= _find(temp_t.begin(),temp_t.end(),*iter_s);
        if(temp_t.end()!=iter_t)
        {
            if(isDesignated(demand_i,demandSize,*iter_s))
                (*iter_t)->weight=INF;
            chrom_t.push_back(*iter_t);
        }
        else
        {
            table t=makeEmpty();
            t->linkID=0;
            t->vertex=*iter_s;
            t->weight=0;
            chrom_t.push_back(t);
        }
        //remenbor to clear chrom_t
    }
}





