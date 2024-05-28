#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
void insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

int main(){
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("---------------[===== [김민경] [2023041054] =====]---------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void insert(Node* head, int key){
	// 삽입할 새 노드 생성
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    // 새 노드를 삽입할 위치 찾기
    Node* current = head->left;
    Node* parent = NULL; // 부모 노드 저장 변수

    while (current != NULL) {
        // 부모 노드 변경
        parent = current;

        // 삽입할 왼쪽, 오른쪽 결정
        if (key < current->key) {
        current = current->left;
        } else {
        current = current->right;
        }
    }

    // Insert the new node at the correct position
    if (parent == NULL) { // Insert as the root node
        head->left = newNode;
    } else if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

void inorderTraversal(Node* ptr){
	Node* p = ptr;
	if(p){
		inorderTraversal(p->left);
		printf("[%d] ",p->key);
		inorderTraversal(p->right);
	}
}

void preorderTraversal(Node* ptr){
	Node* p = ptr;
	if(p){
		printf("[%d] ",p->key);
		preorderTraversal(p->left);
		preorderTraversal(p->right);
	}
}

void postorderTraversal(Node* ptr){
	Node* p = ptr;
	if(p){
		postorderTraversal(p->left);
		postorderTraversal(p->right);
		printf("[%d] ",p->key);
	}
}

int deleteLeafNode(Node* head, int key){
    // 트리가 empty 이면 return
    if (head == NULL) {
        return 1;
    }

    // Search for the target node
    Node* parent = NULL;
    Node* target = head->left; // Start from the leftmost child

    while (target != NULL) {
        if (target->key == key) {
            break; // Found the target node
        } else if (key < target->key) {
            parent = target;
            target = target->left;
        } else {
            parent = target;
            target = target->right;
        }
    }
    
    
    // If the target node was not found
    if (target == NULL) {
        printf("삭제할 노드를 찾을 수 없음\n");
        return 1; // Node with the given key does not exist
    }

    
    //삭제할 노드가 root 노드라면
    if (parent == NULL){
        //root 노드의 왼쪽, 오른쪽 자식이 둘 다 NULL이 아니거나 오른쪽 자식이 null이 아니라면
        if(target->left != NULL && target->right != NULL || target->right != NULL){
            
            Node* successor = target->right;
            if (successor != NULL) {
                while (successor->left != NULL) successor = successor->left;
            }
            target->key = successor->key;
            printf("su: %d\n",successor->key);

            target->right=successor->right;
            if(successor->right==NULL) free(successor);
        }
        //root 노드의 왼쪽 자식이 null이 아니고 오른쪽 자식은 null이라면
        else{
            Node* successor = target->left;
            if (successor != NULL) {
                while (successor->left != NULL) successor = successor->right;
            }
            target->key = successor->key;
            printf("target: %d\n",target->key);

            target->left=successor->left;
            if(successor->left==NULL) free(successor);
        }
    }


    //root 노드가 아니고 삭제할 노드의 자식이 있다면
    else if (target->left != NULL || target->right != NULL) {
        // 연결해야 될 자식 찾기
        //삭제할 노드의 오른쪽 자식(왼쪽 노드보다 큰 노드) 중 가장 작은 노드(왼쪽 노드)를 찾기
        Node* successor = target->right;
        if (successor != NULL) {
            while (successor->left != NULL) successor = successor->left;
        }
        printf("target: %d\n",target->key);
        
        // printf("successor: %d\n",successor->key);
        // printf("parent: %d\n",parent->key);
        // 삭제할 노드 key 위치에 찾은 노드의 key 넣기
        target->key = successor->key;

        // Delete the successor node (which is guaranteed to be a leaf node)
        // Find the parent of the successor
        while (parent->left != successor && parent->right != successor) {
            if (successor->key < parent->key) parent = parent->left;
            else parent = parent->right;
            
        }
        
        if (parent->left == successor) {
            parent->left = successor->left;
        } else {
            parent->right = successor->left;
        }
        free(successor);

    }
    
    else { // Handle deletion of a leaf node
        // Remove the leaf node
        if (parent == NULL) head->left = NULL;
        else if (parent->left == target) parent->left = NULL;
        else parent->right = NULL;
        free(target);
    }

    return 1; // Successful deletion
}

Node* searchRecursive(Node* ptr, int key){
	Node* p = ptr;

	if (p->key == key) return p; //키가 현재 노드의 키와 같을 경우 p 리턴
  	else if (key < p->key) return searchRecursive(p->left, key); //키가 현재 노드의 키보다 작을 경우 왼쪽 하위 트리에서 키 검색
	return searchRecursive(p->right, key); //키가 현재 노드의 키보다 큰 경우 오른쪽 하위 트리에서 키 검색
}

Node* searchIterative(Node* head, int key){
	Node* p = head->left;
    
	while (p != NULL){
		if(p->key==key) return p;
		else if(key < p->key) p = p->left;
		else p=p->right;
	}
	return NULL;
}


int freeBST(Node* head){
    // Node* temp=head->left;
    // // Base case: Empty tree
    // if (temp == NULL) {
    //     return 1; // Successful deallocation (nothing to free)
    // }

    // // Recursively free left and right subtrees
    // freeBST(temp->left);
    // freeBST(temp->right);

    // // Free the current node after freeing its children
    // free(temp);
    // return 1; // Successful deallocation
}





