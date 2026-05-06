#include <vector>
#include <algorithm>
using namespace std;

//天际线问题的解决
class Solution{
    public :
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings){
        //如果建筑物为空
        if(buildings.empty()) return {};
        //如果只有一个建筑物
        if(buildings.size() == 1){
            return {
                {buildings[0][0],buildings[0][2]},
                {buildings[0][1],0}
            };
        }
        //分
        int mid = buildings.size() / 2;
        vector<vector<int>> leftbuildings(buildings.begin(), buildings.begin() + mid);
        vector<vector<int>> rightbuildings(buildings.begin() + mid, buildings.end());
        //分别计算左边和右边的skyline
        vector<vector<int>> leftskyline = getSkyline(leftbuildings);
        vector<vector<int>> rightskyline = getSkyline(rightbuildings);
        //合
        return mergeSkylines(leftskyline, rightskyline);
    }
    private:
    vector<vector<int>> mergeSkylines(vector<vector<int>>& left, vector<vector<int>>& right){
        //使用两个指针
        int p1 = 0;
        int p2 = 0;
        //用于记录当前的最高的高度
        int h1=-1;
        int h2=-1;
        vector<vector<int>> res;
        //开始遍历
    }
}