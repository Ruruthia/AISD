#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <float.h> 
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Punkt{
    int x;
    int y;
};

double MIN = FLT_MAX;
int ile_punktow;
Punkt X[500000];
vector <Punkt> Y;
Punkt minT[3]; //minimalny trójkąt

//do sortowania po Y
bool porownajY(Punkt p1, Punkt p2)
{   
    if(!(p1.y==p2.y)) return p1.y<p2.y;
    return p1.x<p2.x;

}


//do sortowania po X
int porownajX(const void* p1, const void* p2)
{
   if((*(Punkt*)p1).x<(*(Punkt*)p2).x) return -1;
   if((*(Punkt*)p1).x>(*(Punkt*)p2).x) return 1;
   else {
    if((*(Punkt*)p1).y<(*(Punkt*)p2).y) return -1;
    if((*(Punkt*)p1).y>(*(Punkt*)p2).y) return 1;
    else return 0;
   };
}

inline double odleglosc (const Punkt &a,const Punkt &b){
   return sqrt((double)((long long)(a.x-b.x)*(long long)(a.x-b.x) + (long long)(a.y-b.y)*(long long)(a.y-b.y)));
}

inline double obwod (const Punkt &a,const Punkt &b,const Punkt &c){
    return odleglosc(a, b)+odleglosc(b, c)+odleglosc(c, a);
}

//szukanie minimalnego trojkata w danym pasku
//do łączenia wyników z wywołań rekurencyjnych
//warunki wewnętrznych pętli dla danego p spełnia max 16 punktów
void pasek (const Punkt pasek[], int size){
    double marg = MIN/2;
    for (int i=0; i<size; i++){
        for (int j=i+1; j<size && (pasek[j].y - pasek[i].y )< marg; j++){
            for (int k=j+1; k<size && (pasek[k].y-pasek[i].y) < marg; k++){
                    if(obwod(pasek[i], pasek[j], pasek[k])<MIN){
                    MIN = obwod(pasek[i], pasek[j], pasek[k]);
                    minT[0]=pasek[i];
                    minT[1]=pasek[j];
                    minT[2]=pasek[k];
                    }
            }
        }
    }
}


void glowna(int l, int r, const vector<Punkt> L){ 

    int n = r - l; 
    if(n<3) return;

    int sL=L.size();
    int mid = l+n/2;
    Punkt midPoint=X[mid];
    vector <Punkt> leweY, praweY;
    leweY.reserve(1+sL/2);
    praweY.reserve(1+sL/2);

    for(int i=0; i<L.size(); i++){
        if(porownajX(&L[i], &midPoint)==-1){
            leweY.push_back(L[i]);
        }  
        else{
        praweY.push_back(L[i]);
        }
    }

    glowna(l, mid, leweY);
    glowna(mid, r, praweY);
    Punkt p[sL];  
    int j = 0;
    //tworzymy pasek w okolicy midpoint
        for(int i = 0; i<sL; i++){
        if(abs(L[i].x - midPoint.x)<(MIN/2))
        {
            p[j]=L[i];
            j++;
        }
    }
    pasek(p, j);
}

//preprocessing
void pre(int n){

    qsort(X, n, sizeof(Punkt), porownajX);
    sort(Y.begin(), Y.end(), porownajY);    
    glowna(0, n, Y);
}


int main()
{
    ios_base::sync_with_stdio(false);

    scanf("%d", &ile_punktow);
    Y.reserve(ile_punktow);
    for(int i=0; i<ile_punktow; i++)
    {
        Punkt temp;
        int tx, ty;
        scanf("%d %d", &tx, &ty);
        temp.x=tx;
        temp.y=ty;
        X[i]=temp;
        Y.push_back(temp);
    };
    pre(ile_punktow);
    printf("%d %d \n%d %d \n%d %d \n",minT[0].x, minT[0].y, minT[1].x, minT[1].y, minT[2].x, minT[2].y);
    return 0;

}