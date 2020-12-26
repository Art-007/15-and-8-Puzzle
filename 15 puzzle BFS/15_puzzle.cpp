// 15_puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

#define N 4 

struct Node
{
	Node* parent;
	int mat[N][N];
	//stores blank tile coordinates 
	int x, y;
	//Hamming Distance
	int cost;
	//level in tree
	int level;
	//stores previous state index
	int ps;
};
// Function to print N x N matrix 
void printMatrix(Node* n)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d ", n->mat[i][j]);
		printf("\n");
	}
}

Node* newNode(int mat[N][N], int x, int y, int newX,
	int newY, int level, int ps, Node* parent)
{
	Node* node = new Node;
	node->parent = parent;
	//copy data
	memcpy(node->mat, mat, sizeof node->mat);
	//move tile 
	swap(node->mat[x][y], node->mat[newX][newY]);
	//max hamming(will be calculated later)
	node->cost = INT_MAX;
	node->level = level;
	//indicate parent node
	node->ps = ps;
	//new blank coords 
	node->x = newX;
	node->y = newY;
	return node;
}
// bottom, left, top, right 
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

// Function to calculate Hamming Distance
int calculateCost(int initial[N][N], int final[N][N])
{
	int count = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (initial[i][j] && initial[i][j] != final[i][j])
				count++;
	return count;
}

// Function to check if (x, y) is a valid matrix cordinate 
int isSafe(int x, int y)
{
	return (x >= 0 && x < N && y >= 0 && y < N);
}


bool exists(Node* child, Node* arr[], int length)
{
	//bool b;
	bool row[N];

	for (int l = 0; l < length; l++)
	{
		for (int i = 0; i < N; i++)
		{
			row[i] = true;
			for (int j = 0; j < N; j++)
			{
				if (child->mat[i][j] != arr[l]->mat[i][j])
					row[i] = false;
			}
		}
		if (row[0] && row[1] && row[2] && row[3])
			return true;
	}
	return false;
}
//BFS
void BFS(int initial[N][N], int x, int y, int final[N][N])
{
	Node* arr[1000];
	Node* root = newNode(initial, x, y, x, y, 0, 0, NULL);
	//initialize
	arr[0] = root;
	int length = 0;
	int c_i = 0; //current index
	cout << "Puzzle number: " << c_i + 1 << " level: " << arr[c_i]->level << '\n';
	printMatrix(arr[c_i]);
	while (arr[c_i]->cost != 0)
	{
		Node* temp = arr[c_i];
		//Find next possible states
		for (int i = 0; i < 4; i++)
		{
			if (isSafe(temp->x + row[i], temp->y + col[i]))
			{
				Node* child = newNode(temp->mat, temp->x,
					temp->y, temp->x + row[i],
					temp->y + col[i],
					temp->level + 1, c_i, temp);
				child->cost = calculateCost(child->mat, final);
				if (!exists(child, arr, length))
				{
					length++;
					arr[length] = child;
				}
			}
		}
		c_i++;
		cout << "Puzzle number: " << c_i + 1 << " Level: " << arr[c_i]->level << " Parent: " << arr[c_i]->ps << '\n';
		printMatrix(arr[c_i]);
		if (arr[c_i]->cost == 0)
			break;
	}
	cout << "Goal state found at puzzle " << c_i + 1 << '\n';
}
int InvCount(int arr[N][N])
{
	int count = 0;
	int p1, p2;
	for (int i = 0; i < N * N - 1; i++)
	{
		for (int j = i + 1; j < N * N; j++)
		{
			//first pair
			p1 = arr[i / N][i % N];
			//second pair
			p2 = arr[j / N][j % N];
			if (p1 != 0 && p2 != 0 && p1 > p2)
				count++;
		}
	}
	//cout << count << '\n';
	return count;
}
//find position of blank from bottom
int findBlank(int arr[N][N])
{
	int index = 0;
	for (int i = N - 1; i >= 0; i--)
	{
		for (int j = N - 1; j >= 0; j--)
		{
			if (arr[i][j] == 0)
				index = N - i;
		}
	}
	//cout << index << '\n';
	return index;
}
bool isSolvable(int arr[N][N])
{
	int index = findBlank(arr);
	bool b = (InvCount(arr) % 2 == 0) ^ (index % 2 == 0);
	if (b)
		cout << "The puzzle is solvable\n";
	else
		cout << "The puzzle is not solvable\n";
	return b;
}
// Driver code 
int main()
{
	// Initial Puzzle, 0 represents empty space
	/*
	int initial[N][N] =
	{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 0, 15}
	};
	*/
	//this one is possible
	// /*
	int initial[N][N] =
	{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 0, 10, 12},
		{13, 14, 11, 15}
	};
	// */
	//this one is not possible
	/*
	int initial[N][N] =
	{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 0, 10, 12},
		{13, 11, 14, 15}
	};
	*/
	// Goal state 
	int final[N][N] =
	{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 0}
	};
	// blank coords
	int x = 2, y = 1;
	if (isSolvable(initial))
	{
		auto start_time = high_resolution_clock::now();
		BFS(initial, x, y, final);
		auto stop_time = high_resolution_clock::now();

		auto result = chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);
		cout << "The run time is " << result.count() << endl;

	}
	//isSolvable(initial);
	return 0;
}
