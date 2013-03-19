/*
  ifs.h
*/
#include <stdio.h>

#ifndef _IFS_H_
#define _IFS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned int id; /* index of this vertex, starting from 0 */
    float x;         /* x component */
    float y;         /* y component */
    float z;         /* z component */
} VERTEX;

typedef struct {
    VERTEX* a;       /* first vertex */
    VERTEX* b;       /* second vertex */
    VERTEX* c;       /* third vertex */
} TRIANGLE;          /* triangle face in the right-hand orientation */

typedef struct {
    char* modelName;           /* Short Description of this model */
    unsigned int numVertices;  /* Number of vertices */
    VERTEX* vertices;          /* malloc'ed array of vertices */
    unsigned int numTriangles; /* Number of triangles */
    TRIANGLE* triangles;       /* malloc'ed array of triangles */
} IFS_DATA;

/*
  load a model from a file [filename] and return the data structure
  representing the object.
*/
IFS_DATA* load_ifs_file (const char* filename);

/*
  print a text summary of an IFS object [ifs_data] to an output stream [target]
*/
void print_ifs_summary(FILE* target, IFS_DATA* ifs_data);

/*
  free the memory used by an IFS object structure [ifs_data]
*/
void free_ifs_data(IFS_DATA** ifs_data);

#ifdef __cplusplus
}
#endif

#endif /* ifndef _IFS_H_ */
