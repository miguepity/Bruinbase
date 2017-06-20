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