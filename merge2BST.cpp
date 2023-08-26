void bstToDLL(TreeNode* root, TreeNode* &head) {
    //base case
    if(root == NULL) {
        return;
    }
    
    bstToDLL(root -> right, head);
    root -> right = head;
    
    if(head != NULL) 
        head -> left = root;
        
    head = root;

    bstToDLL(root -> left, head);
}

int countNodes(TreeNode* head) {
    int cnt = 0;
    
    TreeNode* temp = head;
    while(temp != NULL) {
        cnt++;
        temp = temp -> right;
    }
    return cnt;
}

TreeNode* mergeDLL(TreeNode* head1, TreeNode* head2) {
    
    TreeNode* head = NULL;
    TreeNode* tail = NULL;
    
    while(head1 != NULL && head2 != NULL) {
        if(head1 -> data < head2 -> data) {
            if(head == NULL) {
                head = head1;
                tail = head1;
                head1 = head1 -> right;
            }
            else {
                tail -> right = head1;
                head1 -> left = tail;
                tail = head1;
                head1 = head1 -> right;
            }
        }
        else {
            if(head == NULL) {
                head = head2;
                tail = head2;
                head2 = head2 -> right;
            }
            else {
                tail -> right = head2;
                head2 -> left = tail;
                tail = head2;
                head2 = head2 -> right;
            }
        }
    }

    while(head1 != NULL) {
        tail -> right = head1;
        head1 -> left = tail;
        tail = head1;
        head1 = head1 -> right;
    }

    while(head2 != NULL){
        tail -> right = head2;
        head2 -> left = tail;
        tail = head2;
        head2 = head2 -> right;
    }

    return head;
}

TreeNode* createBst(TreeNode* &head, int n) {
    //base case
    if(n <= 0 || head == NULL) {
        return NULL;
    }
    
    TreeNode* left = createBst(head, n/2);
    
    TreeNode* root = head;
    root -> left = left;

    head = head -> right;

    root -> right = createBst(head, n-n/2-1);

    return root;
}

void inorder(TreeNode* head, vector<int> &ans) {
    //base case
    if(head == NULL) {
        return;
    }

    inorder(head -> left, ans);
    ans.push_back(head -> data);
    inorder(head -> right, ans);
}

vector<int> mergeBST(TreeNode *root1, TreeNode *root2)
{
    //step1 : convert the BSTs into DLL
    
    TreeNode* head1 = NULL;
    TreeNode* head2 = NULL;

    bstToDLL(root1, head1);
     
    bstToDLL(root2, head2);

    //step2 : merge two sorted LL's

    TreeNode* head3 = mergeDLL(head1, head2);

    //step 3 : convert the LL's into BST

    int n = countNodes(head3);

    TreeNode* bst3 = createBst(head3, n);

    vector<int> ans; 

    inorder(bst3, ans);

    return ans;
}