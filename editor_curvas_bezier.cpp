#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdio.h> 
#include<stdlib.h>
void mapeamento(int xtmax, int xtmin, int ytmax, int ytmin, int xumax, int xumin, int yumax, int yumin, float xu, float yu );

typedef struct
{
    float pontoInicioX;
    float pontoInicioY;
    float pontoFimX;
    float pontoFimY;
    float pontoControleAX;
    float pontoControleAY;
    float pontoControleBX;
    float pontoControleBY;
}Curvas;
float xt, yt;

int maxx, maxy, poly[10], i, errorcode;
int gd = DETECT, gm;
char driver[] = "";

void limpar_universo();
void inserir_curvas(Curvas curvas[], int numeroCurvas, int maxx, int maxy);
void mapeamento(int xtmax, int xtmin, int ytmax, int ytmin, int xumax, int xumin, int yumax, int yumin, float xu, float yu ) {
	
	xt = ((xtmax - xtmin) * (xu - xumin))/(xumax - xumin) + xtmin;
    yt = ((ytmin - ytmax) * (yu - yumin))/(yumax - yumin) + ytmax;
}
void limpar_universo(){
   clearviewport();
}

void inserir_curvas(Curvas curvas[], int numeroCurvas, int maxx, int maxy){
	limpar_universo();
	float t=0, px, py;  //pow(variável, expoente)
	int i;
	for(i=0; i < numeroCurvas;i++){
		t=0;
		while(t<1){
		   	px = pow((1-t),3) * curvas[i].pontoInicioX + 3 * t * pow((1-t),2) * curvas[i].pontoControleAX + 3 * pow(t,2) * (1-t) * curvas[i].pontoControleBX + pow(t,3) * curvas[i].pontoFimX;
		    py = pow((1-t),3) * curvas[i].pontoInicioY + 3 * t * pow((1-t),2) * curvas[i].pontoControleAY + 3 * pow(t,2) * (1-t) * curvas[i].pontoControleBY + pow(t,3) * curvas[i].pontoFimY;
		    
		    mapeamento(maxx, 0, maxy, 0, 6, 0, 6, 0, px, py );
			
			putpixel(xt, yt, WHITE);
			t = t + 0.001;
	   	
   		}
   }
   getch();
 
}


int main()
{
   Curvas curvas[10];
   
   initgraph(&gd, &gm, driver);
   errorcode=graphresult();
   if(errorcode)
       exit(1);

   maxx = getmaxx();
   maxy = getmaxy();
   
   setviewport(0,0,maxx,maxy,1);
   int opcaoCurva=0;
   int opcao=1;
   int opcaoPropriedadeCurva=1;
   int numeroCurvas=0;
	while (opcao!=4)
	{
	
		printf("\n\n ----------------------- ");
		
		printf("\n 1 - Inserir Curva ");
		printf("\n 2 - Modificar Pontos de Controle ");
		printf("\n 3 - Limpar Tela ");
		printf("\n 4 - Fechar Programa ");
		printf("\n\n Escolha uma opcao: ");
		scanf("%d",&opcao);
		
		// estrutura switch
		switch (opcao) {
			case 1:
			{
				system("cls");
				if(numeroCurvas == 0){
					printf("\n\n Opcao escolhida: 1 ");
					printf("\n\nDigite um ponto inicial\n");
					printf("\n\nDigite o ponto X\n");
					scanf("%f",&curvas[numeroCurvas].pontoInicioX);
					printf("\n\nDigite o ponto Y\n");
					scanf("%f",&curvas[numeroCurvas].pontoInicioY);
				}else{
					curvas[numeroCurvas].pontoInicioX = curvas[numeroCurvas-1].pontoFimX;
					curvas[numeroCurvas].pontoInicioY = curvas[numeroCurvas-1].pontoFimY;
				}
				
				printf("\n\nDigite um ponto final\n");
				printf("\n\nDigite o ponto X\n");
				scanf("%f",&curvas[numeroCurvas].pontoFimX);
				printf("\n\nDigite o ponto Y\n");
				scanf("%f",&curvas[numeroCurvas].pontoFimY);
				
				printf("\n\nDigite um ponto de controle 1\n");
				printf("\n\nDigite o ponto X\n");
				scanf("%f",&curvas[numeroCurvas].pontoControleAX);
				printf("\n\nDigite o ponto Y\n");
				scanf("%f",&curvas[numeroCurvas].pontoControleAY);
				
				printf("\n\nDigite um ponto de controle 2\n");
				printf("\n\nDigite o ponto X\n");
				scanf("%f",&curvas[numeroCurvas].pontoControleBX);
				printf("\n\nDigite o ponto Y\n");
				scanf("%f",&curvas[numeroCurvas].pontoControleBY);
				
				printf("\n\n Ponto Inicial (%.2f,%.2f): ", curvas[numeroCurvas].pontoInicioX, curvas[numeroCurvas].pontoInicioY);
				printf("\n\n Ponto Fim (%.2f,%.2f): ", curvas[numeroCurvas].pontoFimX, curvas[numeroCurvas].pontoFimY);
				printf("\n\n Ponto Controle A (%.2f,%.2f): ", curvas[numeroCurvas].pontoControleAX, curvas[numeroCurvas].pontoControleAY);
				printf("\n\n Ponto Controle B (%.2f,%.2f): ", curvas[numeroCurvas].pontoControleBX, curvas[numeroCurvas].pontoControleBY);
				printf("\n\nCurva adicionada! Pressione uma tecla.");
				
				++numeroCurvas;
				fflush(stdin);
				printf("\n\nNumero de Curvas: %i", numeroCurvas);
				inserir_curvas(curvas, numeroCurvas, maxx, maxy);
				break;
			}
			case 2:
			{
				while (opcaoPropriedadeCurva!=5)
				{
					printf("\n\n ----------------------- ");
					
					for(i=0;i<numeroCurvas;i++){
						printf("\n %i - Modificar Curva %i ", i+1,i+1);
					}
					printf("\n %i - Voltar ", numeroCurvas+1);
					
					printf("\n\n Escolha uma curva para editar: ");
					scanf("%d",&opcaoCurva);
					if(opcaoCurva == numeroCurvas+1){
						break;
					}
					fflush(stdin);
					printf("\n\n Escolha uma propriedade para editar: ");
					
					printf("\n\n Curva %i: ", opcaoCurva);
					printf("\n\n 1 - Ponto Inicial (%.2f,%.2f): ", curvas[opcaoCurva].pontoInicioX,curvas[opcaoCurva].pontoInicioY);
					printf("\n\n 2 - Ponto Fim (%.2f,%.2f): ", curvas[opcaoCurva].pontoFimX,curvas[opcaoCurva].pontoFimY);
					printf("\n\n 3 - Ponto Controle A (%.2f,%.2f): ", curvas[opcaoCurva].pontoControleAX,curvas[opcaoCurva].pontoControleAY);
					printf("\n\n 4 - Ponto Controle B (%.2f,%.2f): ", curvas[opcaoCurva].pontoControleBX,curvas[opcaoCurva].pontoControleBY);
					printf("\n\n 5 - Voltar");
					
					
					scanf("%d",&opcaoPropriedadeCurva);
					if(opcaoPropriedadeCurva == 5){
						opcaoPropriedadeCurva = 0;
						break;
					}
					
					switch (opcaoPropriedadeCurva) {
						case 1:
						{
							fflush(stdin);			
							printf("\n\n Digite um novo Ponto Inicial");
							printf("\n\nDigite o ponto X\n");
							scanf("%f",&curvas[opcaoCurva].pontoInicioX);
							printf("\n\nDigite o ponto Y\n");
							scanf("%f",&curvas[opcaoCurva].pontoInicioY);
							inserir_curvas(curvas, numeroCurvas, maxx, maxy);
							fflush(stdin);
							break;
						}
						case 2:
						{			
							printf("\n\n Digite um novo Ponto Fim");
							printf("\n\nDigite o ponto X\n");
							scanf("%f",&curvas[opcaoCurva].pontoFimX);
							printf("\n\nDigite o ponto Y\n");
							scanf("%f",&curvas[opcaoCurva].pontoFimY);
							inserir_curvas(curvas, numeroCurvas, maxx, maxy);
							break;
						}
						case 3:
						{		
							printf("\n\n Digite um novo Ponto de Controle A");
							printf("\n\nDigite o ponto X\n");
							scanf("%f",&curvas[opcaoCurva].pontoControleAX);
							printf("\n\nDigite o ponto Y\n");
							scanf("%f",&curvas[opcaoCurva].pontoControleAY);
							inserir_curvas(curvas, numeroCurvas, maxx, maxy);
							break;
						}
						case 4:
						{			
							printf("\n\n Digite um novo Ponto de Controle B");
							printf("\n\nDigite o ponto X\n");
							scanf("%f",&curvas[opcaoCurva].pontoControleBX);
							printf("\n\nDigite o ponto Y\n");
							scanf("%f",&curvas[opcaoCurva].pontoControleBY);
							inserir_curvas(curvas, numeroCurvas, maxx, maxy);
							break;
						}
					}
				} 
				break;
			}case 3:
			{
				limpar_universo();
				break;
			}
		}
	}
   closegraph();
   return 0;
}
