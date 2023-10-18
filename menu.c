#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 



int estoque[10]={20,30,50,40,80,20,90,50,40,20};
double crediario[10]={0,0,0,0,0,0,0,0,0,0};



void menu();    



void tabelaDeProdutos(){
    printf("\n\tCod\tProduto\t\t\tDisponiveis");
    printf("\n\t0\tSabao\t\t\t%i",estoque[0]);
    printf("\n\t1\tMacarrao\t\t%i",estoque[1]);
    printf("\n\t2\tOleo\t\t\t%i",estoque[2]);
    printf("\n\t3\tArroz\t\t\t%i",estoque[3]);
    printf("\n\t4\tFeijao\t\t\t%i",estoque[4]);
    printf("\n\t5\tBolinho ana maria\t%i",estoque[5]);
    printf("\n\t6\tPao\t\t\t%i",estoque[6]);
    printf("\n\t7\tBolo\t\t\t%i",estoque[7]);
    printf("\n\t8\tCoca cola\t\t%i",estoque[8]);
    printf("\n\t9\tItaipava\t\t%i\n\n",estoque[9]);
}



double descontoPorAtacado(int codProduto, int quantidadeDoProduto){
    double saida,
    valoresDosProdutos[]= {2.50,10.00,7.80,14.50,11.90,5.00,1.00,8.00,7.00,4.00},
    valoresComDesconto[]= {2.40,9.50 ,7.40,14.00,11.00,4.90,0.80,7.50,6.70,3.50};
    int minimoParaDesconto[]= {2,3,3,2,5,6,2,3,3,2};
    
    for(int i = 0; i <= 9; i++)
    {
        if ((codProduto==i) && (minimoParaDesconto[i]<=quantidadeDoProduto))
        {
            saida=valoresComDesconto[i]*(quantidadeDoProduto*1.00);
            break;
        } 
        else if (codProduto==i && (minimoParaDesconto[i]>quantidadeDoProduto))
        {
            saida=valoresDosProdutos[i]*quantidadeDoProduto;
            break;
        }
    }
    return saida;
}



void simularCompra(){
    double valorDaCompra=0;
    int quantidadeDoProduto, codProduto, cliente;
    char pag;
    

    printf("\"-1\" para encerrar compras.\n");
    tabelaDeProdutos();


    do
    {
        printf("\nQual o codigo do produto desejado? ");
        scanf("%i",&codProduto);

        if ((codProduto<0) || (codProduto>9)){ break; }
        
        printf("Quantas unidades? ");
        scanf("%i", &quantidadeDoProduto);

        if (estoque[codProduto]<quantidadeDoProduto)
            {
            printf("\n\tNao temos essa quantidade do produto.\n");
            } 
            else
            {
                estoque[codProduto]-=quantidadeDoProduto;
                valorDaCompra+=descontoPorAtacado(codProduto, quantidadeDoProduto);
            }
    } while (TRUE);

    system("cls");

    printf("\nQual a forma de pagamento? ");
    printf("\n\tP - Pix");
    printf("\n\tD - Dinheiro");
    printf("\n\tC - Cartao \n");
    if (valorDaCompra<100)
    {
        printf("\tF - Crediario\n"); //Senhor, que me proteja de pessoas mau intencionadas que tentarão apertar a opção escondida.
    }
    
    
    scanf(" %c",&pag);
    

    if (pag=='p'||pag=='P'){
        valorDaCompra*=0.95;
        printf("Ficou por R$%.2lf",valorDaCompra);
    }
    
    else if (pag=='d'||pag=='D'){
        valorDaCompra*=0.98;
        printf("Ficou por R$%.2lf",valorDaCompra);
    }

    else if (pag=='c'||pag=='C'){
        printf("Ficou por R$%.2lf",valorDaCompra);
    }

    else if (pag=='f'||pag=='F'){
        printf("Ficou por R$%.2lf",valorDaCompra);
        printf("\nInsira o codigo do cliente: ");
        scanf("%i",&cliente);

        crediario[cliente]+=valorDaCompra;
        printf("\nAgora o cliente tem R$%.2lf a pagar!",crediario[cliente]);  
    }
    
    else{
        printf("\nOpcao invalida. Vai dar calote em outro!");
    }
    
    
    
    

    printf("\nPressione \"-1\" para continuar... ");
    scanf(" %i",&estoque[20]);
    menu();
}



void preencherEstoque(){
    char a; int i;

    printf("\nDeseja preencher todo o estoque?(s/n) ");
    scanf(" %c", &a);

    tabelaDeProdutos();
    
    if (a=='n' || a=='N'){
        printf("\nQual o codigo do produto a ser alterado? ");
        scanf("%i", &i);

        printf("\nTinhamos %i do produto %i.", estoque[i],i);
        printf("\nDeseja mudar para quantos? ");
        scanf("%i", &estoque[i]);
    } else {
        for (i = 0; i <= 9; i++){
            printf("\nTinhamos %i do produto %i.", estoque[i],i);
            printf("\nDeseja mudar para quantos? ");
            scanf("%i", &estoque[i]);
        }
    }

    Sleep(4000);
    menu();
}



void consultarCrediario(){
    int cliente;
    printf("\nInsira o codigo do cliente: ");
    scanf("%i",&cliente);


    if (cliente<0 || cliente>9){ 
        printf("\nCliente invalido!");
        
    } else {
        printf("\nAtualmente o cliente tem R$%.2lf a pagar!",crediario[cliente]);

    }


    Sleep(4000);
    menu();
}



void pagarCrediario(){
    int cliente; 
    double valorPago;

    printf("\nInsira o codigo do cliente: ");
    scanf("%i",&cliente);

    if (cliente<0 || cliente>9){ 
        printf("\nCliente invalido!");

    } else {


        if (crediario[cliente]==0){
            printf("\nEste cliente nao tem dividas no crediario.");
            Sleep(4000);
            menu();
        }
        
        
        printf("\nAtualmente o cliente tem R$%.2lf a pagar!",crediario[cliente]);

        printf("\nInsira o valor pago: ");
        scanf("%lf",&valorPago);


        while (crediario[cliente]<valorPago){
            printf("\nValor acima do permido. Tente novamente: ");
            scanf("%lf",&valorPago);
        }


        if (valorPago<0){
            printf("\nMeu caro, acho que deveriamos conversar um pouco sobre honestidade...");
        } else {
            crediario[cliente]-=valorPago;
        }
        
        
        printf("\nRestaram R$%.2lf a pagar!",crediario[cliente]);
    }


    Sleep(4000);
    menu();
}



void perdaoDivino(){
    int possivel=0;

    for (int i = 0; i <=9; i++){
        if (crediario[i]!=0) { possivel=1; }
    }

    while (possivel==1)
    {
        int perdoado=rand()%9;
        if ((crediario[perdoado]!=0)&&(possivel=1))
        {
            printf("\nTemos um escolhido entre nos!!!\n O cliente %i recebeu o perdao de suas dividas.", perdoado);
            crediario[perdoado]=0;
            break;
        }
    }

    if (possivel==0){
        printf("Nao ha clientes devedores.");
    }
     
    
    Sleep(4000);
    menu();
}



void consultarEstoque(){

    tabelaDeProdutos();
    printf("\nPressione \"-1\" para continuar... ");
    scanf(" %i",&estoque[20]);
    menu();
}



void menu(){
    int selecao;
    system("cls");

    printf("\nPressione \"-1\" para sair.\n");
    printf("\n\t 1 - Simular Compra");
    printf("\n\t 2 - Consultar debitos de clientes do crediario");
    printf("\n\t 3 - Preencher estoque");
    printf("\n\t 4 - Consultar estoque");
    printf("\n\t 5 - Pagar debitos de clientes do crediario");
    printf("\n\t 6 - Sortear um cliente que tera sua divida do crediario perdoada\n");
    
    scanf("%i", &selecao);

    switch (selecao){
    case 1:
        system("cls");
        simularCompra();
        break;
    case 2:
        system("cls");
        consultarCrediario();
        break;
    case 3:
        system("cls");
        preencherEstoque();
        break;
    case 4:
        system("cls");
        consultarEstoque();
        break;
    case 5:
        system("cls");
        pagarCrediario();
        break;
    case 6:
        system("cls");
        perdaoDivino();//A função onde suas horações para o Deus do Pix serão atendidas...
        break;
    default:
        break;
    }

    
}



int main()
{
    menu();
    
    return 0;
}
