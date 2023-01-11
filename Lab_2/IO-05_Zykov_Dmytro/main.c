#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "huffman.h"

int main(int argc, char **argv)
{
	if (argc != 4) {
		printf("Usage: %s <input file> <output file> [-c|-d]\n" \
			"-c - compress\n" \
			"-d - decompress\n", argv[0]);
		return 1;
	}

	const char *input_filename = argv[1];
	int input_fd = open(input_filename, O_RDONLY);
	if (input_fd == -1) {
		fprintf(stderr, "Failed to open input file %s\n", input_filename);
		return 1;
	}

	const char *output_filename = argv[2];
	int output_fd = open(output_filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (output_fd == -1) {
		fprintf(stderr, "Failed to open output file %s\n", output_filename);
		close(input_fd);
		return 1;
	}

	const char *mode = argv[3];
	if (strncmp(mode, "-c", 2) == 0) {
		huffman_encode(input_fd, output_fd);
#ifdef DEBUG
		close(output_fd);

		output_fd = open(output_filename, O_RDONLY);
		int decoded_fd = open(".huf_test", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
		huffman_decode(output_fd, decoded_fd);

		lseek(decoded_fd, 0, SEEK_SET);
		ssize_t size = lseek(decoded_fd, 0, SEEK_END);
		lseek(decoded_fd, 0, SEEK_SET);
		char *decoded = (char *)malloc(size);
		read(decoded_fd, decoded, size);


		lseek(input_fd, 0, SEEK_SET);
		if (lseek(input_fd, 0, SEEK_END) != size) {
			printf("Test: Encoded incorrectly!\n");
		} else {
			lseek(input_fd, 0, SEEK_SET);
			char *original = (char *)malloc(size);
			read(input_fd, original, size);

			if (memcmp(decoded, original, size) == 0) {
				printf("Test: Encoded correctly!\n");
			} else {
				printf("Test: Encoded incorrectly!\n");
			}
			free(original);
		}
		
		close(decoded_fd);
		remove(".huf_test");
		free(decoded);
#endif // DEBUG
	} else if (strncmp(mode, "-d", 2) == 0) {
		huffman_decode(input_fd, output_fd);
	} else {
		printf("Unknown mode '%s'\nOnly allowed [-c|-d]\n"
			"-c - compress\n" \
			"-d - decompress\n", mode);
	}
	
	close(output_fd);
	close(input_fd);

	return 0;
}