#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

// -------- Numeric function to maximize ----------
double f(double x){
    return -(x*x) + 10*x; // you can change any numeric function
}

// ---------- FITNESS FUNCTION ----------
double fitness(vector<double> &state){
    return f(state[0]); // state has only 1 gene (one number)
}

// ---------- RANDOM STATE ----------
vector<double> randomState(int dummy){
    vector<double> s(1);
    s[0] = ((double)rand()/RAND_MAX) * 10.0; // search space 0 to 10
    return s;
}

// ---------- CROSSOVER ----------
vector<double> crossover(vector<double> &p1, vector<double> &p2){
    vector<double> child(1);
    child[0] = (p1[0] + p2[0]) / 2.0; // midpoint crossover
    return child;
}

// ---------- MUTATION ----------
void mutate(vector<double> &state){
    double prob = ((double) rand() / RAND_MAX);
    if(prob < 0.1){ // 10% chance mutation
        double change = (((double)rand()/RAND_MAX)-0.5)*2.0; // -1 to +1
        state[0] += change;
        if(state[0] < 0) state[0]=0;
        if(state[0] > 10) state[0]=10;
    }
}

// ---------- SELECTION (Roulette Wheel) ----------
vector<double> selectParent(vector<vector<double>> &pop, vector<double> &fitSum){
    double total = fitSum.back();
    double r = ((double)rand()/RAND_MAX)*total;
    for(int i=0;i<fitSum.size();i++){
        if(r < fitSum[i]) return pop[i];
    }
    return pop.back();
}

// ---------- MAIN ----------
int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    srand(time(0));

    int t=1;
    cin>>t;
    while(t--){
        int n; // useless here but keeping template structure
        cin>>n;

        int populationSize = 50;
        int maxGenerations = 300;

        vector<vector<double>> population;
        for(int i=0;i<populationSize;i++)
            population.pb(randomState(n));

        double bestFit = -1e18;
        vector<double> bestState;

        for(int gen=0; gen<maxGenerations; gen++){
            vector<double> fits;
            for(auto &ind : population)
                fits.pb(fitness(ind));

            for(int i=0;i<populationSize;i++){
                if(fits[i] > bestFit){
                    bestFit = fits[i];
                    bestState = population[i];
                }
            }

            vector<double> fitSum(populationSize);
            fitSum[0] = fits[0];
            for(int i=1;i<populationSize;i++)
                fitSum[i] = fitSum[i-1] + fits[i];

            vector<vector<double>> newPop;
            for(int i=0;i<populationSize;i++){
                vector<double> p1 = selectParent(population, fitSum);
                vector<double> p2 = selectParent(population, fitSum);
                vector<double> child = crossover(p1,p2);
                mutate(child);
                newPop.pb(child);
            }
            population = newPop;
        }

        cout<<"Best fitness = "<<bestFit<<"\n";
        cout<<"Best X = "<<bestState[0]<<"\n\n";
    }

    return 0;
}
