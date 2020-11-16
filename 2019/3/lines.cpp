#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define X first
#define Y second
#define P1 first
#define P2 second

typedef std::pair<int, int> point;
typedef std::pair<point, point> line;

// Check if the line is vertical by looking at it's points X positions (they should be the same)
bool vertical(line line) {
    return line.P1.X == line.P2.X;
}

// If the line isn't vertical, then under the rules of the puzzle, it is horizontal
bool horizontal(line line) {
    return !vertical(line);
}

int intersectX(line l1, line l2) {
    if (vertical(l1) && horizontal(l2)) { 
        // Check if the lines X are within the same interval
        if (l1.P1.X < l2.P1.X || l1.P1.X > l2.P2.X) {
            return l1.P1
        }
        return 0;
    }
    return l2.P1.X >= l1.P1.X && l2.P1.X <= l1.P2.X;
}

int intersectY(line l1, line l2) {
    if (vertical(l1) && horizontal(l2) || horizontal(l1) && vertical(l2)) { 
        // Check if the lines Y are within the same interval
        if (l1.P1.Y >= l2.P1.Y && l1.P1.Y <= l2.P2.Y) {
            return l2.P1.Y + l2.P2.Y - l1.P1.Y;
        }
        return 0;
    }
    
    if (l1.P1.X >= l2.P1.X && l1.P1.X <= l2.P2.X) {
        return l1.P1.Y;
    }

    return 0;
}

point intersection(
    line l1, line l2) {

    int ix = intersectX(l1, l2), iy = intersectY(l1, l2);

    return point(ix, iy);
}

line create_line(point p1, point p2) {
    if (p1.X == p2.X) {
        if (p1.Y <= p2.Y) { 
            return line(p1, p2);
        }
        return line(p2, p1);
    } 

    if (p1.X <= p2.X) {
        return line(p1, p2);
    }

    return line(p2, p1);
}

// Parse out the points for each wire
// Given a current position (0, 0)
// 1. Store the current position
// 2. Find the direction and length of the next "turn"
//      First character -> Direction (char)
//      The rest -> Length (int)
// 3. Modify the current position according to the next turn
//      U / D -> Modify Y position
//      L / R -> Modify X position
// 4. Repeat from (1)
std::vector<point> points(std::string l) {
    std::vector<point> pairs;
    std::stringstream ss(l);

    int x = 0, y = 0;

    pairs.push_back(point(0, 0));

    for (char dir; ss >> dir;) {

        if (dir == ',') {
            continue;
        }
        
        int number; 
        ss >> number;

        switch (dir) {
            case 'U': 
                y += number;
                break;
            case 'D':
                y -= number;
                break;
            case 'L':
                x -= number;
                break;
            case 'R':
                x += number;
                break;
        }

        point p(x, y);
        pairs.push_back(p);
    }
    return pairs;
}

int main () {
    std::string str_line;

    // Determine the lowest distance
    // 1. Create line segments from points
    // 2. Check if line segments intersect

    
    std::getline(std::cin, str_line);
    auto first_wire = points(str_line);

    std::getline(std::cin, str_line);
    auto second_wire = points(str_line);
             
    for (int i = 0; i < first_wire.size(); i++) {
        for (int j = 0; j < first_wire.size(); j++) {

            line l1 = create_line(first_wire[i], first_wire[i + 1]);
            line l2 = create_line(second_wire[i], second_wire[i + 1]);

            point p = intersection(l1, l2);

            if (p.first != -1) {
                std::cout << p.X + p.Y << std::endl;
            }
        }
    }

    return 0;
} 