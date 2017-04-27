#include "assertTrue.h"

int assertTrue (int left, int right, char *curFunction){
    if(left == right){
        //printf("Assert Test Passed\n");
        return 1;
    }
    else{
        printf("Assert Test FAILED\n");
        printf("Left=%d, Right=%d, while testing %s\n", left, right, curFunction);
        return 0;
    }
}
