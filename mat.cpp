#include <bits/stdc++.h>

using namespace std;

struct aluno;
struct materia;
struct listaAluno;
struct listaMateria;
struct periodo;

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
};

materia *buscarMatPer(materia *inicio, int id)
{
    if (inicio == NULL)
        return NULL;
    if (inicio->id == id)
        return inicio;
    else
        return buscarMatPer(inicio->prox, id);
}

aluno *buscarAluPer(aluno *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->id == id)
        return inicio;
    else
        return buscarAluPer(inicio->prox, id);
}

listaAluno *buscarAluMat(listaAluno *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->alu->id == id)
        return inicio;
    else
        return buscarAluMat(inicio->prox, id);
}

listaMateria *buscarMatAlu(listaMateria *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->mat->id == id)
        return inicio;
    else
        return buscarMatAlu(inicio->prox, id);
}

int inserirAluPer(int id_alu, periodo *&per)
{
    if (buscarAluPer(per->periodoAlu, id_alu) != nullptr)
    {
        printf("Aluno ja esta cadastrado\n");
        return 0;
    }
    else
    {
        fflush(stdin);
        aluno *aux = (aluno *)malloc(sizeof(aluno));
        aux->id = id_alu;
        printf("Digite o nome do aluno:\n ");
        scanf("%[^\n]s",aux->nome);
        fflush(stdin);
        printf("Digite o cpf do aluno:\n ");
        scanf("%[^\n]s",aux->cpf);
        fflush(stdin);
        aux->prox = per->periodoAlu;
        per->periodoAlu = aux;
        return 1;
    }
}

int inserirMatPer(int id_mat, periodo *&per)
{
    if (buscarMatPer(per->periodoMat, id_mat) != nullptr)
    {
        printf("A materia ja esta cadastrada\n");
        return 0;
    }
    else
    {
        fflush(stdin);
        materia *aux = (materia *)malloc(sizeof(materia));
        aux->id = id_mat;
        printf("Digite o nome do materia:\n");
        scanf("%[^\n]s",aux->nome);
        fflush(stdin);
        printf("Digite o nome do professor:\n");
        scanf("%[^\n]s",aux->professor);
        fflush(stdin);
        printf("Digite o numero de creditos da materia:\n");
        scanf(" %d", &aux->cred);
        fflush(stdin);
        aux->prox = per->periodoMat;
        per->periodoMat = aux;
        return 1;
    }
}

int main()
{
    periodo *init = (periodo *)malloc(sizeof(periodo));
    // ini->tmp
    // cout << init->ano << "\n";
     inserirAluPer(45,init);
     inserirMatPer(32,init);

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
