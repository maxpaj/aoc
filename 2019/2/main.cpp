#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

const int ADD = 1;
const int MUL = 2;
const int EXIT = 99;

std::vector<int> parse(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);

    int number;
    std::vector<int> codes;

    for (int i; ss >> i;) {
        codes.push_back(i);    
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }
    return codes;
}

int run (std::vector<int> program, int noun, int verb) {
    program[1] = noun;
    program[2] = verb;

    for (int pc = 0; program[pc] != EXIT; pc += 4) {
        switch (program[pc]) {
            case ADD: 
                program[program[pc + 3]] = program[program[pc + 1]] + program[program[pc + 2]];
                break;
            case MUL: 
                program[program[pc + 3]] = program[program[pc + 1]] * program[program[pc + 2]];
                break;
            default:
                return -1;
        }
    }
    return program[0];
}

int main () {
    std::ifstream file("./input.txt");
    std::vector<int> program = parse(file);

    int noun = 98, verb = 20;
    
    std::cout << run(program, noun, verb) << std::endl;
    std::cout << (100 * noun + verb) << std::endl;

    file.close();
    return 0;
} 