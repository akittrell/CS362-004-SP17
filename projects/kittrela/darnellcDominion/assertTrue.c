#include "assertTrue.h"

int assertTrue (int left, int right, char *testNote){
    if(left == right){
        //printf("Assert Test Passed\n");
        return 1;
    }
    else{
        printf("Assert Test FAILED\n");
        printf("Left=%d, Right=%d, while testing %s\n", left, right, testNote);
        return 0;
    }
}
