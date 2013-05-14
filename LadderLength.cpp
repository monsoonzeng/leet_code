class Solution {
public:
    class Node{
    public:
        int row;
        int col;
    };
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        unordered_set<string>::iterator it = dict.begin();
        vector<string> dict_array;
        vector<bool> status;
        dict_array.push_back(start);
        for (; it!= dict.end(); ++it) {
            if(!start.compare(*it) || !end.compare(*it)) {
                continue;
            }
            dict_array.push_back(*it);
        }
        dict_array.push_back(end);
        if (start.length() < 1 || start.length() < 1 || dict.size()<1 || !start.compare(end)) {
            return 0;
        }
        int len = start.length();
        int count = dict_array.size();
        bool* p_m = new bool[count*count];
        bool** pp_m = (bool**)malloc(count*sizeof(bool*));
        for (int i=0; i< count; ++i) {
            pp_m[i] = p_m + count*i;
        }
        vector<vector<int> > vv_m ;
        if (!transformer_matrix(pp_m, vv_m, start, end, dict_array)) {
            return 0;
        }
        unordered_set<int> sequence;
        sequence.insert(0);
        int result = rec_transformer(pp_m, vv_m,sequence,  0, count-1);
        
        free(pp_m);
        delete[] p_m;
        return result;
    }
    
private:
    int rec_transformer(bool** pp_m, vector<vector<int> > &vv_m, unordered_set<int> &sequence,
            int start, int end) {
        if (pp_m[start][end]) {
            return 2;
        }
        int result = vv_m.size()+1;
        for (int i=0; i<vv_m[start].size(); ++i) {
            int mid = vv_m[start][i];
            if (sequence.find(mid) != sequence.end()) {
                continue;
            }
            sequence.insert(mid);
            int cur = rec_transformer(pp_m, vv_m, sequence,mid, end);
            if (cur == 0) {
                continue;
            }
            ++cur;
            sequence.erase(mid);
            if (cur < result) {
                result = cur;
            }
        }
        if (result > vv_m.size()) {
            result = 0;
        }
        return result;
    }
    //start is the first row, end is the last row
    bool transformer_matrix(bool** pp_m, vector<vector<int> > &vv_m, 
            string start, string end, vector<string> &dict) {
        int len=start.length();
        if (len != end.length()) {
            return false;
        }
        int count = dict.size();
        for (int i=0; i<count; ++i) {
            vv_m.push_back(vector<int>());
        }
        //contruct matrix, pp_m[i][j]=true indicate 
        for(int i=count-1; i>=0; --i) {
            pp_m[i][i] = false;
            for(int j=count-1; j>i; --j) {
                //dict[i], dict[j] distance 1
                int distance=0;
                if (len != dict[i].length() || len != dict[j].length()) return false;
                int k=0;
                for(k=0; k<len; ++k) {
                    if(dict[i][k]!=dict[j][k]){
                        ++distance;
                        if (distance>1) {
                            break;
                        }
                    }
                }
                if (k==len) {
                    pp_m[i][j] = true;
                    pp_m[j][i] = true;
                    vv_m[i].push_back(j);
                    vv_m[j].push_back(i);
                }else {
                    pp_m[i][j] = false;
                    pp_m[j][i] = false;
                }
            }
        }
        return true;
    }
};
