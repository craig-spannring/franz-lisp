/* ./alloc.c */
extern int debugin;
extern int bitmapi[BITLONGS];
extern double zeroq;
extern char *bbitmap;
extern double *qbitmap;
extern int bitmsk[32];
/* static struct types *spaces[NUMSPACES]; */
extern struct types *gcableptr[];
extern int get_more_space(struct types *type_struct, int purep);
extern int space_warn(int g);
extern struct atom *newatom(int pure);
extern char *newstr(int purep);
/* static char *Iinewstr(char *s, int purep); */
extern char *inewstr(char *s);
extern char *pinewstr(char *s);
extern int printall;
extern int gc1(void);
extern long npages;
extern char *gethspace(int segsiz, int type);
extern int gcrebear(void);
extern char *xsbrk(int n);
extern char *ysbrk(int pages, int type);
extern int hashfcn(char *symb);
extern int myhook(void);
