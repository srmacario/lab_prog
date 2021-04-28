#include <bits/stdc++.h>

using namespace std;

struct aluno;
struct materia;
struct listaAluno;
struct listaMateria;
struct periodo;

//função melhorada pra fflush, fflush varia pra linux e windows
void clean_stdin(){
    int c;
    do{
        c = getchar();
    } while (c != '\n' and c != EOF);
}

struct aluno
{
    int id;
    char cpf[10];
    char nome[50];
    listaMateria *listMat = NULL;
    aluno *prox = NULL;
};

struct listaAluno
{
    listaAluno *prox = NULL;
    aluno *alu = NULL;
};

struct materia
{
    int id, cred;
    char nome[50], professor[50];
    materia *prox = NULL;
    listaAluno *listAlu = NULL;
};

struct listaMateria
{
    listaMateria *prox = NULL;
    materia *mat = NULL;
};

struct periodo
{
    char ano[10];
    aluno *periodoAlu = NULL;
    materia *periodoMat = NULL;
    periodo *prox = NULL;
};

periodo *buscarPer(periodo *inicio, char aux_ano[10])
{
    if (inicio == nullptr)
        return inicio;
    if (strcmp(inicio->ano, aux_ano) == 0)
        return inicio;
    return buscarPer(inicio->prox, aux_ano);
}

int inserirPer(periodo *&inicio, char aux_ano[10])
{
    if (buscarPer(inicio, aux_ano) != nullptr)
    {
        printf("O periodo ja esta cadastrado\n");
        return 0;
    }
    else
    {
        periodo *aux = (periodo *)malloc(sizeof(periodo));
        strcpy(aux->ano, aux_ano);
        aux->prox = inicio;
        inicio = aux;
        return 1;
    }
}

materia *buscarMatPer(materia *inicio, int id)
{
    if (inicio == NULL)
        return NULL;
    if (inicio->id == id)
        return inicio;
    return buscarMatPer(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico
}

aluno *buscarAluPer(aluno *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->id == id)
        return inicio;
    return buscarAluPer(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico
}

listaAluno *buscarAluMat(listaAluno *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->alu->id == id)
        return inicio;
    return buscarAluMat(inicio->prox, id); //não precisa de else, ja vai cair aqui automatico
}

listaMateria *buscarMatAlu(listaMateria *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->mat->id == id)
        return inicio;
    return buscarMatAlu(inicio->prox, id); //não precisa de else, ja vai cair aqui automatico
}

int inserirAluPer(periodo *&per, int id_alu)
{
    if (buscarAluPer(per->periodoAlu, id_alu) != nullptr){
        printf("Aluno ja esta cadastrado\n");
        return 0;
    }
    else{
        aluno *aux = (aluno *)malloc(sizeof(aluno));
        aux->id = id_alu;
        printf("Digite o nome do aluno: ");
        scanf("%[^\n]s",aux->nome);
        clean_stdin();
        printf("Digite o cpf do aluno: ");
        scanf("%[^\n]s",aux->cpf);
        clean_stdin();
        aux->prox = per->periodoAlu;
        per->periodoAlu = aux;
        return 1;
    }
}

int inserirMatPer(periodo *&per, int id_mat)
{
    if (buscarMatPer(per->periodoMat, id_mat) != nullptr){
        printf("A materia ja esta cadastrada\n");
        return 0;
    }
    else{
        materia *aux = (materia *)malloc(sizeof(materia));
        aux->id = id_mat;
        printf("Digite o nome do materia:\n");
        scanf("%[^\n]s",aux->nome);
        clean_stdin();
        printf("Digite o nome do professor:\n");
        scanf("%[^\n]s",aux->professor);
        clean_stdin();
        printf("Digite o numero de creditos da materia:\n");
        scanf(" %d", &aux->cred);
        clean_stdin();
        aux->prox = per->periodoMat;
        per->periodoMat = aux;
        return 1;
    }
}

int main(){
    periodo *init = (periodo *)malloc(sizeof(periodo));
    // ini->tmp
    // cout << init->ano << "\n";
    //inserirAluPer(45,init);
    //cout << (buscarAluPer(init, 45)) -> id << "\n";
    //  inserirMatPer(32,init);

    // //Criar mat�ria
    // init->periodoMat = (materia*)malloc(sizeof(materia));
    // init->periodoMat->id = 1;
    // init->periodoMat->cred = 7;
    // init->periodoMat->nome = "Matem�tica";
    // init->periodoMat->professor = "Pepe";

    // //Criar aluno
    // init->periodoAlu = (aluno*)malloc(sizeof(aluno));
    // init->periodoAlu->id = 1;
    // init->periodoAlu->cpf = "06747288580";
    // init->periodoAlu->nome = "Aguiar";

    //Cadastras na mat�ria

    free(init);
}
