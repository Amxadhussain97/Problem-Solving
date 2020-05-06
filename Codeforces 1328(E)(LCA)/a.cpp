/*
    হ্যাঁ এটাই সাইন্স!!!!
*/
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
#define ll long long
#define pb push_back
#define S second
#define F first
#define mem(a, b)     memset(a, b, sizeof(a))
#define pii          pair<ll,ll>
#define bug(a)       cerr << #a << " : " << a << endl;
#define BaChao     ios_base::sync_with_stdio(false);cin.tie(NULL);

typedef tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > ordered_set;
typedef tree <int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update > ordered_multiset;

/*
Note :  There is a problem with erase() function in ordered_multiset (for less_equal<int> tag).
        lower_bound() works as upper_bound() and vice-versa.
        Be careful to use.
        i) find_by_order(k) : kth smallest element counting from 0 .
        ii) order_of_key(k) : number of elements strictly smaller than k.
*/

/******************************************
#Rows are numbered from top to bottom.
#Columns are numbered from left to right.
Moves : L, U, R, D, LU, RU, RD, LD.
Lower bound e >=
Upper bound e >b
******************************************/

/*...... ! Code starts from here ! ......*/
const int MX = 300000;
int vis[MX],dep[MX],T[MX],P[MX][30];
vector<int>v[MX];
void dfs(int node, int lev,int par)
{
    vis[node]=1;
    dep[node]=lev;
    T[node]=par;
    for(auto i:v[node])
    {
        if(!vis[i]) dfs(i,lev+1,node);
    }
}
void initLCA(int n)
{
    memset(P,-1,sizeof P);

    for(int i=1;i<=n;i++)
        P[i][0] = T[i];

    for(int j=1; 1<<j <n;j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(P[i][j-1] != -1)
                P[i][j] = P[P[i][j-1]][j-1];
        }
    }
}
int query(int n,int u,int v)
{
    if(dep[u] < dep[v])
        swap(u,v);

    int log = 1;

    while(1)
    {
        int next = log+1;
        if((1<<next) > dep[u])
            break;
        log++;
    }

    for(int i=log;i>=0;i--)
    {
        if(dep[u]-(1<<i) >= dep[v])
            u = P[u][i];
    }

    if(u == v)
        return u;

    for(int i=log;i>=0;i--)
    {
        if(P[u][i] != -1 && P[u][i] != P[v][i])
        {
            u = P[u][i];
            v = P[v][i];
        }
    }
    return T[u];
}
bool cmp(int x, int y)
{
    return dep[x]>dep[y];
}
int main()
{
    BaChao
    int n,m,x,y,now,par;
    cin>>n>>m;
    for(int i=1;i<n;i++)
    {
        cin>>x>>y;
        v[x].pb(y);
        v[y].pb(x);
    }
    dfs(1,0,-1);
    initLCA(n);
    for(int i=0;i<m;i++)
    {
        cin>>x;
        int val[x],f=1;
        for(int j=0;j<x;j++)
        {
            cin>>val[j];
        }
        sort(val,val+x,cmp);
        now=val[0];
        for(int j=1;j<x;j++)
        {
            par=query(n,now,val[j]);
            if((dep[val[j]]-dep[par])>1) f=0;

        }
        f?cout<<"YES"<<endl:cout<<"NO"<<endl;

    }





}
