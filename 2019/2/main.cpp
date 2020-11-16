#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

int run(std::vector<int> memory, int noun, int verb) {
    memory[1] = noun;
    memory[2] = verb;

    int op, r1, r2, r3;

    for (int pc = 0; pc < memory.size(); pc += 4) {
        op = memory[pc];
        r1 = memory[pc + 1];
        r2 = memory[pc + 2];
        r3 = memory[pc + 3];

        switch (op) {
            case 1:
                memory[r3] = memory[r1] + memory[r2];
                break;
            case 2:
                memory[r3] = memory[r1] * memory[r2];
                break;
            case 99:
                return memory[0];
        }
    }

    return memory[0];
}

int main () {
    std::vector<int> memory = std::vector<int>(0);
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    for (int i; ss >> i;) {
        memory.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    int answer = run(std::vector<int>(memory), 0, 0);
    int noun = run(std::vector<int>(memory), 1, 0) - answer;
    int verb = run(std::vector<int>(memory), 0, 1) - answer;

    int TARGET = 19690720 - answer;
    int nouns = TARGET / noun;
    int verbs = TARGET % noun;

    std::cout << answer << std::endl;
    std::cout << 100 * nouns + verbs << std::endl;

    return 0;
}