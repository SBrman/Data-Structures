#include "..\include\QuadTree.h"
#include <raylib.h>


QuadTree::QuadTree(Custom::Rectangle& bounds, int capacity) 
{
	this->bounds = bounds;
	this->capacity = capacity;
	
	points = new Custom::Point[capacity];

	point_counts = 0;
	divided = false;
}


void QuadTree::subdivide() 
{
	// Origin is top left
	float half_w = bounds.w / 2;
	float half_h = bounds.h / 2;

	Custom::Rectangle lt{ bounds.x, bounds.y, half_w, half_h };
	Custom::Rectangle lb{ bounds.x, bounds.y + half_h, half_w, half_h };
	Custom::Rectangle rt{ bounds.x + half_w, bounds.y, half_w, half_h };
	Custom::Rectangle rb{ bounds.x + half_w, bounds.y + half_h, half_w, half_h };

	childs[0] = new QuadTree(lb, capacity);
	childs[1] = new QuadTree(lt, capacity);
	childs[2] = new QuadTree(rb, capacity);
	childs[3] = new QuadTree(rt, capacity);

	divided = true;
}

// Check if current level contains point
bool QuadTree::contains(Custom::Point p) 
{
	if (p.x < bounds.x) return false;
	if (p.x > bounds.x + bounds.w) return false;
	if (p.y < bounds.y) return false;
	if (p.y > bounds.y + bounds.h) return false;
	return true;
}

// Returns whether insertion in current node was successful
bool QuadTree::insert(Custom::Point& point) 
{	
	// If does not contain point, stop and return false
	if (!contains(point)) 
		return false;

	// Can insert
	if (point_counts < capacity) {
		points[point_counts++] = point;
		return true;
	}
	// Can't insert, subdivide
	else {
		if (!divided) 
			subdivide();

		bool insertion = false;
		for (auto child : childs) {
			if (child->insert(point)) {
				insertion = true;
				break;
			}
		}
		return insertion;
	}
}

void QuadTree::draw() 
{
	// Draw the boundary
	DrawRectangleLines(bounds.x, bounds.y, bounds.w, bounds.h, WHITE);
	
	// Draw all the points in this boundary
	for (int i = 0; i < point_counts; i++)
		DrawCircle(points[i].x, points[i].y, 1, RED);
	
	// If children exist, draw them
	if (divided) {
		for (auto child : childs) 
			child->draw(); 
	}
}

