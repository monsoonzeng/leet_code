class Solution {
public:
    int minCut(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s.empty()) {
              return 0;
        }
        size_t len = s.length();
        const char* input = s.c_str();
        bool* p_m = (bool*)calloc(len*len, sizeof(bool));
        bool** pp_m = (bool**)malloc(len*sizeof(bool*));                                     
        int* cut_array = (int*) malloc(len*sizeof(int));                                 
        for (size_t i=0; i<len; ++i) {                                                       
            pp_m[i] = p_m + i*len;
        }                                                                                    
        //init palindrome matrix                                                             
        pp_m[len-1][len-1] = true;
        /*          for (int i=len-2; i>=0; --i) {
          pp_m[i][i] = true;
          pp_m[i][i+1] = (input[i]==input[i+1]);
          for (size_t j=i+2; j<len; ++j) {
              pp_m[i][j] = ((input[i]==input[j])?pp_m[i+1][j-1]:false);
          }   
        }   
        */          
        //set
        int result = 0;
        cut_array[len-1] = 0;
        for (int i=len-2; i>=0; --i) {
            pp_m[i][i] = true;
            pp_m[i][i+1] = (input[i]==input[i+1]);
            cut_array[i] = cut_array[i+1] + 1;
            for (size_t j=i+1; j<len; ++j) {
                if(input[i]==input[j] && (j==i+1 || pp_m[i+1][j-1])) {
                    pp_m[i][j] = true;
                    if (cut_array[i]>cut_array[j+1]+1) {
                        cut_array[i] = cut_array[j+1]+1;
                    }
                }
            }
            if (pp_m[i][len-1]) cut_array[i] = 0;
        }
        result = cut_array[0];
        
        free(p_m);
        free(pp_m);
        free(cut_array);
        return result;
    }
};
