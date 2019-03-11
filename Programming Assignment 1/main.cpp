/*  Programming Assignment - 1
 *  COMP6651
 *  Dr. Tiberiu Popa
 *  Himen Hitesh Sidhpura
 *  40091993
 *  Due Date:- 22- Feb - 2018
 */
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#define INT_MAX 2147483647
using namespace std;

int *graph;
int *destination;
vector < vector < int > > matrix;
vector < vector < int > > vertexCombination;
vector <int> result;
void swap(int x, int y){
    int temp;
    temp = destination[x];
    destination[x] = destination[y];
    destination[y] = temp;
}
void generateCombintation(int end,int node){
    if(end == 0){
        vector<int> vertex;
        for(int i =0 ;i < node;i++)
            vertex.push_back(destination[i]);
        vertexCombination.push_back(vertex);
        vertex.clear();
    } else {
        for(int i =end-1; i>=0 ;i--){
            swap(i,end-1);
            generateCombintation(end-1,node);
            swap(i,end-1);
        }

    }
}
void calculateMinPath(int node){
    destination = new int[node-1];
      for(int i =0 ;i < node-1;i++){
          destination[i] = i+1;
      }
     generateCombintation(node-1,node-1);
     int rootNode = 0;
     int minPath = INT_MAX;
     for(int i = 0; i< vertexCombination.size();i++){
     int path = 0;
         int currentNode = rootNode;
         vector<int> tempVector = vertexCombination[i];
         for(int j = 0;j < tempVector.size();j++){
            path+=*(graph + currentNode*node + tempVector[j]);
            currentNode = tempVector[j];
         }
         path += *(graph + currentNode*node + rootNode );
         minPath = min(minPath,path);
         tempVector.clear();
    }
    result.push_back(minPath);
    vertexCombination.clear();
    free(destination);
    free(graph);
}
void generateMatrix(){
    int vertices;
    bool flag = false;
    for(int i = 0 ;i < matrix.size() ;i++ ){
      vector<int> currentData = matrix[i];
      if(currentData.size() == 2){
         if(flag){
            calculateMinPath(vertices);
         }
        graph= (int *)malloc(currentData[0] * currentData[0] * sizeof(int));
        vertices = currentData[0];
        for(int i = 0 ; i < vertices ;i++){
             for(int j = 0 ; j < vertices ;j++){
                   *(graph + i*vertices + j) = 0;
            }
        }
        flag = false;
       } else if(currentData.size() == 3){
           *(graph + currentData[0]*vertices + currentData[1]) = currentData[2];
           *(graph + currentData[1]*vertices + currentData[0]) = currentData[2];
            flag = true;
       }
    }
    if(flag){
        calculateMinPath(vertices);
    }
}

int main(int argc, char* argv[]) {
  string currentLine = "";
  ifstream INPUT_FILE(argv[1]);
  ofstream OUTPUT_FILE(argv[2]);
  if (INPUT_FILE.is_open()) {
    int lineNo = 0;
    bool dataFlag = false;
    string currentCharacter;
    int isInteger;
    while (getline(INPUT_FILE, currentLine)) {
      if (lineNo >= 1) {
        stringstream currentString;
        currentString << currentLine;
        vector < int > currentData;
        while (!currentString.eof()) {
          currentString >> currentCharacter;
          if (stringstream(currentCharacter) >> isInteger) {
            currentData.push_back(isInteger);
          }
          currentCharacter = "";
        }
        if (currentData.size() == 2) {
          matrix.push_back(currentData);
        } else if (currentData.size() == 3) {
          matrix.push_back(currentData);
        }
        currentData.clear();
      }
      lineNo++;
    }
    INPUT_FILE.close();
  }
  generateMatrix();
  if(OUTPUT_FILE.is_open()){
    for(int i=0 ; i< result.size();i++){
        OUTPUT_FILE << result[i] << "\n";
      }
    OUTPUT_FILE.close();
  }
  result.clear();
  return 0;
}
