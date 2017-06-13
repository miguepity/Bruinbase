#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "SqlEngine.h"


using namespace std;


extern FILE* sqlin;
int sqlparse(void);


RC SqlEngine::run(FILE* commandline)
{
  fprintf(stdout, "Bruinbase> ");

  
  sqlin = commandline;
  sqlparse();  
               

  return 0;
}

RC SqlEngine::select(int attr, const string& table, const vector<SelCond>& cond)
{
  RecordFile rf;   // RecordFile containing the table
  RecordId   rid;  // record cursor for table scanning

  RC     rc;
  int    key;     
  string value;
  int    count;
  int    diff;

  // open the table file
  if ((rc = rf.open(table + ".tbl", 'r')) < 0) {
    fprintf(stderr, "Error: table %s does not exist\n", table.c_str());
    return rc;
  }

  // scan the table file from the beginning
  rid.pid = rid.sid = 0;
  count = 0;
  while (rid < rf.endRid()) {
    // read the tuple
    if ((rc = rf.read(rid, key, value)) < 0) {
      fprintf(stderr, "Error: while reading a tuple from table %s\n", table.c_str());
      goto exit_select;
    }

    // check the conditions on the tuple
    for (unsigned i = 0; i < cond.size(); i++) {
      // compute the difference between the tuple value and the condition value
      switch (cond[i].attr) {
      case 1:
  diff = key - atoi(cond[i].value);
  break;
      case 2:
  diff = strcmp(value.c_str(), cond[i].value);
  break;
      }

      // skip the tuple if any condition is not met
      switch (cond[i].comp) {
      case SelCond::EQ:
  if (diff != 0) goto next_tuple;
  break;
      case SelCond::NE:
  if (diff == 0) goto next_tuple;
  break;
      case SelCond::GT:
  if (diff <= 0) goto next_tuple;
  break;
      case SelCond::LT:
  if (diff >= 0) goto next_tuple;
  break;
      case SelCond::GE:
  if (diff < 0) goto next_tuple;
  break;
      case SelCond::LE:
  if (diff > 0) goto next_tuple;
  break;
      }
    }

    // the condition is met for the tuple. 
    // increase matching tuple counter
    count++;

    // print the tuple 
    switch (attr) {
    case 1:  // SELECT key
      fprintf(stdout, "%d\n", key);
      break;
    case 2:  // SELECT value
      fprintf(stdout, "%s\n", value.c_str());
      break;
    case 3:  // SELECT *
      fprintf(stdout, "%d '%s'\n", key, value.c_str());
      break;
    }

    // move to the next tuple
    next_tuple:
    ++rid;
  }

  // print matching tuple count if "select count(*)"
  if (attr == 4) {
    fprintf(stdout, "%d\n", count);
  }
  rc = 0;

  // close the table file and return
  exit_select:
  rf.close();
  return rc;
}

RC SqlEngine::load(const string& table, const string& loadfile, bool index)
{
    RC temporal;
    RecordFile archivo_registro;
    fstream stream_archivo;
    int llave;
    string valor;
    RecordId id_record;
    string linea;
    BTreeIndex arbol;


    stream_archivo.open(loadfile.c_str(),fstream::in);

    if(!stream_archivo.is_open())
      fprintf(stderr,"Error %s\n",loadfile.c_str());


    if(archivo_registro.open(table + ".tbl", 'w'))
        return RC_FILE_OPEN_FAILED;


    if(index)
    {
        temporal=archivo_registro.append(llave,valor,id_record);
      int iterator=0;
      temporal=arbol.open(table + ".idx",'w');
      if(!temporal)
      {
        int iterator=0;

        while(getline(stream_archivo,linea))
        {
          temporal=parseLoadLine(linea,llave,valor);
          if(temporal)
            break;

          temporal=archivo_registro.append(llave,valor,id_record);
          if(temporal)
            break;

          temporal=arbol.insert(llave,id_record);
          if(temporal)
            break;
        }

        arbol.close();
      }
    }
    else{

      while(!stream_archivo.eof()){
          getline(stream_archivo, linea);


          temporal=parseLoadLine(linea, llave, valor);
          if(temporal)
              break;


          temporal=archivo_registro.append(llave, valor, id_record);
          if(temporal)
              break;
      }
    }


    stream_archivo.close();

    if(archivo_registro.close())
        return RC_FILE_CLOSE_FAILED;

    cout << "Se creo el archivo" << endl;
    if(index){
      cout << "Se creo el indice" << endl;
    }  
    return temporal;
  return 0;
}

RC SqlEngine::parseLoadLine(const string& linea, int& llave, string& value)
{
    const char *s;
    char        c;
    string::size_type loc;
    

    c = *(s = linea.c_str());
    while (c == ' ' || c == '\t') { c = *++s; }


    llave = atoi(s);


    s = strchr(s, ',');
    if (s == NULL) { return RC_INVALID_FILE_FORMAT; }


    do { c = *++s; } while (c == ' ' || c == '\t');
    

    if (c == 0) { 
        value.erase();
        return 0;
    }


    if (c == '\'' || c == '"') {
        s++;
    } else {
        c = '\n';
    }


    value.assign(s);
    loc = value.find(c, 0);
    if (loc != string::npos) { value.erase(loc); }

    return 0;
}
