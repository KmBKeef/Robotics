#include <iostream> // Calliing the iostream library
#include <cmath>		// and the cmath library to help us with mathmatical functions
using namespace std;
/*
 * The Goal of this program is to create a virtual x-y graph 
 * for the movement of the robot which can be used to navigate
 * on the map via another program (interpitur) on the EV3 brain.
 *
 * With this virtual repressentation of the mapo this program 
 * will be able to find the shortest path possible between any
 * two points on the map.
 *
*/

int x, y;   		// These varibles are gointg to be used in order to detern=mine the (x,y)
								// coordinater of the points
int count = 0;  // counts stuff
int hight = 9;  // the scale of the map
int	length = 9; 
float nodes[9*9][4]; // this is a 2D array that will store the index of points in 
										//addition to their (x,y) values, their weight relativly to the end point and their label.
int cNode;				
int sy, sx; // the x,y values for the starting point
int ex, ey; // the x,y values for the last point.
int h, h2, j, g; // Random varibles used in loops.
int sCount, eCount;
int label = 1;
bool flag1 = false;
bool flag2 = false;

float weight(int a) {
	return sqrt((nodes[h2][0]-nodes[a][0])*(nodes[h2][0]-nodes[a][0])+(nodes[h2][1]-nodes[a][1])*(nodes[h2][1]-nodes[a][1])); // Calculates the weight of point 'a' relitevly to the end point
}

void destination() { // Input from the user (sx,sy,ex,ey).
	cout << "Enter the Starting point> \n[X]: " << flush; 
	cin >> sx; 
	cout << "[Y]: " << flush;
	cin >> sy;
	cout << "Enter the End point> \n[X]: " << flush;
	cin >> ex;
	cout << "[Y]: " << flush;
	cin >> ey;
}

void show() { // Prints out the content of nodes[][]. (For DEbuging)
	count = 0;
	for(x = 1; x <= hight; x++) {
		for(y = 1; y <= length; y++) {
			cout << "Count: " << count << " X: " << nodes[count][0] << " Y: " << nodes[count][1] << " Weight: " << nodes[count][2] << " Label: " << nodes[count][3]<< endl;
			count++;
		}
	}
}

void assign() { // Assigns the x,y points of a line
	count = 0;
	for(x = 1; x < hight+1; x++) {
		for(y = 1; y < length+1; y++) {
			nodes[count][0] = x;
			nodes[count][1] = y;
			count++;
		}
	}
}

void quickSort(int arr[], int left, int right) { 
	
	// A sorting algorathim used to find the nearest point with the lowest weight.
	
	int b = left; int e = right; float tmp; float pivot = (nodes[arr[(left + right) / 2]][2]);

	while(b <= e) {

		count++;
		while (nodes[arr[b]][2] < pivot)
			b++;

		while (nodes[arr[e]][2] > pivot)
			e--;

		if (b <= e) {
			tmp = arr[b]; 
			arr[b] = arr[e];
			arr[e] = tmp;
			b++;
			e--;
		}
	};

	if (left < e) quickSort(arr, left, e); 

	if (b < right) quickSort(arr, b, right);
}

int light(int q) {

	// outputs the nearest point with the lightest weight
	
  int myarr[8];
  myarr[0] = (q+1);
  myarr[1] = (q-1);
	myarr[2] = (q+length);
	myarr[3] = (q+length+1);
	myarr[4] = (q+length-1);
	myarr[5] = (q-length);
	myarr[6] = (q-length+1);
	myarr[7] = (q-length-1);
	quickSort(myarr, 0, 7);
	
	//	for(x =0; x<8; x++) {
	//	cout << "Myarr[" << x <<"] = " << myarr[x] << " of Weight:" << nodes[myarr[x]][2]<< endl;
	//	}
	
	return myarr[0];
}


int main() {


	destination(); // takes the input
	assign(); // assigns the values

	h = 0;
	
	// the following h, and h2 loops find the corelating no. of the starting point and the end point.

	for(j = 0; j <= hight; j++) {   
		for(g = 0; g <= length; g++) {
			if(nodes[h][0] == sx && nodes[h][1] == sy) {
				cNode = h;
				nodes[h][3] = label;
				label++;
			}
			
			h++;

		}
	}


 h2 = 0;
	for(int wu = 0; wu <= hight; wu++) {
		for(int wy = 0; wy <= length; wy++) {
			if(nodes[h2][0] == ex && nodes[h2][1] == ey) {
				eCount = h2;
				flag2 = true;
				break;
			}
			if(flag2 == true)
			{break;}
			h2++;

		}
	}

	// Assignes weights.

	for(int z = 0; z < 81; z++ ) {

			nodes[z][2] =	weight(z);
	}

	// The following loop finds the shortest path and gives each point we need to cross a label.
	
	while(nodes[cNode][2] != 0) {

		nodes[light(cNode)][3] = label;
		cNode = light(cNode);
		label++;

	}


	// Now we simply output the points with labels. (Labels show the path to take)

	cout << "\n\n" << "==================================================\n"  << "The shortest path is:\n "<< endl;
	for(int u = 0; u < length*hight; u++) {
	
		if(nodes[u][3] != 0) {
		cout << "	Label:"  << nodes[u][3] << " X: "<<nodes[u][0] << " Y: " << nodes[u][1] << " Point: "<< u  << endl;
		}
	
	}
 
	cout << "\nThe end..............................\n" << endl;

	// TODO Support coordinates  x,y 1 and x,y 9

	return 0;
}
