#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node *CreateNewNode(int data[3][3]);
void addChild(Node *node, int data[3][3]);
struct Node
{
    int data[3][3];
    vector<Node *> children;
};
int cnt=0;
Node *root;
Node *temp = root;
vector<Node *> AllNodes;
int flag1 = 0;
queue<Node *>Que;

void get_Co_Zero(int mat[3][3], int *zerx, int *zery)
{
    int flag = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (mat[i][j] == 0){
                *zerx = i;
                *zery = j;
                flag = 1;
                break;
            }
        }
        if (flag == 1){
            break;
        }
    }
}
bool isVisited(Node *node)
{
    int checkflag = 0;
    for (int i = 0; i < AllNodes.size(); i++){
        // cout << "checkflag===" << checkflag;
        // cout << "\naniket\n";
        if (checkflag == 0){
            checkflag = 1;
            // cout << "checkflag1===" << checkflag;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (AllNodes[i]->data[j][k] != node->data[j][k])
                    {
                        checkflag = 0;
                        break;
                    }
                }
                if (checkflag == 0)
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
    if (checkflag == 0)
    {
        AllNodes.push_back(node);
        return false;
    }
    return true;
}

// void misplaced_tile(Node * node){
//     int goal[3][3]= {
//         {1,2,3},
//         {4,5,6},
//         {7,8,0}};
//     int cnt=0;
//     for (int i = 0; i < 3; i++){
//         for (int j = 0; j < 3; j++){
//             if (node->data[i][j] != goal[i][j]){
//                 cnt++;
//             }
//         }
//     }
//     cout<<"Misplaced tiles are: "<<cnt<<endl;
// }

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
        cout << "up"<<endl;
        addChild(temp, newm);
        cnt++;
        Que.push(updatedmat);
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
        cout << "down"<<endl;
        addChild(temp, newm);
        cnt++;
        Que.push(updatedmat);
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
        cout << "right"<<endl;
        addChild(temp, newm);
        cnt++;
        Que.push(updatedmat);
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
        cout << "left"<<endl;
        addChild(temp, newm);
        cnt++;
        Que.push(updatedmat);
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
            cout << node->data[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    // misplaced_tile(node);
}

bool compareTwoArrays(Node *node)
{
    int goal[3][3] = {{1,2,3},
                      {4,5,6},
                      {7,8,0}};
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (node->data[i][j] != goal[i][j]){
                 return false;
            }
        }
    }
    cout << "Reached"<<endl;
    cout << "Total state space= "<<cnt; 
    return true;
}

void checkAllPossibilties(Node *temp, int *zerx, int *zery)
{
    while(!Que.empty())
    {
        // cout << "comparing=" << !compareTwoArrays(temp->children[i]);
        if (!compareTwoArrays(Que.front())&&flag1==0)
        {
            get_Co_Zero(Que.front()->data, zerx, zery);
            decide(Que.front(), Que.front()->data, *zerx, *zery);
            for (int j = 0; j < Que.front()->children.size(); j++)
            {
                printData(Que.front()->children[j]);
                if (compareTwoArrays(Que.front()->children[j]))
                {
                    flag1 = 1;
                    break;
                }
                if(flag1==1){
                    break;
                }
            }
            cout<<"\n";
        }
        Que.pop();
    }
    
    
}

int main()
{
    int zerx, zery;
    int mat[3][3] = {{1,2,3},
                     {0,4,6},
                     {7,5,8}};
    // for (int i = 0; i < 3; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         cin >> mat[i][j];
    //     }
    // }
    root = CreateNewNode(mat);
    temp = root;
    AllNodes.push_back(temp);
    // checkAllPossibilties(temp, &zerx, &zery);

    cout << "root"<<endl;
    for (int j = 0; j < 3; j++)
    {
        for (int k = 0; k < 3; k++)
        {
            cout << root->data[j][k]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    get_Co_Zero(mat, &zerx, &zery);
    decide(temp, mat, zerx, zery);
    for (int i = 0; i < root->children.size(); i++)
    {
        printData(root->children[i]);
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
    return newNode;
}

// function to add a child to a specific node
void addChild(Node *node, int data[3][3])
{
    Node *newNode = CreateNewNode(data);
    node->children.push_back(newNode);
}

