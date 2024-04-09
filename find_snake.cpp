#include<iostream>
#include<vector>
#define N 60
using namespace std;
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
		if(0<=x+dx[i] && x+dx[i]<n && 0<=y+dy[i] && y+dy[i]<n && a[x+dx[i]][y+dy[i]]!='0'){
			dirs[countDir++]=i;
		}
	}

	int hx,hy,tx,ty;
    if(countDir==1){	// the position we randomly chosed is either the head or the tail
        hx=x;
        hy=y;
		int newDir=0;
		dirs[0]=-1;
		while(newDir!=-1){
			newDir=-1;
			for(int i=0;i<4 && newDir==-1;i++){
				if(i==dirs[0])continue;
				if(0<=x+dx[i] && x+dx[i]<n && 0<=y+dy[i] && y+dy[i]<n && a[x+dx[i]][y+dy[i]]!='0'){
					newDir=i;
					x+=dx[newDir];
					y+=dy[newDir];
					dirs[0]=3-newDir;
				}
			}
		}
		tx=x;
		ty=y;
    }else{				// the position we randomly chosed is neither the head nor the tail
        tx=x;
        ty=y;
		int newDir=0;
		for(int j=0;j<2;j++){
			newDir=0;
			while(newDir!=-1){
				newDir=-1;
				for(int i=0;i<4 && newDir==-1;i++){
					if(i==dirs[j])continue;
					if(0<=x+dx[i] && x+dx[i]<n && 0<=y+dy[i] && y+dy[i]<n && a[x+dx[i]][y+dy[i]]!='0'){
						newDir=i;
						x+=dx[newDir];
						y+=dy[newDir];
						dirs[j]=3-newDir;
					}
				}
			}
			if(j==0){
				hx=x;
				hy=y;
				x=tx;
				y=ty;
			}
		}
		tx=x;
		ty=y;
    }
	
	// determine who is the head and who is the tail
    if(a[hx][hy]-a[tx][ty]>0 || (a[hx][hy]-a[tx][ty]==0 && (hx>tx || (hx==tx && hy>ty)))){
		swap(hx,tx);
		swap(hy,ty);
    }

	// print the answer
	dirs[0]=-1;
	x=hx;
	y=hy;
	int newDir=0;
	while(newDir!=-1){
		newDir=-1;
		cout<<a[x][y];
		for(int i=0;i<4 && newDir==-1;i++){
			if(i==dirs[0])continue;
			if(0<=x+dx[i] && x+dx[i]<n && 0<=y+dy[i] && y+dy[i]<n && a[x+dx[i]][y+dy[i]]!='0'){
				newDir=i;
				x+=dx[newDir];
				y+=dy[newDir];
				dirs[0]=3-newDir;
			}
		}
	}
}
