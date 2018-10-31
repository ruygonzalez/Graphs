/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2018
 * @copyright This code is in the public domain.
 *
 * @brief The MST and Shortest Path algorithms
 * (implementation).
 *
 */
#include "GraphAlgorithms.hpp"

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to GraphAlgorithms.hpp if you write a helper
 * function!
 *
 */

/**
 * TODO: Implement Prim's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Prim's algorithm
 *
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				onMST and notOnMST are two vectors defined in
 *				GraphAlgorithms.hpp
 * 				that you can use to store which nodes are both in/not in the
 * 				MST. These are cleared at the start of the MST computation for 
 * 				you. To access the nodes that a specific node connects to
 *				you, you can use the vector<Node *> edges which is part
 *				of the Node struct in structs.hpp
 * 				You can compare two nodes to see if they are the same by
 * 				comparing the id attribute of a Node.
 *				You can calculate distance from one node to another by calling
 * 				the double distance(Node a) function of the Node struct.
 * 				Whenever you decide to add an edge between two nodes
 *				to the MST, you can use the provided drawEdge function
 *				in GraphAlgorithms.cpp
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * OUTLINE:
 * onMST.erase(onMST.begin(), onMST.end());
 * notOnMST.erase(notOnMST.begin(), notOnMST.end());
 * FOR i = 0 TO g.nodes.size() DO
 *  notOnMST.push_back(g.nodes[i])
 * ENDFOR
 * NODE * a = notOnMST.pop()
 * onMST.push_back(a)
 * WHILE notOnMST.size() > 0 DO
 *  Node* a
 *  Node* b
 *  int distance = 1000000
 *  FOR i = 0 TO onMST.size() DO
 *      Node* temp = onMST[i]
 *      FOR j = 0 TO temp.edges.size() DO
 *          int temp2 = temp.distance(temp.edges[j])
 *          IF temp2 < distance THEN
 *              bool already = false
 *              FOR k = 0 TO onMST.size() DO
 *                  IF onMST[k].id == b.id) THEN
 *                      already = true
 *                  ENDIF
 *              ENDFOR
 *              IF !already THEN
 *                  a = temp
 *                  b = temp.edges[j]
 *                  distance = temp2
 *              ENDIF
 *          ENDIF
 *      ENDFOR
 *  ENDFOR
 *  drawEdge(a, b, edges, app, true)
 *  onMST.push(b)
 *  FOR m = 0 TO notOnMST.size() DO
 *      IF notOnMST[m].id == b.id THEN
 *          notOnMST.erase[m]
 *          BREAK
 *      ENDIF
 *  ENDFOR
 * ENDWHILE
 *
 *
 */
void buildMSTPrim(Graph g, GraphApp *app) {
    onMST.erase(onMST.begin(), onMST.end());
    notOnMST.erase(notOnMST.begin(), notOnMST.end());
// Add all nodes in graph to the not added vector
    for(unsigned int i = 0; i < g.nodes.size(); i++)
        notOnMST.push_back(g.nodes[i]);
// Start with the first node in the vector and add it to the mst while removing from the not on mst vector
    Node* a = notOnMST[0];
    notOnMST.erase(notOnMST.begin(), notOnMST.begin()+1);
    onMST.push_back(a);
// While there are still unconnected nodes
    while(notOnMST.size() > 0){
        Node* a;
        Node* b;
        double dist = 1000000;
// Look through every node already in MST
        for(unsigned int i = 0; i < onMST.size(); i++){
            Node* temp = onMST[i];
// Look through all the adjacent nodes (edges) to this node
            for(unsigned int j = 0; j < temp->edges.size(); j++){
                double temp2 = temp->distance(*(temp->edges[j]));
// Check if this is the least weighted path found yet 
                if(temp2 < dist){
                    bool already = false;
// Check if the desired node is already connected to something else
                    for(unsigned int k = 0; k < onMST.size(); k++)
                        if(onMST[k]->id == temp->edges[j]->id)
                            already = true;
// If the node isn't already in the solutions then it's a possibility
                    if(!already){
                        a = temp;
                        b = temp->edges[j];
                        dist = temp2;
                    }
                }
            }
        }
// Once you have both nodes for the edge, draw them
        drawEdge(a, b, g.edges, app, true);
// Add the new node to mst and remove from the not on mst vector
        onMST.push_back(b);
        for(int m = 0; (unsigned)m < notOnMST.size(); m++)
            if(notOnMST[m]->id == b->id){
                notOnMST.erase(notOnMST.begin()+m, (notOnMST.begin() + m + 1));
                break;
            }
    }
}

/**
 * TODO: Implement Kruskal's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Kruskal's algorithm
 *
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than
 *passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				You'll want to use a priority queue to determine which edges
 * 				to add first. We've created the priority queue for you
 * 				along with the compare function it uses. All you need to do
 * 				is call edge_queue.top(), edge_queue.pop(), edge_queue.push()
 * 				The data type that this priority queue stores, KruskalEdge 
 *              is defined in GraphAlgorithms.hpp and is an edge between
 *              any two trees. Each Node has a kruskal_edges attribute to store
 *              all the nodes it connects to in the MST. Make sure to use this
 *				to be able to join trees later!
 * 				To know which tree a node is in, use the which_tree attribute.
 * 				You can still use the edges, distance, and id
 *				attributes of a Node.
 * 				When connecting trees, you can call the
 *				kruskalFloodFill function
 * 				defined in structs.hpp on a node to convert it and its
 * 				MST connected nodes to a different tree number recursively.
 *				As in Prim's algorith, call drawEdge to add a connection between
 * 				two nodes to the MST
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * Add your outline here
 *
 *
 */
void buildMSTKruskal(Graph g, GraphApp *app) {
    auto compare_func = [](KruskalEdge *a, KruskalEdge *b) {
        return (a->weight > b->weight);
    };
    std::priority_queue<KruskalEdge *, std::vector<KruskalEdge *>,
                        decltype(compare_func)>
        edge_queue(compare_func);

    // Write code here
}

/**
 * TODO: Implement Djikstra's shortest path algorithm.
 *
 * @brief Find the shortest path between start and end nodes with Djikstra's
 * 		  shortest path algorithm
 *
 * @param start	Index of start node of path to find
 * 				Can access the Node * element by using
 *				g.nodes[start]
 * @param end	Index of end node of path to find
 * 				Can access the Node * element by using g.nodes[end]
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				You can use the distance_to_start attribute of the Node struct
 * 				in structs.hpp to keep track of what the distance from each
 * 				Node to the start node during computation
 * 				You can use the previous attribute of the Node struct
 *				in structs.hpp to keep track of the path you are taking to
 *				later backtrack.
 *				To access the nodes that a specific node connects to you, you
 * 				can use the vector<Node *> edges which is part of the Node struct
 * 				in structs.hpp
 *				Whenever you decide to add an edge between two nodes
 *				to the MST, you can use the provided drawEdge function in
 *				GraphAlgorithms.cpp
 *
 * OUTLINE:
 * onMST.erase(onMST.begin(), onMST.end())
 * notOnMST.erase(notOnMST.begin(), notOnMST.end())
 * Node* source = g.nodes[start]
 * Node* goal = g.nodes[end]
 * source->distance_to_start = 0
 * source->previous = nullptr
 * FOR i = 0 TO g.nodes.size() DO
 *  IF g.nodes[i]->id != source->id THEN
 *      g.nodes[i]->distance_to_start = 9999999
 *      g.nodes[i]->previous = nullptr
 *  ENDIF
 * ENDFOR
 * FOR i = 0 TO g.nodes.size() DO
       notOnMST.push_back(g.nodes[i])
 * ENDFOR
 * WHILE notOnMST.size() > 0 DO
 *  Node* a
 *  double low = 99999999
 *  int m = 0
 *  FOR i = 0 TO notOnMST.size() DO
 *      IF notOnMST[i]->distance_to_start < low THEN
 *          a = notOnMST[i]
 *          low = notOnMST[i]->distance_to_start
 *          m = i
 *      ENDIF
 *  ENDFOR
 *  notOnMST.erase(notOnMST.begin() + m, notOnMST.begin() + m + 1)
 *  FOR i = 0 TO a->edges.size() DO
 *    Node * v = a->edges[i]
 *    double alt = a->distance_to_start + a->distance(*v)
 *    IF alt < v->distance_to_start THEN
 *      v->distance_to_start = alt
 *      v->previous = a
 *    ENDIF
 *    ENDFOR
 * ENDWHILE
 * Node * current = goal
 * WHILE current->id != source->id THEN
 *   Node* next = current->previous
 *   drawEdge(current, next, g.edges, app, false)
 *   current = next
 * ENDWHILE
 * ENDFUNCTION
 */

void findShortestPath(int start, int end, Graph g, GraphApp *app) {
// Clear everything from before
    onMST.erase(onMST.begin(), onMST.end());
    notOnMST.erase(notOnMST.begin(), notOnMST.end());
    Node* source = g.nodes[start];
    Node* goal = g.nodes[end];
// Distance from source to itself is zero and it has no previous node
    source->distance_to_start = 0;
    source->previous = nullptr;
// Initialize all the other distances from source to a large number with no previous node and add them to not on MST
    for(unsigned int i = 0; i < g.nodes.size(); i++){
        if (g.nodes[i]->id != source->id){
            g.nodes[i]->distance_to_start = 9999999;
            g.nodes[i]->previous = nullptr;
        }
    }
    for(unsigned int i = 0; i < g.nodes.size(); i++)
       notOnMST.push_back(g.nodes[i]);
// While there are still unadded nodes find the shortest path to them
    while(notOnMST.size() > 0){
        Node* a;
        double low = 99999999;
        int m = 0;
// Update distance from source if there is a shorter path found using a 
        for(unsigned int i = 0; i < notOnMST.size(); i++){
            if(notOnMST[i]->distance_to_start < low){
                a = notOnMST[i];
                low = notOnMST[i]->distance_to_start;
                m = i;
            }
        }
// Remove from unadded since it's been visited
        notOnMST.erase(notOnMST.begin() + m, notOnMST.begin() + m + 1);
        for(unsigned int i = 0; i < a->edges.size(); i++){
            Node * v = a->edges[i];
            double alt = a->distance_to_start + a->distance(*v);
            if(alt < v->distance_to_start){
                v->distance_to_start = alt;
                v->previous = a;
            }
        }
    }
    Node * current = goal;
    while(current->id != source->id){
        Node* next = current->previous;
        drawEdge(current, next, g.edges, app, false);
        current = next;
    }
}

/**
 * @brief Adds an edge to either the MST or the shortest path based on the
 * 			nodes to connect given. This is done by iterating through the edges
 * 			to find the correct edge given the nodes.
 *
 * @param pt1	One side of edge to draw
 * @param pt2	Other side of edge to draw
 * @param edges	Vector of edges in the graph
 * @param app	Graphics application class
 * @param mst	True if we are adding edge to MST, False if we are adding edge
 * 				to shortest path
 **/

void drawEdge(Node *pt1, Node *pt2, vector<Edge *> edges, GraphApp *app,
              bool mst) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        if ((edges[i]->a == pt1 && edges[i]->b == pt2) ||
            (edges[i]->a == pt2 && edges[i]->b == pt1)) {
            if (mst)
                app->add_to_mst(edges[i]);
            else
                app->add_to_path(edges[i]);
            break;
        }
    }
    return;
}
