#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// typedef vector<int> vi; 
// typedef vector<vector<int>> vvi; 
// typedef vector<long long> vl; 
// typedef vector<vector<long long>> vvl; 
// typedef vector<bool> vb; 
// typedef vector<vector<bool>> vvb; 
// typedef map<int, int> mii; 
// typedef map<long long, long long> mll; 
// typedef pair<int, int> pii; 
// typedef pair<long long, long long> pll; 
// typedef unsigned long long ull; 
// typedef long double ld; 
// typedef long long ll;

bool dfs(long long int ind, vector<vector<long long int>> &graph, vector<long long int> &vis, vector<long long int> &col, long long int &one, long long int &two)
{
    // returns whether the graph is bipartite, if true, int one and two store the number of alternate coloured nodes
    // vis - visited array, col - array to store the color 

    vis[ind]=1;

    for(auto it : graph[ind]){

        if(vis[it]==0){

            if(col[ind]==1){

                col[it]=2;
                two++;

                if(dfs(it, graph, vis, col, one, two) == false){
                    return false;
                }
            }
            else{

                col[it]=1;
                one++;

                if(dfs(it,graph, vis, col, one, two) == false){
                    return false;
                }
            }
        }
        else{
            if(col[it]==col[ind]){
                return false;
            }
        }
    }

    return true;

}

int main()
{
    
    long long int n; cin>>n;
    vector<vector<long long int>> seq(n, vector<long long int> (3, 0));

    for(int i=0; i<n; i++) {
        for(int j=0; j<3; j++) {
            cin>>seq[i][j];
        }
    }

    vector<vector<long long int>> graph(n);

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            // checking if any two circles are tangent to each other
            unsigned long long int x1 = ((abs(seq[i][0]-seq[j][0]))*(abs(seq[i][0]-seq[j][0]))) ;
            x1+=((abs(seq[i][1]-seq[j][1]))*(abs(seq[i][1]-seq[j][1])));

            unsigned long long int x2 = (abs(seq[i][2]+seq[j][2]));
            x2*= (abs(seq[i][2]+seq[j][2]));

            // if tangent, add to them to the graph
            if(x1==x2){
                graph[i].push_back(j);
                graph[j].push_back(i);
            }

        }
    }
    
    bool ans=false;
    vector<long long int> vis(n, 0);
    vector<long long int> col(n, 0);
    for(int i=0; i<n; i++){

        if(vis[i]==0){
            long long int one=1, two=0;
            col[i]=1;

            // if bipartite, check whether the different coloured nodes are not same in number
            if(dfs(i, graph, vis, col, one, two) == true){
                if((one-two)!=0){
                    // cout<<one<<" "<<two<<" @\n";
                    ans=true;
                }
            }
        }

    }

    if(ans==true){
        cout<<"YES\n";
    }
    else{
        cout<<"NO\n";
    }

    

}