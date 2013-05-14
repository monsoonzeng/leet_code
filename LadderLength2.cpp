iclass Solution {
public:
    class Node{
    public:
        int row;
        int col;
    };
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<string> dict_array;
        vector<bool> status;
        dict_array.push_back(start);
        unordered_set<string>::iterator it = dict.begin();
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
        int count = dict_array.size();
        vector<vector<int> > vv_m ;
        if (!transformer_matrix(pp_m, vv_m, start, end, dict_array)) {
            return 0;
        }
        int result = transformer(vv_m, 0, count-1);
        
        return result;
    }
    
private:
    int transformer(vector<vector<int> > &vv_m, int start, int end) {
	//depth first 
	query<int> q;
	q.push(0);
	int cur, depth=1;
        vector<int> status;//store use visited node 
        for (int i=0; i< vv_m.size(); ++i) {
            status.push_back(0);
        }
	while(!q.empty()) {
	    cur = q.front();
	    q.pop();
	    for (int i=0; i<vv_m[cur].size(); ++i) {
		int adjcent = vv_m[cur][i];
		if(status[adjcent]!=0) { continue;}
		if (adjcent == end) { return depth+1;} 
		q.push(adjcent);
		status[adjcent] = 1;
	    }
	    ++depth;
	}
	return 0;
    }

    int dijkstra_transformer(vector<vector<int> > &vv_m, int start, int end) {
        vector<int> stack;
        stack.push_back(start);
        vector<int> status;//store use edge number
	int count = vv_m.size();
	vecotr<int> len_v; //store min length to start
        for (int i=0; i< vv_m.size(); ++i) {
            status.push_back(0);
	    len_v.push_back(count+1);
        }
	len_v[0] = 0;
        int min_len = 0;
	int min_index = 0;
	int result = count+1;
	for(int index=0; index<count; ++index) {
            //find min length node
	    min_len = count+2;
	    for (int j=0; j<count; ++j) {
	        if(status[j]==0 && len_v[j]<min_len) {
		    min_len = lev_v[j];
		    min_index = j;
		}
	    }
            if (min_len == count+2) {break;}
	    status[min_index] = 1;
	    if (min_index==end) {result = min_len; break;}
	    for(int i=0; i<vv_m[min_index].size(); ++i) {
	    	int adjcent = vv_m[min_index][i];
		if (status[adjcent]==0&&len_v[adjcent]>min_len+1) {
		    len_v[adjcent] = min_len+1;
		}
	    }
	}
	if (result > count) { result =0;}
	return result;
    }
    //start is the first row, end is the last row
    bool transformer_matrix(vector<vector<int> > &vv_m, 
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
                if (distance < 2) {
                    vv_m[i].push_back(j);
                    vv_m[j].push_back(i);
                }
            }
        }
        return true;
    }
};
