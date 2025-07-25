#include "Frontend.h"

#include <cstring>
#include <iostream>

int Frontend::create_table(char relname[ATTR_SIZE], int no_attrs, char attributes[][ATTR_SIZE], int type_attrs[]) {
  return Schema::createRel(relname, no_attrs, attributes, type_attrs);
}

int Frontend::drop_table(char relname[ATTR_SIZE]) {
  return Schema::deleteRel(relname);
}

int Frontend::open_table(char relname[ATTR_SIZE]) {
  // Schema::openRel
  return Schema::openRel(relname);
}

int Frontend::close_table(char relname[ATTR_SIZE]) {
  // Schema::closeRel
  return Schema::closeRel(relname);
}

int Frontend::alter_table_rename(char relname_from[ATTR_SIZE], char relname_to[ATTR_SIZE]) {
  // Schema::renameRel
  return Schema::renameRel(relname_from, relname_to);
}

int Frontend::alter_table_rename_column(char relname[ATTR_SIZE], char attrname_from[ATTR_SIZE],
                                        char attrname_to[ATTR_SIZE]) {
  // Schema::renameAttr
  return Schema::renameAttr(relname, attrname_from, attrname_to);
}

int Frontend::create_index(char relname[ATTR_SIZE], char attrname[ATTR_SIZE]) {
  // Schema::createIndex
  return Schema::createIndex(relname, attrname);
}

int Frontend::drop_index(char relname[ATTR_SIZE], char attrname[ATTR_SIZE]) {
  // Schema::dropIndex
  return Schema::dropIndex(relname, attrname);
}

int Frontend::insert_into_table_values(char relname[ATTR_SIZE], int attr_count, char attr_values[][ATTR_SIZE]) {
  return Algebra::insert(relname, attr_count, attr_values);
}

int Frontend::select_from_table(char relname_source[ATTR_SIZE], char relname_target[ATTR_SIZE]) {

  // Call appropriate project() method of the Algebra Layer

  // Return Success or Error values appropriately
  return Algebra::project(relname_source, relname_target);
}

int Frontend::select_attrlist_from_table(char relname_source[ATTR_SIZE],
  char relname_target[ATTR_SIZE],
  int attr_count,
  char attr_list[][ATTR_SIZE]) {

// Call appropriate project() method of the Algebra Layer

// Return Success or Error values appropriately
return Algebra::project(relname_source, relname_target, attr_count, attr_list);
}

int Frontend::select_from_table_where(char relname_source[ATTR_SIZE], char relname_target[ATTR_SIZE],
                                      char attribute[ATTR_SIZE], int op, char value[ATTR_SIZE]) {
  // Algebra::select
  return Algebra::select(relname_source, relname_target, attribute, op, value);
  //return SUCCESS;
}

int Frontend::select_attrlist_from_table_where(
  char relname_source[ATTR_SIZE], char relname_target[ATTR_SIZE],
  int attr_count, char attr_list[][ATTR_SIZE],
  char attribute[ATTR_SIZE], int op, char value[ATTR_SIZE]) {

    char temp[] = ".temp";  // Create a mutable copy of the string


  // Call select() method of the Algebra Layer with correct arguments to
  // create a temporary target relation with name ".temp" (use constant TEMP)
  int k = Algebra::select(relname_source, temp, attribute, op, value);

  // TEMP will contain all the attributes of the source relation as it is the
  // result of a select operation

  // Return Error values, if not successful
  if(k!=SUCCESS) return k;

  // Open the TEMP relation using OpenRelTable::openRel()
  // if open fails, delete TEMP relation using Schema::deleteRel() and
  // return the error code
  int z = OpenRelTable::openRel(temp);
  if(z<0 && z>=MAX_OPEN){
    Schema::deleteRel(temp);
    return z;
  } 

  // On the TEMP relation, call project() method of the Algebra Layer with
  // correct arguments to create the actual target relation. The final
  // target relation contains only those attributes mentioned in attr_list
  int zx = Algebra::project(temp, relname_target, attr_count, attr_list);

  // close the TEMP relation using OpenRelTable::closeRel()
  OpenRelTable::closeRel(z);
  // delete the TEMP relation using Schema::deleteRel()
  Schema::deleteRel(temp);

  // return any error codes from project() or SUCCESS otherwise
  return zx;
}

int Frontend::select_from_join_where(char relname_source_one[ATTR_SIZE], char relname_source_two[ATTR_SIZE],
                                     char relname_target[ATTR_SIZE],
                                     char join_attr_one[ATTR_SIZE], char join_attr_two[ATTR_SIZE]) {
  // Algebra::join
  return Algebra::join(relname_source_one, relname_source_two, relname_target, join_attr_one, join_attr_two);
}

int Frontend::select_attrlist_from_join_where(char relname_source_one[ATTR_SIZE], char relname_source_two[ATTR_SIZE],
                                              char relname_target[ATTR_SIZE],
                                              char join_attr_one[ATTR_SIZE], char join_attr_two[ATTR_SIZE],
                                              int attr_count, char attr_list[][ATTR_SIZE]) {
  // Algebra::join + project
  char temp[] = ".temp"; 
  // Call join() method of the Algebra Layer with correct arguments to
    // create a temporary target relation with name TEMP.
    int ret = Algebra::join(relname_source_one, relname_source_two, temp, join_attr_one, join_attr_two);

    // TEMP results from the join of the two source relation (and hence it
    // contains all attributes of the source relations except the join attribute
    // of the second source relation)

    // Return Error values, if not successful
    if(ret!=  SUCCESS) return ret;

    // Open the TEMP relation using OpenRelTable::openRel()
    int newrelid = OpenRelTable::openRel(temp);
    // if open fails, delete TEMP relation using Schema::deleteRel() and
    // return the error code
    if(newrelid<0 || newrelid>=MAX_OPEN) return newrelid;

    // Call project() method of the Algebra Layer with correct arguments to
    // create the actual target relation from the TEMP relation.
    // (The final target relation contains only those attributes mentioned in attr_list)
    ret = Algebra::project(temp, relname_target, attr_count, attr_list);

    // close the TEMP relation using OpenRelTable::closeRel()
    OpenRelTable::closeRel(newrelid);
    // delete the TEMP relation using Schema::deleteRel()
    Schema::deleteRel(temp);

    // Return Success or Error values appropriately
    return ret;
}

int Frontend::custom_function(int argc, char argv[][ATTR_SIZE]) {
  // argc gives the size of the argv array
  // argv stores every token delimited by space and comma

  // implement whatever you desire

  return SUCCESS;
}
