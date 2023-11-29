#ifndef SRC_GUI_VIEWER_H_
#define SRC_GUI_VIEWER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned vertex_cnt;
  unsigned facet_cnt;
  double *vertexes_arr;
  unsigned *facets_arr;
} data_t;

void cnt_of_vertexes_and_facets(FILE *obj_file, data_t *ptr);
void skip_spaces(FILE *obj_file);
void fill_vertexes_array(data_t *ptr, FILE *obj_file);
void fill_facets_array(data_t *ptr, FILE *obj_file);
void move_z(data_t *obj, double offset);
void move_y(data_t *obj, double offset);
void move_x(data_t *obj, double offset);
void rotation_by_ox(data_t *obj, double angle);
void zoom(data_t *obj, double k);
void rotation_by_oz(data_t *obj, double angle);
void rotation_by_oy(data_t *obj, double angle);
#endif
