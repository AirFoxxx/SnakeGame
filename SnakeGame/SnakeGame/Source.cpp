#include <iostream>
#include "olcConsoleGameEngine.h"
#include <random>
#include "AStar.h"

#ifndef INVALID_LOCATION
#define INVALID_LOCATION GridLocation{-1,-1}
#endif
//TODO

//Both snakes should be dead if they touch their own bodies and vice versa (for enemy we can add its own body to walls.)
//moving and respawning the goal location.
//implement growing a body if the element is eaten.
//implement the point system (goal picked up, thats it?)
//implement blocking for player, enemy body and such.
// make all parts of code map size agnostic.

// ADDITIONAL FEATURES
//implement a way to randomise walls?
//Maybe add the forrests and other tiles that are hard for the enemy to pass through (though not impossible).

enum class Keys
{
	W = 1, A = 2, S = 4, D = 8
};

class OneLoneCoder_Example : public olcConsoleGameEngine
{
public:
	OneLoneCoder_Example() {}

	bool OnUserCreate() override
	{
		////CREATE FOR WALLS DEMO

		//initiLIZE the snake and enemy to an arbitrary size for now.
		for (int i = 0; i < 3; i++)
		{
			GridLocation element{ i + 10, 10 };
			//snake.push_back(element);
			enemy.push_back({ 40, i + 40 });
		}

		//fill this block with white
		this->Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, COLOUR::FG_WHITE);

		//// create for ASTAR, will have to be redone
		astar.addEmptyWeightedGraphDiagonal(this->ScreenWidth(), this->ScreenHeight());

		//Add walls - bounds are checked already inside AStar class
		//astar.addWallToGraph(10, 50, 10, 13);
		//astar.addWallToGraph(55, 56, 1, 70);

		//draw walls
		//for (auto& location : astar.forrestGrid.walls)
		//{
		//	this->Draw(location.x, location.y, PIXEL_SOLID, FG_BLACK);
		//}

		//draw snake - lets hope it is not in a wall
		//for (auto& snakeBody : snake)
		//{
		//	this->Draw(snakeBody.x, snakeBody.y, PIXEL_SOLID, FG_GREEN);
		//}

		//draw enemy - lets hope it is not in a wall
		for (auto& snakeBody : enemy)
		{
			this->Draw(snakeBody.x, snakeBody.y, PIXEL_SOLID, FG_RED);
		}

		// set the end node
		end = { 90,10 };

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// accrue the spent time
		elapsedTime += fElapsedTime;

		// Take the pressed keys (makes it super smooth if it is this often)
		//if (m_keys[L'W'].bPressed || m_keys[L'W'].bHeld)
		//{
		//	wantToGO = Keys::W;
		//}
		//else if (m_keys[L'A'].bPressed || m_keys[L'A'].bHeld)
		//{
		//	wantToGO = Keys::A;
		//}
		//else if (m_keys[L'S'].bPressed || m_keys[L'S'].bHeld)
		//{
		//	wantToGO = Keys::S;
		//}
		//else if (m_keys[L'D'].bPressed || m_keys[L'D'].bHeld)
		//{
		//	wantToGO = Keys::D;
		//}

		// if it has been at least half a second...
		if (elapsedTime > 0.1F)
		{
			//DRAWING
			//fill this block with white
			this->Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, COLOUR::FG_WHITE);

			//draw walls
			//for (const auto& location : astar.forrestGrid.walls)
			//{
			//	this->Draw(location.x, location.y, PIXEL_SOLID, FG_BLACK);
			//}

			// The moving of snake mechanic
			//auto oldSnake = snake;
			//auto oldHead = snake.at(0);
			//elapsedTime = 0;
			//if (wantToGO == Keys::W && key != Keys::S)
			//{
			//	auto newHead = oldHead;
			//	newHead.y -= 1;
			//	snake.clear();
			//	snake.push_back(newHead);
			//	for (auto it = oldSnake.begin(); it != oldSnake.end(); it++)
			//	{
			//		snake.push_back(*it);
			//	}
			//	this->astar.forrestGrid.walls.erase(*snake.rbegin());
			//	snake.pop_back();
			//	key = Keys::W;
			//}
			//else if (wantToGO == Keys::A && key != Keys::D)
			//{
			//	auto newHead = oldHead;
			//	newHead.x -= 1;
			//	snake.clear();
			//	snake.push_back(newHead);
			//	for (auto it = oldSnake.begin(); it != oldSnake.end(); it++)
			//	{
			//		snake.push_back(*it);
			//	}
			//	this->astar.forrestGrid.walls.erase(*snake.rbegin());
			//	snake.pop_back();
			//	key = Keys::A;
			//}
			//else if (wantToGO == Keys::S && key != Keys::W)
			//{
			//	auto newHead = oldHead;
			//	newHead.y += 1;
			//	snake.clear();
			//	snake.push_back(newHead);
			//	for (auto it = oldSnake.begin(); it != oldSnake.end(); it++)
			//	{
			//		snake.push_back(*it);
			//	}
			//	this->astar.forrestGrid.walls.erase(*snake.rbegin());
			//	snake.pop_back();
			//	key = Keys::S;
			//}
			//else if (wantToGO == Keys::D && key != Keys::A)
			//{
			//	auto newHead = oldHead;
			//	newHead.x += 1;
			//	snake.clear();
			//	snake.push_back(newHead);
			//	for (auto it = oldSnake.begin(); it != oldSnake.end(); it++)
			//	{
			//		snake.push_back(*it);
			//	}
			//	this->astar.forrestGrid.walls.erase(*snake.rbegin());
			//	snake.pop_back();
			//	key = Keys::D;
			//}
			//else
			//{
			//	auto newHead = oldHead;
			//	switch ((int)key)
			//	{
			//	case 1:
			//		newHead.y -= 1;
			//		break;
			//	case 2:
			//		newHead.x -= 1;
			//		break;
			//	case 4:
			//		newHead.y += 1;
			//		break;
			//	case 8:
			//		newHead.x += 1;
			//		break;
			//	}
			//	// default direction
			//	snake.clear();
			//	snake.push_back(newHead);
			//	for (auto it = oldSnake.begin(); it != oldSnake.end(); it++)
			//	{
			//		snake.push_back(*it);
			//	}
			//	this->astar.forrestGrid.walls.erase(*snake.rbegin());
			//	snake.pop_back();
			//}

			//LETS implement the automatic enemy movement here
			auto next = astar.nextTileDiagonal(*enemy.begin(), end);
			if (next == GridLocation{ INVALID_LOCATION })
			{
				return false;
			}
			auto enemycopy = enemy;
			enemy.clear();
			enemy.push_back(next);
			for (auto it = enemycopy.begin(); it != enemycopy.end(); it++)
			{
				enemy.push_back(*it);
			}
			GridLocation temp = *enemy.rbegin();
			enemy.pop_back();

			// add the players new head to walls so the snake avoids it.
			//this->astar.forrestGrid.walls.insert(*snake.begin());

			// flip the snake around end of map here
			//for (auto& snakeBody : snake)
			//{
			//	snakeBody = flipCoordinates(snakeBody);
			//}

			//check the goal
			if (isAtGoal(*enemy.cbegin()))
				enemy.push_back(temp);
			//isAtGoal(*snake.cbegin());

			//draw snake - lets hope it is not in a wall
			//for (auto& snakeBody : snake)
			//{
			//	this->Draw(snakeBody.x, snakeBody.y, PIXEL_SOLID, FG_GREEN);
			//}
			//draw enemy - lets hope it is not in a wall
			for (const auto& snakeBody : enemy)
			{
				this->Draw(snakeBody.x, snakeBody.y, PIXEL_SOLID, FG_RED);
			}

			//draw the goal

			this->Draw(end.x, end.y, PIXEL_SOLID, FG_DARK_YELLOW);
			elapsedTime = 0.0F;
		}

		return true;
	}

	bool isAtGoal(const GridLocation head)
	{
		if (head.x == end.x && head.y == end.y)
		{
			//add points
			//respawn goal
			end.x = rand() % this->ScreenWidth();
			end.y = rand() % this->ScreenHeight();
			return true;
		}
		return false;
	}

	/// <summary>
	/// Wraps the incoming GridLocations coordinates around the end of the map and returns it.
	/// </summary>
	/// <param name="inLocation">The in location.</param>
	/// <returns></returns>
	GridLocation flipCoordinates(const GridLocation inLocation)
	{
		GridLocation outLocation{ inLocation };
		if (inLocation.x > this->ScreenWidth())
		{
			outLocation.x = 0;
		}
		if (inLocation.y > this->ScreenHeight())
		{
			outLocation.y = 0;
		}
		if (inLocation.x < 0)
		{
			outLocation.x = this->ScreenWidth();
		}
		if (inLocation.y < 0)
		{
			outLocation.y = this->ScreenHeight();
		}
		return outLocation;
	}

private:
	Keys wantToGO = Keys::S;
	Keys key = Keys::S;
	float elapsedTime = 0.0F;
	AStar astar;
	// walls parameters
	std::unordered_set<GridLocation> walls;
	GridLocation start;
	GridLocation end;
	std::vector<GridLocation> snake;
	std::vector<GridLocation> enemy;
};

int main()
{
	int width;
	int height;
	std::cout << "Please input a width for a graph (10-200)" << std::endl;
	std::cin >> width;
	std::cout << "Please input a height for a graph (10-200)" << std::endl;
	std::cin >> height;

	OneLoneCoder_Example game;
	game.ConstructConsole(width, height, 8, 8);
	game.Start();
	return 0;
}
