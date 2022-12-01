#include <iostream>
#include <vector>
using namespace std;

struct Node *CreateNewNode(int data[3][3]);
void addChild(Node *node, int data[3][3]);
struct Node
{
    int data[3][3];
    vector<Node *> children;
};
Node *root;
Node *temp = root;
int cnt=0;
vector<Node *> allNodes;
int flag1 = 0;

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
                        // cout << "ak";
                        flagCheck = 0;
                        break;
                    }
                    // else
                    // {
                    //     cout << "flagCheck2===" << flagCheck;
                    //     cout << "\nalli=" << allNodes[i]->data[j][k];
                    //     cout << "\nnode=" << node->data[j][k];
                    // }
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
        cout << "up"<<endl;
        cnt++;
        addChild(temp, newm);
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
        cnt++;
        addChild(temp, newm);
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
        cnt++;
        addChild(temp, newm);
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
        cnt++;
        addChild(temp, newm);
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
            down(temp, mat, zerx, zery);
            right(temp, mat, zerx, zery);

            break;
        case 1:
            left(temp, mat, zerx, zery);
            right(temp, mat, zerx, zery);
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
            up(temp, mat, zerx, zery);
            right(temp, mat, zerx, zery);
            left(temp, mat, zerx, zery);
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
            up(temp, mat, zerx, zery);
            right(temp, mat, zerx, zery);
            left(temp, mat, zerx, zery);

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
                      {4, 5, 6},
                      {7, 8, 0}};
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
    cout<<"total state space= "<<cnt <<endl;
    return true;
}

void checkAllPossibilties(Node *temp, int *zerx, int *zery)
{
    for (int i = 0; i < temp->children.size(); i++)
    {
        // cout << "comparing=" << !compareTwoArrays(temp->children[i]);
        if (!compareTwoArrays(temp->children[i]))
        {
            get_Co_Zero(temp->children[i]->data, zerx, zery);
            decide(temp->children[i], temp->children[i]->data, *zerx, *zery);
            for (int j = 0; j < temp->children[i]->children.size(); j++)
            {

                printData(temp->children[i]->children[j]);
                if (compareTwoArrays(temp->children[i]->children[j]))
                {
                    flag1 = 1;
                    break;
                }
            }
        }
        else if (flag1 == 1)
        {
            // cout << "aniketeeeee";
            // exit(0);
            // flag1 = 1;
            break;
        }
    }
    if (flag1 == 0)
    {
        for (int i = 0; i < temp->children.size(); i++)
        {
            temp = temp->children[i];
            checkAllPossibilties(temp, zerx, zery);
        }
    }
}

int main()
{
    int zerx, zery;
    int mat[3][3]=  {{1,2,3},
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
    allNodes.push_back(temp);
    checkAllPossibilties(temp, &zerx, &zery);

    for (int i = 0; i < allNodes.size(); i++)
    {
        cout << "\nallnodes"<<endl;
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cout << allNodes[i]->data[j][k];
            }
            cout<<endl;
        }
    }
    get_Co_Zero(mat, &zerx, &zery);
    decide(temp, mat, zerx, zery);
    // cout << root->children.size();
    for (int i = 0; i < root->children.size(); i++)
    {
        printData(root->children[i]);
    }
    checkAllPossibilties(temp, &zerx, &zery);

    // get_Co_Zero(root->children[0]->data,&zerx,&zery);
    // decide(root->children[0]->data,zerx,zery);
    // for(int i=0;i<root->children[0]->children.size();i++){
    //     printData(root->children[0]->children[i]);
    // }

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



