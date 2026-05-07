#include "regiao.h"

Regiao criarRegiao(int x, int y, int u, int v) {
    Regiao r;
    r.sup_esq.x = x;
    r.sup_esq.y = y;
    r.inf_dir.x = u;
    r.inf_dir.y = v;
    return r;
}

Regiao intersecao(Regiao r1, Regiao r2) {
    Regiao r;

    r.sup_esq.x = (r1.sup_esq.x > r2.sup_esq.x) ? r1.sup_esq.x : r2.sup_esq.x;
    r.sup_esq.y = (r1.sup_esq.y < r2.sup_esq.y) ? r1.sup_esq.y : r2.sup_esq.y;

    r.inf_dir.x = (r1.inf_dir.x < r2.inf_dir.x) ? r1.inf_dir.x : r2.inf_dir.x;
    r.inf_dir.y = (r1.inf_dir.y > r2.inf_dir.y) ? r1.inf_dir.y : r2.inf_dir.y;

    return r;
}

int vazia(Regiao r) {
    return (r.sup_esq.x > r.inf_dir.x || r.inf_dir.y > r.sup_esq.y);
}