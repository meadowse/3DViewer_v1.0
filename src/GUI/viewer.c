#include "viewer.h"

void cnt_of_vertexes_and_facets(FILE *obj_file, data_t *ptr) {
  int c = 0;
  int prev = '\n';
  int pre_prev = 0;
  while ((c = fgetc(obj_file)) != EOF) {
    if (prev == 'v' && pre_prev == '\n' && c == ' ') {
      ptr->vertex_cnt++;
    }
    if (prev == 'f' && pre_prev == '\n' && c == ' ') {
      ptr->facet_cnt++;
    }
    pre_prev = prev;
    prev = c;
  }
}

void fill_vertexes_array(data_t *ptr, FILE *obj_file) {
  int c = 0;
  int prev = '\n';
  int pre_prev = 0;
  int i = 0;
  ptr->vertexes_arr = malloc(sizeof(double) * ptr->vertex_cnt * 3);
  while ((c = fgetc(obj_file)) != EOF) {
    if (prev == 'v' && pre_prev == '\n' && c == ' ') {
      skip_spaces(obj_file);
      fscanf(obj_file, "%lf", &(ptr->vertexes_arr[i]));
      i++;
      skip_spaces(obj_file);
      fscanf(obj_file, "%lf", &(ptr->vertexes_arr[i]));
      i++;
      skip_spaces(obj_file);
      fscanf(obj_file, "%lf", &(ptr->vertexes_arr[i]));
      i++;
    }
    pre_prev = prev;
    prev = c;
  }
}

void fill_facets_array(data_t *ptr, FILE *obj_file) {
  int c = 0;
  int prev = '\n';
  int pre_prev = 0;
  size_t len = 0;
  char *str = NULL;
  unsigned ready_str[8];
  int arr_index = 0;
  ptr->facets_arr = malloc(6 * ptr->facet_cnt * sizeof(unsigned));
  while ((c = fgetc(obj_file)) != EOF) {
    if (prev == 'f' && pre_prev == '\n' && c == ' ') {
      getline(&str, &len, obj_file);
      for (int i = 0, j = 0; str[i] != '\0' && str[i] != '\n' && str[i] != '\r';
           i++) {
        if (str[i] == ' ') {
          continue;
        } else {
          sscanf(str + i, "%u", &(ready_str[j]));
          i++;
          j++;
          while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0' &&
                 str[i] != '\r') {
            i++;
          }
        }
      }
      ptr->facets_arr[arr_index] = ready_str[0] - 1;
      arr_index++;
      ptr->facets_arr[arr_index] = ready_str[1] - 1;
      arr_index++;
      ptr->facets_arr[arr_index] = ready_str[1] - 1;
      arr_index++;
      ptr->facets_arr[arr_index] = ready_str[2] - 1;
      arr_index++;
      ptr->facets_arr[arr_index] = ready_str[2] - 1;
      arr_index++;
      ptr->facets_arr[arr_index] = ready_str[0] - 1;
      arr_index++;
      c = fgetc(obj_file);
      pre_prev = '\n';
      prev = c;
    } else {
      pre_prev = prev;
      prev = c;
    }
  }
  ptr->facet_cnt = arr_index;
  free(str);
}

void skip_spaces(FILE *obj_file) {
  int c = ' ';
  while (c == ' ') {
    c = fgetc(obj_file);
  }
  ungetc(c, obj_file);
}

void move_x(data_t *obj, double offset) {
  for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
    if (i % 3 == 0) obj->vertexes_arr[i] += offset;
  }
}

void move_y(data_t *obj, double offset) {
  for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
    if (i % 3 == 1) obj->vertexes_arr[i] += offset;
  }
}

void move_z(data_t *obj, double offset) {
  for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
    if (i % 3 == 2) obj->vertexes_arr[i] += offset;
  }
}

void rotation_by_ox(data_t *obj, double angle) {
  double temp_y = 0;
  double temp_z = 0;
  for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
    if (i % 3 == 1) {
      temp_y = obj->vertexes_arr[i];
      temp_z = obj->vertexes_arr[i + 1];
      obj->vertexes_arr[i] = cos(angle) * temp_y - sin(angle) * temp_z;
    }
    if (i % 3 == 2)
      obj->vertexes_arr[i] = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void zoom(data_t *obj, double k) {
  for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
    obj->vertexes_arr[i] *= k;
  }
}

void rotation_by_oy(data_t *obj, double angle) {
  double temp_x = 0;
  double temp_z = 0;
  for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
    if (i % 3 == 0) {
      temp_x = obj->vertexes_arr[i];
      temp_z = obj->vertexes_arr[i + 2];
      obj->vertexes_arr[i] = cos(angle) * temp_x + sin(angle) * temp_z;
    }
    if (i % 3 == 2)
      obj->vertexes_arr[i] = sin(angle) * -temp_x + cos(angle) * temp_z;
  }
}
void rotation_by_oz(data_t *obj, double angle) {
  double temp_x = 0;
  double temp_y = 0;
  for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
    if (i % 3 == 0) {
      temp_x = obj->vertexes_arr[i];
      temp_y = obj->vertexes_arr[i + 1];
      obj->vertexes_arr[i] = cos(angle) * temp_x - sin(angle) * temp_y;
    }
    if (i % 3 == 1)
      obj->vertexes_arr[i] = sin(angle) * temp_x + cos(angle) * temp_y;
  }
}
