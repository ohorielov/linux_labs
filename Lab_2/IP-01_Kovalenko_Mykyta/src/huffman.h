#include "stdio.h"

void determine_frequency(FILE *f);
void allocate_tree();
int read_header(FILE *f);
int write_header(FILE *f);
int read_bit(FILE *f);
int write_bit(FILE *f, int bit);
int flush_buffer(FILE *f);
int decode(const char* ifile, const char *ofile);
int encode(const char* ifile, const char *ofile);
int assert_round_trip(const char* ifile, const char* ofile, const char* rtfile);
void encode_character(FILE *fout, int character);
void build_tree();
void add_leaves();
int add_node(int index, int weight);
void finalise();
void init();
