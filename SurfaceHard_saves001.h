/* 
 * File:   main.cpp
 * Author: Jahan
 *
 * Created on 2 juillet 2015, 23:34
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <vector>
#include  <iomanip>

using namespace std;

namespace b {
    const long maxX = 1200;
    const long maxY = 1200;
    const long sqsz = maxX*maxY;

    class World {
    public:
        
        clock_t begin;
        long h, l;
        bitset<sqsz> dat;

        vector<long> inputX;
        vector<long> inputY;

        vector<long> buff;
        vector<long> areaSize;

        long lakechain[sqsz];
        long lakesize[sqsz];

        World(void) {
            
             begin = clock();
            dat^=dat;
            buff.reserve(sqsz);
            
            cerr << "INIT CHAIN " << "  " << maxX << " " << maxY <<" endCo "<< co(maxX,maxY ) << endl;
            for (long i = 0; i < maxX-4; i++) {
                for (long j = 0; j < maxY-4; j++) {
                    lakechain[co(i, j)] = co(i, j);
                    lakesize[co(i, j)] = 0;
                    
                    //long debughim=3646;
                    //if(co(i,j)==debughim) cerr << debughim << " polong to -> " << lakechain[debughim];                     
                }
            }
        }

        long co(long x, long y) {
            long cc= (x + 1) + (y + 1) * (maxY + 2);
                        if(cc==0){  cerr<<" coord x y "<<x <<","<< y <<cc <<endl; exit(0); }
            return cc;
        }

        long findIdLake(long x, long y) {
            buff.clear();
            long c = co(x, y);
            //cerr << "finding " << c << "->" << lakechain[c]<<endl;
            while (c != lakechain[c]) {
                if(c==0){  cerr<<"  "<<c << "->" ;for (long i=0;i<buff.size();i++) std::cout << buff[i] << " P  "; cout<<endl; exit(0); }                
                
                buff.push_back(c);
                c = lakechain[c];
                
                
             //   clock_t end = clock();
             //   double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;    
             //   if(elapsed_secs > 0.5) cerr<<" "<< elapsed_secs << "  "<<c << "->" << lakechain[c]<<endl;
            }
            for(long i=0;i<buff.size();i++){
              //  cerr << "optFind " << buff[i] << "<-" << c;
                lakechain[buff[i]]=c;
            }
            //cerr<<endl;
            // clock_t end = clock();
            // double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            return c;
        }

        void putLakeSquare(long x, long y) {
            dat[co(x, y)] = true;            
            
            long root = -1;
            long me=co(x,y);
            long ts = 0;
            long ls = 0;
            long mesz = 1;
            if (dat[co(x, y - 1)]) {
                root = findIdLake(x, y - 1);
                mesz += lakesize[root];
                lakechain[me]=root;                
                me=root;
            }
            long idLeft=findIdLake(x - 1, y);
            if (dat[co(x - 1, y)] && idLeft != me) {
                mesz += lakesize[idLeft];
                lakechain[idLeft] = me;
            }
            lakesize[me] = mesz;

        }

        void putLine(string row, long numL) {
            for (long i = 0; i < row.length(); ++i) {
                char c = row[i];
                if (c == 'O') {
                    putLakeSquare(i, numL);
                }
            }
        //    long debughim=3646;
          //  cerr << debughim << " polong to -> " << lakechain[debughim]; 
        }
        
        long findSize(long x,long y){
            
                long root = findIdLake(x, y);
                //cout << setfill('0') << setw(2) << hex << " "<<inputX[cas]<<","<< inputY[cas]<<" is " << root << " " << dat[root] << endl;

                if (dat[root] == true)
                    return lakesize[root];
                else {
                    return 0;
                }       
            bitset<sqsz> ess;
            
            
            
        }

        void debug_prlong(bitset<sqsz> m) {
            for (long i = 0; i < l + 1; i++) {
                for (long j = 0; j < h; j++) {
                    cerr << m[co(i, j)] ? 'O' : '#';
                }
                cerr << endl;
            }
        }
        
        void debug_prlong(){
            
            for (long i = 0; i < h ; i++) {
                for (long j = 0; j < l; j++) {
                    cerr << dat[co(j,i)] ? 'O' : '#';
                }
                cerr << endl;
            }
            cout << "REF" << endl;
            for (long i = 0; i < h ; i++) {
                for (long j = 0; j < l; j++) {
                    cout << "|" << setfill('0') << setw(2) << hex << co(j,i) ;
                }
                cerr << endl;
            }              
            cout << "ROOTS " << endl;
            for (long i = 0; i < h; i++) {
                for (long j = 0; j < l; j++) {
                    cout << "|" << setfill('0') << setw(2) << hex << lakechain[co(j,i)] ;
                }
                cerr << endl;
            }     
            cout << "SIZE" << endl;
            for (long i = 0; i < h ; i++) {
                for (long j = 0; j < l; j++) {
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
long doContest() {
    World *w = new World;
    long L;
    cin >> L;
    cin.ignore();
    long H;
    cin >> H;
    cin.ignore();

    w->h = H;
    w->l = L;
    //  cerr << " read map " << endl;
                clock_t begin = clock();

    for (long i = 0; i < H; i++) {
        string row;
        cin >> row;
        //  cerr << row << endl;
        w->putLine(row, i);
        cin.ignore();
        
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;             
        cerr << "lect " << i <<"  t  " << elapsed_secs << endl;
   
    }
    long N;
    cin >> N;
    cin.ignore();
    for (long i = 0; i < N; i++) {
        long X;
        long Y;

        cin >> X >> Y;
        
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;      
        cerr << "findSize " << X <<"," << Y <<"  t  " << elapsed_secs << endl;
        long sz=w->findSize(X, Y);

        
        cin.ignore();
        cerr << sz << endl;
        cout << sz << endl;        
    }

}

void doLoopTime(){
                clock_t begin = clock();
                double last=0;
    while(true){
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;       
            
            if(elapsed_secs > last + 0.01){
                last= elapsed_secs;
                cout << " t " << elapsed_secs << endl;
            
            }
            
            if(elapsed_secs > 1.3) return;
    }
}

void doBasicTest() {
        World *w = new World;
    long L;
    L=6;
    long H;
    H=4;

    w->h = H;
    w->l = L;

    w->putLine("#OOO##",0);
    w->putLine("#O#O##",1);
    w->putLine("#OOOOO",2);
    w->putLine("####OO",3);
    

    
    //w->putInputCoord(0, 0);
   // w->putInputCoord(0, 1);
   // w->putInputCoord(2, 1);
   // w->putInputCoord(5, 4);
   // w->calcAllArea();
    
    w->debug_prlong();
cout << w->findSize(0,0) << endl;
cout << w->findSize(1,0) << endl;
cout << w->findSize(1,3) << endl;
cout << w->findSize(4,3) << endl;

}

int main() {
    //doBasicTest();
   doContest();
    //doLoopTime();
}
