#include<iostream>
#include <curses.h>
#include <cstdlib>
#include <ctime>
using namespace::std;

void shuffleDeck( int[][14], int[], int[] );
void mostrarMano( int[][14] );
void imprimeJugadas( int[][14], int[], int[] );
int escaleraColor( int[]);
int escaleraReal( int[]);

int main (){
	srand(time(NULL));
	initscr();
	cbreak(); // Cerrar con Ctrl z
	int c;
	double bet = 0.00;
	double creditos = 0.00;
	int y,x; // Posicion de Pantalla
        int cartas[5][14] = { {0, 0} };
	int palos[53] = {0};
 	int valores[53] = { 0 };
	
	getmaxyx(stdscr,y,x);
	printw("Ingrese Apuesta:1. 500 2. 1000 3. 1500\n");
        refresh();
	shuffleDeck( cartas, palos, valores );
	while((c = getch()) != 27){
		move(15,30);
		mostrarMano( cartas );
		imprimeJugadas( cartas, palos, valores );
		mvprintw(0,90,"Bet: %4.2f\n", bet);
		mvprintw(1,90,"Creditos: %4.2f\n", creditos);
		refresh();
		move(30,30);
		
	}	
	// Espera entrada de usuario
        endwin(); 
	return 0;
}

void shuffleDeck(int cartas[][14], int palos[], int valores[] ) {
 	int contador;
 	int tipoCarta;
 	int numeroCarta;
 	for ( contador = 1; contador <= 52; contador++ ){ 
 		do{
 			tipoCarta = 1 + rand() % 4;
 			numeroCarta = 1 + rand() % 13;
 		}while( 0 != cartas[tipoCarta][numeroCarta] );
 		if ( 0 == cartas[tipoCarta][numeroCarta] ){
 			cartas[tipoCarta][numeroCarta] = contador;
 			palos[contador] = tipoCarta;
 			valores[contador] = numeroCarta;
 		}
 	} 
 	return;
}

void mostrarMano( int deck[][14]){
	int x,y;
	getmaxyx(stdscr,y,x);
 	const char *valores[14] = { "0", "As", "Dos", "Tres", "Cuatro", "Cinco",
 	"Seis", "Siete", "Ocho", "Nueve", "Diez",
 	"Jota", "Reina", "Rey"};
 	const char *palos[5] = { "0", "Corazones", "Treboles", "Espadas","Diamantes"};	
 	for ( int r = 1; r <= 5; r++ ){
 		for ( int y = 1; y <= 4; y++ ){
 			for ( int z = 1; z <= 13; z++ ){
 				if ( r == deck[y][z]){
					printw(" [%s  %s] ",valores[z],palos[y]);	
				}	
 			}
 		} 
 	}
 }

void imprimeJugadas( int xcartas[][14], int Fig[], int Num[] ){
	int y,x; // Posicion de Pantalla
	int contador_pares = 0;
        int contador_tercia = 0;
        int contador_poquer = 0;
 	int temp = Fig[1];
 	int iguales = 1;
 	int corrida = 0; 
 	int temp2[14] = {0 };
	getmaxyx(stdscr,y,x);

	// Revisa los numeros	
 	for ( int s = 1; s <= 5; s++ ){
 		temp2[Num[s]]++; // Se guardan los numeros de la mano en el arreglo temporal.
 	}
 	for ( int w = 1; w <= 14; w++ ){
 		if ( 2 == temp2[w] ) //Si hay un par en la mano lo guarda en contador de pares.
 			contador_pares++;
 		if ( 3 == temp2[w] ) //Si hay un trio en la mano lo guarda en contador de trios.
 			contador_tercia = 1;
 		if ( 4 == temp2[w] ){ // Si hay cuatro cartas iguales en la mano lo guarda en contador de poker.
 			contador_poquer = 1;
 		}

	}

 	if ( 0 != contador_pares ){
		if(1 == contador_pares){
			mvprintw(10,70,"Tiene 1 Par");
		}
		else{
		 	mvprintw(10,70,"Tiene 2 Pares");
		}
 	}

 	if ( 1 == contador_tercia ){
		if(0 != contador_pares){
			mvprintw(10,70,"Tiene Un Full");
		}
		else{
			mvprintw(10,70,"Tiene 1 Trio");
		}
 	}
 	if ( 1 == contador_poquer ){
		mvprintw(10,70,"Tiene Un Poker");
 	}
	//Revisa las Figuras
 	for ( int i = 2; i <= 5; i ++ ){
 		if ( Fig[ i ] != temp ){
 			iguales = -1;
 		} 
	}	
 	if ( 1 == iguales ){
 		corrida = escaleraColor( Num ); //Revisa si los numeros estan consecutivamente
 		int flor;
 		if ( 0 == corrida ){
 			flor = escaleraReal(Num); //Revisa si hay escalera real
 			if ( 0 == flor ){
				mvprintw(10,70,"Tiene Un Color (Flush)");
 			}
 			else
				mvprintw(10,70,"Tiene Una Escalera Real!");
 		}	
 		else{
			mvprintw(10,70,"Tiene Una Escalera De Color!");
 		}
 	}
 	else{
 		int escalera;
 		escalera = escaleraColor(Num);
 		if ( 1 == escalera ){
			mvprintw(10,70,"Usted tiene 1 escalera");
 		}
 	}
}

int escaleraColor( int numeros[]){
		int temporal;
 		for ( int l = 1; l < 5; l++){
 			for ( int d = 1; d < 5; d++ ){
 				if ( numeros[d + 1] < numeros[d] ){ 
 					temporal = numeros[d];
 					numeros[d] = numeros[d + 1];
 					numeros[d + 1] = temporal;
 				}
 			}
 		}
 		int ordenados = 0;
 		for ( int t = 1; t < 5; t++ ){
 			if ( numeros[t + 1] == numeros[t] + 1 ){
 				ordenados++;
 			}
 		}
	 	if ( 4 != ordenados )
 			return 0;

 		else
 			return 1;
}

int escaleraReal( int numeros[] ){
	int tempor;
 	for ( int f = 1; f < 5; f++){ // Ordena de menor a mayor los numeros
 		for ( int d = 1; d < 5; d++ ){ 
 			if ( numeros[d + 1] < numeros[d] ){
 				tempor = numeros[d];
 				numeros[d] = numeros[d + 1];
 				numeros[d + 1] = tempor;
 			}
 		}
	}
 	int variable = 10;
 	int cambio = 0;
 	if ( 1 != numeros[1] )
 		return 0;
 	else{
 		for ( int z = 2; z <= 5; z++ ){ //Abre for
 			if ( numeros[z] != variable ){
 				cambio = 1;
 			}
 			variable++;
 		}
 	}
 	if ( 0 != cambio )
 		return 0;
 	else
 		return 1;
}

