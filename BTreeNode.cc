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

RC BTLeafNode::insertAndSplit(int key, const RecordId& rid, BTLeafNode& sibling, int& siblingKey){ 
    int keyCount=getKeyCount();

    if(getMaxLlaves()>keyCount+1)
        return RC_INVALID_ATTRIBUTE;

    if(sibling.getKeyCount()!=0)
        return RC_INVALID_ATTRIBUTE;

    
    int insertIndex;
    localizar(key,insertIndex);

    
    char* buffer2=(char*)malloc(2*(PageFile::PAGE_SIZE));
    memset(buffer2, '\0', (2*PageFile::PAGE_SIZE));

    
    memcpy(buffer2,buffer,insertIndex);

    
    memcpy(buffer2+insertIndex,&key,sizeof(int));
    memcpy(buffer2+insertIndex+sizeof(int),&rid,sizeof(RecordId));
    
    
    memcpy(buffer2+insertIndex+sizeof(int)+sizeof(RecordId),buffer+insertIndex,(PageFile::PAGE_SIZE-insertIndex));

    
    double dKey=keyCount+1;
    double first=ceil((dKey)/2);

    int splitIndex=first*L_PAIR_SIZE;

    
    memcpy(buffer,buffer2,splitIndex);

    
    memcpy(sibling.buffer,buffer2+splitIndex,PageFile::PAGE_SIZE+L_PAIR_SIZE-splitIndex);

    
    memset(buffer+splitIndex,'\0',PageFile::PAGE_SIZE-splitIndex);

    
    memset(sibling.buffer+(PageFile::PAGE_SIZE+L_PAIR_SIZE-splitIndex),'\0',splitIndex-L_PAIR_SIZE);

    
    free(buffer2);

    
    memcpy(&siblingKey,sibling.buffer,sizeof(int));
    
    return 0; 
}