#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 10

struct data{
    char s[MAX_DATA][128];
};

void remove_space(char* s){
    char* d = s;
    do {
        while(*d == ' '){
            ++d;
        }
    } while(*s++ = *d++);   // !
}

void get_field(char* line, struct data *d, int end_idx){
    int idx = 0;

    char* token = strtok(line, ",");    // ! 

    do {
        strcpy(d->s[idx++], token);
    } while ( idx != end_idx && (token = strtok(NULL, ",")));
}

int main(){
    FILE * stream = fopen("demo.csv", "r");

    char line[128];
    while(fgets(line, 128, stream)){
        remove_space(line);
        
        struct data d;

        char* tmp = strdup(line);   // 새로운 메모리 할당 후 복제
        get_field(tmp, &d, MAX_DATA);

        printf("[%s] [%s] [%s]\n", d.s[0], d.s[1], d.s[2]);
        
        free(tmp);  // !
    }

    return 0;
}