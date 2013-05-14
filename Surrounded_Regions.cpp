class Solution {
public:
    class Region {
    public:
        int start_row=0;
        int end_row=0;
        vector<int> start_col;
        vector<int> end_col;
    };
    class Node {
    public:
        int row;
        int col;
        Node(){}
        Node(int i, int j):row(i),col(j){}
        bool operator== (const Node &node) {
            return row==node.row && col==node.col;
        }
        bool operator!= (const Node &node) {
            return row!=node.row || col!=node.col;
        }
    };
    void solve(vector<vector<char>> &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        //region=c(start_row, end_row, index=[end_row-start_row][2])
        //op = {0:begin, 1:col+1, 2:col+1&row+1, 3: row+1, 4:row-1&col+1, 
        //      5:row+1&col-1, 6:col-1, 7:row-1, 8:row-1&col-1}
        
        //init op_matrix which 
        vector<vector<unsigned char> > op_m;
        //init node status: which show in cur stack;
        vector<vector<int> > status_m ;
        for (int row=0; row < board.size(); ++row) {
            status_m.push_back(vector<int>());
            op_m.push_back(vector<unsigned char>());
            for (int col=0; col < board[row].size(); ++col) {
                
                op_m[row].push_back(0);
                status_m[row].push_back(0);
            }
        }
        //all regions
        vector<Region> regions;
        vector<Node> node_stack;
        for (int row=0; row < op_m.size(); ++row) {
            for (int col=0; col < op_m[row].size(); ++col) {
                if(board[row][col]!='X' || op_m[row][col] >= 8) {
                    continue;
                }
                node_stack.push_back(Node(row, col));
                status_m[row][col] = 1;
                
                //find region start with cur node
                while(!node_stack.empty()) {
                    Node cur_node = node_stack.back();
                    Node next_node;
                    if(walk2next(board, cur_node, next_node, op_m)) {
                        //has next node, 
                        int next_node_status = status_m[next_node.row][next_node.col];
                        if (next_node_status>0) {
                            //exit region, 
			    //record region
                            Region r;
                            r.start_row = next_node.row;
                            r.end_row = next_node.row;
                            r.start_col.push_back(next_node.col);
                            r.end_col.push_back(next_node.col);
                            for (int i=next_node_status; i < node_stack.size(); ++i) {
                                cur_node = node_stack[i];
                                if (cur_node.row >r.end_row) {
                                    r.end_row = cur_node.row;
                                    r.start_col.push_back(cur_node.col);
                                    r.end_col.push_back(cur_node.col);
                                } else if(cur_node.row < r.start_row) {
                                    r.start_row = cur_node.row;
                                    r.start_col.insert(r.start_col.begin(), cur_node.col);
                                    r.end_col.insert(r.end_col.begin(), cur_node.col);
                                } else {
                                    int index = cur_node.row-r.start_row;
                                    if (cur_node.col < r.start_col[index]) {
                                        r.start_col[index] = cur_node.col;
                                    } else if (cur_node.col > r.end_col[index]) {
                                        r.end_col[index] = cur_node.col;
                                    }
                                }
                            }
                            if (r.end_row - r.start_row > 1) {
                                regions.push_back(r);
                            }
                        } else {
                            //push next node if no region
                            node_stack.push_back(next_node);
                            status_m[next_node.row][next_node.col] = node_stack.size();
                        }
                    } else {
                        node_stack.pop_back();
                        //clear status
                        status_m[cur_node.row][cur_node.col] = 0;
                        
                    }
                }
            }
        }
        //get all regions
        //flip table
        for(int i=0; i< regions.size(); ++i) {
            for(int j=regions[i].start_row; j<=regions[i].end_row; ++j) {
                for (int k=regions[i].start_col[j]; k<=regions[i].end_col[j]; ++k) {
                    board[j][k] = 'X';
                }
            }
        }
        
    }
private:
    //get next x node base cur node and cur node op value
    bool walk2next(const vector<vector<char> > &board, const Node &cur_node, Node &next_node, 
            vector<vector<unsigned char> > &op_m) {
        //if no next return false    
        //op = {0:begin, 1:col+1, 2:col+1&row+1, 3: row+1, 4:row-1&col+1, 
        //      5:row+1&col-1, 6:col-1, 7:row-1, 8:row-1&col-1, 9:done}
        bool result = false;
        switch (op_m[cur_node.row][cur_node.col]) {
        case 0:
            if ((cur_node.col+1 < board[cur_node.row].size()) 
                    && board[cur_node.row][cur_node.col+1]=='X') {
                result = true;
                next_node.row = cur_node.row;
                next_node.col = cur_node.col+1;
                op_m[cur_node.row][cur_node.col] = 1;
                break;
            }
        case 1:
            if ((cur_node.row+1<board.size()) && (cur_node.col+1 < board[cur_node.row+1].size()) 
                    &&board[cur_node.row+1][cur_node.col+1]=='X') {
                result = true;
                next_node.row = cur_node.row+1;
                next_node.col = cur_node.col+1;
                op_m[cur_node.row][cur_node.col] = 2;
                break;
            }
        case 2:
            if ((cur_node.row+1<board.size()) && (cur_node.col < board[cur_node.row+1].size()) 
                    && board[cur_node.row+1][cur_node.col]=='X') {
                result = true;
                next_node.row = cur_node.row+1;
                next_node.col = cur_node.col;
                op_m[cur_node.row][cur_node.col] = 3;
                break;
            }
        case 3:
            if ((cur_node.row-1>=0) && (cur_node.col+1 < board[cur_node.row-1].size()) 
                    && board[cur_node.row-1][cur_node.col+1]=='X') {
                result = true;
                next_node.row = cur_node.row-1;
                next_node.col = cur_node.col+1;
                op_m[cur_node.row][cur_node.col] = 4;
                break;
            }
        case 4:
            if ((cur_node.row+1<board.size()) && (cur_node.col-1 < board[cur_node.row+1].size() &&cur_node.col-1>=0) 
                    && board[cur_node.row+1][cur_node.col-1]=='X') {
                result = true;
                next_node.row = cur_node.row+1;
                next_node.col = cur_node.col-1;
                op_m[cur_node.row][cur_node.col] = 5;
                break;
            }
        case 5:
            if ((cur_node.col-1>=0) 
                    && board[cur_node.row][cur_node.col-1]=='X') {
                result = true;
                next_node.row = cur_node.row;
                next_node.col = cur_node.col-1;
                op_m[cur_node.row][cur_node.col] = 6;
                break;
            }
        case 6:
            if ((cur_node.row-1>=0) && (cur_node.col < board[cur_node.row-1].size()) 
                    && board[cur_node.row-1][cur_node.col]=='X') {
                result = true;
                next_node.row = cur_node.row-1;
                next_node.col = cur_node.col;
                op_m[cur_node.row][cur_node.col] = 7;
                break;
            }
        case 7:
            if ((cur_node.row-1>=0) && (cur_node.col-1 < board[cur_node.row-1].size() && cur_node.col-1>=0) 
                    && board[cur_node.row-1][cur_node.col-1]=='X') {
                result = true;
                next_node.row = cur_node.row-1;
                next_node.col = cur_node.col-1;
                op_m[cur_node.row][cur_node.col] = 8;
                break;
            }
        case 8:
            result = false;
            break;
        }
        return result;
    }
    
};
