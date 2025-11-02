#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
vector<pair<int, int>> a[N];
int edges, orig[N];
char init, target;
bool vis[N], found = false;
vector<int> traversal;
int dist[N];

bool ucs(int start, int goal)
{
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;
    fill(dist, dist + N, INT_MAX);
    dist[start] = 0;
    orig[start] = -1;
    pq.push(make_pair(0, start));

    while (!pq.empty())
    {
        pair<int, int> top = pq.top();
        pq.pop();
        int cost = top.first;
        int u = top.second;

        if (vis[u]) continue;
        vis[u] = true;
        traversal.push_back(u);

        if (u == goal)
        {
            found = true;
            return true;
        }

        for (int i = 0; i < a[u].size(); i++)
        {
            int v = a[u][i].first;
            int w = a[u][i].second;

            if (!vis[v] && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                orig[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return false;
}

int32_t main()
{
    cout << "Enter number of edges: " << '\n';
    cin >> edges;
    cout << "Enter initial and target node: " << '\n';
    cin >> init >> target;
    cout << "Enter edges with cost : " << '\n';
    for (int i = 0; i < edges; i++)
    {
        char x, y;
        int cost;
        cin >> x >> y >> cost;
        int u = x - 'A';
        int v = y - 'A';
        a[u].push_back(make_pair(v, cost));
    }

    int start = init - 'A';
    int goal = target - 'A';

    fill(vis, vis + N, false);
    traversal.clear();
    orig[start] = -1;
    found = false;

    if (ucs(start, goal))
    {
        cout << "Traversing Sequence: ";
        for (int i = 0; i < traversal.size(); i++)
            cout << char(traversal[i] + 'A') << " ";
        cout << '\n';

        vector<int> path;
        int des = goal;
        while (des != -1)
        {
            path.push_back(des);
            des = orig[des];
        }
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (int i = 0; i < path.size(); i++)
            cout << char(path[i] + 'A') << " ";
        cout << '\n';

        cout << "Total Cost: " << dist[goal] << '\n';
    }
    else
    {
        cout << "Failure! No path from " << init << " to " << target << " found.\n";
    }

    return 0;
}
