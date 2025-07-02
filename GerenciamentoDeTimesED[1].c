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

/***************************************************************************/
/* ESTRUTURAS */
/****************************************************************************/
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

/***************************************************************************/
/* INICIAR A LISTA */
/****************************************************************************/
Head *iniciarHead(void) {
    Head *head = (Head*)malloc(sizeof(Head));
    if (head == NULL) return NULL;
    head->quantidade = 0;
    head->refInicio = NULL;
    head->refFinal = NULL;
    return head;
}

/***************************************************************************/
/* Verificar se as equipes são iguais */
/****************************************************************************/
int equipe_igual(noTime *equipe, char *nome, char *esporte, char *categoria) {
    return (strcmp(equipe->time.nome, nome) == 0 &&
            strcmp(equipe->time.esporte, esporte) == 0 &&
            strcmp(equipe->time.categoria, categoria) == 0);
}

/***************************************************************************/
/* buscar equipe na lista */
/****************************************************************************/
noTime* buscar_equipe(Head *head, char *nome, char *esporte, char *categoria) {
    noTime *aux = head->refInicio;
    while (aux != NULL) {
        if (equipe_igual(aux, nome, esporte, categoria)) return aux;
        aux = aux->proxTime;
    }
    return NULL;
}

/***************************************************************************/
/* cadastrar equipe */
/****************************************************************************/
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


/***************************************************************************/
/* cadastrar atleta em equipe */
/****************************************************************************/
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


/***************************************************************************/
/* Função que remove uma equipe da lista */
/****************************************************************************/
void remover_equipe(Head *head) {
    // Variáveis para armazenar os dados da equipe
    char nome[50], esporte[50], categoria[50];

    // Entrada dos dados da equipe
    printf("\nDigite o nome da equipe: "); 
    fgets(nome, 50, stdin); 
    nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere '\n' ao final

    printf("Digite o esporte: "); 
    fgets(esporte, 50, stdin); 
    esporte[strcspn(esporte, "\n")] = '\0';

    printf("Digite a categoria: "); 
    fgets(categoria, 50, stdin); 
    categoria[strcspn(categoria, "\n")] = '\0';

    // Ponteiros auxiliares para percorrer e remover
    noTime *aux = head->refInicio, *anterior = NULL;

    // Busca pela equipe na lista
    while (aux && !equipe_igual(aux, nome, esporte, categoria)) {
        anterior = aux;
        aux = aux->proxTime;
    }

    // Caso a equipe não seja encontrada
    if (!aux) { 
        printf("Equipe nao encontrada.\n"); 
        return; 
    }

    // Se houver atletas na equipe, libera todos
    if (aux->listaAtletas) {
        noAtleta *inicio = aux->listaAtletas;

        // Quebra a circularidade da lista de atletas
        inicio->ant->prox = NULL;

        // Liberação da memória dos atletas
        while (inicio) {
            noAtleta *tmp = inicio;
            inicio = inicio->prox;
            free(tmp);
        }
    }

    // Remoção do nó da equipe na lista encadeada
    if (!anterior) 
        head->refInicio = aux->proxTime; // Era o primeiro
    else 
        anterior->proxTime = aux->proxTime; // Meio ou fim

    // Atualiza ponteiro final, se necessário
    if (aux == head->refFinal) 
        head->refFinal = anterior;

    // Libera memória da equipe e atualiza contador
    free(aux);
    head->quantidade--;

    printf("Equipe removida.\n");
}


/***************************************************************************/
/* Função que remove um atleta de uma equipe específica */
/****************************************************************************/
void remover_atleta(Head *head) {
    // Dados da equipe
    char nome[50], esporte[50], categoria[50];

    // Leitura dos dados identificadores da equipe
    printf("\nDigite o nome da equipe: "); 
    fgets(nome, 50, stdin); 
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite o esporte: "); 
    fgets(esporte, 50, stdin); 
    esporte[strcspn(esporte, "\n")] = '\0';

    printf("Digite a categoria: "); 
    fgets(categoria, 50, stdin); 
    categoria[strcspn(categoria, "\n")] = '\0';

    // Busca pela equipe na lista
    noTime *equipe = buscar_equipe(head, nome, esporte, categoria);

    // Se equipe não existe ou não tem atletas
    if (!equipe || !equipe->listaAtletas) {
        printf("Equipe ou atletas inexistentes.\n"); 
        return;
    }

    // Dados do atleta a ser removido
    char nomeAtleta[50]; 
    int matricula;

    printf("Nome do atleta: "); 
    fgets(nomeAtleta, 50, stdin); 
    nomeAtleta[strcspn(nomeAtleta, "\n")] = '\0';

    printf("Matricula do atleta: "); 
    scanf("%d", &matricula); 
    getchar(); // Consome o '\n' deixado pelo scanf

    // Ponteiro para percorrer a lista circular de atletas
    noAtleta *aux = equipe->listaAtletas;

    // Percorre a lista circular
    do {
        // Compara nome e matrícula do atleta atual
        if (strcmp(aux->atleta.nome, nomeAtleta) == 0 && aux->atleta.matricula == matricula) {
            
            // Caso o atleta seja o único na lista
            if (aux->prox == aux) 
                equipe->listaAtletas = NULL;

            else {
                // Ajusta os ponteiros para remover o nó da lista
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;

                // Se o atleta removido for o primeiro da lista
                if (equipe->listaAtletas == aux) 
                    equipe->listaAtletas = aux->prox;
            }

            // Libera a memória do atleta removido
            free(aux);
            printf("Atleta removido.\n");
            return;
        }

        aux = aux->prox;

    } while (aux != equipe->listaAtletas); // Percorre até voltar ao início

    // Caso o atleta não seja encontrado
    printf("Atleta nao encontrado.\n");
}

/***************************************************************************/
/* mostrar as equipes cadastradas */
/****************************************************************************/
void exibir_equipes(Head *head)
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


/***************************************************************************/
/* função para mostrar a composição da equipe */
/****************************************************************************/
void mostrar_composicao_equipe(Head *head, char nomeProcurado[30], char categoriaProcurada[30], char esporteProcurado[30])
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


/***************************************************************************/
/* função para mostrar informações especificas sobre determinado atleta de uma certa equipe, modalidade e categoria */
/****************************************************************************/
void mostrar_dados_atleta(Head *head) {
    char nome[50], esporte[50], categoria[50], nomeAtleta[50]; int matricula; // criterios de busca para encontrar as infos do atleta
    printf("\nEquipe nome: "); fgets(nome, 50, stdin); nome[strcspn(nome, "\n")] = '\0';
    printf("Esporte: "); fgets(esporte, 50, stdin); esporte[strcspn(esporte, "\n")] = '\0';
    printf("Categoria: "); fgets(categoria, 50, stdin); categoria[strcspn(categoria, "\n")] = '\0';
    noTime *equipe = buscar_equipe(head, nome, esporte, categoria); // nó simplesmnete encadeado que irá fazer uma busca inicial entre as equipe, depois que encontra a equipe, busca pelo nome da equipe, esporte e categoria
    if (!equipe || !equipe->listaAtletas) { printf("Equipe ou atletas inexistentes.\n"); return; } // mensagem para caso haja erro na busca
    printf("Nome do atleta: "); fgets(nomeAtleta, 50, stdin); nomeAtleta[strcspn(nomeAtleta, "\n")] = '\0';
    printf("Matricula: "); scanf("%d", &matricula); getchar();
    noAtleta *a = equipe->listaAtletas; // no duplamente encadeado que percorre a lista circular com as infos das equipes e ponteiro que leva para a lista de atletas 
    do {
      // condicional para que ao dar match com as infos digitadas pelo usuario retorne nome, idade, num da camisa e num de faltas desse determinado atleta solicitado
        if (strcmp(a->atleta.nome, nomeAtleta) == 0 && a->atleta.matricula == matricula) {
            printf("Nome: %s, Idade: %d, Camisa: %d, Faltas: %d\n", a->atleta.nome, a->atleta.idade, a->atleta.numeroDaCamisa, a->atleta.quantDeFaltas);
            return;
        }
        a = a->prox;
    } while (a != equipe->listaAtletas); // condição de parada e/ou erro
    printf("Atleta nao encontrado.\n");
}


/***************************************************************************/
/* função que mostra todos os atletas de uma determinada categoria. Ex.: todos os atletas da categoria SUB-20 do Flamengo */
/****************************************************************************/
void mostrar_atletas_categoria(Head *head) {
    char categoria[50];
    printf("\nDigite a categoria: ");
    fgets(categoria, 50, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    noTime *equipe = head->refInicio; // nó com ponteiro que leva para o inicio da lista das equipes para que seja buscado a categoria nelas
    int categoria_encontrada = 0; 
    int atletas_encontrados = 0; 

    while (equipe) {
        if (strcmp(equipe->time.categoria, categoria) == 0) { //condição para comparação e inicio da lista caso o time possua a determinada categoria
            categoria_encontrada = 1; 
            if (equipe->listaAtletas) { // mesma condição só que agora para ter atletas cadastrados nessa categoria
                atletas_encontrados = 1;
                printf("Equipe %s (%s):\n", equipe->time.nome, equipe->time.esporte);
                noAtleta *a = equipe->listaAtletas; // no com ponteiro que leva para a lista de atletas, para que seja possivel iniciar o filtro de categoria
                do {
                    printf("   %s - Matricula: %d\n", a->atleta.nome, a->atleta.matricula);
                    a = a->prox; // imprime o nome de um atleta e vai para o prox, se ele atender as coaracteristicas adiciona o nome desse atleta na lista
                } while (a != equipe->listaAtletas);
            }
        }
        equipe = equipe->proxTime;
    }

    if (!categoria_encontrada) { // condições de parada/erro
        printf("Nenhuma equipe encontrada para a categoria '%s'.\n", categoria);
    } else if (categoria_encontrada && !atletas_encontrados) {
        printf("Nao ha atletas associados a nenhuma equipe na categoria '%s'.\n", categoria);
    }
}

/***************************************************************************/
/* FUNÇÃO PRINCIPAL */
/****************************************************************************/
int main() {
    Head *head = iniciarHead();
    int op;
    do {
        printf("--------------------------------\n");
        printf("GERENCIAMENTO DE CLUBE ESPORTIVO\n");
        printf("              MENU              \n");
        printf("--------------------------------\n");
        printf("1 - Cadastrar equipe;\n");
        printf("2 - Cadastrar atleta em equipe;\n");
        printf("3 - Remover equipe;\n");
        printf("4 - Remover atleta;\n");
        printf("5 - Mostrar todas as equipes;\n");
        printf("6 - Mostrar composição de equipe;\n");
        printf("7 - Mostrar dados de atleta;\n");
        printf("8 - Mostrar atletas por categoria;\n");
        printf("0 - Encerrar programa.\n");
        printf("--------------------------------\n");
        printf("Digite uma opção: ");
        scanf("%d", &op);
        getchar();

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

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while(op != 0);
    return 0;
}
