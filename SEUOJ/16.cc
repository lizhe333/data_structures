#include <vector>
#include <iostream>
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
        int h1=0;
        int h2=0;
        vector<vector<int>> res;
        //开始遍历
        int leftsize = left.size();
        int rightsize = right.size();
        while(p1<leftsize && p2<rightsize){
            int x1=left[p1][0];
            int x2=right[p2][0];
            int h_max=-1;
            if(x1<x2){
                h1 = left[p1][1];
                h_max = max(h1, h2);
                if(res.empty()||h_max!=res.back()[1]){
                    res.push_back({x1, h_max});
                }
                p1++;
            }else if(x1>x2){
                h2 = right[p2][1];
                h_max = max(h2, h1);
                if(res.empty()||h_max!=res.back()[1]){
                    res.push_back({x2, h_max});
                }
                p2++;
            }else{
                //如果两个x坐标相同，同时刷新状态进行比较
                h1 = left[p1][1];
                h2 = right[p2][1];
                h_max = max(h1, h2);
                if(res.empty()||h_max!=res.back()[1]){
                    res.push_back({x1, h_max});
                } 
                //两个指针都要后移
                p1++;
                p2++;
            }
        }
        while(p1<leftsize){
            //如果左边还有建筑物
            if(res.empty() || res.back()[1] != left[p1][1]) {
                res.push_back(left[p1]);
            }
        }
        while(p2<rightsize){
            //如果右边还有建筑物
            if (res.empty() || res.back()[1] != right[p2][1]) {
                res.push_back(right[p2]);
            }
            p2++;
        }
        return res;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    if (!(cin >> N)) return 0; 
    vector<vector<int>> buildings(N, vector<int>(3));
    for (int i = 0; i < N; ++i) {
        cin >> buildings[i][0] >> buildings[i][1] >> buildings[i][2];
    }
    Solution sol;
    vector<vector<int>> result = sol.getSkyline(buildings);
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i][0] << " " << result[i][1] << "\n";
    }

    return 0;
}