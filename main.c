#include "src/nauty2_8_9/gtools.h"
// #include "/Users/jim/Dropbox/Wayne State/Research/Graph Isomorphism/code/nauty/nauty2_8_9/showg.c"


static void
putam(FILE *f, graph *g, int linelength, boolean space, boolean triang,
      int m, int n)   /* write adjacency matrix */
{
    set *gi;
    int i,j;
    boolean first;

    for (i = 0, gi = (set*)g; i < n - (triang!=0); ++i, gi += m)
    {
        first = TRUE;
        for (j = triang ? i+1 : 0; j < n; ++j)
        {
            if (!first && space) putc(' ',f);
            else                 first = FALSE;
            if (ISELEMENT(gi,j)) putc('1',f);
            else                 putc('0',f);
        }
        putc('\n',f);
    }
}


int main(int argc, char *argv[]) {
    FILE *infile;
    int codetype;
    char * infilename;
    if (argc < 2){
        infilename = "../graphs/M-10.g6";
        // printf("Need to pass graph file name as CLI parameter!\n");
        // exit(1);
    } else {
        infilename = argv[1];
    }

    infile = opengraphfile(infilename,&codetype,FALSE,1);
    if (codetype != GRAPH6 && codetype != (GRAPH6+HAS_HEADER)){
        printf("Unsupported graph type %d encoutered.", codetype);
        exit(-1);
    }
    int m, n;
    graph *g = readg(infile, NULL, 0, &m, &n);
    fclose(infile);

    /* initialize and set options to default options */
    static DEFAULTOPTIONS_GRAPH(options);

    options.getcanon = TRUE;

    /* The following optional call verifies that we are linking
    to compatible versions of the nauty routines. */
    nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);

    int *lab, *ptn, *orbits;
    int lab_sz=0, ptn_sz=0, orbits_sz=0;

    DYNALLOC1(int,lab,lab_sz,n,"malloc");
    DYNALLOC1(int,ptn,ptn_sz,n,"malloc");
    DYNALLOC1(int,orbits,orbits_sz,n,"malloc");
    statsblk stats;

    graph *h;
    int h_sz;
    h = malloc(1);
    DYNALLOC2(graph, h, h_sz, m, n, "malloc");

    densenauty(g, lab, ptn, orbits, &options, &stats, m, n, h);

    // putam(stdout, h, 0, TRUE, FALSE, m, n);

    printf("Number of nodes: %lu\n", stats.numnodes);

    FREES(lab);
    FREES(ptn);
    FREES(orbits);
    FREES(g);

    return 0;
}