#%%
from pyray import *

# %%
from dataclasses import dataclass

@dataclass
class Rectangle:
    x: float
    y: float
    w: float
    h: float


@dataclass
class Point:
    x: float
    y: float


class QuadTree:
    def __init__(self, rectangle: Rectangle, capacity: int):
        
        self.boundary: Rectangle = rectangle
        self.capacity: int = capacity

        self.subdivided: bool = False
        self.points: list[Point] = []
        self.childs: list[Rectangle] = [None, None, None, None]
    

    def __contains__(self, point: Point) -> bool:
        """Returns True if the point is inside the rectangle"""
        if point.x < self.boundary.x:
            return False
        if point.y < self.boundary.y:
            return False
        if point.x > self.boundary.x + self.boundary.w:
            return False
        if point.y > self.boundary.y + self.boundary.h:
            return False
        return True
    

    def subdivide(self) -> None:
        self.subdivided = True

        half_w = self.boundary.w/2
        half_h = self.boundary.h/2
        
        # Left top
        self.childs[0] = QuadTree(Rectangle(x=self.boundary.x, y=self.boundary.y, w=half_w, h=half_h), self.capacity)
        # Left bottom
        self.childs[1] = QuadTree(Rectangle(x=self.boundary.x, y=self.boundary.y + half_h, w=half_w, h=half_h), self.capacity)
        # Right top
        self.childs[2] = QuadTree(Rectangle(x=self.boundary.x + half_w, y=self.boundary.y, w=half_w, h=half_h), self.capacity)
        # Right bottom
        self.childs[3] = QuadTree(Rectangle(x=self.boundary.x + half_w, y=self.boundary.y + half_h, w=half_w, h=half_h), self.capacity)

    
    def insert(self, point: Point) -> bool:
        """Inserts a point into the quadtree"""
        
        if point not in self:
            return False

        if len(self.points) < self.capacity:
            self.points.append(point)
            return True
        else:
            if not self.subdivided:
                self.subdivide()
            
            insertation = False
            for child in self.childs:
                if child.insert(point):
                    insertation = True
                    break
            return insertation
                
    
    def query(self, point):
        """Returns the rectangle that contains the point"""
        pass
    
    
    def draw(self):
        # draw_rectangle_lines(self.boundary.x, self.boundary.y, self.boundary.w, self.boundary.h, WHITE)
        draw_rectangle_lines(int(self.boundary.x), int(self.boundary.y), int(self.boundary.w), int(self.boundary.h), WHITE)

        for point in self.points:
            draw_circle(point.x, point.y, 2, RED)
        
        if self.subdivided:
            for child in self.childs:
                child.draw()

    
    
def main():
    init_window(800, 800, 'Quadtree')
    
    qtree = QuadTree(Rectangle(0, 0, 800, 800), 4)
    
    while not window_should_close():
        begin_drawing()
        clear_background(BLACK)
        
        qtree.insert(Point(get_mouse_x(), get_mouse_y()))

        qtree.draw()
        
        end_drawing()
        
    close_window()


if __name__ == "__main__":
    main()
    
    