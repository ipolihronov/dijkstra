#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define DEBUG_INFO
#define NODES 7

class Node{
public:
  int id;
  int dist;
  int prev;
  bool done;
  bool checked[NODES];
};

Node n[NODES];
int graph [NODES][NODES] = {
  /* for each node there is an array
  * 0 - no connection
  * >0 - distance between the nodes
  */
  {0, 2, 5, 0, 0, 0, 88},
  {2, 0, 0, 0, 0, 0, 0},
  {5, 0, 0, 4, 0, 0, 0},
  {0, 0, 4, 0, 1, 0, 0},
  {0, 0, 0, 1, 0, 1, 0},
  {0, 0, 0, 0, 1, 0, 9},
  {88, 0, 0, 0, 0, 9, 0}
};


std::vector<Node> NodeQueue;
std::vector<Node>::iterator it;

bool NodeSort(const Node &a, const Node &b){
  return (a.dist < b.dist);
}

#ifdef DEBUG_INFO
void printNodes(void){
  std::cout << '\n';
  for (it = NodeQueue.begin(); it != NodeQueue.end(); it++){
    std::cout << "ID: "<<it->id << " ";
    std::cout << "DIST: "<<it->dist << " ";
    std::cout << "PREV: "<<it->prev << " ";
    std::cout << "DONE: "<<it->done << " ||";
    for (int a = 0; a < NODES; a++){
      std::cout << it->checked[a] << " ";
    }
    std::cout << '\n';
  }
}
#endif

int isChecked(int id, int index){
  for (it = NodeQueue.begin(); it != NodeQueue.end(); it++){
    if(id == (it->id)){
      return it->checked[index];
    }
  }
}

int getIndexInQueue(int id){
  int index = 0;
  for (it = NodeQueue.begin(); it != NodeQueue.end(); it++){
    if(id == (it->id)){
      break;
    }
    index++;
  }
  return index;
}

void init(int first){
  int i = 0;
  for (int a = 0; a < NODES; a++){
    NodeQueue.push_back(n[a]);
  }
  for (it = NodeQueue.begin(); it != NodeQueue.end(); it++){
    it->dist = 0xffff;
    it->prev = 0xffff;
    it->id = i;
    it->done = false;
    it->checked[NODES] = false;
    i++;
  }
  std::cout << first << '\n';
  NodeQueue[first].dist = 0;
  NodeQueue[first].prev = first;

}

/*
* args:
* - int begin - the id of the starting node
* - int end - the id of the end node
* - vector<int>shortestPath - contains the shortest path
* return
* - int result - the shoretest distance in given units
*/

int dij(int begin, int end, std::vector<int>& shortestPath){
  init(begin);
  std::sort (NodeQueue.begin(), NodeQueue.end(), NodeSort);
  bool done = false;
  int index = 0;
  int idx;
  while(true != done){
#ifdef DEBUG_INFO
    std::cout << "------------------" << '\n';
    std::cout << "------------------" << '\n';
    std::cout << "index is: " << index << '\n';
    std::cout << "the current node is: " << NodeQueue[index].id << '\n';
#endif
    for (int a = 0; a < NODES; a++){
      if(( 0 < graph[NodeQueue[index].id][a])){
#ifdef DEBUG_INFO
        std::cout << "found a connection: node " << a << ". Dist " << graph[NodeQueue[index].id][a]<<'\n';
#endif
          if (true != isChecked(a, index)){
            idx = getIndexInQueue(a);
#ifdef DEBUG_INFO
            std::cout << "id of node in the queue: " << idx << '\n';
#endif
            int distTemp = graph[NodeQueue[index].id][a] + NodeQueue[index].dist;
            if (distTemp < NodeQueue[idx].dist){
              NodeQueue[idx].dist = distTemp;
              NodeQueue[idx].prev = NodeQueue[index].id; //правилно
            }
            NodeQueue[index].checked[a] = true; //правилно
          }
          else{
#ifdef DEBUG_INFO
            std::cout << "connection already checked" << '\n';
#endif
          }
      }
    }
    std::sort (NodeQueue.begin(), NodeQueue.end(), NodeSort);
    index++;
    if( end == NodeQueue[index].id ){
      /* the end node is reached */
      done = true;
      std::cout << "enddd" << '\n';
    }
#ifdef DEBUG_INFO
    printNodes();
#endif
  }
  /* the shortest path found */
  int a = index;
  while( NodeQueue[getIndexInQueue(a)].prev != NodeQueue[getIndexInQueue(a)].id){
    a = NodeQueue[getIndexInQueue(a)].prev;
    shortestPath.push_back(a);
  }
  int result = NodeQueue[getIndexInQueue(end)].dist;
  return result;
}
int main(void){
  /* vector to hold the shortest path (sequence of nodes) */
  std::vector<int> v;
  int dist = 0;
  dist = dij(1, 6, v);

  std::cout << "the shortest dist: "<< dist << '\n';
  std::cout << "path:" << '\n';
  for(std::vector<int>::iterator i = v.begin(); i != v.end(); i++){
    std::cout << *i << "\t";
  }
  return 0;
}
