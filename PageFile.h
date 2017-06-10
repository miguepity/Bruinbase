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


};
  
#endif
