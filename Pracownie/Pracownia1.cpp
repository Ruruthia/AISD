#include <stdio.h>
#include <vector>
using namespace std;

struct Kostka{
  int l;
  int m;
  int r;
};

bool visited [10001] = {false};
bool isroot=false, iscomplete=false;
vector<Kostka> Kostki[10001];
vector<Kostka> Chodnik;
bool dfs(Kostka root);

int main(){

  int ile_kostek, l, m, r;

  scanf("%i", &ile_kostek);
  for(int i=0; i<ile_kostek; i++){
    Kostka nowa;
    scanf("%i %i %i", &l, &m, &r);
    if( l==0 ){
      isroot=true;
    }
    nowa.l=l;
    nowa.m=m;
    nowa.r=r;
    Kostki[l].push_back(nowa);
  }

  if(!isroot){
    printf("%s", "BRAK");
  }

  while(!iscomplete&&(!Kostki[0].empty())){
    for(int i=0; i<10001; i++){
      visited[i]=false;
    }
    Chodnik.clear();
    dfs(Kostki[0].back());
    Kostki[0].pop_back();
  }

  if(!iscomplete){
    printf("%s", "BRAK");
  }

  else{
    printf("%li \n", Chodnik.size());
    for(int i=0;i<Chodnik.size();i++){
      printf("%i %i %i \n", Chodnik[i].l, Chodnik[i].m, Chodnik[i].r);
    }
  }
  return 0;
}

bool dfs(Kostka root){

  visited[root.r]=true;
  if(Kostki[root.r].empty()){
    return false;
  }

  Chodnik.push_back(root);

  if(root.r==0){
    iscomplete=true;
    return true;
  }

  for(int i=0; i<Kostki[root.r].size(); i++){
    if(!visited[Kostki[root.r][i].r]){
      if(dfs(Kostki[root.r][i])){
        return true;
      }
    }
  }
  Chodnik.pop_back();
  return false;
}
