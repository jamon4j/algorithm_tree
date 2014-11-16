/*
 *	Author:zjj
 *	Date:2014/11/16 9:32
 *  Desc:九度OJ1385：重建二叉树，输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
    假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
    例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并输出它的后序遍历序列。
 *  Method: 根据前序首部找到根节点，再到中序中找到该根节点划分左右子树递归建树 
 */
 
#include<stdio.h>
#include<stdlib.h>
#define SIZE 1001
typedef struct TreeNode
{
	int data;
	struct TreeNode *leftChild;
	struct TreeNode *rightChild;
}TreeNode;

int ArrPre[SIZE];
int ArrMid[SIZE];
int CanBuild;

int getMidPos(int key,int start,int end)
{
	for(int i=start;i<end;i++)
	{
		if(ArrMid[i]==key) return i;
	}
	return -1;
}

void createNode(TreeNode **TNode,int data)
{
	 *TNode = (TreeNode*)malloc(sizeof(TreeNode));
	 (*TNode)->data = data;
	 (*TNode)->leftChild = NULL;
	 (*TNode)->rightChild = NULL;	
}

void createBiTree(TreeNode **TNode,int preIndex,int midIndex,int length)
{
	if(length == 0) return;//判断建树结束返回 
	createNode(TNode,ArrPre[preIndex]);
	int midPos = getMidPos(ArrPre[preIndex],midIndex,midIndex+length);
	/*判断根据前序结点，若没有在中序中找到，则该序列无法创建树*/
	if(midPos == -1) 
	{
		CanBuild = 0;
		return;
	}
	
	createBiTree(&((*TNode)->leftChild),preIndex+1,midIndex,midPos-midIndex);
	createBiTree(&((*TNode)->rightChild),preIndex+(midPos-midIndex)+1,midPos+1,length-(midPos-midIndex)-1);
}

void postTravelTree(TreeNode *TNode)
{
	if(TNode == NULL) return;
	postTravelTree(TNode->leftChild); 
	postTravelTree(TNode->rightChild); 
	printf("%d ",TNode->data);
}

void destroyNode(TreeNode **TNode)
{
	(*TNode)->leftChild = NULL;
	(*TNode)->rightChild = NULL;
	free(*TNode);
}

void destroyBiTree(TreeNode **TNode)
{
	if(*TNode == NULL) return;
	destroyBiTree(&((*TNode)->leftChild));
	destroyBiTree(&((*TNode)->rightChild));
	destroyNode(TNode);
}

int main()
{
	int N;
	TreeNode *Root;

	while(scanf("%d",&N)!=EOF)
	{
		for(int i=0;i<N;i++) scanf("%d",&ArrPre[i]);
		for(int i=0;i<N;i++) scanf("%d",&ArrMid[i]);

		CanBuild = 1;
		createBiTree(&Root,0,0,N);
		if(!CanBuild)
		{
			printf("No\n");
		}
		else
		{
			postTravelTree(Root);
			printf("\n");
		}
		
		destroyBiTree(&Root);
	}
	return 0;
} 
/*
8
1 2 4 7 3 5 6 8
4 7 2 1 5 3 8 6
8
1 2 4 7 3 5 6 8
4 1 2 7 5 3 8 6
*/
