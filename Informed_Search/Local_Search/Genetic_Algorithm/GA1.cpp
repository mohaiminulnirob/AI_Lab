#include <bits/stdc++.h>
using namespace std;

int n;
int POP_SIZE = 50;
int MAX_GEN = 1000;
double MUT_RATE = 0.08;

// ==============================
// FITNESS FUNCTION
// ==============================
int fitness(vector<int> &gene) {
    int non_attacking = 0;
    int total_pairs = n * (n - 1) / 2;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (gene[i] != gene[j] && abs(gene[i] - gene[j]) != abs(i - j))
                non_attacking++;
        }
    }
    return non_attacking;
}

// ==============================
// CROSSOVER
// ==============================
vector<int> crossover(vector<int> &p1, vector<int> &p2) {
    int point = rand() % n;
    vector<int> child(n);
    for (int i = 0; i < point; i++) child[i] = p1[i];
    for (int i = point; i < n; i++) child[i] = p2[i];
    return child;
}

// ==============================
// MUTATION
// ==============================
void mutate(vector<int> &gene) {
    double r = (double)rand() / RAND_MAX;
    if (r < MUT_RATE) {
        int i = rand() % n;
        gene[i] = (rand() % n) + 1;
    }
}

// ==============================
// SELECTION (Tournament)
// ==============================
int selectParent(vector<vector<int>> &population, vector<int> &fit) {
    int a = rand() % POP_SIZE;
    int b = rand() % POP_SIZE;
    if (fit[a] > fit[b]) return a;
    return b;
}

// ==============================
// PRINT BOARD
// ==============================
void printBoard(vector<int> &gene) {
    cout << "\nChessboard configuration:\n";
    for (int row = 1; row <= n; row++) {
        for (int col = 0; col < n; col++) {
            if (gene[col] == row)
                cout << " Q ";
            else
                cout << " . ";
        }
        cout << endl;
    }
}

// ==============================
// MAIN FUNCTION
// ==============================
int main() {
    srand(time(0));
    cout << "Enter N: ";
    cin >> n;

    vector<vector<int>> population(POP_SIZE, vector<int>(n));
    for (int i = 0; i < POP_SIZE; i++) {
        for (int j = 0; j < n; j++)
            population[i][j] = (rand() % n) + 1;
    }

    vector<int> fit(POP_SIZE);
    int maxFitness = n * (n - 1) / 2;
    vector<int> bestGene;
    int bestFit = -1;

    for (int gen = 0; gen < MAX_GEN; gen++) {
        // Evaluate fitness
        for (int i = 0; i < POP_SIZE; i++)
            fit[i] = fitness(population[i]);

        // Track best
        for (int i = 0; i < POP_SIZE; i++) {
            if (fit[i] > bestFit) {
                bestFit = fit[i];
                bestGene = population[i];
            }
        }

        // Check for perfect
        if (bestFit == maxFitness) {
            cout << "\n✅ Perfect solution found at generation " << gen << "!\n";
            break;
        }

        // Generate new population
        vector<vector<int>> newPop;
        newPop.push_back(bestGene); // elitism

        while (newPop.size() < POP_SIZE) {
            int p1 = selectParent(population, fit);
            int p2 = selectParent(population, fit);
            vector<int> child = crossover(population[p1], population[p2]);
            mutate(child); 
            newPop.push_back(child);
        }

        population = newPop;
    }

    // OUTPUT
    cout << "\nBest-so-far solution:\n";
    for (int i = 0; i < n; i++) cout << bestGene[i] << " ";
    cout << "\nFitness: " << bestFit << "/" << maxFitness << endl;

    if (bestFit == maxFitness)
        cout << "🎯 This is a perfect N-Queens solution!\n";
    else
        cout << "⚙ Not perfect, but close to optimal.\n";

    // Print the board
    printBoard(bestGene);

    return 0;
}