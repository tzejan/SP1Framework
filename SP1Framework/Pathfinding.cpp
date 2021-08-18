#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "ConsoleGameEngine.h"

using namespace std;

class PathFinding : public ConsoleGameEngine
{
private:
	struct sNode
	{
		bool isWall = false;			// Is the node a wall?
		bool hasVisited = false;		// Has this node been visited before?
		float globalGoal;				// Distance to goal
		float localGoal;				// Distance to goal if alternative route taken
		int x;							// Nodes position in 2D space
		int y;
		vector<sNode*> vecNeighbours;	// Connections to neighbours
		sNode* parent;					// Node connecting to this node that offers shortest parent
	};

	sNode* nodes = nullptr;
	int cols = 16;
	int rows = 16;

	sNode* startNode = nullptr;
	sNode* endNode = nullptr;

protected:
	virtual bool OnUserCreate()
	{
		// 2D array of nodes
		nodes = new sNode[cols * rows];
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				nodes[j * cols + i].x = i;
				nodes[j * cols + i].y = j;
				nodes[j * cols + i].isWall = false;
				nodes[j * cols + i].parent = nullptr;
				nodes[j * cols + i].hasVisited = false;
			}
		}

		// Connect nodes together
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if (j > 0)
				{
					nodes[j * cols + i].vecNeighbours.push_back(&nodes[(j - 1) * cols + (i + 0)]);
				}
				if (j < rows - 1)
				{
					nodes[j * cols + i].vecNeighbours.push_back(&nodes[(j + 1) * cols + (i + 0)]);
				}
				if (i > 0)
				{
					nodes[j * cols + i].vecNeighbours.push_back(&nodes[(j + 0) * cols + (i - 1)]);
				}
				if (i < cols - 1)
				{
					nodes[j * cols + i].vecNeighbours.push_back(&nodes[(j + 0) * cols + (i + 1)]);
				}
			}
		}

		// Position start and end node
		startNode = &nodes[(rows / 2) * cols + 1];
		endNode = &nodes[(rows / 2) * cols + cols - 2];
		return true;
	}

	bool Solve_AStar()
	{
		// default state
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				nodes[j * cols + i].hasVisited = false;
				nodes[j * cols + i].globalGoal = INFINITY;
				nodes[j * cols + i].localGoal = INFINITY;
				nodes[j * cols + i].parent = nullptr;
			}
		}

		auto distance = [](sNode* a, sNode* b)
		{
			return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
		};

		auto heuristic = [distance](sNode* a, sNode* b)
		{
			return distance(a, b);
		};

		// Setup starting conditions
		sNode* currentNode = startNode;
		startNode->localGoal = 0.0f;
		startNode->globalGoal = heuristic(startNode, endNode);

		// Start node added to not tested list
		// Newly discovered nodes are added to this list as the algorithm goes on
		list<sNode*> listNotTestedNodes;
		listNotTestedNodes.push_back(startNode);

		while (!listNotTestedNodes.empty() && currentNode != endNode)// Find absolutely shortest path // && currentNode != endNode)
		{
			// Untested nodes sorted by lowest global goal first
			listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->globalGoal < rhs->globalGoal; });

			// Remove already visited nodes
			while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->hasVisited)
			{
				listNotTestedNodes.pop_front();
			}

			// Stop testing if all nodes tested
			if (listNotTestedNodes.empty())
			{
				break;
			}

			currentNode = listNotTestedNodes.front();
			currentNode->hasVisited = true;

			// Check each of the neighbours of node
			for (auto neighbourNode : currentNode->vecNeighbours)
			{
				// add node to not tested list if node had not been visited and is not a wall
				if (!neighbourNode->hasVisited && neighbourNode->isWall == 0)
				{
					listNotTestedNodes.push_back(neighbourNode);
				}

				// Calculate the neighbours potential lowest parent distance
				float possibleLowerGoal = currentNode->localGoal + distance(currentNode, neighbourNode);

				// Update neighbour to use current node as path source and set distance scores
				// If pathing through node is a lower distance than current set distance
				if (possibleLowerGoal < neighbourNode->localGoal)
				{
					neighbourNode->parent = currentNode;
					neighbourNode->localGoal = possibleLowerGoal;

					// Update neighbour's score after new best path length found
					neighbourNode->globalGoal = neighbourNode->localGoal + heuristic(neighbourNode, endNode);
				}
			}
		}
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		int nodeSize = 9;
		int nodeBorder = 2;

		// Gets cursor location to select node
		int selectedNodeX = m_mousePosX / nodeSize;
		int selectedNodeY = m_mousePosY / nodeSize;

		// Use mouse to draw walls
		if (m_mouse[0].bReleased)
		{
			if (selectedNodeX >= 0 && selectedNodeX < cols)
			{
				if (selectedNodeY >= 0 && selectedNodeY < rows)
				{
					// Use shift key to place start location
					if (m_keys[VK_SHIFT].bHeld)
					{
						startNode = &nodes[selectedNodeY * cols + selectedNodeX];
					}
					// Use ctrl key to place end location
					else if (m_keys[VK_CONTROL].bHeld)
					{
						endNode = &nodes[selectedNodeY * cols + selectedNodeX];
					}
					else
					{
						nodes[selectedNodeY * cols + selectedNodeX].isWall = !nodes[selectedNodeY * cols + selectedNodeX].isWall;
					}
					Solve_AStar();
				}
			}
		}

		// Draw connections between node and neighbours
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				for (auto n : nodes[j * cols + i].vecNeighbours)
				{
					DrawLine(i * nodeSize + nodeSize / 2, j * nodeSize + nodeSize / 2,
						n->x * nodeSize + nodeSize / 2, n->y * nodeSize + nodeSize / 2, PIXEL_SOLID, FG_DARK_BLUE);
				}
			}
		}

		// Draw Nodes on top
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				Fill(i * nodeSize + nodeBorder, j * nodeSize + nodeBorder, (i + 1) * nodeSize - nodeBorder, (j + 1) * nodeSize - nodeBorder, PIXEL_HALF, nodes[j * cols + i].isWall ? FG_WHITE : FG_BLUE);

				if (nodes[j * cols + i].hasVisited)
				{
					Fill(i * nodeSize + nodeBorder, j * nodeSize + nodeBorder, (i + 1) * nodeSize - nodeBorder, (j + 1) * nodeSize - nodeBorder, PIXEL_SOLID, FG_BLUE);
				}
				if (&nodes[j * cols + i] == startNode)
				{
					Fill(i * nodeSize + nodeBorder, j * nodeSize + nodeBorder, (i + 1) * nodeSize - nodeBorder, (j + 1) * nodeSize - nodeBorder, PIXEL_SOLID, FG_GREEN);
				}
				if (&nodes[j * cols + i] == endNode)
				{
					Fill(i * nodeSize + nodeBorder, j * nodeSize + nodeBorder, (i + 1) * nodeSize - nodeBorder, (j + 1) * nodeSize - nodeBorder, PIXEL_SOLID, FG_RED);
				}
			}
		}

		// Draw Path from end node, and follow parent node trail back to start node
		if (endNode != nullptr)
		{
			sNode* p = endNode;
			while (p->parent != nullptr)
			{
				DrawLine(p->x * nodeSize + nodeSize / 2, p->y * nodeSize + nodeSize / 2,
					p->parent->x * nodeSize + nodeSize / 2, p->parent->y * nodeSize + nodeSize / 2, PIXEL_SOLID, FG_YELLOW);

				// Set next node to current node's parent
				p = p->parent;
			}
		}
		return true;
	}
};

int main()
{
	PathFinding game;
	game.ConstructConsole(160, 160, 6, 6);
	game.Start();
	return 0;
}