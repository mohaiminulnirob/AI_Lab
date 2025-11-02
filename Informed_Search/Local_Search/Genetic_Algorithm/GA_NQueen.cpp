#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

// ---------- FITNESS FUNCTION ----------
int fitness(vector<int> &state){
    int n = state.size();
    int attacks = 0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(state[i]==state[j]) attacks++; // same row
            if(abs(state[i]-state[j])==abs(i-j)) attacks++; // same diagonal
        }
    }
    int max_pairs = n*(n-1)/2;
    return max_pairs - attacks; // higher = better
}

// ---------- RANDOM STATE ----------
vector<int> randomState(int n){
    vector<int> s(n);
    for(int i=0;i<n;i++) s[i] = rand()%n;
    return s;
}

// ---------- CROSSOVER ----------
vector<int> crossover(vector<int> &p1, vector<int> &p2){
    int n = p1.size();
    int point = rand()%n;
    vector<int> child(n);
    for(int i=0;i<n;i++){
        if(i<point) child[i]=p1[i];
        else child[i]=p2[i];
    }
    return child;
}

// ---------- MUTATION ----------
void mutate(vector<int> &state){
    double prob = ((double) rand() / RAND_MAX);
    if(prob < 0.05){ // 5% chance
        int n = state.size();
        int a = rand()%n;
        int b = rand()%n;
        swap(state[a], state[b]);
    }
}

// ---------- SELECTION (Roulette Wheel) ----------
vector<int> selectParent(vector<vector<int>> &pop, vector<int> &fitSum){
    int total = fitSum.back();
    int r = rand()%total;
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
        int n;
        cin>>n;

        int populationSize = 50;
        int maxGenerations = 500;

        vector<vector<int>> population;
        for(int i=0;i<populationSize;i++)
            population.pb(randomState(n));

        int max_pairs = n*(n-1)/2;
        vector<int> bestState;
        int bestFit = -1;

        for(int gen=0; gen<maxGenerations; gen++){
            vector<int> fits;
            for(auto &ind : population)
                fits.pb(fitness(ind));

            // find best
            for(int i=0;i<populationSize;i++){
                if(fits[i] > bestFit){
                    bestFit = fits[i];
                    bestState = population[i];
                }
            }

            if(bestFit == max_pairs) break; // solved

            // compute cumulative fitness
            vector<int> fitSum(populationSize);
            fitSum[0] = fits[0];
            for(int i=1;i<populationSize;i++)
                fitSum[i] = fitSum[i-1] + fits[i];

            // new population
            vector<vector<int>> newPop;
            for(int i=0;i<populationSize;i++){
                vector<int> p1 = selectParent(population, fitSum);
                vector<int> p2 = selectParent(population, fitSum);
                vector<int> child = crossover(p1,p2);
                mutate(child);
                newPop.pb(child);
            }
            population = newPop;
        }

        cout<<"Best fitness = "<<bestFit<<"\n";
        cout<<"State: ";
        for(auto x:bestState) cout<<x<<" ";
        cout<<"\n\n";
    }

    return 0;
}
