#include "huffman.h"

int main(int argc, char *argv[]) {
    FILE *fp_in, *fp_out, *fp_table, *fp_encode;
    char filename[FILENAME_SIZE] = {0};
    unsigned int frequency[FREQUENCY_SIZE] = {0};

    fp_in = open_file(fp_in, filename, argc, argv);                     //get fp_in

    read_file(fp_in, frequency);                                        //import the file and fills frequency array

    print_table(frequency);                                             //print the code table

    fp_out = encoding(frequency, filename, fp_in, fp_out);              //Encode and save the encoded file

    fclose(fp_in);
    fclose(fp_out);

    fp_out = create_table(fp_out, filename, frequency);                 //create .table file and fill it
    calculate_bytes(frequency);                                         //calculate bytes before encode and after

    fclose(fp_out);
    clear_data(filename, frequency);                                    // clear data for decoding

    strcpy(filename, "compressed_text.txt.table");
    fp_table = file_for_decode(fp_table, filename, "r");    // open table
    strcpy(filename, "compressed_text.txt");
    fp_encode = file_for_decode(fp_encode, filename, "r");  // open encode

    read_table(fp_table, frequency);                                    //get table

    strcpy(filename, "after_decoded.txt");
    fp_out = file_for_decode(fp_out, filename, "w");        // create file for decode

    strcpy(filename, "compressed_text.txt.table");
    decoding(fp_encode, fp_out, filename);                              // decode file and write result
    calculate_bytes_after_decoding(frequency);                          // check bitstream

    fclose(fp_encode);
    fclose(fp_table);
    fclose(fp_out);

    return 0;
}