#pragma once
#include <memory>
#include <iostream>


namespace Custom {
	struct Point {
		float x, y;
	};

	struct Rectangle {
		float x, y, w, h;
	};
};


class QuadTree {
private:
	Custom::Rectangle bounds;
	int capacity, point_counts;
	bool divided;
	Custom::Point* points;

	QuadTree* childs[4];

public:
	QuadTree(Custom::Rectangle&, int);

	~QuadTree() {
		delete[] points;
		for (int i = 0; i < 4; i++)
			delete childs[i];
	}

	void subdivide();
	bool contains(Custom::Point p);
	bool insert(Custom::Point&);
	Custom::Rectangle get_tree(Custom::Point&);

	void draw();
};
