#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
struct Node *CreateNewNode(int data[3][3]);
void addChild(Node *node, int data[3][3]);
struct Node
{
    int data[3][3];
    // int fn;
    vector<Node *> children;
};
Node *root;
Node *temp = root;
vector<Node *> allNodes;
int flag1 = 0;
queue<Node *>Que;
// queue<Node *>Q;
int cnt=0;
// vector<Node *> childNodes;
map<int, Node *> openList;
vector<Node *> closedList;
int findFn(int mat[3][3]){
int misplaced_tile=0;
int goal[3][3] = {{1,2,3},
{4,5,6},
{7,8,0}};
for (int i = 0; i < 3; i++)
{
    for (int j = 0; j < 3; j++)
    {
        if (mat[i][j] != goal[i][j])
        {
            misplaced_tile++;
        }
    }
}
    return misplaced_tile;
}
void get_Co_Zero(int mat[3][3], int *zerx, int *zery)
{
int flag = 0;
for (int i = 0; i < 3; i++)
{
for (int j = 0; j < 3; j++)
{
if (mat[i][j] == 0)
{
*zerx = i;
*zery = j;
flag = 1;
break;
}
}
if (flag == 1)
{
break;
}
}
}
bool isVisited(Node *node)
{
int flagCheck = 0;
for (int i = 0; i < allNodes.size(); i++)
{
// cout << "flagCheck===" << flagCheck;
// cout << "\naniket\n";
if (flagCheck == 0)
{
flagCheck = 1;
// cout << "flagCheck1===" << flagCheck;
for (int j = 0; j < 3; j++)
{
for (int k = 0; k < 3; k++)
{
if (allNodes[i]->data[j][k] != node->data[j][k])
{
flagCheck = 0;
break;
}
}
if (flagCheck == 0)
{
break;
}
}
}
else
{
break;
}
}
if (flagCheck == 0)
{
allNodes.push_back(node);
return false;
}
return true;
}
void up(Node *temp, int mat[3][3], int zerx, int zery)
{
int newm[3][3];
if (zerx != 0)
{
for (int i = 0; i < 3; i++)
{
for (int j = 0; j < 3; j++)
{
newm[i][j] = mat[i][j];
}
}
int newPos = zerx - 1;
int temp = newm[newPos][zery];
newm[newPos][zery] = 0;
newm[zerx][zery] = temp;
}
Node *updatedmat = CreateNewNode(newm);
if (!isVisited(updatedmat))
{
cout << "up";
addChild(temp, newm);
// Q.push(updatedmat);
cnt++;
openList.insert(pair<int,Node *>(findFn(newm),updatedmat));
}
else{
cout<<"visited!!!";
}
}
void down(Node *temp, int mat[3][3], int zerx, int zery)
{
int newm[3][3];
if (zerx != 2)
{
for (int i = 0; i < 3; i++)
{
for (int j = 0; j < 3; j++)
{
newm[i][j] = mat[i][j];
}
}
int newPos = zerx + 1;
int temp = newm[newPos][zery];
newm[newPos][zery] = 0;
newm[zerx][zery] = temp;
}
Node *updatedmat = CreateNewNode(newm);
if (!isVisited(updatedmat))
{
cout << "down";
addChild(temp, newm);
// Q.push(updatedmat);
cnt++;
openList.insert(pair<int,Node *>(findFn(newm),updatedmat));
}
else{
cout<<"visited!!!";
}
}
void right(Node *temp, int mat[3][3], int zerx, int zery)
{
int newm[3][3];
if (zery != 2)
{
for (int i = 0; i < 3; i++)
{
for (int j = 0; j < 3; j++)
{
newm[i][j] = mat[i][j];
}
}
int newPos = zery + 1;
int temp = newm[zerx][newPos];
newm[zerx][newPos] = 0;
newm[zerx][zery] = temp;
}
Node *updatedmat = CreateNewNode(newm);
if (!isVisited(updatedmat))
{
cout << "right";
addChild(temp, newm);
// Q.push(updatedmat);
openList.insert(pair<int,Node *>(findFn(newm),updatedmat));
cnt++;
}
else{
cout<<"visited!!!";
}
}
void left(Node *temp, int mat[3][3], int zerx, int zery)
{
int newm[3][3];
if (zery != 0)
{
for (int i = 0; i < 3; i++)
{
for (int j = 0; j < 3; j++)
{
newm[i][j] = mat[i][j];
}
}
int newPos = zery - 1;
int temp = newm[zerx][newPos];
newm[zerx][newPos] = 0;
newm[zerx][zery] = temp;
}
Node *updatedmat = CreateNewNode(newm);
if (!isVisited(updatedmat))
{
cout << "left";
addChild(temp, newm);
// Q.push(updatedmat);
openList.insert(pair<int,Node *>(findFn(newm),updatedmat));
cnt++;
}
else{
cout<<"visited!!!";
}
}
void decide(Node *temp, int mat[3][3], int zerx, int zery)
{
switch (zerx)
{
case 0:
switch (zery)
{
case 0:
right(temp, mat, zerx, zery);
down(temp, mat, zerx, zery);
break;
case 1:
right(temp, mat, zerx, zery);
left(temp, mat, zerx, zery);
down(temp, mat, zerx, zery);
break;
case 2:
left(temp, mat, zerx, zery);
down(temp, mat, zerx, zery);
break;
default:
break;
}
break;
case 1:
switch (zery)
{
case 0:
right(temp, mat, zerx, zery);
up(temp, mat, zerx, zery);
down(temp, mat, zerx, zery);
break;
case 1:
right(temp, mat, zerx, zery);
left(temp, mat, zerx, zery);
up(temp, mat, zerx, zery);
down(temp, mat, zerx, zery);
break;
case 2:
left(temp, mat, zerx, zery);
up(temp, mat, zerx, zery);
down(temp, mat, zerx, zery);
break;
default:
break;
}
break;
case 2:
switch (zery)
{
case 0:
right(temp, mat, zerx, zery);
up(temp, mat, zerx, zery);
break;
case 1:
right(temp, mat, zerx, zery);
left(temp, mat, zerx, zery);
up(temp, mat, zerx, zery);
break;
case 2:
left(temp, mat, zerx, zery);
up(temp, mat, zerx, zery);
break;
default:
break;
}
break;
default:
break;
}
}
void printData(Node *node)
{
for (int i = 0; i < 3; i++)
{
for (int j = 0; j < 3; j++)
{
cout << node->data[i][j];
}
cout<<endl;
}
cout << endl;
}
bool compareTwoArrays(Node *node)
{
int goal[3][3] = {{1, 2, 3},
{4,5,6},
{7,8,0}};
for (int i = 0; i < 3; i++)
{
for (int j = 0; j < 3; j++)
{
// cout << "\nnodeij=" << node->data[i][j];
// cout << "\ngoalij=" << goal[i][j];
if (node->data[i][j] != goal[i][j])
{
return false;
}
}
}
cout << "Reached"<<endl;
cout<<"Total state space="<<cnt;
return true;
}
void checkAllPossibilties(Node *temp, int *zerx, int *zery)
{
// while(!Q.empty())
// {
// cout << "comparing=" << !compareTwoArrays(temp->children[i]);
while (!compareTwoArrays((*openList.begin()).second)&&flag1==0)
{
Node *minNode=(*openList.begin()).second;
int fn=(*openList.begin()).first;
Que.push((*openList.begin()).second);
openList.erase(fn);
while(fn==(*openList.begin()).first){
Que.push((*openList.begin()).second);
openList.erase(fn);
}
// Q.push(minNode);
openList.clear();
while(!Que.empty()){
minNode=Que.front();
get_Co_Zero(minNode->data, zerx, zery);
cout<<"\nminnode=";
printData(minNode);
cout<<"\n";
cout<<"children\n";
decide(minNode, minNode->data, *zerx, *zery);
// sort(childNodes.begin(),childNodes.end());
for (int j = 0; j < minNode->children.size(); j++)
{
printData(minNode->children[j]);
cout<<"fn="<<findFn(minNode->children[j]->data)<<"\n";
if (compareTwoArrays(minNode->children[j]))
{
flag1 = 1;
break;
}
}
cout<<"\n";
if(flag1==1){
break;
}
Que.pop();
}
}
// Q.pop();
// }
}
int main()
{
int zerx, zery;
int mat[3][3] = {{1,2,3},
{0,4,6},
{7,5,8}};
// for (int i = 0; i < 3; i++)
// {
// for (int j = 0; j < 3; j++)
// {
// cin >> mat[i][j];
// }
// }
root = CreateNewNode(mat);
temp = root;
allNodes.push_back(temp);
// checkAllPossibilties(temp, &zerx, &zery);
cout << "root";
for (int j = 0; j < 3; j++)
{
for (int k = 0; k < 3; k++)
{
cout << root->data[j][k];
}
}
cout<<"\n";
get_Co_Zero(mat, &zerx, &zery);
cout<<"\nchildren\n";
decide(temp, mat, zerx, zery);
for (int i = 0; i < root->children.size(); i++)
{
printData(root->children[i]);
cout<<"fn="<<findFn(root->children[i]->data)<<"\n";
}
cout<<"\n";
checkAllPossibilties(temp, &zerx, &zery);
return 0;
}
// function to create new node
Node *CreateNewNode(int data[3][3])
{
Node *newNode = new Node();
for (int i = 0; i < 3; i++)
{
for (int j = 0; j < 3; j++)
{
newNode->data[i][j] = data[i][j];
}
}
// newNode->fn=findFn(data);
return newNode;
}
// function to add a child to a specific node
void addChild(Node *node, int data[3][3])
{
Node *newNode = CreateNewNode(data);
node->children.push_back(newNode);
}