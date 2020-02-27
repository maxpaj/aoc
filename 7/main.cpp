#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#define ADD 1
#define MUL 2
#define STORE 3
#define OUT 4
#define JUMPIFTRUE 5
#define JUMPIFFALSE 6
#define LESSTHAN 7
#define EQUALS 8

using namespace std;

struct instruction {
    int op;
    bool mode1;
    bool mode2;
    bool mode3;
};

void print_program(vector<int> program) {
    for (auto it = program.begin(); it != program.end(); it++) {
        cerr << *it << ", ";
    }
    cerr << endl;
}

vector<int> int_to_arr(int x)
{
    vector<int> arr;
    while (true)
    {
    arr.insert(arr.begin(), x % 10);
    x /= 10;
    if (x == 0)
        return arr;
    }
}

instruction create_instruction(int operation) {
    instruction i;

    vector<int> v = int_to_arr(operation);

    int op = v[v.size() - 1];

    i.op = op;

    if (v.size() > 1) {
        i.op += v[v.size() - 2] * 10;
    };

    i.mode1 = v.size() - 3 >= 0 ? v[v.size() - 3] : 0;
    i.mode2 = v.size() - 4 >= 0 ? v[v.size() - 4] : 0;
    i.mode3 = v.size() - 5 >= 0 ? v[v.size() - 5] : 0;

    return i;
}

int run(vector<int> program, int phase, int input) {
    instruction i;
    
    int pc = 0; 
    int r1, r2, r3;
    int p1, p2, p3;

    while (pc < program.size()) {
        i = create_instruction(program[pc]);

        r1 = program[pc + 1];
        r2 = program[pc + 2];
        r3 = program[pc + 3];

        p1 = i.mode1 ? r1 : program[r1]; 
        p2 = i.mode2 ? r2 : program[r2]; 
        p3 = i.mode3 ? r3 : program[r3]; 

        // print_program(program);
        // cerr << "Operation " << i.op << endl;
        // cerr << "R1 " << r1 << "  MODE " << (i.mode1 ? "IMMEDIATE" : "POSITION ") << " -> P1 = " << p1 << endl;
        // cerr << "R2 " << r2 << "  MODE " << (i.mode2 ? "IMMEDIATE" : "POSITION ") << " -> P2 = " << p2 << endl;
        // cerr << "R3 " << r3 << "  MODE " << (i.mode3 ? "IMMEDIATE" : "POSITION ") << " -> P3 = " << p3 << endl;

        switch (i.op) {
            case ADD:
                program[r3] = p1 + p2;
                pc += 4;
                break;

            case MUL:
                program[r3] = p1 * p2;
                pc += 4;
                break;

            case STORE:
                program[r1] = input;
                pc += 2;
                break;

            case OUT:
                return p1;

            case JUMPIFTRUE:
                if (p1) {
                    pc = p2;
                } else {
                    pc += 3;
                }
                break;

            case JUMPIFFALSE:
                if (!p1) {
                    pc = p2;
                } else {
                    pc += 3;
                }
                break;

            case LESSTHAN:
                if (p1 < p2) {
                    program[r3] = 1;
                } else {
                    program[r3] = 0;
                }
                pc += 4;
                break;

            case EQUALS:
                if (p1 == p2) {
                    program[r3] = 1;
                } else {
                    program[r3] = 0;
                }
                pc += 4;
                break;

            // EXIT
            case 99:
                return 0;
        }
    }

    return 0;
}

int main () {
    instruction a, b, c, d, e;

    a = create_instruction(4);
    assert(a.op == 4);
    
    b = create_instruction(99);
    assert(b.op == 99);
    
    c = create_instruction(11102);
    assert(c.op == 2);
    assert(c.mode1 == 1);
    assert(c.mode2 == 1);
    assert(c.mode3 == 1);

    d = create_instruction(1102);
    assert(d.op == 2);
    assert(d.mode1 == 1);
    assert(d.mode2 == 1);
    assert(d.mode3 == 0);

    e = create_instruction(1002);
    assert(e.op == 2);
    assert(e.mode1 == 0);
    assert(e.mode2 == 1);
    assert(e.mode3 == 0);

    vector<int> program = vector<int>(0);
    string line;
    getline(cin, line);
    stringstream ss(line);

    for (int i; ss >> i;) {
        program.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    int input = 5;
    int phase = 4;

    input = run(vector<int>(program), phase, input);
    
    phase = 3;
    input = run(vector<int>(program), phase, input);
    
    phase = 2;
    input = run(vector<int>(program), phase, input);
    
    phase = 1;
    input = run(vector<int>(program), phase, input);
    
    phase = 0;
    input = run(vector<int>(program), phase, input);
    
    cout << input << endl;
    
    return 0;
}