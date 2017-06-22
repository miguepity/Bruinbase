#include "BTreeNode.h"
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define L_PAIR_SIZE (sizeof(RecordId)+sizeof(int))
#define NL_PAIR_SIZE (sizeof(PageId)+sizeof(int))

BTLeafNode::BTLeafNode(){
    memset(buffer, '\0', PageFile::PAGE_SIZE);
 }

RC BTLeafNode::read(PageId pid, const PageFile& pf){ 
    
    return pf.read(pid, buffer);
}

RC BTLeafNode::write(PageId pid, PageFile& pf){
    
    return pf.write(pid, buffer);
}

int BTLeafNode::getKeyCount(){   
    int keyCounter=0;
    char* tmp=buffer;
 
    int curr;
    int i=4;

    while(i<1024){
        memcpy(&curr,tmp,sizeof(int));
        if(curr==0)
            break;
        
        keyCounter++;
        tmp+=L_PAIR_SIZE;
        i+=L_PAIR_SIZE;
    }

    if(keyCounter>1){
        memcpy(&curr,tmp-sizeof(int),sizeof(int));
        if(curr==0){
            memcpy(&curr,tmp-2*sizeof(int),sizeof(int));
            if(curr==0){
                keyCounter--;
            }
        }
    }

    return keyCounter;
}


int BTLeafNode::getMaxLlaves(){
    
    int parejas_maximas=floor((PageFile::PAGE_SIZE-sizeof(PageId))/(L_PAIR_SIZE));
    return parejas_maximas;
}