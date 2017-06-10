#ifndef PAGEFILE_H
#define PAGEFILE_H

#include <string>
#include "Bruinbase.h"

typedef int PageId;

//escribir y leer a un archivo
class PageFile {
 public:

  static const int TAM_PAG = 1024;    // tamaño de pagina 1KB

  PageFile();
  PageFile(const std::string& filename, char mode);

    /**
   * open a file in read or write mode.
   * when opened in 'w' mode, if the file does not exist, it is created.
   * @param filename[IN] the name of the file to open
   * @param mode[IN] 'r' for read, 'w' for write
   * @return error code. 0 if no error
   */
  RC open(const std::string& filename, char mode);

  /**
   * close the file.
   * @return error code. 0 if no error
   */
  RC close();
  
  /**
   * read a disk page into memory buffer.
   * @param pid[IN] the page to read
   * @param buffer[OUT] pointer to memory buffer
   * @return error code. 0 if no error
   */
  RC read(PageId pid, void *buffer) const;
  
  /**
   * write the memory buffer to the disk page.
   * if (pid >= endPid()), the file is expanded such that
   * endPid() becomes (pid + 1).
   * @param pid[IN] page to write to
   * @param buffer[IN] the content to write
   * @return error code. 0 if no error
   */
  RC write(PageId pid, const void *buffer);
    
  /**
   * note the +1 part. The last page id in the file is actually endPid()-1.
   * that is, the last page can be read by "read(endPid()-1, buffer)".
   * @return the id of the last page in the file (+ 1)
   */
  PageId endPid() const;

};
  
#endif
