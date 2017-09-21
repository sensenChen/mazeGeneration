#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <ctime>
#include "MersenneTwister.h"

#include <map>
#include <set>
using namespace std;

class tile {
public:
  tile() {
    walls = vector<bool>(4, false);
    visited = false;
    val = 0;
  }

  vector<bool> walls;
  bool visited;
  int val;
  vector<int> dir;
};

class grid {
public:
  grid(int M, int N) {
    data = vector<vector<tile> >(M, vector<tile>(N, tile()));
  }

  void print() {
    cout<<string(data[0].size()*4+1,'-')<<endl;
    for(int i=0;i<data.size();i++) {
      for(int j=0;j<data[0].size();j++) {
        cout<<"| "<<data[i][j].val<<" ";
      } cout<<"|"<<endl;
      cout<<string(data[0].size()*4+1,'-')<<endl;
    }
  }

  bool get(int i, int j) {
    return data[i][j].visited;
  }

  void set(int i, int j) {
    data[i][j].visited = true;
  }

  void addPair(int i, int j, int dir) {
    data[i][j].dir.push_back(dir);
  }


  vector<vector<tile> > data;
};

int M=10, N=10;
grid g(M, N);


int myrandom (int i) {
  MTRand mrand;
  // std::srand ( unsigned ( std::time(0) ) );
  return mrand.randInt()%i;
}

vector<int> randomDirections() {
  vector<int> direction;
  for(int i=0;i<4;i++) {
    direction.push_back(i);
  }


  random_shuffle(direction.begin(), direction.end(), myrandom);
  return direction;
}


int countNum = 0;
vector<vector<bool> > visited(M, vector<bool>(N, false));
map<int, map<int, set<int> > > check;

void dfs(int i, int j, int previ, int prevj, int dir, int goalM, int goalN) {

  if(i<0 || j<0 || i>=g.data.size() || j>= g.data[0].size() || g.get(i,j)){
    return;
  }
  // if(countNum==4*(goalM+1)*(goalN+1)) return;

  else {
    // set spot as visited
    g.set(i,j);
    visited[i][j] = true;
    // cout<<i<<" "<<j<<endl;

    countNum++;
    if(i!=-1 && j!=-1){
      check[previ][prevj].insert(dir);
        // g.addPair(previ, prevj,dir);
    }

  }

  vector<int> rd = randomDirections();
  for(int x=0;x<rd.size();x++) {
    if(rd[x]==0) {
      //up
      dfs(i-1,j,i,j,rd[x],goalM,goalN);
    } else if(rd[x]==1) {
      //right
      dfs(i,j+1,i,j,rd[x],goalM,goalN);
    } else if(rd[x]==2) {
      //down
      dfs(i+1,j,i,j,rd[x],goalM,goalN);
    } else {
      //left
      dfs(i,j-1,i,j,rd[x],goalM,goalN);
    }
  }
}

void print(vector<vector<char> >& display) {
  for(int i=0;i<display.size()-1;i++) {
    for(int j=0;j<display[0].size()-1;j++) {
      cout<<display[i][j]<<" ";
    } cout<<endl;
  }
}


int main() {
  dfs(0,0,-1,-1,0,M-1,N-1);

  vector<vector<char> > display(2*M+2, vector<char>(2*N+2,'*'));
  for(int i=0;i<M;i++) {
    for(int j=0;j<N;j++) {
      display[2*i+1][2*j+1] = ' ';
    }
  }


  for(int i=0;i<M;i++) {
    for(int j=0;j<N;j++) {
      if(check[i][j].find(0)!=check[i][j].end()) {
        display[2*i+1-1][2*j+1] = ' ';
      }

      if(check[i][j].find(1)!=check[i][j].end()) {
        display[2*i+1][2*j+1+1] = ' ';
      }

      if(check[i][j].find(2)!=check[i][j].end()) {
        display[2*i+1+1][2*j+1] = ' ';
      }

      if(check[i][j].find(3)!=check[i][j].end()) {
        display[2*i+1][2*j+1-1] = ' ';
      }
    }
  }

  // cout<<"{"<<endl;
  // for(int i=0;i<display.size()-1;i++) {
  //   for(int j=0;j<display[0].size()-1;j++) {
  //     if(display[i][j]=='*') {
  //       cout<<"{\"type\": wall,\n\"row\": "<<i<<",\n"<<"\"col\": "<<j<<"},"<<endl;
  //     }
  //   } //cout<<endl;
  // }
  // cout<<"}"<<endl;

  // for(int i=0;i<display.size()-1;i++) {
  //   for(int j=0;j<display[0].size()-1;j++) {
  //     // cout<<display[i][j]<<" ";
  //
  //     for(int k=0;k<4;k++) {
  //       if(display[i][j]=='*')
  //         cout<<'1';
  //       else
  //         cout<<'0';
  //       if(j!=display[0].size()-2 && k=3) cout<<", ";
  //     }
  //
  //   } cout<<endl;
  // }



  print(display);
  return 0;
}
