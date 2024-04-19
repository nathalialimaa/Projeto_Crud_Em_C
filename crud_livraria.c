#include <stdio.h>

    typedef struct{
    char nome[100];
    char autor[50];
    char editora [80];
    int codigoBarras;
}Livro;

// ========== Função para Mostrar o Menu de Opções da livraria ==========

void menu(){
    printf("\n\t************* ABELHINHA DOCE LIVRARIA  *************");
    printf("\n\t1 - CADASTRAR LIVRO");
    printf("\n\t2 - LISTAR LIVROS EXISTENTES");
    printf("\n\t3 - ATUALIZAR LIVROS");
    printf("\n\t4 - DELETAR LIVRO");
    printf("\n\t5 - SALVAR LISTA DE LIVROS CADASTRADOS");
    printf("\n\t6 - LER LISTA DE LIVROS CADASTRADOS");
    printf("\n\t7 - SAIR DO SISTEMA");
}

// ========== Função para Cadastrar livros ==========
int cadastrarLivro(Livro l[], int tamanhoVetor, int qtd){
    Livro cadastrarLivro;

    // Pedindo dados para o usuário
    printf("\nDigite o seu nome do livro: ");
    scanf("%99[^\n]", cadastrarLivro.nome);
    getchar();
    printf("\nDigite o autor do livro: ");
    scanf("%49[^\n]", cadastrarLivro.autor);
    getchar();
    printf("\nDigite a editora do livro: ");
    scanf("%79[^\n]", cadastrarLivro.editora);
    getchar();

    do{
        printf("\nDigite o código de barras do livro: ");
        scanf("%d", &cadastrarLivro.codigoBarras);

        getchar();

        if((cadastrarLivro.codigoBarras) < 0 ){
            puts("\n\tIdade invalida! Tente novamente.");
        }
    }while((cadastrarLivro.codigoBarras) < 0 );
    
    l[qtd] = cadastrarLivro;

    return 1;
}

// ========== Função para Listar os Livros cadastrados ==========

void listarLivros(Livro l[], int qtd){
    printf("\n\t\t\tLista de Pessoas:\n");
    printf("\t----------------------------------------------------\n");
    for(int i = 0; i < qtd; i++){
        printf("\t******************************************\n");
        printf("\tLivro %d\n\tNome: %s\n\tAutor: %s\n\tEditora: %s\n\tcodigoBarras: %d\n", (i+1), l[i].nome, l[i].autor,l[i].editora,l[i].codigoBarras);
        printf("\t******************************************\n");
    }
    printf("\t----------------------------------------------------\n");
}

// ========== Função para Alterar Algum livro Cadastrado ==========

void alterarLivros(Livro l[], int qtd){
    if (qtd == 0){
        printf("\nVoce ainda nao possui livros cadastrados!\n");
    } else {
        listarLivros(l, qtd);

        int id;

        printf("\n\tDigite o numero (identificador) do livro que deseja atualizar: ");
        scanf("%d", &id);
        getchar();
            
        // vamos decrementar o id, pois nossos indices do vetor pessoa
        // vão de zero até qtd;
        id--;

        // validando o indice passado pelo usuário
        if (id >= 0 && id < qtd) {
            Livro livroAtualizado;

            printf("\nDigite o novo nome do livro: ");
            scanf("%99[^\n]", livroAtualizado.nome);
            getchar();
            printf("\nDigite o novo autor do livro: ");
            scanf("%49[^\n]", livroAtualizado.autor);
            getchar();
            printf("\nDigite a nova editora do livro: ");
            scanf("%79[^\n]", livroAtualizado.editora);
            getchar();

            do{
                printf("\nDigite a novo código de barras do livro: ");
                scanf("%d", &livroAtualizado.codigoBarras);

                getchar();

                if((livroAtualizado.codigoBarras) < 0){
                    puts("\n\tCódigo de barras invalido! Tente novamente.");
                }
            }while((livroAtualizado.codigoBarras) < 0 );

            l[id] = livroAtualizado;
        } else {
            printf("\n\tNumero (identificador) Invalido!\n");
        }
    }
    //função deletar livros
}
int deletarLivro(Livro l[], int qtd){
    if (qtd==0){
        printf("Não é possível deletar, pois não há livros cadastrados");
        return 0;
    }
    int opcao;
    listarLivros (l,qtd);
    printf ("\n\t digite o índice da pessoa que você quer deletar:  ");
    scanf ("%d", &opcao);
    opcao --;
  
    if (opcao >=0 && opcao<qtd ){
        if (opcao==qtd- 1){
            printf("livro removido com sucesso");
            return -1;
        }
    } else {
        int i,j;
        for ( i=opcao; i<qtd ; i++){
            if (i==qtd - 1){
                j=i;
            } else {
                j=i+1;
            }
            Livro temporario = l[i];
            l[i]=l[j];
            l[j]= temporario;
        }
    }
    printf("Livro deletado com sucesso!");
    return -1;
    
}
//função salvar lista de livros Cadastrados
void salvarLivrosArquivo(Livro l[], int qtd, char arq[]){
    FILE *arquivo = fopen(arq, "w");

    if(arquivo){
        fprintf(arquivo, "%d\n", qtd);
        for(int i = 0; i < qtd; i++){
            fprintf(arquivo, "%s\n", l[i].nome);
            fprintf(arquivo, "%s\n", l[i].autor);
            fprintf(arquivo, "%s\n", l[i].editora);
            fprintf(arquivo, "%d\n", l[i].codigoBarras);
        }
        fclose(arquivo);
    }

    printf("\n\tSua Lista Foi Salva Com Sucesso\n");
}

//função para listar de livros Cadastrados
int lerArquivoTexto(Livro l[], char nomeArquivo[]){
    FILE *arquivo = fopen(nomeArquivo, "r");
    int quantidadeLivros = 0;
    Livro novoLivro;

    if (arquivo){
        fscanf(arquivo, "%d\n", &quantidadeLivros);
        for(int i = 0; i < quantidadeLivros; i++){
            fscanf(arquivo, "%99[^\n]\n", novoLivro.nome);
            fscanf(arquivo, "%49[^\n]\n", novoLivro.autor);
            fscanf(arquivo, "%79[^\n]", novoLivro.editora);
            fscanf(arquivo, "%d\n", &novoLivro.codigoBarras);
            l[i] = novoLivro;
        }
        fclose(arquivo);
        printf("\n\tSua lista foi carregada no sistema\n");
    } else {
        printf("\n\tNao foi possivel abrir o arquivo\n");
    }

    return quantidadeLivros;
}


int main(){

    /*Nessa quarta parte vamos:
    1 - Vamos criar uma procedimento para alterar uma pessoa cadastrada;
    */

    int opcao;
    Livro livros[50];
    int tamanhoVetorLivros = sizeof(livros) / sizeof (Livro);
    int qtdLivros = 0;
    char listadeLivros[]="listadelivros.txt";

    do{
        menu();
        printf("\nDigite o numero da sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                /* CADASTRAR LIVROS */
                getchar();
                qtdLivros += cadastrarLivro(livros, tamanhoVetorLivros, qtdLivros);
                printf("\n\n\nLivros Cadastrados = %d\n", qtdLivros);
                break;
            
            case 2:
                /* LISTAR livros */
                listarLivros(livros, qtdLivros);
                break;
            
            case 3:
                /* ATUALIZAR LIVROS */
                alterarLivros(livros, qtdLivros);
                break;
            
            case 4:
                /* DELETAR LIVRO */
                qtdLivros = qtdLivros + deletarLivro(livros, qtdLivros);
                break;
            
            case 5:
                /* SALVAR LISTA DE LIVROS CADASTRADOS */
                salvarLivrosArquivo(livros, qtdLivros,listadeLivros);
                break;
            
            case 6:
                /*LER LISTA DE LIVROS CADASTRADOS */
                qtdLivros = lerArquivoTexto(livros, listadeLivros);
                break;
            
            case 7:
                /* SAIR DO SISTEMA */
                printf("\nObrigado por usar nosso sistema!\n\n");
                break;
            
            default:
                /* OPÇÃO INVALIDA DIGITADA PELO FOFINHO DO USUÁRIO*/
                printf("\nOpcao invalida!!! Digite um valor de 1 a 7\n\n");
                break;
        }

    }while(opcao != 7);


    return 0;
}
