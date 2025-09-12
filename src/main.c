#include <stdio.h>
#include <stdint.h>
#include <string.h>

// prototypes (from convert.c)
void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);  // Fixed - no FILE* needed

int main(void) {
    printf("Program started!\n");
    FILE *infile = fopen("A1_tests.txt", "r");   // open test file
    FILE *outfile = fopen("output.txt", "w");    // open results file for writing

    if (infile == NULL) {
        printf("Error: could not open A1_tests.txt\n");
        return 1;
    }
    if (outfile == NULL) {
        printf("Error: could not open output.txt\n");
        return 1;
    }

    char line[256];
    int test_num = 1;
    int pass_count = 0, total_count = 0;

    while (fgets(line, sizeof(line), infile) != NULL) {

        // skip comments (#) and blank lines
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        char func[20], expected[65];
        uint32_t n;
        int base;
        
        // DIV_CONVERT AND SUB_CONVERT CASE - SAME INPUT FORMAT
        if (sscanf(line, "%s %u %d %s", func, &n, &base, expected) == 4) {
            char buffer[65];
            total_count++;

            if (strcmp(func, "div_convert") == 0) {
                div_convert(n, base, buffer);
            } else if (strcmp(func, "sub_convert") == 0) {
                sub_convert(n, base, buffer);
            } else {
                continue; // skip unknown functions
            }

            if (strcmp(buffer, expected) == 0) {
                fprintf(outfile, "Test %d: %s(%u, %d) -> Expected: \"%s\", Got: \"%s\" [PASS]\n",
                        test_num, func, n, base, expected, buffer);
                pass_count++;
            } else {
                fprintf(outfile, "Test %d: %s(%u, %d) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                        test_num, func, n, base, expected, buffer);
            }
            test_num++;
        }
        // PRINT TABLES CASE
        else if (sscanf(line, "%s %u", func, &n) == 2) {
            if (strcmp(func, "print_tables") == 0) {
                total_count++;
                fprintf(outfile, "Test %d: %s(%u)\n", test_num, func, n);
                
                // Redirect stdout to file temporarily
                FILE *old_stdout = stdout;
                stdout = outfile;
                print_tables(n);  // Now prints to file
                stdout = old_stdout;  // Restore stdout
                
                pass_count++; // assume pass since no expected value
                test_num++;
            }
        }
    }

    fprintf(outfile, "\nSummary: %d/%d tests passed\n", pass_count, total_count);
    fclose(infile);
    fclose(outfile);

    printf("Results written to output.txt\n");
    return 0;
}