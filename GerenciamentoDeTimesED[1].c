/*
UNIVERSIDADE FEDERAL DE SERGIPE
CIDADE UNIVERSITÁRIA PROF. JOSÉ ALOÍSIO DE CAMPOS
CENTRO DE CIÊNCIAS EXATAS E TECNOLOGIA
DEPARTAMENTO DE COMPUTAÇÃO
ENGENHARIA DE COMPUTAÇÃO
COMP0405 - ESTRUTURAS DE DADOS - 2025.1
Turma 02
------------------------------
TRABALHO DA PRIMEIRA UNIDADE
GRUPO 11 - TEMA 12:
------------------------------
Utilizando multilista faça um programa para gerenciamento de times ou equipes em um clube esportivo. O programa deve cadastrar as equipes usando uma lista simplesmente encadeada de forma que cada equipe aponte para a equipe seguinte. Para cada equipe devem ser cadastrados os atletas usando uma lista circular simplesmente encadeada. Cada atleta deve apontar para o próximo atleta. Para cada atleta devem ser guardadas as informações de nome, matrícula, idade, número da camisa e quantidade de faltas. Para cada time ou equipe devem ser guardadas as informações nome do time ou equipe, esporte treinado e categoria. A categoria diz respeito a idade dos jogadores e devido a grande variedade entre esportes, pode ser cadastrada como um string de 30 letras. O sistema deve possuir no mínimo as seguintes funcionalidades:
• Cadastrar equipe
• Cadastrar atleta em equipe
• Remove equipe
• Remover atleta
• Mostrar todas as equipes cadastradas
• Mostrar composição de equipe específica
• Mostrar dados de atleta específico
• Mostrar dados de todos os atletas de determinada categoria
------------------------------
AUTORES:
------------------------------
ÁLEX MATHEUS COLETA SANTOS - 202200014669
ENZO LIBÓRIO FRAGA - 202400028810
LAUREN VICTORIA FERREIRA ROMA - 202200014749
LUIS FELIPE RAMALHO CARVALHO - 202400028955
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os dados do Time/Equipe
typedef struct gerenciamentoTimes {
    char nome[50];
    char categoria[50];
    char esporte[50];
} Time;

// Estrutura para os dados do Atleta
typedef struct gereciamentoAtletas {
    char nome[50];
    int matricula;
    int idade;
    int numeroDaCamisa;
    int quantDeFaltas;
} Atleta;

// Nó da lista de atletas (circular duplamente encadeada)
typedef struct noAtleta {
    Atleta atleta;
    struct noAtleta *prox;
    struct noAtleta *ant;
} noAtleta;

// Nó da lista de times (simplesmente encadeada)
typedef struct noTime {
    Time time;
    struct noTime *proxTime;
    noAtleta *listaAtletas;
} noTime;

// Cabeçalho da lista de times
typedef struct head {
    noTime *refInicio;
    noTime *refFinal;
    int quantidade;
} Head;

Head *iniciarHead(void) {
    Head *head = (Head*)malloc(sizeof(Head));
    if (head == NULL) return NULL;
    head->quantidade = 0;
    head->refInicio = NULL;
    head->refFinal = NULL;
    return head;
}
// Verificar se as equipes são iguais
int equipe_igual(noTime *equipe, char *nome, char *esporte, char *categoria) {
    return (strcmp(equipe->time.nome, nome) == 0 &&
            strcmp(equipe->time.esporte, esporte) == 0 &&
            strcmp(equipe->time.categoria, categoria) == 0);
}
// buscar equipe na lista

noTime* buscar_equipe(Head *head, char *nome, char *esporte, char *categoria) {
    noTime *aux = head->refInicio;
    while (aux != NULL) {
        if (equipe_igual(aux, nome, esporte, categoria)) return aux;
        aux = aux->proxTime;
    }
    return NULL;
}
// cadastrar equipe
void cadastrar_equipe(Head *head) {
    if (!head) return;
    // alocação de memoria
    noTime *novo = (noTime*)malloc(sizeof(noTime));
    if (!novo) return;
    printf("\nCadastro de nova equipe\n");
    // colocar o nome,categoria e esporte do time
    printf("Nome: "); fgets(novo->time.nome, 50, stdin); novo->time.nome[strcspn(novo->time.nome, "\n")] = '\0';
    printf("Esporte: "); fgets(novo->time.esporte, 50, stdin); novo->time.esporte[strcspn(novo->time.esporte, "\n")] = '\0';
    printf("Categoria: "); fgets(novo->time.categoria, 50, stdin); novo->time.categoria[strcspn(novo->time.categoria, "\n")] = '\0';
    novo->listaAtletas = NULL;
    novo->proxTime = NULL;
    // verificar na lista se tem algum time
    if (!head->refInicio) head->refInicio = head->refFinal = novo;
    // se não tiver, fazer a apontação dos laços
    else { head->refFinal->proxTime = novo; head->refFinal = novo; }
    head->quantidade++;
    printf("Equipe cadastrada com sucesso!\n");
}
// cadastrar atleta na equipe
void cadastrar_atleta(Head *head) {
    char nome[50], esporte[50], categoria[50];
    // verificar se existe a equipe
    printf("\nDigite o nome da equipe: "); fgets(nome, 50, stdin); nome[strcspn(nome, "\n")] = '\0';
    printf("Digite o esporte: "); fgets(esporte, 50, stdin); esporte[strcspn(esporte, "\n")] = '\0';
    printf("Digite a categoria: "); fgets(categoria, 50, stdin); categoria[strcspn(categoria, "\n")] = '\0';
    noTime *equipe = buscar_equipe(head, nome, esporte, categoria);
    if (!equipe) { printf("Equipe nao encontrada.\n"); return; }
    noAtleta *novo = (noAtleta*)malloc(sizeof(noAtleta));
    if (!novo) return;
    // digitar dados do atleta
    printf("\nNome do atleta: "); fgets(novo->atleta.nome, 50, stdin); novo->atleta.nome[strcspn(novo->atleta.nome, "\n")] = '\0';
    printf("Matricula: "); scanf("%d", &novo->atleta.matricula);
    printf("Idade: "); scanf("%d", &novo->atleta.idade);
    printf("Numero da camisa: "); scanf("%d", &novo->atleta.numeroDaCamisa);
    printf("Faltas: "); scanf("%d", &novo->atleta.quantDeFaltas);
    getchar();
    // verificar se já existe um atleta na lista
    if (!equipe->listaAtletas) {
        novo->prox = novo->ant = novo;
        equipe->listaAtletas = novo;
        // fazer os apontamentos da lista circular duplamente encadeada do atleta
    } else {
        noAtleta *ult = equipe->listaAtletas->ant;
        novo->prox = equipe->listaAtletas;
        novo->ant = ult;
        ult->prox = novo;
        equipe->listaAtletas->ant = novo;
    }
    printf("Atleta cadastrado com sucesso!\n");
}

void remover_equipe(Head *head) {
    char nome[50], esporte[50], categoria[50];
    printf("\nDigite o nome da equipe: "); fgets(nome, 50, stdin); nome[strcspn(nome, "\n")] = '\0';
    printf("Digite o esporte: "); fgets(esporte, 50, stdin); esporte[strcspn(esporte, "\n")] = '\0';
    printf("Digite a categoria: "); fgets(categoria, 50, stdin); categoria[strcspn(categoria, "\n")] = '\0';
    noTime *aux = head->refInicio, *anterior = NULL;
    while (aux && !equipe_igual(aux, nome, esporte, categoria)) {
        anterior = aux;
        aux = aux->proxTime;
    }
    if (!aux) { printf("Equipe nao encontrada.\n"); return; }
    if (aux->listaAtletas) {
        noAtleta *inicio = aux->listaAtletas;
        inicio->ant->prox = NULL;
        while (inicio) {
            noAtleta *tmp = inicio;
            inicio = inicio->prox;
            free(tmp);
        }
    }
    if (!anterior) head->refInicio = aux->proxTime;
    else anterior->proxTime = aux->proxTime;
    if (aux == head->refFinal) head->refFinal = anterior;
    free(aux);
    head->quantidade--;
    printf("Equipe removida.\n");
}

void remover_atleta(Head *head) {
    char nome[50], esporte[50], categoria[50];
    printf("\nDigite o nome da equipe: "); fgets(nome, 50, stdin); nome[strcspn(nome, "\n")] = '\0';
    printf("Digite o esporte: "); fgets(esporte, 50, stdin); esporte[strcspn(esporte, "\n")] = '\0';
    printf("Digite a categoria: "); fgets(categoria, 50, stdin); categoria[strcspn(categoria, "\n")] = '\0';
    noTime *equipe = buscar_equipe(head, nome, esporte, categoria);
    if (!equipe || !equipe->listaAtletas) { printf("Equipe ou atletas inexistentes.\n"); return; }
    char nomeAtleta[50]; int matricula;
    printf("Nome do atleta: "); fgets(nomeAtleta, 50, stdin); nomeAtleta[strcspn(nomeAtleta, "\n")] = '\0';
    printf("Matricula do atleta: "); scanf("%d", &matricula); getchar();
    noAtleta *aux = equipe->listaAtletas;
    do {
        if (strcmp(aux->atleta.nome, nomeAtleta) == 0 && aux->atleta.matricula == matricula) {
            if (aux->prox == aux) equipe->listaAtletas = NULL;
            else {
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;
                if (equipe->listaAtletas == aux) equipe->listaAtletas = aux->prox;
            }
            free(aux);
            printf("Atleta removido.\n");
            return;
        }
        aux = aux->prox;
    } while (aux != equipe->listaAtletas);
    printf("Atleta nao encontrado.\n");
}

void exibir_equipes(Head *head) // função para mostrar as equipes cadastradas
{
    if (head == NULL || head->refFinal == NULL) // se não tiver nenhuma equipe cadastrada, já retorna avisando
    {
        printf("Nenhuma equipe cadastrada\n");
        return;
    }
    noTime *aux = head->refInicio; // aux é um ponteiro auxiliar que aponta para o inicio da lista
    printf("Equipes participantes:\n\n");
    while (aux != NULL) // mostra todos os dados das equipes enqaunto tiver equipe na lista
    {
        printf("Nome da equipe: %s\n", aux->time.nome);
        printf("Categoria da equipe: %s\n", aux->time.categoria);
        printf("Esporte da equipe: %s\n\n", aux->time.esporte);
        aux = aux->proxTime; // aponta pro proximo time
    }
}

void mostrar_composicao_equipe(Head *head, char nomeProcurado[30], char categoriaProcurada[30], char esporteProcurado[30]) // função para mostrar a composição da equipe
{
    // verifica se tem equipe cadastrada, senão já sai
    if (head == NULL || head->refInicio == NULL)
    {
        printf("Nenhuma equipe cadastrada.\n");
        return;
    }

    noTime *aux = head->refInicio; // aux é um ponteiro auxiliar que aponta para o inicio da lista
    while (aux != NULL) // percorre enquanto tiver times
    {
        // verifica se achou a equipe com nome, categoria e esporte igual
        if (strcmp(aux->time.nome, nomeProcurado) == 0 &&
            strcmp(aux->time.categoria, categoriaProcurada) == 0 &&
            strcmp(aux->time.esporte, esporteProcurado) == 0)
        {
            noAtleta *auxAtleta = aux->listaAtletas; //aponta para o primeiro atleta
            if (auxAtleta == NULL)
            {
                printf("Não há atletas cadastrados nesta equipe.\n");
                return;
            }

            printf("Atletas da equipe %s:\n", nomeProcurado);
            noAtleta *inicio = auxAtleta; // Salva o endereço do primeiro atleta da lista pra depois saber onde parar
            do
            {
                printf("- %s\n", auxAtleta->atleta.nome);
                auxAtleta = auxAtleta->prox;
            } while (auxAtleta != inicio); // vai até voltar no início da lista

            return; // terminou de exibir os atletas
        }

        aux = aux->proxTime; // passa pra próxima equipe
    }

    printf("Equipe não encontrada.\n");
}

void mostrar_dados_atleta(Head *head) {
    char nome[50], esporte[50], categoria[50], nomeAtleta[50]; int matricula;
    printf("\nEquipe nome: "); fgets(nome, 50, stdin); nome[strcspn(nome, "\n")] = '\0';
    printf("Esporte: "); fgets(esporte, 50, stdin); esporte[strcspn(esporte, "\n")] = '\0';
    printf("Categoria: "); fgets(categoria, 50, stdin); categoria[strcspn(categoria, "\n")] = '\0';
    noTime *equipe = buscar_equipe(head, nome, esporte, categoria);
    if (!equipe || !equipe->listaAtletas) { printf("Equipe ou atletas inexistentes.\n"); return; }
    printf("Nome do atleta: "); fgets(nomeAtleta, 50, stdin); nomeAtleta[strcspn(nomeAtleta, "\n")] = '\0';
    printf("Matricula: "); scanf("%d", &matricula); getchar();
    noAtleta *a = equipe->listaAtletas;
    do {
        if (strcmp(a->atleta.nome, nomeAtleta) == 0 && a->atleta.matricula == matricula) {
            printf("Nome: %s, Idade: %d, Camisa: %d, Faltas: %d\n", a->atleta.nome, a->atleta.idade, a->atleta.numeroDaCamisa, a->atleta.quantDeFaltas);
            return;
        }
        a = a->prox;
    } while (a != equipe->listaAtletas);
    printf("Atleta nao encontrado.\n");
}

void mostrar_atletas_categoria(Head *head) {
    char categoria[50];
    printf("\nDigite a categoria: ");
    fgets(categoria, 50, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    noTime *equipe = head->refInicio;
    int categoria_encontrada = 0; 
    int atletas_encontrados = 0; 

    while (equipe) {
        if (strcmp(equipe->time.categoria, categoria) == 0) {
            categoria_encontrada = 1; 
            if (equipe->listaAtletas) {
                atletas_encontrados = 1;
                printf("Equipe %s (%s):\n", equipe->time.nome, equipe->time.esporte);
                noAtleta *a = equipe->listaAtletas;
                do {
                    printf("   %s - Matricula: %d\n", a->atleta.nome, a->atleta.matricula);
                    a = a->prox;
                } while (a != equipe->listaAtletas);
            }
        }
        equipe = equipe->proxTime;
    }

    if (!categoria_encontrada) {
        printf("Nenhuma equipe encontrada para a categoria '%s'.\n", categoria);
    } else if (categoria_encontrada && !atletas_encontrados) {
        printf("Nao ha atletas associados a nenhuma equipe na categoria '%s'.\n", categoria);
    }
}

int main() {
    Head *head = iniciarHead();
    int op;
    do {
        printf("\n1-Cadastrar equipe\n2-Cadastrar atleta\n3-Remover equipe\n4-Remover atleta\n5-Listar equipes\n6-Composicao equipe\n7-Dados de atleta\n8-Atletas por categoria\n0-Sair\nOpcao: ");
        scanf("%d", &op); getchar();
        switch(op) {
            case 1: cadastrar_equipe(head); break;
            case 2: cadastrar_atleta(head); break;
            case 3: remover_equipe(head); break;
            case 4: remover_atleta(head); break;
            case 5: exibir_equipes(head); break;
            case 6: {
            char nome[50], categoria[50], esporte[50];

            printf("Digite o nome da equipe: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite o esporte da equipe: ");
            fgets(esporte, sizeof(esporte), stdin);
            esporte[strcspn(esporte, "\n")] = '\0';

            printf("Digite a categoria da equipe: ");
            fgets(categoria, sizeof(categoria), stdin);
            categoria[strcspn(categoria, "\n")] = '\0';

            mostrar_composicao_equipe(head, nome, categoria, esporte);
            break;
        }
            case 7: mostrar_dados_atleta(head); break;
            case 8: mostrar_atletas_categoria(head); break;
        }
    } while(op != 0);
    return 0;
}
