
#include <bits/stdc++.h>
#include <stdlib.h>

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

listaMateria *buscarAnteriorMatAlu(listaMateria *inicio, int id)
{
    //se a lista nao existir ou se quem for removido for o primeiro, retorna null
    if (inicio == nullptr or inicio->mat->id == id)
        return nullptr;
    //se for o ultimo da lista, ou o proximo for o aluno desejado, retorna o ponteiro atual
    if (inicio->prox == nullptr or inicio->prox->mat->id == id)
        return inicio;
    return buscarAnteriorMatAlu(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico
}

materia *buscarMatPer(materia *inicio, int id)
{
    if (inicio == NULL)
        return NULL;
    if (inicio->id == id)
        return inicio;
    return buscarMatPer(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico
}

materia *buscarAnteriorMatPer(materia *inicio, int id)
{
    //se a lista nao existir ou se quem for removido for o primeiro, retorna null
    if (inicio == nullptr or inicio->id == id)
        return nullptr;
    //se for o ultimo da lista, ou o proximo for o aluno desejado, retorna o ponteiro atual
    if (inicio->prox == nullptr or inicio->prox->id == id)
        return inicio;
    return buscarAnteriorMatPer(inicio->prox, id); // não precisa de else, ja vai cair aqui automatico
}

periodo *buscarPer(periodo *inicio, char aux_ano[20])
{
    if (inicio == nullptr)
        return inicio;
    if (strcmp(inicio->ano, aux_ano) == 0)
        return inicio;
    return buscarPer(inicio->prox, aux_ano);
}

periodo *buscarAnteriorPer(periodo *inicio, char aux_ano[20])
{
    if (inicio == nullptr or strcmp(inicio->ano, aux_ano) == 0)
        return nullptr;
    if (inicio->prox == nullptr)
        return inicio;
    if (strcmp(inicio->prox->ano, aux_ano) == 0)
        return inicio;
    return buscarAnteriorPer(inicio->prox, aux_ano);
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
        printf("O aluno com este ID não está cadastrado.\n");
        return;
    }

    printf("ID\tNome\tCPF\t\tLista de Materias\n");

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
        printf("A materia com este ID nao esta cadastrada.\n");
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

int delAlu(periodo *per)
{
    if(per->periodoAlu == nullptr) return 1;
    aluno *aux = per->periodoAlu->prox;
    free(per->periodoAlu);
    per->periodoAlu = aux;
    delAlu(per);
    return 1;

}

int delMat(periodo *per)
{
    if(per->periodoMat == nullptr) return 1;
    materia *aux = per->periodoMat->prox;
    free(per->periodoMat);
    per->periodoMat = aux;
    delMat(per);
    return 1;

}

int inserirAluMat(periodo *per,int id_mat)
{
    int id_alu = -1;
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
    /*  printf("Digite o ID da materia:\n");
    scanf(" %d", &id_mat); */
    materia *m = buscarMatPer(per->periodoMat, id_mat);
    if (m == nullptr)
    {
        printf("Essa materia nao esta cadastrada neste periodo.\n");
        return 0;
    }
    if (buscarAluMat(m->listAlu, id_alu) != nullptr)
    {
        printf("Ja existe aluno matriculado com este ID.\n");
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
        printf("Ja existe aluno cadastrado com esse ID neste periodo.\n");
        return 0;
    }
    else
    {
        aluno *aux = (aluno *)malloc(sizeof(aluno));
        aux->prox = nullptr;
        aux->id = id_alu;
        printf("Digite o nome do aluno:\n ");
        scanf(" %49[^\n]s", aux->nome);
        clean_stdin();
        printf("Digite o cpf do aluno: ");
        scanf(" %19[^\n]s", aux->cpf);
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

        printf("Ja existe materia cadastrada com esse ID neste periodo.\n");
        return 0;
    }
    else
    {
        materia *aux = (materia *)malloc(sizeof(materia));
        aux->id = id_mat;
        printf("Digite o nome do materia:\n");
        scanf(" %49[^\n]s", aux->nome);
        clean_stdin();
        printf("Digite o nome do professor:\n");
        scanf(" %49[^\n]s", aux->professor);
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
        printf("Esse periodo ja esta cadastrado.\n");
        return 0;
    }
    else
    {
        periodo *aux = (periodo *)malloc(sizeof(periodo));
        strcpy(aux->ano, aux_ano);
        aux->prox = inicio;
        inicio = aux;
        inicio->periodoAlu = nullptr;
        inicio->periodoMat = nullptr;
        return 1;
    }
}

void listarAluPer(periodo *inicio)
{
    printf("Lista de alunos cadastrados no periodo:\n");
    aluno *aux = inicio->periodoAlu;
    printf("ID\tNome do aluno\n");
    while (aux != nullptr)
    {
        printf("%d\t%s\n", aux->id, aux->nome);
        aux = aux->prox;
    }
}
void listarMatPer(periodo *inicio)
{
    printf("Lista de materias cadastradas no periodo:\n");
    materia *aux = inicio->periodoMat;
    printf("ID\tNome da materia\n");
    while (aux != nullptr)
    {
        printf("%d\t%s\n", aux->id, aux->nome);
        aux = aux->prox;
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
void makeFileAlu(periodo *per)
{
    char url[20] = "alunos.txt";
    FILE *arq;
   
    arq = fopen(url, "w");
    if (arq == nullptr)
        printf("Erro ao abrir arquivo\n");
    else
    {
        while (per != nullptr)
        {
           
            aluno *aux = per->periodoAlu;
            while (aux != nullptr)
            {
                fprintf(arq, "%s\n", per->ano);
                fprintf(arq, "%d\n", aux->id);
                fprintf(arq, "%s\n", aux->nome);
                fprintf(arq, "%s\n", aux->cpf);
                aux = aux->prox;
            }
            per = per->prox;
        }
            fclose(arq);
    }
}
void makeFileMat(periodo *per)
{
    char url[20] = "materias.txt";
    FILE *arq;
   
    arq = fopen(url,"w");
    if(arq == nullptr) printf("Erro ao abrir arquivo\n");
    else
    {
        while(per != nullptr)
        {
            materia *aux = per->periodoMat;
            while(aux != nullptr)
            {
                fprintf(arq,"%s\n",per->ano);
                fprintf(arq,"%d\n",aux->id);
                fprintf(arq,"%s\n",aux->nome);
                fprintf(arq,"%s\n",aux->professor);
                fprintf(arq,"%d\n",aux->cred);
                aux = aux->prox;
            }
            per = per->prox;
        }
        fclose(arq);
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

int menuPer(periodo *per)
{
    int opcao;
    printf("\nVoce esta consultando o seguinte periodo: %s\n", per->ano);
    printf("Escolha a opcao:\n");
    printf("1. Listar alunos cadastrados\n");
    printf("2. Listar materias cadastradas\n");
    printf("3. Inserir materia\n");
    printf("4. Remover materia\n");
    printf("5. Inserir aluno\n");
    printf("6. Remover aluno\n");
    printf("7. Consultar dados de um aluno\n");
    printf("8. Entrar no menu de uma materia\n");
    printf("0. Sair\n");

    scanf("%d", &opcao);
    return opcao;
}

int menuPerMat(materia *mat)
{
    int opcao;
    printf("\nVoce esta consultando a seguinte materia: %s\n", mat->nome);
    printf("Escolha a opcao:\n");
    printf("1. Dados da materia\n");
    printf("2. Consultar lista de alunos\n");
    printf("3. Inserir aluno\n");
    printf("4. Remover aluno\n");
    printf("0. Sair\n");

    scanf("%d", &opcao);
    return opcao;
}

int removeAluMat(materia *&mat, aluno *&alu)
{
    //REMOVE ALUNO DA LISTA ALUNO MATERIA
    listaAluno *aluAnt = buscarAnteriorAluMat(mat->listAlu, alu->id), *aluAtual;

    //atual == nullptr: não existe lista ou preciso remover a head
    if (aluAnt == nullptr)
    {
        //se a head não existir, não faz nada
        if (mat->listAlu == nullptr)
        {

            printf("Aluno não está na matéria!");
            return 0;
        }
        //head existe e quero remove-la, troco
        aluAtual = mat->listAlu;
        mat->listAlu = aluAtual->prox;
        // free(aluAtual);
        // return 1;
    }
    //atual->prox == nullptr, chegou ao final e não achou
    else if (aluAnt->prox == nullptr)
    {
        printf("Aluno não está na lista!");
        return 0;
    }
    //coloca o prox pra apontar para o proximo da lista
    else
    {
        aluAtual = aluAnt->prox;
        aluAnt->prox = aluAtual->prox;
        // free(aluAtual);
    }

    //REMOVE MATERIA DA LISTA MATERIA DO ALUNO
    listaMateria *matAnt = buscarAnteriorMatAlu(alu->listMat, mat->id), *matAtual;

    //atual == nullptr: não existe lista ou preciso remover a head
    if (matAnt == nullptr)
    {
        //se a head não existir, não faz nada
        if (alu->listMat == nullptr)
        {
            printf("Matéria não pertence ao aluno!");
            return 0;
        }
        //head existe e quero remove-la, troco
        matAtual = alu->listMat;
        alu->listMat = matAtual->prox;
        free(aluAtual);
        free(matAtual);
        return 1;
    }
    //atual->prox == nullptr, chegou ao final e não achou
    else if (matAnt->prox == nullptr)
    {
        printf("Aluno não está na lista!");
        return 0;
    }
    //coloca o prox pra apontar para o proximo da lista
    matAtual = matAnt->prox;
    matAnt->prox = matAtual->prox;
    free(matAtual);
    free(aluAtual);
    return 1;
}

int removeAluPer(periodo *&per, int id_alu)
{
    aluno *ant = buscarAnteriorAluPer(per->periodoAlu, id_alu), *atual;
    listaMateria *matAtual;

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
        matAtual = atual->listMat;
        while (matAtual)
        {
            //agora remove aluMat já tira o aluno da materia e a materia do aluno, alterando o ponteiro matAtual->mat
            removeAluMat(matAtual->mat, atual);
            matAtual = matAtual->prox;
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
    matAtual = atual->listMat;
    while (matAtual)
    {
        removeAluMat(matAtual->mat, atual);
        matAtual = matAtual->prox;
    }
    ant->prox = atual->prox;
    free(atual);
    return 1;
}

int removeMatPer(periodo *&per, int id_mat)
{
    materia *ant = buscarAnteriorMatPer(per->periodoMat, id_mat), *atual;
    listaAluno *aluAtual;

    //atual == nullptr: não existe lista ou preciso remover a head
    if (ant == nullptr)
    {
        //se a head não existir, não faz nada
        if (per->periodoMat == nullptr)
        {
            printf("Matéria não está na lista!");
            return 0;
        }
        atual = per->periodoMat;
        //head existe e quero remove-la, troco
        aluAtual = atual->listAlu;
        while (aluAtual)
        {
            //agora remove aluMat já tira o aluno da materia e a materia do aluno, alterando o ponteiro aluAtual->alu
            removeAluMat(atual, aluAtual->alu);
            aluAtual = aluAtual->prox;
        }
        per->periodoMat = atual->prox;
        free(atual);
        return 1;
    }
    //atual->prox == nullptr, chegou ao final e não achou
    else if (ant->prox == nullptr)
    {
        printf("Matéria não está na lista!");
        return 0;
    }
    //coloca o prox pra apontar para o proximo da lista
    atual = ant->prox;
    aluAtual = atual->listAlu;
    while (aluAtual)
    {
        removeAluMat(atual, aluAtual->alu);
        aluAtual = aluAtual->prox;
    }
    ant->prox = atual->prox;
    free(atual);
    return 1;
}

int removePer(periodo *&per, char aux_ano[20])
{
    periodo *ant = buscarAnteriorPer(per, aux_ano), *atual;

    //atual == nullptr: não existe lista ou preciso remover a head
    if (ant == nullptr)
    {
        //se a head não existir, não faz nada
        if (per == nullptr)
        {
            printf("Período não existe!");
            return 0;
        }
        atual = per;
        //head existe e quero remove-la, troco

        per = atual -> prox;
        delAlu(atual);
        delMat(atual);
        free(atual);
        return 1;
    }
    //atual->prox == nullptr, chegou ao final e não achou
    else if (ant->prox == nullptr)
    {
        printf("Período não existe!");
        return 0;
    }
    //coloca o prox pra apontar para o proximo da lista
    atual = ant->prox;
    ant -> prox = atual -> prox;
    delAlu(atual);
    delMat(atual);
    free(atual);
    return 1;
}

int main()
{
    periodo *init = nullptr;

    int opcaoMain = -1;
    cout << init << "\n";
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
            scanf(" %9[^\n]s", temp);
            clean_stdin();
            inserirPer(init, temp);
            break;
        case 3:
            printf("Digite o periodo que deseja remover:(ex:2021-1)\n");
            scanf(" %9[^\n]s",temp);
            clean_stdin();
            removePer(init,temp);

            break; // remover periodo
        case 4:
            printf("Escolha o periodo:\n");
            scanf(" %9[^\n]s", temp);
            clean_stdin();
            periodo *aux_per = buscarPer(init, temp);
            if (aux_per == nullptr)
                printf("O periodo nao esta cadastrado\n");
            else
            {
                int opcaoPer = -1;
                do
                {

                    opcaoPer = menuPer(aux_per);
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
                        scanf(" %d", &temp_id_mat);
                        clean_stdin();
                        inserirMatPer(init, temp_id_mat);
                        break;
                    case 4:
                        printf("Insira o Id da materia que deseja remover:\n");
                        scanf(" %d",&temp_id_mat);
                        clean_stdin();
                        removeMatPer(init,temp_id_mat);

                        break; //remover materia per
                    case 5:
                        printf("Insira o ID do aluno:\n");
                        int temp_id_alu;
                        scanf(" %d", &temp_id_alu);
                        clean_stdin();
                        inserirAluPer(init, temp_id_alu);
                        break;
                    case 6:
                        printf("Insira o ID do aluno que deseja remover do periodo:\n");
                        scanf(" %d", &temp_id_alu);
                        clean_stdin();
                        removeAluPer(init, temp_id_alu);
                        break;
                    case 7:
                        printf("Insira o ID do aluno:\n");
                        scanf(" %d", &temp_id_alu);
                        clean_stdin();
                        dadosAlu(init, temp_id_alu);
                        break;
                    case 8:
                        printf("Insira o ID da materia:\n");
                        scanf(" %d", &temp_id_mat);
                        clean_stdin();
                        materia *aux = buscarMatPer(init->periodoMat, temp_id_mat);
                        if (aux == nullptr)
                            printf("A materia nao esta cadastrada\n");
                        else
                        {
                            int opcaoPerMat = -1;
                            do
                            {

                                opcaoPerMat = menuPerMat(aux);
                                switch (opcaoPerMat)
                                {
                                case 1:
                                    dadosMat(init, temp_id_mat);
                                    break;
                                case 2:
                                    aluPorMat(init, temp_id_mat);
                                    break;
                                case 3:
                                    inserirAluMat(init, aux->id);
                                    break;
                                case 4:
                                    printf("Insira o ID do aluno que deseja remover da materia:\n");
                                    scanf(" %d", &temp_id_alu);
                                    clean_stdin();
                                    listaAluno *aux_alu = buscarAluMat(aux->listAlu,temp_id_alu);
                                    if(aux_alu != nullptr) removeAluMat(aux, aux_alu->alu);// funcao recebe como aluno* como parametro
                                    else printf("Esse ID nao está cadastrado\n");           // então preciso procurar aluno* com o id

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
