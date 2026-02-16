#include<vector>
using namespace std;
class FindUnion{
  private:
    vector<int> parent;
    
    int count;
    public:
    FindUnion(vector<vector<char>>& grid){
        count=0;
        int n=grid.size();
        int m=grid[0].size();
        for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]=='0')
                parent.push_back(-1);//记录无效位置
            else{parent.push_back(i*m+j);
                count++;
            }
        }
        }
    }
    int find(int x){
        if(x==parent[x]){
            return x;
        }
        parent[x]=find(parent[x]);
        return parent[x];
    }
    void unite(int x,int y){
        int rootX=find(x);
        int rootY=find(y);
        if(rootX!=rootY){
        parent[rootX]=rootY;
        count--;
        }
    return;
    }
    int getCount() const {
        return count;
    }
};
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int nr=grid.size(), nc=grid[0].size();
        FindUnion uf(grid);
        //进行遍历，然后尝试合并
        for(int i=0;i<nr;i++){
            for(int j=0;j<nc;j++){
                if(grid[i][j]=='1'){
                    
                    int index=i*nc+j;
                   
                    if(i>0 && grid[i-1][j]=='1'){
                        uf.unite(index,index-nc);
                    }
                    if(i<nr-1 && grid[i+1][j]=='1'){
                        uf.unite(index,index+nc);
                    }
                    if(j>0 && grid[i][j-1]=='1'){
                        uf.unite(index,index-1);
                    }
                    if(j<nc-1 && grid[i][j+1]=='1'){
                        uf.unite(index,index+1);
                    }
                }
            }
        }
        return uf.getCount();
    }
};