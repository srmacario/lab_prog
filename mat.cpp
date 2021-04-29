
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
    char cpf[20];
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

listaAluno *buscarAluMat(listaAluno *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->alu->id == id)
        return inicio;
    return buscarAluMat(inicio->prox, id); //não precisa de else, ja vai cair aqui automatico
}

listaAluno *buscarAnteriorAluMat(listaAluno *inicio, int id)
{
    //se a lista nao existir ou se quem for removido for o primeiro, retorna null
    if (inicio == nullptr or inicio->alu->id == id)
        return nullptr;
    //se for o ultimo da lista, ou o proximo for o aluno desejado, retorna o ponteiro atual
    if (inicio->prox == nullptr or inicio->prox->alu->id == id)
        return inicio;
    return buscarAnteriorAluMat(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico
}

aluno *buscarAluPer(aluno *inicio, int id)
{
    if (inicio == nullptr)
        return nullptr;
    if (inicio->id == id)
        return inicio;
    return buscarAluPer(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico
}

aluno *buscarAnteriorAluPer(aluno *inicio, int id)
{
    //se a lista nao existir ou se quem for removido for o primeiro, retorna null
    if (inicio == nullptr or inicio->id == id)
        return nullptr;
    //se for o ultimo da lista, ou o proximo for o aluno desejado, retorna o ponteiro atual
    if (inicio->prox == nullptr or inicio->prox->id == id)
        return inicio;
    return buscarAnteriorAluPer(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico
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

void clean_stdin()
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' and c != EOF);
}
//nao testado
void dadosAlu(periodo *per, int id_alu)
{
    aluno *aux = buscarAluPer(per->periodoAlu, id_alu);
    if (aux == nullptr)
    {
        printf("O aluno não está cadastrado\n");
        return;
    }

    printf("ID\tNome\tCPF\tLista de Materias\n");
    printf("%d\t", aux->id);
    printf("%s\t", aux->nome);
    printf("%s\t", aux->cpf);
    listaMateria *aux_listaMateria;
    aux_listaMateria = aux->listMat;
    while (aux_listaMateria != nullptr)
    {
        printf("%s/", aux_listaMateria->mat->nome);
        aux_listaMateria = aux_listaMateria->prox;
    }
    printf("\n");
    return;
}
void dadosMat(periodo *per, int id_mat)
{
    materia *aux = buscarMatPer(per->periodoMat, id_mat);
    if (aux == nullptr)
    {
        printf("A materia nao esta cadastrada\n");
        return;
    }
    printf("ID\tCreditos\tNome\tProfessor\tLista de alunos\n");
    printf("%d\t", aux->id);
    printf("%d\t", aux->cred);
    printf("%s\t", aux->nome);
    printf("%s\t", aux->professor);
    listaAluno *aux_listaAluno;
    aux_listaAluno = aux->listAlu;
    while (aux_listaAluno != nullptr)
    {
        printf("%s/", aux_listaAluno->alu->nome);
        aux_listaAluno = aux_listaAluno->prox;
    }
    printf("\n");
    return;
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
    if (a == nullptr)
    {
        printf("Esse aluno nao esta cadastrado neste periodo.\n");
        return 0;
    }
    printf("Digite o ID da materia:\n");
    scanf(" %d", &id_mat);
    materia *m = buscarMatPer(per->periodoMat, id_mat);
    if (m == nullptr)
    {
        printf("Essa materia nao esta cadastrada neste periodo.\n");
        return 0;
    }
    if (buscarAluMat(m->listAlu, id_alu) != nullptr)
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
    if (buscarAluPer(per->periodoAlu, id_alu) != nullptr)
    {
        printf("Aluno ja esta cadastrado\n");
        return 0;
    }
    else
    {
        aluno *aux = (aluno *)malloc(sizeof(aluno));
        aux->prox = nullptr;
        aux->id = id_alu;
        printf("Digite o nome do aluno:\n ");
        scanf(" %[^\n]s", aux->nome);
        clean_stdin();
        printf("Digite o cpf do aluno: ");
        scanf(" %[^\n]s", aux->cpf);
        clean_stdin();
        aux->prox = per->periodoAlu;
        per->periodoAlu = aux;
        aux->listMat = nullptr;
        return 1;
    }
}

int inserirMatPer(periodo *&per, int id_mat)
{
    if (buscarMatPer(per->periodoMat, id_mat) != nullptr)
    {
        printf("A materia ja esta cadastrada\n");
        return 0;
    }
    else
    {
        materia *aux = (materia *)malloc(sizeof(materia));
        aux->id = id_mat;
        printf("Digite o nome do materia:\n");
        scanf(" %[^\n]s", aux->nome);
        clean_stdin();
        printf("Digite o nome do professor:\n");
        scanf(" %[^\n]s", aux->professor);
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

void listarAluPer(periodo *inicio)
{
    printf("Lista de alunos cadastrados no periodo:\n");
    aluno *aux =inicio->periodoAlu;
    printf("ID\tNome do aluno\n");
    while(aux != nullptr)
    {
        printf("%d\t%s\n",aux->id,aux->nome);
    }

}
void listarMatPer(periodo *inicio)
{
    printf("Lista de materias cadastradas no periodo:\n");
    materia *aux = inicio->periodoMat;
    printf("ID\tNome da materia\n");
    while(aux != nullptr)
    {
        printf("%d\t%s\n",aux->id,aux->nome);
    }
}
void listarPer(periodo *inicio)
{
    printf("Periodos cadastrados:\n");
    while (inicio != nullptr)
    {
        printf("%s\n", inicio->ano);
        inicio = inicio->prox;
    }
}

int aluPorMat(periodo *inicio, int id)
{
    materia *aux = buscarMatPer(inicio->periodoMat, id);
    listaAluno *alAtual = nullptr;
    if (aux == nullptr)
    {
        printf("Essa materia nao esta cadastrada neste periodo.\n");
        return 0;
    }
    else
    {
        printf("Alunos matriculados:\n");
        printf("ID\tNome\n");
        alAtual = aux->listAlu;
        while (alAtual != nullptr)
        {
            printf("%d\t%s\n", alAtual->alu->id, alAtual->alu->nome);
            alAtual = alAtual->prox;
        }
        return 1;
    }
}

int matPorAlu(periodo *inicio, int id)
{
    aluno *aux = buscarAluPer(inicio->periodoAlu, id);
    listaMateria *matAtual = nullptr;
    if (aux == nullptr)
    {
        printf("Esse aluno nao esta cadastrado neste periodo.\n");
        return 0;
    }
    else
    {
        printf("Materias em que o aluno esta matriculado:\n");
        printf("ID\tMateria\t\tProf.\t\tCreditos Necessarios\n");
        matAtual = aux->listMat;
        while (matAtual != nullptr)
        {
            printf("%d\t%s\t\t%s\t\t%d\n", matAtual->mat->id, matAtual->mat->nome, matAtual->mat->professor, matAtual->mat->cred);
            matAtual = matAtual->prox;
        }
        return 1;
    }
}

int menuMain()
{
    int opcao;
    printf("Escolha a opcao:\n");
    printf("1. Listar peridos cadastrados\n");
    printf("2. Inserir periodo\n");
    printf("3. Remover periodo\n");
    printf("4. Consultar periodo\n");
    printf("0. Sair\n");

    scanf("%d", &opcao);
    return opcao;
}

int menuPer()
{
    int opcao;
    printf("voce esta consultando um periodo\n");
    printf("Escolha a opcao:\n");
    printf("1. Listar alunos cadastrados\n");
    printf("2. Listar materias cadastradas\n");
    printf("3. Inserir materia\n");
    printf("4. Remover materia\n");
    printf("5. Inserir aluno\n");
    printf("6. Remover aluno\n");
    printf("7. Consultar dados de um aluno\n");
    printf("8. Consultar materia\n");
    printf("0. Sair\n");

    scanf("%d", &opcao);
    return opcao;
}

int menuPerMat()
{
    int opcao;
    printf("Voce esta consultando uma materia\n");
    printf("Escolha a opcao:\n");
    printf("1. Dados da materia\n");
    printf("2. Consultar lista de alunos\n");
    printf("3. Inserir aluno\n");
    printf("4. Remover aluno\n");
    printf("0. Sair\n");

    scanf("%d", &opcao);
    return opcao;
}

int removeAluMat(materia *&mat, int id_alu)
{
    listaAluno *ant = buscarAnteriorAluMat(mat->listAlu, id_alu), *atual;

    //atual == nullptr: não existe lista ou preciso remover a head
    if (ant == nullptr)
    {
        //se a head não existir, não faz nada
        if (mat->listAlu == nullptr)
        {
            printf("Aluno não está na matéria!");
            return 0;
        }
        //head existe e quero remove-la, troco
        atual = mat->listAlu;
        mat->listAlu = atual->prox;
        free(atual);
        return 1;
    }
    //atual->prox == nullptr, chegou ao final e não achou
    else if (ant->prox == nullptr)
    {
        printf("Aluno não está na lista!");
        return 0;
    }
    //coloca o prox pra amontar para o proximo da lista
    atual = ant->prox;
    ant->prox = atual->prox;
    free(atual->prox);
    return 1;
}

int removeAluPer(periodo *&per, int id_alu)
{
    aluno *ant = buscarAnteriorAluPer(per->periodoAlu, id_alu), *atual;

    //atual == nullptr: não existe lista ou preciso remover a head
    if (ant == nullptr)
    {
        //se a head não existir, não faz nada
        if (per->periodoAlu == nullptr)
        {
            printf("Aluno não está na lista!");
            return 0;
        }
        atual = per->periodoAlu;
        //head existe e quero remove-la, troco
        //mantendo dois ponteiros, atual e anterior
        listaMateria *matAtual = atual->listMat, *matAnt = nullptr;
        while (matAtual != nullptr)
        {
            //remote o alu da lista de materia
            removeAluMat(matAtual->mat, id_alu);
            //faz o ponteiro que indica o inicio de listMat passar para o proximo
            atual->listMat = matAtual->prox;
            //faz o anterior apontar para o proximo, servindo de auxiliar
            matAnt = matAtual->prox;
            //libera a materia atual atual
            free(matAtual);
            //reatualiza os ponteiros atual e anterior para prosseguir
            matAtual = matAnt;
            matAnt = nullptr;
        }
        per->periodoAlu = atual->prox;
        free(atual);
        return 1;
    }
    //atual->prox == nullptr, chegou ao final e não achou
    else if (ant->prox == nullptr)
    {
        printf("Aluno não está na lista!");
        return 0;
    }
    //coloca o prox pra apontar para o proximo da lista
    atual = ant->prox;
    listaMateria *matAtual = atual->listMat, *matAnt = nullptr;
    while (matAtual != nullptr)
    {
        //remote o alu da lista de materia
        removeAluMat(matAtual->mat, id_alu);
        //faz o ponteiro que indica o inicio de listMat passar para o proximo
        atual->listMat = matAtual->prox;
        //faz o anterior apontar para o proximo, servindo de auxiliar
        matAnt = matAtual->prox;
        //libera a materia atual atual
        free(matAtual);
        //reatualiza os ponteiros atual e anterior para prosseguir
        matAtual = matAnt;
        matAnt = nullptr;
    }
    ant->prox = atual->prox;
    free(atual);
    return 1;
}

int main()
{
    periodo *init = (periodo *)malloc(sizeof(periodo));
    init->periodoAlu = nullptr;
    init->periodoMat = nullptr;

    int opcaoMain = -1;

    do
    {
        opcaoMain = menuMain();
        switch (opcaoMain)
        {
        case 1:
            listarPer(init);
            break;
        case 2:
            printf("Digite o periodo:(ex:2021-1)\n");
            char temp[10];
            scanf(" %[^\n]s", temp);
            clean_stdin();
            inserirPer(init, temp);
            break;
        case 3:
            break; // remover periodo
        case 4:
            printf("Escolha o periodo:\n");
            scanf(" %[^\n]s", temp);
            clean_stdin();
            periodo *aux_per = buscarPer(init, temp);
            if (aux_per == nullptr)
                printf("O periodo nao esta cadastrado\n");
            else
            {
                int opcaoPer = -1;
                do
                {
                    opcaoPer = menuPer();
                    switch (opcaoPer)
                    {
                    case 1:
                        listarAluPer(init);
                        break;
                    case 2:
                        listarMatPer(init);
                        break;
                    case 3:
                        printf("Insira o id da materia:\n");
                        int temp_id_mat;
                        scanf("%d", &temp_id_mat);
                        inserirMatPer(init, temp_id_mat);
                        break;
                    case 4:
                        break; //remover materia per
                    case 5:
                        printf("Insira o ID do aluno:\n");
                        int temp_id_alu;
                        scanf("%d", &temp_id_alu);
                        inserirAluPer(init, temp_id_alu);
                        break;
                    case 6:
                        printf("Insira o ID do aluno que deseja remover do periodo:\n");
                        scanf("%d", &temp_id_alu);
                        removeAluPer(init, temp_id_alu);
                        break; 
                    case 7:
                        printf("Insira o ID do aluno:\n");
                        scanf("%d", &temp_id_alu);
                        dadosAlu(init, temp_id_alu);
                        break;
                    case 8:
                        printf("Insira o ID da materia:\n");
                        scanf("%d", &temp_id_mat);
                        materia *aux = buscarMatPer(init->periodoMat, temp_id_mat);
                        if (aux == nullptr)
                            printf("A materia nao esta cadastrada\n");
                        else
                        {
                            int opcaoPerMat = -1;
                            do
                            {
                                opcaoPerMat = menuPerMat();
                                switch (opcaoPerMat)
                                {
                                case 1:
                                    dadosMat(init, temp_id_mat);
                                    break;
                                case 2:
                                    aluPorMat(init, temp_id_mat);
                                    break;
                                case 3:
                                    inserirAluMat(init);
                                case 4:
                                    printf("Insira o ID do aluno que deseja remover da materia:\n");
                                    scanf("%d", &temp_id_alu);
                                    removeAluMat(aux, temp_id_alu); //remover
                                    break;
                                }

                            } while (opcaoPerMat);
                        }
                    }

                } while (opcaoPer);
            }
        }

    } while (opcaoMain);
    free(init);
}