#include<iostream>
#include<vector>
using namespace std;
class Pos{
  private:
	int x;
	int y;
  public:
    Pos(int _x,int _y):x(_x),y(_y){};
	Pos operator+(Pos a);
	void setPos(Pos pos);
	char getChar(const vector<vector<char>>& a) const;	// get char in a at the position
	bool isSnake(const vector<vector<char>>& a) const;	// return whether the position is a part of snake
	static bool compare(Pos a,Pos b);					// return whether a is at the smaller position
};

class Board{
	static const vector<Pos> d;
	vector<vector<char>> a;
	int n;
	Pos now;
	Pos head;
	Pos tail;
  public:
	Board(vector<vector<char>> _a):
		a(_a),n(_a.size()),now(0,0),head(0,0),tail(0,0) {};
	void setPos(string s,Pos pos);			// set now, head, or tail to pos
	char getChar(Pos pos) const;			// get the char of pos
	bool isSnake(Pos pos) const;			// return whethere pos is a part of snake
	void oneStep(int dir);					// go one step (since we have found that there is another part of snake attaching to current position
	int tryOneStep(int oriDir,bool print);	// try if there is another part of snake attaching to current position
	void find(int oriDir,bool print);		// Randomly set to either head or tail
	void setEnds();							// Randomly set (head, tail) to either (real head, real tail) or (real tail, real head)
	bool compare(Pos a,Pos b);				// return whether a is at the smaller position
	void determineHead();					// set (head, tail) to (real head, real tail) (this work correctly only after calling the functions setEnds())
	void printSnake();						// print the snake after setting correct head and tail
};

Pos Pos::operator+(Pos a){
	return {x+a.x,y+a.y};
}

void Pos::setPos(Pos pos){
	x=pos.x;
	y=pos.y;
}

char Pos::getChar(const vector<vector<char>>& a) const{
	return a[x][y];
}

bool Pos::isSnake(const vector<vector<char>>& a) const{
	return (0<=x && x<a.size() && 0<=y && y<a.size()) && getChar(a)!='0';
}

bool Pos::compare(Pos a,Pos b){
	return a.x>b.x || (a.x==b.x && a.y>b.y);
}

const vector<Pos> Board::d={{1,0},{0,1},{0,-1},{-1,0}};

void Board::setPos(string s,Pos pos){
	if(s=="now"){
		now.setPos(pos);
	}else if(s=="head"){
		head.setPos(pos);
	}else if(s=="tail"){
		tail.setPos(pos);
	}else{
		cout<<"ERROR \"setting wrong pos\""<<endl;
	}
}

char Board::getChar(Pos pos) const{
	return pos.getChar(a);
}

bool Board::isSnake(Pos pos) const{
    return pos.isSnake(a);
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

void Board::setEnds(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(a[i][j]!='0'){
				Pos pos(i,j);
				setPos("now",pos);
				break;
			}
		}
	}
	
	vector<int> dirs={-1,-1};
	int countDir=0;
	for(int i=0;i<4;i++){
		if(isSnake(now+d[i])){
			dirs[countDir++]=i;
		}
	}

    if(countDir==1){	// the position we randomly chosed is either the head or the tail
		setPos("tail",now);
		find(-1,false);
		setPos("head",now);
    }else{				// the position we randomly chosed is neither the head nor the tail
		setPos("tail",now);
		find(dirs[0],false);
		setPos("head",now);
		now=tail;
		find(dirs[1],false);
		setPos("tail",now);
    }
}

bool Board::compare(Pos a,Pos b){
	return Pos::compare(a,b);
}

void Board::determineHead(){
    if(getChar(head)-getChar(tail)>0 || (getChar(head)==getChar(tail) && compare(head,tail)) ){
		swap(head,tail);
    }
}

void Board::printSnake(){
	now=head;
	find(-1,true);
}

int main(){
	int n;
	cin>>n;
	vector<vector<char>> a(n,vector<char>(n));

	int x,y;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>a[i][j];
		}
	}

	// initialize the board
	Board board(a);

	// find the two ends of the snake
	board.setEnds();

	// determine who is the head and who is the tail
	board.determineHead();

	// print the answer
	board.printSnake();
}
