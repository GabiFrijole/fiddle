#include<array>
#include<iostream>
#include<cassert>
#include<sstream>
#include<functional>
#include "common.h"

using namespace std;

#define NYI { cout<<"NYI "<<__LINE__<<"\n"; exit(44); }
#define nyi NYI

template<typename T>
string as_string(T t){
	stringstream ss;
	ss<<t;
	return ss.str();
}

template<unsigned X,unsigned Y,typename T>
class Array2{
	std::array<std::array<T,Y>,X> data;

	public:
	T& operator()(unsigned x,unsigned y){
		assert(x<X);
		assert(y<Y);
		return data[x][y];
	}

	T& operator[](pair<unsigned,unsigned> p){
		return (*this)(p.first,p.second);
	}
};

template<typename A,typename B>
ostream& operator<<(ostream& o,pair<A,B> p){
	return o<<"("<<p.first<<","<<p.second<<")";
}

template<unsigned X,unsigned Y>
void webpage(string title,string x_label,string y_label,Array2<X,Y,string> data){
	Tag a("html");
	{
		Tag b("head");
		Tag c("title");
		cout<<title;
	}
	Tag b("body");
	cout<<title<<"\n";
	Tag c("table border");
	{
		Tag a("tr");
		{
			Tag b("td colspan=2 rowspan=2");
		}
		Tag b("td colspan="+to_string(X));
		cout<<x_label;
	}
	{
		Tag a("tr");
		for(auto x:range(X)){
			Tag a("td");
			cout<<x;
		}
	}
	for(auto y:range(Y)){
		Tag a{"tr"};
		if(y==0){
			Tag a("td rowspan="+to_string(Y));
			cout<<y_label;
		}
		{
			Tag a("td");
			cout<<to_string(y);
		}
		for(auto x:range(X)){
			Tag a("td align=right");
			cout<<data(x,y);
		}
	}
}

template<typename A,typename B>
vector<pair<A,B>> cross(vector<A> va,vector<B> vb){
	vector<pair<A,B>> r;
	for(auto a:va) for(auto b:vb){
		r|=make_pair(a,b);
	}
	return r;
}

vector<pair<unsigned,unsigned>> options(unsigned cans_available,unsigned box_time,unsigned can_time){
	vector<pair<unsigned,unsigned>> r;
	static const unsigned MATCH_TIME=60*2+30;
	static const unsigned TELEOP_TIME=MATCH_TIME-15;
	unsigned max_cans=[=](){
		if(can_time){
			return min(cans_available,TELEOP_TIME/can_time);
		}
		return cans_available;
	}();
	for(unsigned cans:range(max_cans+1)){
		unsigned boxes=[=](){
			static const unsigned TOTAL_BOXES=70;
			if(box_time){
				return min(TOTAL_BOXES,(TELEOP_TIME-cans*can_time)/box_time);
			}
			return TOTAL_BOXES;
		}();
		r|=make_pair(boxes,cans);
	}
	return r;
}

template<typename Func,typename T>
auto mapf(Func f,vector<T> v)->vector<decltype(f(v[0]))>{
	vector<decltype(f(v[0]))> r;
	for(auto elem:v) r|=f(elem);
	return r;
}

template<typename T,typename Func>
T argmax(Func f,vector<T> v){
	assert(v.size());
	auto m=mapf([=](T t){ return make_pair(f(t),t); },v);
	return max(m).second;
}

pair<unsigned,unsigned> pts_at_cost(unsigned cans_available,unsigned box_time,unsigned can_time,unsigned max_stack_height,bool two_cans_per_stack){
	return argmax(
		[=](pair<unsigned,unsigned> p){ return max_pts(p.first,p.second,max_stack_height,two_cans_per_stack); },
		options(cans_available,box_time,can_time)
	);
}

static constexpr unsigned W=30,H=30;

enum class Mode{NORMAL,D_BOX,D_CAN,D_HEIGHT,D_CANS_PER_STACK,D_CAN_LIMIT};

Array2<W,H,string> gen_data(Mode mode,bool show_combo,bool two_cans_per_stack,unsigned max_stack_height,unsigned cans_available){
	Array2<W,H,string> a;
	for(auto p:cross(range(W),range(H))){
		/*a(0,0)="zero";
		a(0,1)="what";*/
		stringstream ss;
		//ss<<p;
		if(1){
			auto best_option=pts_at_cost(cans_available,p.second,p.first,max_stack_height,two_cans_per_stack);
			if(show_combo) ss<<best_option<<" ";
			int pts=max_pts(best_option.first,best_option.second,max_stack_height,two_cans_per_stack);
			switch(mode){
				case Mode::NORMAL:
					ss<<pts;
					break;
				case Mode::D_BOX:{
					auto b2=pts_at_cost(cans_available,p.second+1,p.first,max_stack_height,two_cans_per_stack);
					ss<<(pts-(int)max_pts(b2.first,b2.second,max_stack_height,two_cans_per_stack));
					break;
				}
				case Mode::D_CAN:{
					auto b2=pts_at_cost(cans_available,p.second,p.first+1,max_stack_height,two_cans_per_stack);
					ss<<(pts-(int)max_pts(b2.first,b2.second,max_stack_height,two_cans_per_stack));
					break;
				}
				case Mode::D_HEIGHT:{
					auto b2=pts_at_cost(cans_available,p.second,p.first,max_stack_height-1,two_cans_per_stack);
					ss<<(pts-(int)max_pts(b2.first,b2.second,max_stack_height-1,two_cans_per_stack));
					break;
				}
				case Mode::D_CANS_PER_STACK:{
					auto b2=pts_at_cost(cans_available,p.second,p.first,max_stack_height,!two_cans_per_stack);
					ss<<((int)max_pts(b2.first,b2.second,max_stack_height,!two_cans_per_stack)-pts);
					break;
				}
				case Mode::D_CAN_LIMIT:{
					auto b2=pts_at_cost(3,p.second,p.first,max_stack_height,two_cans_per_stack);
					ss<<(pts-(int)max_pts(b2.first,b2.second,max_stack_height,two_cans_per_stack));
					break;
				}
				default: assert(0);
			}
		}
		a[p]=ss.str();//to_string(p);
	}
	return a;
}

vector<string> args(int argc,char **argv){
	vector<string> r;
	for(int i=0;i<argc;i++) r|=string(argv[i]);
	return r;
}

template<typename T>
ostream& operator<<(ostream& o,vector<T> const& v){
	o<<"[ ";
	for(auto a:v) o<<a<<" ";
	return o<<"]";
}

int main(int argc,char **argv){
	Mode mode=Mode::NORMAL;
	bool show_combo=0;
	bool two_cans_per_stack=0;
	unsigned cans_available=7;
	typedef tuple<string,string,std::function<void(void)>> Option;
	vector<Option> options{
		make_tuple("box","Show the derivates by changing the time needed to stack a box",[&](){ mode=Mode::D_BOX; }),
		make_tuple("can","Show the derivates by changing the time needed to stack a can",[&](){ mode=Mode::D_CAN; }),
		make_tuple("height","Show the change in score when changing the max height by 1",[&]{ mode=Mode::D_HEIGHT; }),
		make_tuple("combo","Include in output how many cans and boxes were used",[&]{ show_combo=1; }),
		make_tuple("double_can","Assume that the robot is able to stack two cans on the same box",[&]{ two_cans_per_stack=1; }),
		make_tuple("d_double_can","Difference that a double can capability makes",[&]{ mode=Mode::D_CANS_PER_STACK; }),
		make_tuple("limit_cans","Make it so that only 3 cans are available rather than 7",[&]{ cans_available=3; }),
		make_tuple("d_can_limit","Show the different that going from 3 to 7 cans makes",[&]{ mode=Mode::D_CAN_LIMIT; })
	};
	unsigned max_stack_height=6;
	for(unsigned i=1;i<=6;i++){
		options|=Option(string("stack")+as_string(i),string("Limit stack height to ")+as_string(i),[&,i]{ max_stack_height=i; });
	}
	auto help=[&](){
		cout<<"Outputs HTML.  Options:\n";
		for(auto p:options){
			cout<<"\t--"<<get<0>(p)<<"\n\t\t"<<get<1>(p)<<"\n";
		}
		exit(0);
	};
	options|=Option("help","Print this message",help);
	for(int i=1;i<argc;i++){
		bool found=0;
		for(auto a:options){
			if(argv[i]=="--"+get<0>(a)){
				get<2>(a)();
				found=1;
			}
		}
		if(!found){
			help();
		}
	}
	auto a=gen_data(mode,show_combo,two_cans_per_stack,max_stack_height,cans_available);
	webpage(as_string(args(argc,argv)),"Time per can (seconds)","Time per box (seconds)",a);
}
