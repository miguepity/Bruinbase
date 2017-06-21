#ifndef RECORDFILE_H
#define RECORDFILE_H

#include <string>
#include "PageFile.h"

typedef struct {
  PageId  pid;  
  int     sid;  
} RecordId;



RecordId& operator++ (RecordId& rid);
RecordId  operator++ (RecordId& rid, int);

bool operator> (const RecordId& r1, const RecordId& r2);
bool operator< (const RecordId& r1, const RecordId& r2);
bool operator>= (const RecordId& r1, const RecordId& r2);
bool operator<= (const RecordId& r1, const RecordId& r2);
bool operator== (const RecordId& r1, const RecordId& r2);
bool operator!= (const RecordId& r1, const RecordId& r2);
//
class RecordFile {
 public:


  static const int MAX_VALUE_LENGTH = 100;  


  static const int RECORDS_PER_PAGE = (PageFile::PAGE_SIZE - sizeof(int))/ (sizeof(int) + MAX_VALUE_LENGTH);  


  RecordFile();
  RecordFile(const std::string& filename, char mode);
  
  RC open(const std::string& filename, char mode);

  RC close();

  RC read(const RecordId& rid, int& key, std::string& value) const;

  RC append(int key, const std::string& value, RecordId& rid);

  const RecordId& endRid() const;

 private:
  PageFile pf;     
  RecordId erid;  
};

#endif // RECORDFILE_H
