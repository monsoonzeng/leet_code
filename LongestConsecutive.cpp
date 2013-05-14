
class Solution {
    
public:
    int longestConsecutive(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        int max = 0;
        if(num.empty()) {
            return max;
        }
        int M = num.size();
        unordered_map<int, int> cluster;
    
        int left;
        int right;
        int center;
        int cur_max=1;
        for(int i=0; i<M; ++i) {
            center = num[i];
            left = num[i]-1;
            right = num[i]+1;
            if (cluster.find(center) != cluster.end()) {
                continue;
            }
            cluster[center] = 1;
            cur_max = 1;
            bool has_left = (cluster.find(left)!=cluster.end());
            if(has_left) {
                cur_max = merge(cluster, left, center);
            } 
            bool has_right = (cluster.find(right)!=cluster.end());
            if (has_right) {
                cur_max = merge(cluster, center, right);
            }
            if (cur_max > max) {
                max = cur_max;
            }
        }
        return max;
    }
private:
    int merge(unordered_map<int,int> &cluster, int left, int right) {
        int upper = right + cluster[right] -1;
        int lower = left - cluster[left] + 1;
        int len = upper - lower + 1;
        cluster[upper] = len;
        cluster[lower] = len;
        return len;
    }
};