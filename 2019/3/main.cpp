#include <iostream>
#include <sstream>
#include <vector>

struct point {
    int x;
    int y;
};

struct line {
    point p1;
    point p2;
};

bool horizontal(line l) {
    return l.p1.x != l.p2.x;
}

bool vertical(line l) {
    return !horizontal(l);
}

int manhattan_distance(point p1, point p2) {
    return abs(p2.x - p1.x) + abs(p2.y - p1.y); 
}

point intersect(line v, line h) {
    point p;
    p.x = 0;
    p.y = 0;

    if (horizontal(v) && horizontal(h) ||
        vertical(v) && vertical(h)) {
        return p;
    }

    if (horizontal(v) && vertical(h)) {
        line temp = v;
        v = h;
        h = temp;
    }

    int x = v.p1.x;
    int x1, x2;

    // Order x-interval
    if (h.p1.x < h.p2.x) {
        x1 = h.p1.x;
        x2 = h.p2.x;
    } else {
        x1 = h.p2.x;
        x2 = h.p1.x;
    }

    int y = h.p1.y;
    int y1, y2;

    // Order y-interval
    if (v.p1.y < v.p2.y) {
        y1 = v.p1.y;
        y2 = v.p2.y;
    } else {
        y1 = v.p2.y;
        y2 = v.p1.y;
    }

    if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
        p.x = x;
        p.y = y;
        return p;
    }
    return p;
}

line create_line(point p1, point p2) {
    line l; 
    l.p1 = p1;
    l.p2 = p2;
    return l;
}

point create_point(int x, int y) {
    point p;
    p.x = x;
    p.y = y;
    return p;
}

std::vector<line> parse_wire(std::string l) {
    std::vector<line> lines = std::vector<line>();
    std::stringstream ss(l);

    int x = 0, y = 0;
    int length;
    int distance_covered = 0;

    point p1, p2;

    lines.push_back(create_line(p1, p2));

    for (char dir; ss >> dir;) {
        if (dir == ',')
            continue;

        ss >> length;

        p1.x = x;
        p1.y = y;

        switch (dir) {
            case 'U':
                y += length;
                break;
            case 'D':
                y -= length;
                break;
            case 'R':
                x += length;
                break;
            case 'L':
                x -= length;
                break;
        }

        p2.x = x;
        p2.y = y;

        lines.push_back(create_line(p1, p2));
    }

    return lines;
}

int travelled_distance(std::vector<line> &lines, std::vector<line>::iterator start) {
    int distance = 0;

    for (auto i = start; i != lines.begin(); --i) {
        distance += manhattan_distance(i->p1, i->p2);
    }
    
    return distance;
}

void print_line(line l) {
    std::cout   << "(" << l.p1.x << ", " << l.p1.y << "), " 
                << "(" << l.p2.x << ", " << l.p2.y << ")" << std::endl;
}

void test() {
    line lt1 = create_line(create_point(2, 2), create_point(2, 4));
    line lt2 = create_line(create_point(2, 3), create_point(3, 3));

    point p = intersect(lt1, lt2);
    
    assert(p.x == 2);
    assert(p.y == 3);

    lt1 = create_line(create_point(6, 7), create_point(6, 3));
    lt2 = create_line(create_point(8, 5), create_point(3, 5));

    p = intersect(lt1, lt2);
    
    assert(p.x == 6);
    assert(p.y == 5);
}

int main() {
    test();

    std::string l;
    std::getline(std::cin, l);
    std::vector<line> w1 = parse_wire(l);

    std::getline(std::cin, l);
    std::vector<line> w2 = parse_wire(l);

    int shortest = INT_MAX;
    int distance = INT_MAX;

    point origo;
    origo.x = 0;
    origo.y = 0;

    for (auto l1 = w1.begin(); l1 != w1.end(); ++l1) {
        for (auto l2 = w2.begin(); l2 != w2.end(); ++l2) {
            point i = intersect(*l1, *l2);

            if (i.x == 0 && i.y == 0) {
                continue;
            }

            if (manhattan_distance(origo, i) < distance) {
                distance = manhattan_distance(origo, i);
            }

            int travelled = manhattan_distance(i, l1->p1) + 
                manhattan_distance(i, l2->p1) + 
                travelled_distance(w1, std::prev(l1)) + 
                travelled_distance(w2, std::prev(l2));
            
            if (travelled < shortest) {
                shortest = travelled;
            }
        }
    }

    std::cout << distance << std::endl;
    std::cout << shortest << std::endl;
    
    return 0;
}