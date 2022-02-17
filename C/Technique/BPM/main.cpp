#include <iostream>

#define BPM 130  // Beats Per Minute, 1초에 {BPM/60}개의 비트를 친다 -> 박자가 지나간다.
#define BEATS_PER_ONE_TIME 32  // {BEATS_PER_ONE_TIME}개의 비트가 1박자동안 지속된다.

using namespace std;

int main(){
    // float bps = (float)BPM/60;                  // beats_per_one_sec    1초에 몇비트
    // float tpb = (float)1/BEATS_PER_ONE_TIME;    // times_per_one_beat   1비트에 몇박
    // float tps = bps*tpb;                        // times_per_one_second 1초에 몇박
    // float spt = 1/tps;                          // seconds_per_one_time 1박자에 몇초
    
    // new
    float vps = (float)BPM/60;                  // bak_per_one_sec      1초에 몇박자
    float spb = 1.0/vps;                        // seconds_per_one_bak  1박자에 몇초
    float bpv = spb/BEATS_PER_ONE_TIME;         // seconds_per_one_beat 1비트에 몇초
    float _bpv = 1.0/bpv;                       // beats_per_one_second 1초에 몇비트 =! 몇노트
    cout << _bpv/4*60 << endl;
    return 0;
}