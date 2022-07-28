#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool sair = false;
FILE *pCLT;
FILE *auxCLT;
FILE *indClientes;
struct clientes
{
    int codigo;
    char telefone[14];
    char nome[100], endereco[100];
} clientela;

void indice()
{

    indClientes = fopen("indiceClientes.dat", "a+");

    if (indClientes == NULL)
    {

        printf("Erro de Alocação\n");
        exit(1);
    }

    else
    {

        fseek(pCLT, SEEK_SET, 1);
        fread(&clientela.codigo, sizeof(clientela.codigo), 1, pCLT);
        fwrite(&clientela.codigo, sizeof(clientela.codigo), 1, indClientes);
    }
    fclose(indClientes);
}

void abrir_arq()
{

    pCLT = fopen("clientes.dat", "a+");
    auxCLT = fopen("auxiliar_clientes.dat", "a+");
    if (pCLT == NULL || auxCLT == NULL)
    {
        printf("Erro de alocaçao\n");
        exit(1);
    }
}

void listarClientes()
{
    FILE *pCLT;
    FILE *auxCLT;
    pCLT = fopen("clientes.dat", "r");
    auxCLT = fopen("auxiliar_clientes.dat", "r");
    if (pCLT == NULL || auxCLT == NULL)
    {
        printf("Erro de alocaçao\n");
        exit(1);
    }
    else
    {
        while (fread(&clientela, sizeof(clientela), 1, pCLT) == 1)
        {

            printf("Código: %d\n", clientela.codigo);
            printf("Nome: %s\n", clientela.nome);
            printf("Endereço: %s\n", clientela.endereco);
            printf("Telefone: %s\n", clientela.telefone);
            printf("====================================\n\n");
        }
    }
    fclose(pCLT);
    fclose(auxCLT);
}

void cadastro()
{
    abrir_arq();

    printf("Digite o codigo do cliente: ");
    scanf("%d", &clientela.codigo);
    printf("Informe o telefone do cliente no formato(83)9999-9999: ");
    fscanf(stdin, "%s", clientela.telefone);
    printf("Informe o nome do cliente: ");
    fscanf(stdin, " %99[^\n]", clientela.nome);
    printf("Informe o endereço do cliente: ");
    fscanf(stdin, " %99[^\n]", clientela.endereco);
    printf("====================================\n\n");
    fseek(pCLT, SEEK_END, 1);
    fwrite(&clientela, sizeof(clientela), 1, pCLT);
    indice();

    fclose(pCLT);
    fclose(auxCLT);
}
void consulta()
{
    system("clear");
    abrir_arq();
    int codigo, a = 0;
    printf("Informe o codigo cliente a ser pesquisado: ");
    scanf("%d", &codigo);
    fseek(pCLT, SEEK_SET, 1);
    fread(&clientela, sizeof(clientela), 1, pCLT);
    while (!feof(pCLT))
    {
        if (clientela.codigo == codigo)
        {
            a++;
            printf("Cliente Encontrado\n");
            printf("Codigo do cliente: %d\n", clientela.codigo);
            printf("Nome do cliente: %s\n", clientela.nome);
            printf("Telefone do cliente: %s\n", clientela.telefone);
            printf("Endereço do cliente: %s\n", clientela.endereco);
            printf("====================================\n\n");
        }
        fread(&clientela, sizeof(clientela), 1, pCLT);
    }
    if (a == 0)
        printf(("Cliente não encontrado\n"));
    fclose(pCLT);
    fclose(auxCLT);
}

void exclusao()
{
    abrir_arq();
    int codigo, a = 0;
    printf("Informe o codigo a ser excluido: ");
    scanf("%d", &codigo);
    fseek(pCLT, SEEK_SET, 1);
    fread(&clientela, sizeof(clientela), 1, pCLT);
    while (!feof(pCLT))
    {
        if (clientela.codigo == codigo)
            a++;
        else
            fwrite(&clientela, sizeof(clientela), 1, auxCLT);
        fread(&clientela, sizeof(clientela), 1, pCLT);
    }

    if (a == 0)
        printf("Cliente não encontrado\n");
    else
        printf("Cliente Excluido\n");
    fclose(pCLT);
    fclose(auxCLT);
    remove("clientes.dat");
    rename("auxiliar_clientes.dat", "clientes.dat");
    remove("auxiliar_clientes.dat");
}

void alterar()
{
    abrir_arq();
    int codigo, a = 0;
    printf("Informe o codigo a ser alterado: ");
    scanf("%d", &codigo);
    fseek(pCLT, SEEK_SET, 1);
    fread(&clientela, sizeof(clientela), 1, pCLT);
    while (!feof(pCLT))
    {
        if (clientela.codigo == codigo)
        {
            a++;
            printf("Digite o novo codigo do cliente: ");
            scanf("%d", &clientela.codigo);
            printf("Informe o novo telefone do cliente no formato(83)9999-9999: ");
            fscanf(stdin, " %s", clientela.telefone);
            printf("Informe o nome do novo cliente: ");
            fscanf(stdin, " %99[^\n]", clientela.nome);
            printf("Informe o novo endereço do cliente: ");
            fscanf(stdin, " %99[^\n]", clientela.endereco);

            fwrite(&clientela, sizeof(clientela), 1, auxCLT);
            fread(&clientela, sizeof(clientela), 1, pCLT);
        }

        if (a == 0)
            printf("Cliente não encontrado\n");
        else
            printf("Cliente alterado\n");
        fclose(pCLT);
        fclose(auxCLT);
        remove("clientes.dat");
        rename("auxiliar_clientes.dat", "clientes.dat");
        remove("auxiliar_clientes.dat");
    }
}

FILE *pProd;
FILE *auxProd;
FILE *indProd;
struct Produto
{
    int codigo;
    char nome[50];
    int quantidade;
    float valor;
} estoque;

void listarProd()
{
    FILE *pProd;
    FILE *auxProd;
    pProd = fopen("produtos.dat", "r");
    auxProd = fopen("auxiliarProd.dat", "r");
    if (pProd == NULL || auxProd == NULL)
    {
        printf("Erro de alocaçao\n");
        exit(1);
    }
    else
    {
        while (fread(&estoque, sizeof(estoque), 1, pProd) == 1)
        {

            printf("Código: %d\n", estoque.codigo);
            printf("Produto: %s\n", estoque.nome);
            printf("Quantidade: %d\n", estoque.quantidade);
            printf("Valor R$: %.2f\n", estoque.valor);
            printf("====================================\n\n");

        }
    }
    fclose(pProd);
    fclose(auxProd);
}

void indice_produtos()
{

    indProd = fopen("indiceProduto.dat", "a+");

    if (indProd == NULL)
    {

        printf("Erro de Alocação\n");
        exit(1);
    }

    else
    {

        fseek(pProd, SEEK_SET, 1);
        fread(&estoque.codigo, sizeof(estoque.codigo), 1, pProd);
        fwrite(&estoque.codigo, sizeof(estoque.codigo), 1, indProd);
    }

    fclose(indProd);
}

void abrir_arq_prod()
{

    pProd = fopen("produtos.dat", "a+");
    auxProd = fopen("auxiliarProd.dat", "a+");
    if (pProd == NULL || auxProd == NULL)
    {
        printf("Erro de alocaçao\n");
        exit(1);
    }
}

void cadastro_produtos()
{
    abrir_arq_prod();

    printf("Digite o codigo do produto: ");
    scanf("%d", &estoque.codigo);
    printf("Informe o nome do produto: ");
    fscanf(stdin, " %49[^\n]", estoque.nome);
    printf("Digite a quantidade de produto(s): ");
    scanf("%d", &estoque.quantidade);
    printf("O valor do produto R$: ");
    scanf(" %f", &estoque.valor);
    printf("====================================\n\n");
    fseek(pProd, SEEK_END, 1);
    fwrite(&estoque, sizeof(estoque), 1, pProd);
    indice_produtos();

    fclose(pProd);
    fclose(auxProd);
}

void consulta_produtos()
{
    abrir_arq_prod();
    int codigo, a = 0;
    printf("Informe um codigo a ser pesquisado: ");
    scanf("%d", &codigo);
    fseek(pProd, SEEK_SET, 1);
    fread(&estoque, sizeof(estoque), 1, pProd);
    while (!feof(pProd))
    {
        if (estoque.codigo == codigo)
        {
            a++;
            printf("Produto Encontrado com sucesso!\n");

            printf("Codigo do produto: %d\n", estoque.codigo);
            printf("Nome do produto: %s\n", estoque.nome);
            printf("Quantidade: %d\n", estoque.quantidade);
            printf("Valor do produto R$:%f\n", estoque.valor);
            printf("====================================\n\n");
        }
        fread(&estoque, sizeof(estoque), 1, pProd);
    }
    if (a == 0)
        printf(("Produto não encontrado!\n"));
    fclose(pProd);
    fclose(auxProd);
}

void exclusao_produtos()
{
    abrir_arq_prod();
    int codigo, a = 0;
    printf("Informe um codigo a ser pesquisado: ");
    scanf("%d", &codigo);
    fseek(pProd, SEEK_SET, 1);
    fread(&estoque, sizeof(estoque), 1, pProd);
    while (!feof(pProd))
    {
        if (estoque.codigo == codigo)
            a++;
        else
            fwrite(&estoque, sizeof(estoque), 1, auxProd);
        fread(&estoque, sizeof(estoque), 1, pProd);
    }

    if (a == 0)
        printf("Produto não encontrado!\n");
    else
        printf("Produto Excluido com sucesso!\n");
    fclose(pProd);
    fclose(auxProd);
    remove("produtos.dat");
    rename("auxiliarProd.dat", "produtos.dat");
    remove("auxiliarProd.dat");
}

void alterar_produtos()
{
    abrir_arq_prod();
    int codigo, a = 0;
    printf("Informe um codigo a ser pesquisado: ");
    scanf("%d", &codigo);
    fseek(pProd, SEEK_SET, 1);
    fread(&estoque, sizeof(estoque), 1, pProd);
    while (!feof(pProd))
    {
        if (estoque.codigo == codigo)
        {
            a++;
            printf("Digite o novo codigo: ");
            scanf("%d", &estoque.codigo);
            printf("Digite o nome do produto: ");
            fscanf(stdin, " %49[^\n]", estoque.nome);
            printf("Digite a quantidade do(s) produto(s): ");
            scanf("%d", &estoque.quantidade);
            printf("Digite o valor do produto: ");
            scanf("%f", &estoque.valor);
            printf("====================================\n\n");
            fwrite(&estoque, sizeof(estoque), 1, auxProd);
            fread(&estoque, sizeof(estoque), 1, pProd);
        }

        if (a == 0)
            printf("Produto não encontrado!\n");
        else
            printf("Produto alterado com sucesso!\n");
        fclose(pProd);
        fclose(auxProd);
        remove("produtos.dat");
        rename("auxiliarProd.dat", "produtos.dat");
        remove("auxiliarProd.dat");
    }
}

FILE *pVendas;
FILE *auxVendas;
FILE *indVendas;
struct Vendas
{
    int Numero_Vendas;
    char DataVenda[10];
    int quantVendas;
} Vendas;

void listarVendas()
{
    FILE *pVendas;
    FILE *auxVendas;
    pVendas = fopen("vendas.dat", "r");
    auxVendas = fopen("auxiliar_vendas.dat", "r");
    if (pVendas == NULL || auxVendas == NULL)
    {
        printf("Erro de alocaçao\n");
        exit(1);
    }

    else
    {
        while (fread(&Vendas, sizeof(Vendas), 1, pVendas) == 1)
        {

            printf("Data da venda: %s\n", Vendas.DataVenda);
            printf("Numero da venda: %d\n", Vendas.Numero_Vendas);
            printf("Quantidade de vendas: %d\n", Vendas.quantVendas);
            printf("====================================\n\n");

        }
    }
    fclose(pVendas);
    fclose(auxVendas);
}

void indice_vendas()
{

    indVendas = fopen("indiceVendas.dat", "a+");

    if (indVendas == NULL)
    {

        printf("Erro de Alocação!\n");
        exit(1);
    }

    else
    {

        fseek(pVendas, SEEK_SET, 1);
        fread(&Vendas.Numero_Vendas, sizeof(Vendas.Numero_Vendas), 1, pVendas);
        fwrite(&Vendas.Numero_Vendas, sizeof(Vendas.Numero_Vendas), 1, indVendas);
    }

    fclose(indVendas);
}

void abrir_arq_vendas()
{

    pVendas = fopen("vendas.dat", "a+");
    auxVendas = fopen("auxiliar_vendas.dat", "a+");
    if (pVendas == NULL || auxVendas == NULL)
    {
        printf("Erro de alocaçao!\n");
        exit(1);
    }
}

void cadastro_vendas()
{
    abrir_arq_vendas();

    printf("Digite o codigo da venda: ");
    scanf("%d", &Vendas.Numero_Vendas);
    printf("Digite o codigo do cliente: ");
    scanf("%d", &clientela.codigo);
    printf("Digite o codigo do produto: ");
    scanf("%d", &estoque.codigo);
    printf("Digite a quantidade de produtos: ");
    scanf("%d", &Vendas.quantVendas);
    printf("Informe a data da venda no formato(dd/mm/aaaa): ");
    fscanf(stdin, "%s", Vendas.DataVenda);
    printf("====================================\n\n");

    fseek(pVendas, SEEK_END, 1);
    fwrite(&Vendas, sizeof(Vendas), 1, pVendas);
    indice_vendas();

    fclose(pVendas);
    fclose(auxVendas);
}

void consulta_vendas()
{
    abrir_arq_vendas();
    abrir_arq_prod();
    abrir_arq();
    int codigo, a = 0;
    printf("Informe um codigo a ser pesquisado: ");
    scanf("%d", &codigo);
    fseek(pVendas, SEEK_SET, 1);
    fread(&Vendas, sizeof(Vendas), 1, pVendas);
    fseek(pCLT, SEEK_SET, 1);
    fread(&clientela, sizeof(clientela), 1, pCLT);
    fseek(pProd, SEEK_SET, 1);
    fread(&estoque, sizeof(estoque), 1, pProd);
    float valor_total;

    while (!feof(pVendas))
    {
        if (Vendas.Numero_Vendas == codigo)
        {
            a++;
            printf("Venda Encontrado com sucesso!\n");

            printf("Codigo do produto: %d\n", estoque.codigo);
            printf("Codigo do cliente comprador: %d\n", clientela.codigo);
            printf("Quantidade do produto vendido: %d\n", Vendas.quantVendas);
            printf("Data da venda: %s\n", Vendas.DataVenda);
            printf("Valor Total da Venda: %.2f\n", valor_total = (int)(Vendas.quantVendas) * (float)(estoque.valor));
            printf("====================================\n\n");
        }
        fread(&Vendas, sizeof(Vendas), 1, pVendas);
    }
    if (a == 0)
        printf(("Venda não encontrada!\n"));
    fclose(pVendas);
    fclose(auxVendas);
    fclose(pCLT);
    fclose(auxCLT);
    fclose(pProd);
    fclose(auxProd);
}

void exclusao_vendas()
{
    abrir_arq_vendas();
    int codigo, a = 0;
    printf("Informe um codigo a ser pesquisado: ");
    scanf("%d", &codigo);
    fseek(pVendas, SEEK_SET, 1);
    fread(&Vendas, sizeof(Vendas), 1, pVendas);
    while (!feof(pVendas))
    {
        if (estoque.codigo == codigo)
            a++;
        else
            fwrite(&Vendas, sizeof(Vendas), 1, auxVendas);
        fread(&Vendas, sizeof(Vendas), 1, pVendas);
    }

    if (a == 0)
        printf("Venda não encontrada!\n");
    else
        printf("Venda Excluida com sucesso!\n");
    fclose(pVendas);
    fclose(auxVendas);
    remove("vendas.dat");
    rename("auxiliar_vendas.dat", "vendas.dat");
    remove("auxiliar_vendas.dat");
}

void alterar_vendas()
{
    abrir_arq_vendas();
    int codigo, a = 0;
    printf("Informe um codigo a ser pesquisado: ");
    scanf("%d", &codigo);
    fseek(pVendas, SEEK_SET, 1);
    fread(&Vendas, sizeof(Vendas), 1, pVendas);
    while (!feof(pVendas))
    {
        if (estoque.codigo == codigo)
        {
            a++;
            printf("Digite o novo codigo do produto: ");
            scanf("%d", &estoque.codigo);
            printf("Digite o novo codigo do cliente: ");
            scanf("%d", &estoque.codigo);
            printf("Informe a nova quantidade de produtos vendidos: ");
            scanf("%d", &Vendas.Numero_Vendas);
            printf("Informe o novo valor total da venda: ");
            scanf("%f", &estoque.valor);
            printf("Informe a nova data da venda: ");
            fscanf(stdin, " %s", Vendas.DataVenda);
            printf("====================================\n\n");
            fwrite(&Vendas, sizeof(Vendas), 1, auxVendas);
            fread(&Vendas, sizeof(Vendas), 1, pVendas);
        }

        if (a == 0)
            printf("Venda não encontrado!\n");
        else
            printf("Venda alterada com sucesso!\n");
        fclose(pVendas);
        fclose(auxVendas);
        remove("vendas.dat");
        rename("auxiliar_vendas.dat", "venda.dat");
        remove("auxiliar_vendas.dat");
    }
}

void menu()
{
    int op;
    printf("//////////Clientes////////\n");
    printf("==========================\n");
    printf("||1- Cadastro do cliente||\n");
    printf("||2- Consulta ao cliente||\n");
    printf("||3- Excluir cliente    ||\n");
    printf("||4- Alterar cliente    ||\n");
    printf("||5- Listar Clientes    ||\n");
    printf("==========================\n");
    printf("\n");
    printf("/////////Produto////////\n");
    printf("========================\n");
    printf("||6- Cadastrar Produto ||\n");
    printf("||7- Consultar Produto ||\n");
    printf("||8- Excluir Produto   ||\n");
    printf("||9- Alterar Produto   ||\n");
    printf("||10- Listar Produtos  ||\n");
    printf("========================\n");
    printf("\n");
    printf("////////Vendas/////////\n");
    printf("=======================\n");
    printf("||11- Cadastro Vendas ||\n");
    printf("||12- Consultar Venda ||\n");
    printf("||13- Excluir Venda   ||\n");
    printf("||14- Alterar Venda   ||\n");
    printf("||15- Listar Vendas   ||\n");
    printf("=======================\n");
    printf("\n");
    printf("===========\n");
    printf("||0- Sair||\n");
    printf("===========\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        cadastro();
        break;
    case 2:
        consulta();
        break;
    case 3:
        exclusao();
        break;
    case 4:
        alterar();
        break;
    case 5:
        listarClientes();
        break;
    case 6:
        cadastro_produtos();
        break;
    case 7:
        consulta_produtos();
        break;
    case 8:
        exclusao_produtos();
        break;
    case 9:
        alterar_produtos();
        break;
    case 10:
        listarProd();
        break;
    case 11:
        cadastro_vendas();
        break;
    case 12:
        consulta_vendas();
        break;
    case 13:
        exclusao_vendas();
        break;
    case 14:
        alterar_vendas();
        break;
    case 15:
        listarVendas();
        break;
    case 0:
        sair = true;
        break;
    default:
        printf("Opção Invalida\n");
        break;
    }
}

int main()
{

    while (!sair)
    {
        menu();
    }
    return 0;
}
