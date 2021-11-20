#include <iostream>
#include <vector>

using namespace std;

//template<typename T>
vector<string> func(vector<string>& s){
    auto pall = [](string& s){
        int i = 0, j = s.size() - 1;
        while(i < j){
            if(s[i] != s[j])
                return false;
            i++; j--;
        }
        return true;
    };
    vector<string> ans;
    for(int i = 0; i < s.size(); ++i){
        if(pall(s[i]))
            ans.push_back(s[i]);
    }
    return ans;
}


int main(){
    vector<string> s = {"abc", "abba", "abcba"};
    vector<string> a = func(s);
    for(int i = 0; i < a.size(); ++i){
        cout << a[i] << " "; 
    }
    cout << endl;
}
