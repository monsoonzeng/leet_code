/*
Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 <= m < n <= length of list.

*/

struct ListNode {
 int val;
 ListNode *next;
 ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (m >= n || m <1 || head == NULL) {
            return head;
        }
        // add empty head
        ListNode new_head(0);
        new_head.next = head;
        ListNode *start = NULL;
        ListNode *end = NULL;
        ListNode *next = NULL;
        ListNode *current = &new_head;
        int index = 0;
        for (; current != NULL; current = next, ++index) {
            if (index == m-1) {
                // get start node of revert
                start = current;
                next = current->next;
                current->next = NULL;
            } else if (index >= m && index <= n) {
                // record m
                if (index == m) {
                    end = current;
                }
                // insert current to start
                next = current->next;
                current->next = start->next;
                start->next = current;
                if (index == n) {
                    // link end to next
                    end->next = next;
                    break;
                }
            } else {
                next = current->next;
            }
        }
        return new_head.next;
        
    }
};

