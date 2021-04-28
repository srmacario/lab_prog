#include <bits/stdc++.h>

using namespace std;

struct aluno;
struct materia;
struct listaAluno;
struct listaMateria;
struct periodo;

//função melhorada pra fflush, fflush varia pra linux e windows


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


//Precisa ser testada---------------------------------------------------
int aluPorMat(periodo *inicio, int id)
{
    materia *aux = buscarMatPer(inicio->periodoMat, id);
    listaAluno *alAtual = nullptr;
    if(aux == nullptr)
    {
        printf("Essa materia nao esta cadastrada neste periodo.\n");
        return 0;
    }
    else
    {
        printf("Alunos matriculados:\n");
        printf("ID\tNome\n");
        alAtual = aux->listAlu;
        while(alAtual != nullptr)
        {
            printf("%d\t%s\n", alAtual->alu->id, alAtual->alu->nome);
            alAtual = alAtual->prox;
        }
        return 1;
    }
}

listaAluno *buscarAluMat(listaAluno *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->alu->id == id)
        return inicio;
    return buscarAluMat(inicio->prox, id); //não precisa de else, ja vai cair aqui automatico
}

aluno *buscarAluPer(aluno *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->id == id)
        return inicio;
    return buscarAluPer(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico
}

aluno *buscarAnteriorAlu(aluno *inicio, int id){
    if (inicio == nullptr)
        return nullptr;
    if(inicio->prox == nullptr or inicio->prox->id == id)
        return inicio;
    return buscarAluPer(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico

}

listaMateria *buscarMatAlu(listaMateria *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->mat->id == id)
        return inicio;
    return buscarMatAlu(inicio->prox, id); //não precisa de else, ja vai cair aqui automatico
}

materia *buscarMatPer(materia *inicio, int id)
{
    if (inicio == NULL)
        return NULL;
    if (inicio->id == id)
        return inicio;
    return buscarMatPer(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico
}

periodo *buscarPer(periodo *inicio, char aux_ano[10])
{
    if (inicio == nullptr)
        return inicio;
    if (strcmp(inicio->ano, aux_ano) == 0)
        return inicio;
    return buscarPer(inicio->prox, aux_ano);
}

void clean_stdin(){
    int c;
    do{
        c = getchar();
    } while (c != '\n' and c != EOF);
}

//nao testado
int inserirAluMat(periodo *per)
{
    int id_alu = -1, id_mat = -1;
    listaAluno *aux_alu = (listaAluno *)malloc(sizeof(listaAluno));
    listaMateria *aux_mat = (listaMateria *)malloc(sizeof(listaMateria));
    printf("Digite o ID do aluno a ser matriculado:\n");
    scanf(" %d", &id_alu);
    aluno *a = buscarAluPer(per->periodoAlu, id_alu);
    if(a == nullptr)
    {
        printf("Esse aluno nao esta cadastrado neste periodo.\n");
        return 0;
    }
    printf("Digite o ID da materia:\n");
    scanf(" %d", &id_mat);
    materia *m = buscarMatPer(per->periodoMat, id_mat);
    if(m == nullptr)
    {
        printf("Essa materia nao esta cadastrada neste periodo.\n");
        return 0;
    }
    if(buscarAluMat(m->listAlu, id_alu) != nullptr)
    {
        printf("Este aluno ja esta matriculado\n");
        return 0;
    }
    aux_alu->prox = m->listAlu;
    m->listAlu = aux_alu;
    aux_alu->alu = a;

    aux_mat->prox = a->listMat;
    a->listMat = aux_mat;
    aux_mat->mat = m;

    return 1;
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
        aux->listMat = nullptr;
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
        aux->listAlu = nullptr;
        return 1;
    }
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

int menuMain()
{
    int opcao;
    printf("Escolha a opcao:\n");
    printf("1. Consultar periodo\n");
    printf("2. Inserir periodo\n");
    printf("3. Remover periodo\n");
    printf("0. Sair\n");

    scanf("%d", &opcao);
    return opcao;
}

int menuPer()
{
    int opcao;
    printf("voce esta consultando um periodo\n");
    printf("Escolha a opcao:\n");
    printf("1. Consultar dados de um aluno\n");
    printf("2. Consultar materias\n");
    printf("3. Inserir materia\n");
    printf("4. Remover materia\n");
    printf("0. Sair\n");

    scanf("%d", &opcao);
    return opcao;
}

int menuPerMat()
{
    int opcao;
    printf("Voce esta consultando uma materia\n");
    printf("Escolha a opcao:\n");
    printf("1. Consultar lista de alunos\n");
    printf("2. Inserir aluno\n");
    printf("3. Remover aluno\n");
    printf("0. Sair\n");

    scanf("%d", &opcao);
    return opcao;
}

int removeAluPer(periodo *&per, int id_alu){
    aluno *atual = buscarAnteriorAlu(per->periodoAlu, id_alu);
    if(atual == nullptr or atual->prox == nullptr){
        if(per->periodoAlu->id == id_alu){
            per->periodoAlu = per->periodoAlu->prox;
            return 1;
        }
        printf("Aluno não está na lista!");
        return 0;
    }
    atual -> prox = atual->prox->prox;
    return 1;
}





int main(){
    periodo *init = (periodo *)malloc(sizeof(periodo));
    init -> periodoAlu = nullptr;
    // ini->tmp
    // cout << init->ano << "\n";


    init->periodoAlu = nullptr;
    init->periodoMat = nullptr;


    inserirAluPer(init, 45);
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

    //------------------------------------

    init->prox = nullptr;
    inserirMatPer(init, 1);
    inserirAluPer(init, 50);

    /*init->periodoMat->listAlu = (listaAluno *)malloc(sizeof(listaAluno));
    init->periodoMat->listAlu->alu = init->periodoAlu;
    init->periodoMat->listAlu->prox = (listaAluno *)malloc(sizeof(listaAluno));
    init->periodoMat->listAlu->prox->alu = init->periodoAlu->prox;
    init->periodoMat->listAlu->prox->prox = nullptr;*/
    inserirAluMat(init);
    inserirAluMat(init);

    aluPorMat(init, 1);
    //------------------------------------
    free(init);
}
