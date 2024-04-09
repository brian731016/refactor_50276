#include<iostream>
#include<vector>
#define N 60
using namespace std;

bool isSnake(int x,int y,vector<vector<char>> &a,int n){
    return (0<=x && x<n && 0<=y && y<n) && a[x][y]!='0';
}

void oneStep(int &x,int &y,int dir){
	static vector<int> dx={1,0,0,-1};
	static vector<int> dy={0,1,-1,0};
	x+=dx[dir];
	y+=dy[dir];
}

int tryOneStep(int &x,int &y,int oriDir,vector<vector<char>> &a,int n,bool print){
	static vector<int> dx={1,0,0,-1};
	static vector<int> dy={0,1,-1,0};
	if(print)cout<<a[x][y];
	int newDir=-1;
	for(int i=0;i<4 && newDir==-1;i++){
		if(i==oriDir)continue;
		if(isSnake(x+dx[i],y+dy[i],a,n)){
			newDir=i;
			oneStep(x,y,newDir);
		}
	}
	return newDir;
}

void find(int &x,int &y,int oriDir,vector<vector<char>> &a,int n,bool print){
	static vector<int> dx={1,0,0,-1};
	static vector<int> dy={0,1,-1,0};
	int newDir=0;
	while(newDir!=-1){
		newDir=tryOneStep(x,y,oriDir,a,n,print);
		oriDir=3-newDir;
	}
}

void determineHead(int &hx,int &hy,int &tx,int &ty,vector<vector<char>> &a){
    if(a[hx][hy]-a[tx][ty]>0 || (a[hx][hy]-a[tx][ty]==0 && (hx>tx || (hx==tx && hy>ty)))){
		swap(hx,tx);
		swap(hy,ty);
    }
}

int main(){
	int n;
	vector<vector<char>> a;

	cin>>n;
	a=vector<vector<char>>(n,vector<char>(n));

	int x,y;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>a[i][j];
			if(a[i][j]!='0'){
				x=i;
				y=j;
			}
		}
	}

	vector<int> dx={1,0,0,-1};
	vector<int> dy={0,1,-1,0};
	vector<int> dirs={-1,-1};
	int countDir=0;
	for(int i=0;i<4;i++){
		if(isSnake(x+dx[i],y+dy[i],a,n)){
			dirs[countDir++]=i;
		}
	}

	int hx,hy,tx,ty;
    if(countDir==1){	// the position we randomly chosed is either the head or the tail
        hx=x;
        hy=y;
		tx=x;
		ty=y;
		find(tx,ty,-1,a,n,false);
    }else{				// the position we randomly chosed is neither the head nor the tail
		hx=x;
        hy=y;
		find(hx,hy,dirs[0],a,n,false);
		tx=x;
		ty=y;
		find(tx,ty,dirs[1],a,n,false);
    }
	
	// determine who is the head and who is the tail
	determineHead(hx,hy,tx,ty,a);

	// print the answer
	x=hx;
	y=hy;
	find(hx,hy,-1,a,n,true);
}
