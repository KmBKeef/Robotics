#include <iostream> 
#include <cmath>
using namespace std;

class Point {
	public: 
		int x, y, l;
		float w;
		bool b;
		Point(): b(false), l(0) {}
		Point(const Point& p): x(p.x), y(p.y), l(p.l), w(p.w), b(p.b) {}
		Point(const int _x, const int _y): x(_x), y(_y),l(0) {}
		void distance(int _x, int _y) {w = sqrt(pow(x-_x,2)+pow(y-_y,2));}
		bool operator!= (const Point &p) {return x != p.x || y != p.y; }
		bool operator== (const Point &p) {return x == p.x && y == p.y; }
		void print() const {cout << "	label:"  << l << " x: "<<x << " y: " <<y << " b:" << b << endl; }
};

#define MESH_WIDTH 9
#define MESH_HEIGHT 9

int main() {
	int proximity [8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
	Point mesh[MESH_WIDTH][MESH_HEIGHT]; 

	int sx=0,sy=0;
	int ex=0,ey=0;
	// Read the below from user input
	cout << "Enter the Starting point> \n[Start X]: " << flush; 
	cin >> sx; 
	cout << "[Start Y]: " << flush;
	cin >> sy;
	cout << "Enter the End point> \n[End X]: " << flush;
	cin >> ex;
	cout << "[End Y]: " << flush;
	cin >> ey;

	sx%=MESH_WIDTH;
	sy%=MESH_WIDTH;
	ex%=MESH_HEIGHT;
	ey%=MESH_HEIGHT;

	for (int x = 0 ; x < MESH_WIDTH; x++) {
		for (int y = 0; y < MESH_HEIGHT; y++) {
			mesh[x][y].x = x;
			mesh[x][y].y = y;
			mesh[x][y].distance(ex,ey);
		}
	}

	// Set the step cardinal of the starting point to 1
	mesh[sx][sy].l = 1;

	Point start = mesh[sx][sy];
	Point end = mesh[ex][ey];

	// Define un-walkable points
	mesh[3][3].b = true;
	mesh[3][4].b = true;
	mesh[5][7].b = true;
	mesh[7][7].b = true;
	mesh[7][6].b = true;
	mesh[6][7].b = true;
	mesh[8][6].b = true;
	mesh[5][8].b = true;

	// Start from the begging
	Point next = start;
	int l = 2;
	// Loop until we reach the end-point
	while(next != end) {
		Point closer = next;
		// Check the surrounding points and determine which one is closer to the end
		bool pivoted = false;
		for(auto one: proximity) {
			// Calculate the proximity point coordinates
			int x = one[0] + next.x;
			int y = one[1] + next.y;
			// Skip any points out of our mesh
			if(x < 0 || x > 8 || y <0 || y > 8) continue;
			if(!pivoted && (! mesh[x][y].b) && mesh[x][y].l == 0) {
				closer = mesh[x][y];
				pivoted = true;
			}
			// If the proximity piont is closer lets switch to it.
			//cout << "now on x=" << closer.x << " y=" << closer.y << endl;
			//cout << "mesh-xy x=" << x << " y=" << y << " w=" << mesh[x][y].w << endl;
			if((! mesh[x][y].b) && mesh[x][y].l == 0 && mesh[x][y].w < closer.w) {
			 	closer = mesh[x][y]; 
				//cout << "The above is a match" << endl;
			}
		}
		if(closer == next) {
			cout << "Failed to find a solution" << endl;
			break;
		}
		mesh[closer.x][closer.y].l = l;
		l++;
		next = closer; 
	}
	// Now we simply output the points with labels. (Labels show the path to take)
	cout << "\n\n" << "==================================================\n"  << "The shortest path is:\n "<< endl;

	cout << "X__0_1_2_3_4_5_6_7_8_"<< endl;
	for(int y=0; y<MESH_HEIGHT; y++) {
		cout << y << "_|";
		for(int x=0; x<MESH_WIDTH; x++) {
			auto point = mesh[x][y];
			if(point==start) cout << "s"; 
			else if (point==end) cout <<"e";
			else if (point.l > 0) cout << point.l %10;
			else if (point.b) cout << "x";
			else cout << ".";
			cout << "|";
		}
		cout << endl;
	}

	cout << "\n\nThe end..............................\n" << endl;
	return 0;
}
