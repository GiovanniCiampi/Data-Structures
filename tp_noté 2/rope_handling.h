struct historic;

typedef struct historic * historic;

historic create_historic(rope r, historic h);
rope get_rope(historic h);
void push_sub_nodes_historic(historic h);
historic sub_rope_historic(historic h, int start, int length);
historic concat_historic(historic h);
historic balanced_concat_historic(historic h,rope r);
historic square_historic(historic h);
historic undo(historic h);
void print_historic(historic h);
void historic_draw(historic h, char * file_name, int mode);
void rope_draw(rope r, char * file_name, int mode);
void sub_append_case_historic(historic h);
void sub_sub_case_historic(historic h);
historic sub_rope_push_historic(historic h, int start, int length);
