#include<iostream>
#include<vector>
using namespace std;

struct Pos{
	int x;
	int y;
	Pos operator+(Pos a);
	char getChar(const vector<vector<char>>& a) const;
};

struct Board{
	static const vector<Pos> d;
	vector<vector<char>> a;
	int n;
	Pos now;
	Pos head;
	Pos tail;
	Board(vector<vector<char>> _a,int x,int y):
		a(_a),n(_a.size()),now({x,y}),head({x,y}),tail({x,y}) {};
	char getChar(Pos pos) const;
	bool isSnake(Pos pos) const;
	void oneStep(int dir);
	int tryOneStep(int oriDir,bool print);
	void find(int oriDir,bool print);
	void determineHead();
};

Pos Pos::operator+(Pos a){
	return {x+a.x,y+a.y};
}

char Pos::getChar(const vector<vector<char>>& a) const{
	return a[x][y];
}

const vector<Pos> Board::d={{1,0},{0,1},{0,-1},{-1,0}};

char Board::getChar(Pos pos) const{
	return pos.getChar(a);
}

bool Board::isSnake(Pos pos) const{
    return (0<=pos.x && pos.x<n && 0<=pos.y && pos.y<n) && getChar(pos)!='0';
}

void Board::oneStep(int dir){
	now=now+d[dir];
}

int Board::tryOneStep(int oriDir,bool print){
	if(print)cout<<getChar(now);
	int newDir=-1;
	for(int i=0;i<4 && newDir==-1;i++){
		if(i==oriDir)continue;
		if(isSnake(now+d[i])){
			newDir=i;
			oneStep(newDir);
		}
	}
	return newDir;
}

void Board::find(int oriDir,bool print){
	int newDir=0;
	while(newDir!=-1){
		newDir=tryOneStep(oriDir,print);
		oriDir=3-newDir;
	}
}

void Board::determineHead(){
    if(getChar(head)-getChar(tail)>0 || (getChar(head)==getChar(tail) && (head.x>tail.x || (head.x==tail.x && head.y>tail.y)))){
		swap(head,tail);
    }
}

int main(){
	int n;
	cin>>n;
	vector<vector<char>> a(n,vector<char>(n));

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

	Board board(a,x,y);

	vector<int> dirs={-1,-1};
	int countDir=0;
	for(int i=0;i<4;i++){
		if(board.isSnake(board.now+Board::d[i])){
			dirs[countDir++]=i;
		}
	}

    if(countDir==1){	// the position we randomly chosed is either the head or the tail
		board.find(-1,false);
		board.head=board.now;
    }else{				// the position we randomly chosed is neither the head nor the tail
		board.find(dirs[0],false);
		board.head=board.now;
		board.now=board.tail;
		board.find(dirs[1],false);
		board.tail=board.now;
    }
	
	// determine who is the head and who is the tail
	board.determineHead();

	// print the answer
	board.now=board.head;
	board.find(-1,true);
}
