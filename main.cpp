#include <iostream>
#include <cmath>

using namespace std;

class MathType {
public:
	char type;
	char way[10];
	};

class OldType {
public:
	int x,y,z;
	char p;
	};

MathType MathBase[9];
OldType Old[100];
int MathCol = 0;
int OldCol = 0;
int x,y,z; 

void Init() {
	for(int a=0;a<10;a++)
		MathBase[a].type='0';
	}

int St(int x, int y) {
	int res=x;
	for(int a=1;a<y;a++)
		res=res*x;
	return res;
	}

int TryIt(int x, int y, int bb) {	
	int res = x;
	for(int b=0;b<10;b++)
		if (MathBase[bb].way[b] != ' ')	{
			if (MathBase[bb].way[b]=='*') res *= y;
			if (MathBase[bb].way[b]=='/') if (y!=0) res /= y;
			if (MathBase[bb].way[b]=='+') res += y;
			if (MathBase[bb].way[b]=='-') res -= y;
			if (MathBase[bb].way[b]=='^') res = St(x,2);
			if (MathBase[bb].way[b]=='s') res = St(x,y);
			if (MathBase[bb].way[b]=='k') if (x!=0) res = int(pow(x,1./y));
			if (MathBase[bb].way[b]=='q') if (y!=0) res = int(pow(y,1./x));
			if (MathBase[bb].way[b]=='|') res = x|y;
			if (MathBase[bb].way[b]=='&') res = x&y;
			if (MathBase[bb].way[b]=='%') res = x%y;
			if (MathBase[bb].way[b]=='<') res = x << 1;
			if (MathBase[bb].way[b]=='>') res = x >> 1;
			if (MathBase[bb].way[b]=='[') res = x << 2;
			if (MathBase[bb].way[b]==']') res = x >> 2;
			if (MathBase[bb].way[b]=='{') res = x << y;
			if (MathBase[bb].way[b]=='}') res = x >> y;
			}
	return res;
	}

void CreatorOfWay(int x, int y, int z, int bb, char o) {
	cout<<"Создатель пути : ";
	char bbb[] = " */kq+-^s|<>[]{}&%";
	bool endc = false; bool endp;
	for(int a=0;a<18;a++) if (!endc)
		for(int b=0;b<18;b++) if (!endc)
			for(int c=0;c<18;c++) if (!endc)
				for(int d=0;d<18;d++) if (!endc) {
					for(int e=0;e<10;e++)
						MathBase[bb].way[e]=' ';
						endp=true;
						MathBase[bb].way[0]=bbb[a];
						MathBase[bb].way[1]=bbb[b];
						MathBase[bb].way[2]=bbb[c]; 
						MathBase[bb].way[3]=bbb[d];
						if (TryIt(x,y,bb) != z)
							endp=false;
						for (int ee=0;ee<OldCol;ee++)
							if (Old[ee].p = o) 
								if (TryIt(Old[ee].x,Old[ee].y,bb) != Old[ee].z)
									endp=false;
						if (endp) {
							endc=true; 
							cout<<"WIN";
							}
					}
	if (!endc)
		cout<<"FAIL";
	}

int FindIt(int x, int y, char typeop) {
	int ret = -1;
	for(int a=0;a<10;a++)
		if (MathBase[a].type==typeop)
			ret=TryIt(x,y,a);
	return ret;
	}

int main()
{
	char o; int res,res2;
	setlocale(0,"Rus");
	cout<<endl<<endl<<"Псевдонейронная сеть, которая учится математике :)"<<endl;
	cout<<"=================================================="<<endl<<endl;
	Init();
	while (true) {
		cout<<"\n\nВведите первое значение  : "; 
		cin>>x;
		cout<<"Введите второе значение  : ";
		cin>>y;
		cout<<"Введите оператор (1симв) : ";
		cin>>o;
		res=FindIt(x,y,o);
		cout<<"Получен ответ            : "<<res<<endl;
		cout<<"Введите правильный ответ : ";
		cin>>res2;
		if (res == res2) {
			cout<<"Логика подтверждена (win)";
			}
		else
    			if (res == -1) {
				for(int a=0;a<10;a++)
					if (MathBase[a].type=='0') {
		  				MathBase[a].type=o; 
	         				CreatorOfWay(x,y,res2,a,o);
	        				break;
	        				}
				}
			else {
				for(int a=0;a<10;a++)
					if (MathBase[a].type==o)
						CreatorOfWay(x,y,res2,a,o); 
						break;
				}
	OldCol++;
	Old[OldCol].x=x;
	Old[OldCol].y=y;
	Old[OldCol].z=res;
	Old[OldCol].p=o;
	}
}
