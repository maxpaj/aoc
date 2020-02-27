#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define X first
#define Y second

typedef std::pair<int, int> point;

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

    for (char dir; ss >> dir;) {

        if (dir == ',') {
            continue;
        }
        
        int number; 
        ss >> number;

        switch (dir) {
            case 'U': 
                for (int i = 0; i <= number; i++) {
                    pairs.push_back(point(x, y + i));
                }
                y += number;
                break;
            case 'D':
                for (int i = 0; i <= number; i++) {
                    pairs.push_back(point(x, y - i));
                }
                y -= number;
                break;
            case 'R':
                for (int i = 0; i <= number; i++) {
                    pairs.push_back(point(x + i, y));
                }
                x += number;
                break;
            case 'L':
                for (int i = 0; i <= number; i++) {
                    pairs.push_back(point(x - i, y));
                }
                x -= number;
                break;
        }
    }
    return pairs;
}

std::pair<point, point> get_bounds(std::vector<point> points) {
    int x_min = 0, x_max = 0, y_min = 0, y_max = 0;

    for (auto it = points.begin(); it != points.end(); it++) {
        if (it->X < x_min) {
            x_min = it->X;
        }
        if (it->X > x_max) {
            x_max = it->X;
        }
        if (it->Y > y_max) {
            y_max = it->Y;
        }
        if (it->Y < y_min) {
            y_min = it->Y;
        }
    }

    return std::pair<point, point>(point(x_min, y_min), point(x_max, y_max));
}

bool** get_matrix(std::vector<point> points) {
    // Get the bounds of the map
    std::pair<point, point> bounds = get_bounds(points);

    int sizeY = abs(bounds.first.Y) + abs(bounds.second.Y) + 1;
    int sizeX = abs(bounds.first.X) + abs(bounds.second.X) + 1;

    bool** matrix[sizeX][sizeY];

    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            matrix[i][j] = false;
        }
    }

    // Add the points
    for (int i = 0; i < points.size(); i++) {
        int first = points[i].X - bounds.first.X;
        int second = points[i].Y - bounds.first.Y;
        matrix[points[i].X - bounds.first.X][points[i].Y - bounds.first.Y] = true;
    }
    
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            std::cout << (int) matrix[i][j];
        }
        std::cout << std::endl;
    }

    return matrix;
}

int main () {
    std::string str_line;
    
    std::getline(std::cin, str_line);
    auto first_wire = points(str_line);

    std::getline(std::cin, str_line);
    auto second_wire = points(str_line);

    // Create matrix
    bool matrix[sizeX][sizeY] = get_matrix(first_wire);

    // Check for intersections
    for (int i = 0; i < second_wire.size(); i++) {
        if (second_wire[i].X - bounds.first.X > sizeX ||
            second_wire[i].X - bounds.first.X < 0 ||   
            second_wire[i].Y - bounds.first.Y > sizeY ||   
            second_wire[i].Y - bounds.first.Y < 0) {
            continue;
        }
        
        if (matrix[second_wire[i].X - bounds.first.X][second_wire[i].Y - bounds.first.Y]) {
            std::cout << second_wire[i].X << ", " << second_wire[i].Y << std::endl;
        }
    }

    return 0;
} 