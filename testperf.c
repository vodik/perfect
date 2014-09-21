/*
 * ----------------------------------------------------------------------------
 * Test a perfect hash.
 * By Bob Jenkins.  Public Domain.
 * ----------------------------------------------------------------------------
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "phash.h"

/* user directives: perfect hash? minimal perfect hash? input is an int? */
struct hashform {
    enum {
        NORMAL_HM,                                        /* key is a string */
        INLINE_HM, /* user will do initial hash, we must choose salt for them */
        HEX_HM,          /* key to be hashed is a hexidecimal 4-byte integer */
        DECIMAL_HM,      /* key to be hashed is a hexidecimal 4-byte integer */
        AB_HM,  /* key to be hashed is "A B", where A and B are (A,B) in hex */
        ABDEC_HM                            /* same as AB_HM, but in decimal */
    } mode;
};
typedef  struct hashform hashform;

#define MAXKEYLEN  30
struct key {
    char *kname;
    uint32_t klen;
    struct key *knext;
};
typedef  struct key key;

/* get the list of keys */
static void getkeys(key **keys, uint32_t *nkeys)
{
    key  *mykey;
    char *mytext;
    mytext = malloc(MAXKEYLEN);
    *keys = (key*)0;
    *nkeys = (uint32_t)0;
    while (fgets(mytext, MAXKEYLEN, stdin)) {
        mykey = malloc(sizeof(key));
        mykey->kname = (char *)mytext;
        mytext = malloc(MAXKEYLEN);
        mykey->klen = (uint32_t)(strlen((char*)mykey->kname) - 1);
        mykey->knext = *keys;
        *keys = mykey;
        ++*nkeys;
    }
    free(mytext);
}

/*
 * ------------------------------------------------------------------------------
 * Read in the keys, find the hash, and write the .c and .h files
 * ------------------------------------------------------------------------------
 */
static void driver(hashform *form)
{
    uint32_t nkeys;    /* number of keys */
    key *keys;     /* head of list of keys */
    key *mykey;

    /* read in the list of keywords */
    getkeys(&keys, &nkeys);
    printf("Read in %d keys\n", nkeys);

    for (mykey = keys; mykey; mykey = mykey->knext) {
        uint32_t hash;
        uint32_t i;
        uint32_t a;
        uint32_t b;
        switch (form->mode) {
        case NORMAL_HM:
            hash = phash(mykey->kname, mykey->klen);
            break;
        case INLINE_HM:
            hash = PHASHSALT;
            for (i = 0; i < mykey->klen; ++i) {
                hash = (mykey->kname[i] ^ hash) + ((hash << 26) + (hash >> 6));
            }
            hash = phash(hash);
            break;
        case HEX_HM:
            sscanf(mykey->kname, "%x ", &hash);
            hash = phash(hash);
            break;
        case DECIMAL_HM:
            sscanf(mykey->kname, "%d ", &hash);
            hash = phash(hash);
            break;
        case AB_HM:
            sscanf(mykey->kname, "%x %x ", &a, &b);
            hash = phash(a, b);
            break;
        case ABDEC_HM:
            sscanf(mykey->kname, "%d %d ", &a, &b);
            hash = phash(a, b);
            break;
        }
        printf("%8d  %.*s\n", hash, mykey->klen, mykey->kname);
    }
}


static void usage_error(void)
{
    printf("usage is the same as perfect (which see)\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    hashform form;
    char     *c;
    bool mode_given = false;

    form.mode = NORMAL_HM;

    /* let the user override the default behavior */
    switch (argc) {
    case 1:
        break;
    case 2:
        if (argv[1][0] != '-') {
            usage_error();
            break;
        }
        for (c = &argv[1][1]; *c != '\0'; ++c) switch (*c) {
            case 'n': case 'N':
            case 'i': case 'I':
            case 'h': case 'H':
            case 'd': case 'D':
            case 'a': case 'A':
            case 'b': case 'B':
                if (mode_given == true)
                    usage_error();
                switch (*c) {
                case 'n': case 'N':
                    form.mode = NORMAL_HM; break;
                case 'i': case 'I':
                    form.mode = INLINE_HM; break;
                case 'h': case 'H':
                    form.mode = HEX_HM; break;
                case 'd': case 'D':
                    form.mode = DECIMAL_HM; break;
                case 'a': case 'A':
                    form.mode = AB_HM; break;
                case 'b': case 'B':
                    form.mode = ABDEC_HM; break;
                }
                mode_given = true;
                break;
            case 'm': case 'M':
            case 'p': case 'P':
            case 'f': case 'F':
            case 's': case 'S':
                break;
            default:
                usage_error();
            }
        break;
    default:
        usage_error();
    }

    driver(&form);
    return 1;
}
