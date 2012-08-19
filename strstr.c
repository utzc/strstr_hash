
#include <stdlib.h>
#include <stdio.h>

/* This implementation of strstr uses hashing to reduce the number of times 
 * str2 is compared to a substring of str1.
 *
 * Building the initial hashes of str2 and the first substring of
 * str1 is O(n). Assuming that the hashing is perfect and there are no 
 * collisions, str2 will only be compared to 0 or 1 substrings of str1,
 * so checking if str2 is a substring of str1 will be O(n). So, the
 * implementation as a whole will be O(n).
 *
 * The choice of hash function below is obviously not perfect so
 * this implementation will likely end up doing more comparisons
 * of str2 to substrings of str1 than necessary. A better hash function
 * would improve the run time of this algorithm (reduce the number of
 * times str2 is compared to a substring of str1).
 */
const char *
strstr(const char *str1, const char *str2)
{
    unsigned hash1=0, hash2=0;
    unsigned i, j, str2_len;

    for (i=0; str2[i] != '\0'; i++) {
        hash2 += (unsigned) str2[i];

        if (str1[i] == '\0') {
            /* str2 is longer, so it cannot be a substring. */
            return NULL;
        }

        hash1 += (unsigned) str1[i];
    }

    str2_len = i;

    for (i=0; str1[i] != '\0'; i++) {
        if (hash1 == hash2) {
            // Hashes match ... either we had a collision or the strings are
            // actually equal. We must compare the strings to find out.
            for (j=0; j < str2_len; j++) {
                if (str1[i+j] != str2[j]) {
                    break;
                }
            }
            if (j == str2_len) {
                return str1+i;
            }
        }

        if (str1[i+str2_len] == '\0') {
            // str2 is longer than all substrings of str1 left to check, so none
            // of the remaining substrings will match.
            return NULL;
        }

        // Update hash1 so it is the hash of the substring of str1 we will
        // check in the next iteration.
        hash1 = hash1 - ((unsigned)str1[i]) + ((unsigned)str1[i+str2_len]);
    }
}

int
main(int argc, char **argv)
{
    const char *match;

    if (argc < 3) {
        return 1;
    }

    match = strstr(argv[1], argv[2]);

    if (match) {
        printf("%s\n", match);
    } else {
        printf("NOT FOUND\n");
    }

    return 0;
}
