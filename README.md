Caltech CS2 Assignment 5: Graphs

See [assignment5.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/graphs/blob/master/assignment5.html)

Answer to Debugging 0:
 The depth-first search algorithm is correct. I know because it basically does the following:
 	It starts with the top node (this node) then checks all the nodes connected to it via edges for the value. 
 	However, it does this in a depth first search rather than breath first search since it does this function recursively  for each of the nodes in its edge. 
	So it would check the first edge and follow it all the way down and then goes up to check  adjacent nodes. 
	And if at any point the value of the current node being checked is the value you're looking for, it returns true and  all the nodes above it return true and the recursion stops, since the value was found, as desired. 
  I checked that this was indeed the case by checking values that I knew were the equal to the Node value or to Nodes below it , 
(but made sure that if the Node with the value wasn't connected to it via an edge then it would return false) and checked values that I knew were not going to be found and thus return false, and it worked for every case (edge cases and normal cases), thus confirming that it works. 