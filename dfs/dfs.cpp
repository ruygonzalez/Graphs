/* debugging example */

/*
 * The depth-first search algorithm is correct. I know because it basically does the following:
 * It starts with the top node (this node) then checks all the nodes connected to it via edges for the value. 
 * However, it does this in a depth first search rather than breath first search since it does this function recursively
 * for each of the nodes in its edge. So it would check the first edge and follow it all the way down and then goes up to check 
 * adjacent nodes. And if at any point the value of the current node being checked is the value you're looking for, it returns true and 
 * all the nodes above it return true and the recursion stops, since the value was found, as desired. 
 * I checked that this was indeed the case by checking values that I knew were the equal to the Node value or to Nodes below it 
 * (but made sure that if the Node with the value wasn't connected to it via an edge then it would return false) and checked values that
 * I knew were not going to be found and thus return false, and it worked for every case (edge cases and normal cases), thus confirming
 * that it works. 
 */
#include <iostream>
#include <vector>

class Node
{
    int value;
    std::vector<Node*> edges;
public:
    // insert constructors, destructors,
    // accessors, and mutators here
    Node(){
    }
    void add(Node* edge);
    void val(int v);
    bool dfs(int to_find);
};

void Node::add(Node* edge){
    this->edges.push_back(edge);
}

void Node::val(int v){
    this->value = v;
}

// true indicates that the value was found, and false indicates that the value was not found.
bool Node::dfs(int to_find)
{
    if(this->value == to_find)
    {
        return true;
    }
    std::vector<Node*>::iterator i;
    for(i = this->edges.begin(); i != this->edges.end(); i++)
    {
        Node * n = *i;
        bool r = n->dfs(to_find);
        if(r)
        {
            return r;
        }
    }
    return false;
}

int main(void)
{
    Node a2 = Node();
    Node * a = &a2; 
    std::cout << "Make a Node a with value 1" << std::endl;
    a->val(1);
    Node b2 = Node();
    Node* b = &b2;
    std::cout << "Make a Node b with value 2" << std::endl;
    b->val(2);
    Node c2 = Node();
    Node* c = &c2;
    std::cout << "Make a Node c with value 3" << std::endl;
    c->val(3);
    a->add(b);
    a->add(c);
    std::cout << "Add edges connecting b and c to a" << std::endl;
    Node d2 = Node();
    Node* d = &d2;
    std::cout << "Make a Node d with value 4" << std::endl;
    d->val(4);
    b->add(d);
    std::cout << "Add an edge connecting d to b" << std::endl;
    Node e2 = Node();
    Node* e = &e2;
    std::cout << "Make a Node e with value 5" << std::endl;
    e->val(5);
    std::cout << "Add an edge connecting e to d" << std::endl;
    d->add(e);
    std::cout << "Check if value 5 is in a or one of the Nodes connected to it" << std::endl;
    std::cout << "This should print out True (1): " << a->dfs(5) << std::endl;
    std::cout << "Check if value 2 is in a or one of the Nodes connected to it" << std::endl;
    std::cout << "This should print out True (1): " << a->dfs(2) << std::endl;
    std::cout << "Check if value 7 is in a or one of the Nodes connected to it" << std::endl;
    std::cout << "This should print out False (0): " << a->dfs(7) << std::endl;
    std::cout << "Check if value 1 is in a or one of the Nodes connected to it" << std::endl;
    std::cout << "This should print out True (1) : " << a->dfs(1) << std::endl;
    std::cout << "Check if value 1 is in b or one of the Nodes connected to it (below b since depth first)" << std::endl;
    std::cout << "This should print out False (0): " << b->dfs(1) << std::endl;
    std::cout << "Check if value 8 is in b or one of the Nodes connected to it" << std::endl;
    std::cout << "This should print out False (0): " << b->dfs(8) << std::endl;
    std::cout << "Check if value 5 is in b or one of the Nodes connected to it" << std::endl;
    std::cout << "This should print out True (1): " << b->dfs(5) << std::endl;
    std::cout << "Check if value 3 is in a or one of the Nodes connected to it" << std::endl;
    std::cout << "This should print out True (1): " << a->dfs(3) << std::endl;
    std::cout << "Check if value 3 is in b or one of the Nodes connected to it (below b since depth first)" << std::endl;
    std::cout << "This should print out False (0): " << b->dfs(3) << std::endl;
    std::cout << "Check if value 4 is in c or one of the Nodes connected to it (below c since depth first)" << std::endl;
    std::cout << "This should print out False (0): " << c->dfs(4) << std::endl;
    return 0;

}
