#ifndef TPEDIDO_H_INCLUDED
#define NO_H_INCLUDED

typedef struct no NO; 
struct no {
    int chave;
    struct NO *fesq;
    struct NO *fdir;
    int altura;
};


#endif // NO_H_INCLUDED