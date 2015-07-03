/* 
 * File:   SurfaceHard_saves001.h
 * Author: Jahan
 *
 * Created on 3 juillet 2015, 12:43
 */

#ifndef SURFACEHARD_SAVES001_H
#define	SURFACEHARD_SAVES001_H


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <vector>
#include  <iomanip>

using namespace std;

namespace b {
    const int maxX = 1200;
    const int maxY = 1200;
    const int sqsz = maxX*maxY;

    class World {
    public:
        int h, l;
        bitset<sqsz> dat;

        vector<int> inputX;
        vector<int> inputY;

        vector<int> buff;
        vector<int> areaSize;

        int lakechain[sqsz];
        int lakesize[sqsz];

        World(void) {
            dat^=dat;
            for (int i = 0; i < maxX; i++) {
                for (int j = 0; j < maxY; j++) {
                    lakechain[co(i, j)] = co(i, j);
                    lakesize[co(i, j)] = 0;
                }
            }
        }

        int co(int x, int y) {
            return (x + 1) + (y + 1) * (l + 2);
        }

        int findIdLake(int x, int y) {
            buff.clear();
            int c = co(x, y);
            
            while (c != lakechain[c]) {
                buff.push_back(c);
                c = lakechain[c];
            }
            for(int i=0;i<buff.size();i++){
                lakechain[c]=c;
            }
            return c;
        }

        void putLakeSquare(int x, int y) {
            dat[co(x, y)] = true;            
            
            int root = -1;
            int ts = 0;
            int ls = 0;
            int mesz = 1;
            if (dat[co(x, y - 1)]) {
                root = findIdLake(x, y - 1);
                mesz += lakesize[root];

            }
            if (dat[co(x - 1, y)] && findIdLake(x - 1, y) != root) {
                if (root != -1) {
                    lakechain[root] = co(x, y);
                }

                root = findIdLake(x - 1, y);
                mesz += lakesize[root];
                
            }
            if(root!=-1)
                lakechain[root] = co(x, y);
            lakesize[co(x, y)] = mesz;

        }

        void putLine(string row, int numL) {
            for (int i = 0; i < row.length(); ++i) {
                char c = row[i];
                if (c == 'O') {
                    putLakeSquare(i, numL);
                }
            }
        }
        
        int findSize(int x,int y){
            
                int root = findIdLake(x, y);
                //cout << setfill('0') << setw(2) << hex << " "<<inputX[cas]<<","<< inputY[cas]<<" is " << root << " " << dat[root] << endl;

                if (dat[root] == true)
                    return lakesize[root];
                else {
                    return 0;
                }       
            bitset<sqsz> ess;
            
            
            
        }

        void debug_print(bitset<sqsz> m) {
            for (int i = 0; i < l + 1; i++) {
                for (int j = 0; j < h; j++) {
                    cerr << m[co(i, j)] ? 'O' : '#';
                }
                cerr << endl;
            }
        }
        
        void debug_print(){
            
            for (int i = 0; i < h ; i++) {
                for (int j = 0; j < l; j++) {
                    cerr << dat[co(j,i)] ? 'O' : '#';
                }
                cerr << endl;
            }
            cout << "REF" << endl;
            for (int i = 0; i < h ; i++) {
                for (int j = 0; j < l; j++) {
                    cout << "|" << setfill('0') << setw(2) << hex << co(j,i) ;
                }
                cerr << endl;
            }              
            cout << "ROOTS " << endl;
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                    cout << "|" << setfill('0') << setw(2) << hex << lakechain[co(j,i)] ;
                }
                cerr << endl;
            }     
            cout << "SIZE" << endl;
            for (int i = 0; i < h ; i++) {
                for (int j = 0; j < l; j++) {
                    cout << "|" << setfill('0') << setw(2) << hex << lakesize[co(j,i)] ;
                }
                cerr << endl;
            }                
        }
    };

}

using namespace b;

/*
 * 
 */
int doContest() {
    World *w = new World;
    int L;
    cin >> L;
    cin.ignore();
    int H;
    cin >> H;
    cin.ignore();

    w->h = H;
    w->l = L;
    //  cerr << " read map " << endl;
                clock_t begin = clock();

    for (int i = 0; i < H; i++) {
        string row;
        cin >> row;
        //  cerr << row << endl;
        w->putLine(row, i);
        cin.ignore();
        
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;             
        cerr << "lect " << i <<"  t  " << elapsed_secs << endl;
   
    }
    int N;
    cin >> N;
    cin.ignore();
    for (int i = 0; i < N; i++) {
        int X;
        int Y;

        cin >> X >> Y;
        int sz=w->findSize(X, Y);
        cin.ignore();
        cerr << sz << endl;
        cout << sz << endl;        
    }

}

void doBasicTest() {
        World *w = new World;
    int L;
    L=6;
    int H;
    H=4;

    w->h = H;
    w->l = L;

    w->putLine("#O#O##",0);
    w->putLine("#OOO##",1);
    w->putLine("####OO",2);
    w->putLine("####OO",3);
    

    
    //w->putInputCoord(0, 0);
   // w->putInputCoord(0, 1);
   // w->putInputCoord(2, 1);
   // w->putInputCoord(5, 4);
   // w->calcAllArea();
    
    //w->debug_print();
cout << w->findSize(0,0) << endl;
cout << w->findSize(1,0) << endl;
cout << w->findSize(1,3) << endl;
cout << w->findSize(4,3) << endl;

}

int main() {
    //doBasicTest();
    doContest();
}



#endif	/* SURFACEHARD_SAVES001_H */

