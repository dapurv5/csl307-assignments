/*
 * ifs.c
 *
 *  Created on: 20-Sep-2011
 *      Author: apurv
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ifs.h"

#define UINTSIZE sizeof(unsigned int)
#define FLOATSIZE sizeof(float)

ssize_t read_uint32(int infd, unsigned int* uint_star) {
    if (read(infd, uint_star, UINTSIZE) == UINTSIZE) {
	return UINTSIZE;
    } else {
	fprintf(stderr, "Error reading size of a uint32 field\n");
	exit(-1);
    }
}

ssize_t read_float32(int infd, float* float_star) {
    if (read(infd, float_star, FLOATSIZE) == FLOATSIZE) {
        return FLOATSIZE;
    } else {
        fprintf(stderr, "Error reading size of a float32 field\n");
        exit(-1);
    }
}

ssize_t read_string32 (int infd, char** buf) {
    unsigned int mem_len = 0;
    read_uint32(infd, &mem_len);
    *buf = realloc(*buf, mem_len);
    if (mem_len == read(infd, *buf, mem_len)) {
	return mem_len;
    }
    else {
	fprintf(stderr, "Error reading a string32 field\n");
	exit(-1);
    }
}

IFS_DATA* load_ifs_file (const char* filename) {
    int infd;
    IFS_DATA* ifs_data = NULL;
    float version;
    char* ifstag = NULL;
    unsigned int i;
    unsigned int nVertices = 0;
    unsigned int nTriangles = 0;
    unsigned int tmp_Index = 0;

    if ((infd = open(filename, O_RDONLY)) < 2) {
	fprintf(stderr, "Error opening an input IFS file\n");
	exit(-1);
    }

    ifs_data = (IFS_DATA*) malloc(sizeof(IFS_DATA));
    ifs_data->modelName = NULL;
    ifs_data->numVertices = 0;
    ifs_data->vertices = NULL;
    ifs_data->numTriangles = 0;
    ifs_data->triangles = NULL;

    read_string32(infd, &ifstag);
    if (strcmp(ifstag, "IFS") != 0) {
	fprintf(stderr, "Not IFS filetype\n");
	exit(-1);
    }
    free(ifstag); ifstag = NULL;

    read_float32(infd, &version);
    if (version != 1.0) {
	fprintf(stderr, "Invalid version number: %f\n", version);
	exit(-1);
    }

    read_string32(infd, &(ifs_data->modelName));

    read_string32(infd, &ifstag);
    if (strcmp(ifstag, "VERTICES") != 0) {
	fprintf(stderr, "Not IFS filetype\n");
	exit(-1);
    }
    free(ifstag); ifstag = NULL;

    read_uint32(infd, &nVertices);
    ifs_data->numVertices = nVertices;

    ifs_data->vertices = (VERTEX*) malloc(nVertices * sizeof(VERTEX));
    for (i =0; i < ifs_data->numVertices; ++i) {
	ifs_data->vertices[i].id = i;
	read_float32(infd, &((ifs_data->vertices)[i].x));
	read_float32(infd, &((ifs_data->vertices)[i].y));
	read_float32(infd, &((ifs_data->vertices)[i].z));
    }

    read_string32(infd, &ifstag);
    if (strcmp(ifstag, "TRIANGLES") != 0) {
	fprintf(stderr, "Not IFS filetype\n");
	exit(-1);
    }
    free(ifstag); ifstag = NULL;

    read_uint32(infd, &nTriangles);
    ifs_data->numTriangles = nTriangles;

    ifs_data->triangles = (TRIANGLE*) malloc(nTriangles * sizeof(TRIANGLE));
    for (i =0; i < ifs_data->numTriangles; ++i) {
	read_uint32(infd, &tmp_Index);
	if (tmp_Index >= nVertices) {
	    fprintf(stderr, "Invalid Vertex index\n");
	    exit(-1);
	}
	ifs_data->triangles[i].a = &((ifs_data->vertices)[tmp_Index]);
	read_uint32(infd, &tmp_Index);
	if (tmp_Index >= nVertices) {
	    fprintf(stderr, "Invalid Vertex index\n");
	    exit(-1);
	}
	ifs_data->triangles[i].b = &((ifs_data->vertices)[tmp_Index]);
	read_uint32(infd, &tmp_Index);
	if (tmp_Index >= nVertices) {
	    fprintf(stderr, "Invalid Vertex index\n");
	    exit(-1);
	}
	ifs_data->triangles[i].c = &((ifs_data->vertices)[tmp_Index]);
    }

    if (close(infd) == -1) {
	fprintf(stderr, "Error closing an input IFS file\n");
	exit(-1);
    }

    return ifs_data;
}

void free_ifs_data(IFS_DATA** ifs_data) {
    if (ifs_data) {
	free((*ifs_data)->modelName);
	free((*ifs_data)->vertices);
	free((*ifs_data)->triangles);
    }
    free(*ifs_data);
    *ifs_data = NULL;
}

void print_ifs_summary(FILE* target, IFS_DATA* ifs_data) {
    unsigned int i;
    fprintf(target, "=====  IFS  SUMMARY  =====\n");
    fprintf(target, " Model name          : %s\n", ifs_data->modelName);
    fprintf(target, " Number of vertices  : %d\n", ifs_data->numVertices);
    for (i=0; i<ifs_data->numVertices; ++i) {
	fprintf(target, " v_%06d : (%8f, %8f, %8f)\n",
		ifs_data->vertices[i].id,
		ifs_data->vertices[i].x,
		ifs_data->vertices[i].y,
		ifs_data->vertices[i].z);
    }
    fprintf(target, " Number of triangles : %d\n", ifs_data->numTriangles);
    for (i=0; i<ifs_data->numTriangles; ++i) {
	fprintf(target, " t_%06d : (v_%06d, v_%06d, v_%06d)\n", i,
		(ifs_data->triangles[i].a)->id,
		(ifs_data->triangles[i].b)->id,
		(ifs_data->triangles[i].c)->id);
    }
    fprintf(target, "===== END OF SUMMARY =====\n");
}

