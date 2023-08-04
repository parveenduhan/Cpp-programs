#include<iostream>
#include<queue>
#include<cstdlib>
using namespace std;

class Node
{
	public:
		int key;
		Node *left;
		Node *right;

		Node(int key)
		{
			this->key = key;
			this->left = nullptr;
			this->right = nullptr;
		}

};

class BinaryTree
{
	public:
		Node *root;
		BinaryTree(int key)
		{
			this->root = new Node(key);

		}

		void insert(Node* root, int key)
		{
			if(root == nullptr)
			{
				root = new Node(key);	
				return ;
			}
			queue<Node*> q;
       			q.push(root);

        		while (!q.empty()) {
            			Node* current = q.front();
            			q.pop();

            			if (current->left == nullptr) {
                			current->left = new Node(key);
                			break;
            			} else {
                			q.push(current->left);
            			}

            			if (current->right == nullptr) {
                			current->right = new Node(key);
                				break;
            			} else {
                			q.push(current->right);
            			}	
        		}	
		}

		void in_order(Node* root)
		{
			if(root != nullptr)
			{
				in_order(root->left);
				cout<<root->key<<" ";
				in_order(root->right);
			}	

		}

		void pre_order(Node* root)
		{
			if(root != nullptr)
			{
				cout<<root->key<<" ";
				pre_order(root->left);
				pre_order(root->right);
			}
		}

		void post_order(Node* root)
		{
			if(root != nullptr)
			{
				post_order(root->left);
				post_order(root->right);
				cout<<root->key<<" ";
			}
		}
		void level_order(Node *root)
		{
			if(root == nullptr)
				return;

			queue<Node*> q;
			q.push(root);
			while(!q.empty())
			{
				Node* current = q.front();
				q.pop();

				cout<<current->key<<" ";
				
				if(current->left != nullptr)
					q.push(current->left);
				if(current->right != nullptr)
					q.push(current->right);
			}
		}



		int height(Node *root)
		{
			if(root == nullptr)
				return 0;
			return 1 + max(height(root->left), height(root->right));
		}

		int max(int a, int b)
		{
			return (a>b)? a: b;
		}
		void print_kth_node(Node *root, int k)
		{
			if(root == nullptr)
				return;
			if(k == 0)
			{
				cout<<root->key<<" ";
				return;
			}
			
			print_kth_node(root->left, k-1);
			print_kth_node(root->right, k-1);
			
		}
	int size(Node* root)
	{
		if(root == nullptr)
			return 0;
		return 1 + size(root->left) + size(root->right);
	}
	int max_ele(Node* root)
	{
		if(root == nullptr)
			return 0;
		if(root->left == nullptr && root->right == nullptr)
			return root->key;
		return (root->left == nullptr)? this->max(root->key, this->max_ele(root->right)): (root->right == nullptr)? this->max(root->key, this->max_ele(root->left)) : this->max(root->key, this->max(this->max_ele(root->left), this->max_ele(root->right)));
	}
	bool is_tree_balanced(Node* root)
	{
		/* if diff in height between left and right subtree is more than 1 then we will call it unbalanced*/
		if(root == nullptr)
			return true;

		return abs(height(root->left) - height(root->right)) <= 1 && is_tree_balanced(root->left) && is_tree_balanced(root->right);

	}	
	int max_tree_width(Node* root)
	{
		if(root == nullptr)
			return 0;
		queue<Node*> q;
		q.push(root);
		int res = 0;
		while(!q.empty())
		{
			int count = q.size();
			res = this->max(res, count);
			for(int i = 0; i<count; i++)
			{
				Node* curr = q.front();
				q.pop();
				if(curr->left)
					q.push(curr->left);
				if(curr->right)
					q.push(curr->right);
			}
		}
		return res;
	}
	int preIdx = 0;
	Node* insert_inorder_preorder(vector<int> inorder, vector<int> preorder, int si, int ei)
	{
		if(si>ei)
			return nullptr;
		Node* root = new Node(preorder[preIdx++]);
		int inIdx = 0;
		for(int i=si; i<=ei; i++)
		{

			if(root->key == inorder[i])
			{
				inIdx = i;
				break;
			}
		}
		root->left = insert_inorder_preorder(inorder, preorder, si, inIdx-1);
		root->right = insert_inorder_preorder(inorder, preorder, inIdx+1, ei);
		return root;
	}
		
	// Public interface with default parameter values
	
    	void insert(int key)
	{
		insert(this->root, key);
	}
	void in_order() 
	{
        	in_order(this->root);
    	}

    	void pre_order() 
	{
        	pre_order(this->root);
    	}

    	void post_order() 
	{
        	post_order(this->root);
   	}
	void level_order()
	{
		level_order(this->root);
	}

	int height()
	{
		return height(this->root);
	}
	void print_kth_node(int k)
	{
		print_kth_node(this->root, k);
	}
	int size()
	{
		return size(this->root);
	}
	int max_ele()
	{
		return max_ele(this->root);
	}
	bool is_tree_balanced()
	{
		return is_tree_balanced(this->root);
	}
	int max_tree_width()
	{
		return max_tree_width(this->root);
	}
};

int main()
{
	
	BinaryTree *btree = new BinaryTree(10);
	btree->insert(20);
	btree->insert(30);
	btree->insert(40);
	btree->insert(50);
	btree->insert(60);
	btree->insert(70);
	cout<<"Inorder: ";
	btree->in_order();
	cout<<endl<<"PreOrder: ";
	btree->pre_order();
	cout<<endl<<"PostOrder: ";
	btree->post_order();
	cout<<endl<<"Level Order: ";
	btree->level_order();
	cout<<endl;
	cout<<"Height: "<<btree->height()<<endl;
	int k = 2;
	cout<<"Nodes at "<<k<<"th distance from root are: ";
	btree->print_kth_node(k);
	cout<<endl<<"Size of B Tree is: "<<btree->size()<<endl;
	cout<<"Max Ele: "<<btree->max_ele()<<endl;
	cout<<"Is tree balanced: "<<btree->is_tree_balanced()<<endl;
	cout<<"Maximum tree width is: "<<btree->max_tree_width()<<endl;

	vector<int> inorder = {20,10,40,30,50};
	vector<int> preorder = {10,20,30,40,50};
	BinaryTree *btree2 = new BinaryTree(0);
	btree2->root = btree2->insert_inorder_preorder(inorder, preorder, 0, inorder.size());
	cout<<"Inorder: ";
	btree2->in_order();
	cout<<"Preorder: ";
	btree2->pre_order();
	cout<<"LevelOrder: ";
	btree2->level_order();
	return 0;
}
