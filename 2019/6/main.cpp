#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Node {
    public:
        string name; 
        vector<Node*> children;

        void print(int depth) {
            for (int i = 0; i < depth; i++) {
                cerr << " ";
            }
            cerr << name << endl;

            for (auto it = children.begin(); it != children.end(); it++) {
                (*it)->print(depth + 1);
            }
        }

        void add_child(Node* c) {
            children.push_back(c);
        }

        bool path(string s) {
            if (!s.compare(name)) {
                return true;
            }

            for (auto it = children.begin(); it != children.end(); it++) {
                auto found = (*it)->path(s);
                if (found) {
                    cerr << name << ", ";
                    return found;
                }
            }

            return false;
        }

        int depth_sum(int depth) {
            int sum = depth;

            // Add the sum of the children
            for (auto it = children.begin(); it != children.end(); it++) {
                sum += (*it)->depth_sum(depth + 1);
            }

            return sum;
        }

        Node* find(string s) {
            if (!s.compare(name)) {
                return this;
            }

            for (auto it = children.begin(); it != children.end(); it++) {
                auto found = (*it)->find(s);
                if (found != NULL) {
                    return found;
                }
            }
            return NULL;
        }

        Node (string n) {
            name = n;
            children = vector<Node*>();
        }
};

int main() {
    string line;
    
    Node *com = new Node(string("COM"));

    vector<Node*> trees = vector<Node*>();

    while(getline(cin, line, ')')) {
        auto first_id = line;
        getline(cin, line, '\n');
        auto second_id = line;
        
        auto found = com->find(first_id);

        Node* insert = new Node(second_id);

        if (found != NULL) {
            found->add_child(insert);
        } else {
            found = new Node(first_id);
            found->add_child(insert);
            trees.push_back(found);
        }
    }

    while (trees.size() > 0) {
        for (auto it = trees.begin(); it != trees.end(); it++) {
            auto found = com->find((*it)->name);
            if (found == NULL) {
                continue;
            }

            found->add_child((*it)->children[0]);

            trees.erase(it);
            break;
        }
    }

    cerr << "SAN, ";
    com->path("SAN");
    cerr << endl;

    cerr << "YOU, ";
    com->path("YOU");

    return 0;
}