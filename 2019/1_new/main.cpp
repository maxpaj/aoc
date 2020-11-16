#include <iostream>
#include <string>

int mass_to_fuel(int mass) {
    int fuel = mass / 3 - 2;
    if (fuel < 0) {
        return 0;
    }
    return fuel;
}

int total_fuel(int remainingMass) {
    int total = 0;

    while (remainingMass > 0) {
        total += mass_to_fuel(remainingMass);
        remainingMass = remainingMass / 3 - 2;
    }

    return total;
}

int main () {
    int total = 0;

    for (std::string line; std::getline(std::cin, line);) {
        int moduleMass = atoi(line.c_str());
        total += total_fuel(moduleMass);
    }

    std::cout << total << std::endl;

    return 0;
}