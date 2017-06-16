#include "Bruinbase.h"
#include "RecordFile.h"
#include <cstring>

using std::string;

RecordFile::RecordFile()
{
  erid.pid = 0;
  erid.sid = 0;
}

RecordFile::RecordFile(const string& filename, char mode)
{
  open(filename, mode);
}

RC RecordFile::open(const string& filename, char mode)
{
  RC   rc;
  char page[PageFile::PAGE_SIZE];

  if ((rc = pf.open(filename, mode)) < 0) return rc;
  
  erid.pid = pf.endPid();

  if (erid.pid == 0) {
    erid.sid = 0;
    return 0;
  }

  if ((rc = pf.read(--erid.pid, page)) < 0) {
    erid.pid = erid.sid = 0;
    pf.close();
    return rc;
  }

  erid.sid = getRecordCount(page);
  if (erid.sid >= RECORDS_PER_PAGE) {
    erid.pid++;
    erid.sid = 0;
  }
  
  return 0;
}

RC RecordFile::close()
{
  erid.pid = 0;
  erid.sid = 0;

  return pf.close();
}

RC RecordFile::read(const RecordId& rid, int& key, string& value) const
{
  RC   rc;
  char page[PageFile::PAGE_SIZE];
  
  if (rid.pid < 0 || rid.pid > erid.pid) return RC_INVALID_RID;
  if (rid.sid < 0 || rid.sid >= RecordFile::RECORDS_PER_PAGE) return RC_INVALID_RID;
  if (rid >= erid) return RC_INVALID_RID;
  
  if ((rc = pf.read(rid.pid, page)) < 0) return rc;

  readSlot(page, rid.sid, key, value);

  return 0;
}

RC RecordFile::append(int key, const std::string& value, RecordId& rid)
{
  RC   rc;
  char page[PageFile::PAGE_SIZE];

  if (erid.sid > 0) {
    if ((rc = pf.read(erid.pid, page)) < 0) return rc;
  } else {
    memset(page, 0, PageFile::PAGE_SIZE);
  }
    
  writeSlot(page, erid.sid, key, value);

  setRecordCount(page, erid.sid + 1);

  if ((rc = pf.write(erid.pid, page)) < 0) return rc;
    
  rid = erid;

  ++erid;

  return 0;
}

const RecordId& RecordFile::endRid() const
{
  return erid;
}

static int getRecordCount(const char* page)
{
  int count;
  memcpy(&count, page, sizeof(int));
  return count;
}

static void setRecordCount(char* page, int count)
{
  memcpy(page, &count, sizeof(int));
}

static char* slotPtr(char* page, int n) 
{
  return (page+sizeof(int)) + (sizeof(int)+RecordFile::MAX_VALUE_LENGTH)*n;
}

static void readSlot(const char* page, int n, int& key, std::string& value)
{
  char *ptr = slotPtr(const_cast<char*>(page), n);

  memcpy(&key, ptr, sizeof(int));

  value.assign(ptr + sizeof(int));
}

static void writeSlot(char* page, int n, int key, const std::string& value)
{
  char *ptr = slotPtr(page, n);

  memcpy(ptr, &key, sizeof(int));

  if ((int)value.size() >= RecordFile::MAX_VALUE_LENGTH) {
    memcpy(ptr + sizeof(int), value.c_str(), RecordFile::MAX_VALUE_LENGTH -1);
    *(ptr + sizeof(int) + RecordFile::MAX_VALUE_LENGTH - 1) = 0;
  } else {
    strcpy(ptr + sizeof(int), value.c_str());
  }
}
