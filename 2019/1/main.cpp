#include <iostream>
#include <fstream>
#include <cmath>

int mass_to_fuel (int mass) {
    return floor(mass / 3) - 2;
}

int fuel_required (int mass) {
    int fuel = mass_to_fuel(mass);
    if (fuel > 0) {
        return fuel + fuel_required(fuel);
    }
    return 0;
}

int main () {
    std::string line;
    std::ifstream file("./input.txt");
    int sum = 0;
    while (std::getline(file, line))
    {
        int mass = atoi(line.c_str());
        sum += fuel_required(mass);
    }
    file.close();
    std::cout << sum << std::endl;
    return 0;
} 