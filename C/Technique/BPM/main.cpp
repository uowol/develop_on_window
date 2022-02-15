#include <iostream>

#define BPM 130  // Beats Per Minute, 1초에 {BPM/60}개의 비트를 친다
#define BEATS_PER_ONE_TIME 32  // 하나의 박자는 {BEATS_PER_ONE_TIME}개의 비트로 이루어져있다.

using namespace std;

int main(){
    float bps = (float)BPM/60;                  // beats_per_one_sec    1초에 몇비트
    float tpb = (float)1/BEATS_PER_ONE_TIME;    // times_per_one_beat   1비트에 몇박
    float tps = bps*tpb;                        // times_per_one_second 1초에 몇박
    float spt = 1/tps;                          // seconds_per_one_time 1박자에 몇초
    cout << 60*tps/tpb << ", " << spt << endl;
    return 0;
}