

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <time.h> 
#include <assert.h>
#include <unistd.h>

#define NYI {cout << "NYI " << __LINE__<<"\n"; exit(1);}
 

using namespace std;
/////////////////////////////////////////////////////////////////////////////

// Structures
//
// All Structures
/////////////////////////////////////////////////////////////////////////////
struct point{
	int x;
	int y;
};

struct list{
point pt;
point prev;
bool v;
};
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// operatior point
//
// allow the use of diffrent things with the structure point
/////////////////////////////////////////////////////////////////////////////
bool operator!=(point a,point b){
	return (a.x != b.x || a.y != b.y);
}
ostream&operator<<(ostream& o, point a){
	
	o<< a.x << "," << a.y << endl;

	return o;
}

bool operator==(point a,point b){
	return (a.x == b.x && a.y == b.y);
}
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// lastpointvalid
//
// returns true if the given point is not in the vector
/////////////////////////////////////////////////////////////////////////////
bool lastpointvalid(point p,vector<point> lp)
{
	bool valid = true;

	for (int i=0; i< (int)lp.size(); i++){
		if ( p == lp[i]){
			valid = false;
		}
	}
	return valid;
}


/////////////////////////////////////////////////////////////////////////////
// bounderies
//
// returns true if p is in the grid
/////////////////////////////////////////////////////////////////////////////
bool bounderies(point p){
	bool xvalid = p.x>=1 && p.x<=4;
	bool yvalid = p.y>=1 && p.y<=3;

	return xvalid && yvalid;
}

//////////////////////////////////////////////////////////////////////////////
// Walls
//
// returns true if p is not a wall
//////////////////////////////////////////////////////////////////////////////
bool Walls(point p){

	return !((p.y==1 && p.x==3) || (p.y==2 && p.x==3));

}

/////////////////////////////////////////////////////////////////////////////
// valid																   
//																		   
// returns true if p is not a wall or boundry                              
/////////////////////////////////////////////////////////////////////////////
bool valid(point p){
	return (Walls(p) && bounderies(p));
}

/////////////////////////////////////////////////////////////////////////////
// validpoint
//
// returns true if the given point is not a wall or boundry and has not been visited
/////////////////////////////////////////////////////////////////////////////
bool validpoint(vector<list> v,point q){
	int i;
	int max;
	bool p ;

	p=false;
	max = v.size();
	for(i=0; i<max; i++){
		if(v[i].pt == q){
			p = true;
			break;
		}
		
	}
	return valid(q) && !p;
}


/////////////////////////////////////////////////////////////////////////////
// [dir]p
//
// returns adjacent points
/////////////////////////////////////////////////////////////////////////////
point leftp(point p){
	return point{p.x - 1,p.y};
}

point rightp(point p){
	return point{p.x + 1,p.y};
}

point upp(point p){
	return point{p.x,p.y + 1};
}

point downp(point p){
	return point{p.x,p.y - 1};
}
/////////////////////////////////////////////////////////////////////////////
// nextp
//

//returns next point that has not been visited
////////////////////////////////////////////////////////////////////////////
int nextp(vector<list> v){
	int max;
	int i;

	max = v.size();

	for (i=0; i<max; i++){
		if( !v[i].v){
			break;
		}
	}
	assert(i<max);
	return i;
}
/////////////////////////////////////////////////////////////////////////////
// getpoint
//
// given a point will return a vector of points that are valid
/////////////////////////////////////////////////////////////////////////////
vector<point> getpoint(vector<list> v,point p){
	point a;
	point b;
	point c;
	point d;

	vector<point> validpoints;
	
	a = leftp(p);
	b = rightp(p);
	c = upp(p);
	d = downp(p);

	if(validpoint(v,a)){
		validpoints.push_back(a);		
	}

	if(validpoint(v,b)){
		validpoints.push_back(b);		
	}

	if(validpoint(v,c)){

		validpoints.push_back(c);		
	}

	if(validpoint(v,d)){
		validpoints.push_back(d);		
	}
	
	return validpoints; 

}

/////////////////////////////////////////////////////////////////////////////
//Find Point
//
//finds point
////////////////////////////////////////////////////////////////////////////
int findpoint(vector<list> v,point q){
	int max;
	int i;

	max = v.size();

	for (i=0; i<max; i++){
		if( v[i].pt == q){

			break;
		}
	}
	assert(i<max);
	return i;
}
string dir(point p, point q){
	string s;

	if(q.x < p.x){
	
		s = "Left";
	}
	else if(q.x > p.x){
	
		s = "Right";
	}
	else if(q.y < p.y){
		s = "Up";

	}	
	else if(q.y > p.y){
		s = "Down";
	}
	return s;
}
int  getnum(){
	string s;
	getline(cin,s);
	return atoi(s.c_str());
}
int main(){
	//declarations	
	int lineofvector;
	point p;
	point e;
	vector<list> info;
	vector<point> nextpoint;
	list log;
	point f;
	bool endpoint;
	int lastline;
	vector<point> path;
	string stringpx;
	string stringpy;
	string stringex;
	string stringey;
	int px = -15;
	int py = -15;
	int ex = -15;
	int ey = -15;
	int wtestx;
	int wtesty;
	int etestx;
	int etesty;
	

endpoint = false;
	/////////////////////////////////////////////////////////////////////////////
	//getline
	//
	//request for ints and then input it into a string
	////////////////////////////////////////////////////////////////////////////
	cout << "Insert an int between 1 and 4 for the start postion ""x"" " << endl;
	wtestx = getnum();
	cout << "Insert an int between 1 and 3 for the start postion ""y"" " << endl;
	wtesty = getnum();

	while((wtestx == 3 && wtesty ==  1) || (wtestx == 3 && wtesty == 2) || (wtestx < 1 && wtesty > 4) || (wtestx < 1 && wtesty > 3)) {

			cout << "You Values are invalid please try agian" << endl;
			cout << "Insert an int between 1 and 4 for the start postion ""x"" " << endl;
			wtestx = getnum();
			cout << "Insert an int between 1 and 3 for the start postion ""y"" " << endl;
			wtesty = getnum();
		
	}

	cout << "Insert an int between 1 and 4 for the end postion ""x"" " << endl;
	etestx = getnum();
	cout << "Insert an int between 1 and 3 for the end postion ""y"" " << endl;
	etesty = getnum();

       while((etestx == 3 && etesty ==  1) || (etestx == 3 && etesty == 2) || (etestx < 1 && etesty > 4) || (etestx < 1 && etesty > 3)){
	
			cout << "You Values are invalid please try agian" << endl;
			cout << "Insert an int between 1 and 4 for the start postion ""x"" " << endl;
			etestx = getnum();
			cout << "Insert an int between 1 and 3 for the start postion ""y"" " << endl;
			etesty = getnum();

	}


	//string to int conversions	
	px = wtestx;
	py = wtesty;
	ex = etestx;
	ey = etesty;
	//printing out values before assigning them to points
	cout << "getlined points:" << endl;
	cout << px << "," << py << endl;
	cout << ex << "," << ey << endl;
	
f.x = px - 1;//set
f.y = py - 1;//inital location for previus

p.x = px;//set
p.y = py;//location of start point

e.x = ex;//set
e.y = ey;//location of en/d point

log.prev = f; //sets a prev point 
log.pt = p; //set the original point
log.v = false; // set the visited to not visited
info.push_back(log); //Push the info to the vector of structures 


	while (!endpoint){
		lineofvector = nextp(info); //find the line of stored data that is next in line

		p = info[lineofvector].pt;//save that loacation that you want to go to going to

		nextpoint = getpoint(info,p); // set a vector to have all posable points that are legal
		
		
		for (unsigned int i = 0; i < nextpoint.size(); i++){//loop tell for the size of the vector nextpoint
			log.prev = p; //store prev point
			log.v = false; //set the visisted to not visited
			log.pt = nextpoint[i]; // the point that you are storing
			
			if(log.pt == e){
				endpoint = true;
			}

			info.push_back(log); // store all the stored point
		}
		
	
		info[lineofvector].v = true; // set the visited status to visited

	}

	cout << "PATH:" << endl << endl;

	lastline = findpoint(info,e);
	cout << lastline << "last line" << endl;
	while(lastline != 0){
		cout << info[lastline].prev << endl;
		path.push_back(info[lastline].pt);
		lastline = findpoint(info,info[lastline].prev);
		cout << lastline << "saved vector" << endl;
	}

	path.push_back(info[0].pt);

	for(int i = path.size() - 1; i > 0;i--){
		
		cout << dir(path[i],path[i-1]) << endl << endl;
	}
	
}
