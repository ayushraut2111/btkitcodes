#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
#include<list>
#include<queue>
#include<set>
using namespace std;
typedef vector<int> VI;
typedef long long LL;
#define FOR(x, b, e) for(int x=b; x<=(e); ++x)
#define FORD(x, b, e) for(int x=b; x>=(e); --x)
#define REP(x, n) for(int x=0; x<(n); ++x)
#define VAR(v,n) __typeof(n) v=(n)
#define ALL(c) c.begin(),c.end()
#define SIZE(x) (int)x.size()
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
const int MILION=1000*1000;
const int MAX_SUMA=200;
const int MAX_KWADRAT=2000;
const int MAX_CYFR=20;

LL pot[MAX_CYFR];
bool pierwsza[MAX_SUMA][MAX_KWADRAT];
LL w[MAX_SUMA][MAX_KWADRAT][MAX_CYFR];


bool czyPierwsza(int k){
    if (k<2) return false;
    int i=2;
    while (i*i<=k){
        if (k%i==0) return false;
        i++;
    }
    return true;
}

void ustalPot(){
    pot[0]=1;
    FOR(i,1,MAX_CYFR-1){
        pot[i]=pot[i-1]*10;
    }
}

void ustalPierwsze(){
    FOR(i,2,MAX_SUMA-2){
        FOR(j,2,MAX_KWADRAT-2){
            if (czyPierwsza(i) && czyPierwsza(j)){
                pierwsza[i][j]=true;
            }
        }
    }
}

void ustalW(){
    REP(i,MAX_SUMA){
        REP(j,MAX_KWADRAT){
            if (pierwsza[i][j]){
                w[i][j][0]++;
            }
        }
    }
    FOR(p,1,MAX_CYFR-1){
        REP(i,MAX_SUMA-2){
            REP(j,MAX_KWADRAT-2){
                REP(k,10){
                    if (i+k<MAX_SUMA-2 && j+k*k < MAX_KWADRAT-2){
                        w[i][j][p]+=w[i+k][j+k*k][p-1];
                    }
                }
            }
        }
    }
}

LL daj(int c, int k, LL T){
    if (T<1){
        return pierwsza[c][k];
    }
    LL wyn=0;
    int wyk=0;
    int cyf=1;
    while (pot[wyk]<=T) wyk++;
    wyk--;
    while (cyf*pot[wyk]<=T) cyf++;
    cyf--;
    wyn+=daj(c+cyf,k+cyf*cyf,T-cyf*pot[wyk]);
    if (wyk>-1){
        FOR(i,0,cyf-1){
            wyn+=w[c+i][k+i*i][wyk];
        }
    }
    return wyn;
}


int main(){
    ustalPot();
    ustalPierwsze();
    ustalW();
    int t;
    LL a,b;
    scanf("%d",&t);
    REP(i,t){
        scanf("%lld%lld",&a,&b);
        printf("%lld\n",daj(0,0,b)-daj(0,0,a-1));
    }
    return 0;
}