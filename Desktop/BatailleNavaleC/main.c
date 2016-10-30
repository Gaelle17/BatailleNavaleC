#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define MAP_W 24
#define MAP_H 18
#define MAP_ITEMS 4
#define PLAYER_STATS 3
#define MAP_BAT1 0
#define MAP_BAT2 2
#define MAP_J1 3
#define MAP_J2 1
#define ID_CORVET 1
#define ID_DESTROYER 2
#define ID_CROISEUR 3
#define ID_PORTA 4
#define T_CORVET 1
#define T_DESTROYER 3
#define T_CROISEUR 4
#define T_PORTA 6
#define NB_CORVET 1
#define NB_DESTROYER 2
#define NB_CROISEUR 2
#define NB_PORTA 1

void waitFor ( unsigned int secs ){
    unsigned int retTime = time(0) + secs ;
    while ( time(0) < retTime ) ;
}

int doRand( int startVal , int endVal ){
    waitFor(0.05) ;
    srand( time(NULL) * rand() ) ;
    if( startVal == 0 && endVal == 1 ){
        return rand() % 2 ;
    }else{
        return ( rand() % ( ( endVal + startVal -1 ) ) + startVal ) ;
    }
}

void Color( int couleurDuTexte , int couleurDeFond ){  //Fonction trouvée sur internet pour modifier les couleurs imprimées
    HANDLE H = GetStdHandle( STD_OUTPUT_HANDLE ) ;
    SetConsoleTextAttribute( H , couleurDeFond * 16 + couleurDuTexte ) ;
}
// Color( , ) -> 10 == vert ; 12 == rouge ; 9 == bleu ; 7 == gris ; 15 == blanc ; 0 == noir

void PrintTableau( int map[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int i , j , k ;
    int n = 1 ;
    k = n ;
    for( i = -1 ; i < MAP_H ; i++ ){
        if ( i == -1 ){
            printf( "#" ) ;
        }else{
            printf( "%d" , n ) ;
            n = n + 1 ;
        }
        for( j = -1 ; j < MAP_W ; j++ ){
            if( j == -1 && i != -1 ){
                printf( "%d" , k ) ;
                k = k + 1 ;
            }else{
                printf( "%d" , map[i][j][item] ) ;
            }
        }
        printf( "\n" );
    }
}

void PrintTableauColor( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int i , j , k ;
    int n = 1 ;
    k = n ;
    for( i = -1 ; i < MAP_H ; i++ ){
        if ( i == -1 ){
            Color( 15 , 0 ) ;
            printf( "#" ) ;
        }else{
            Color( 15 , 0 ) ;
            printf( "%d" , n ) ;
            n = n + 1 ;
        }
        for( j = -1 ; j < MAP_W ; j++ ){
            if( j == -1 && i != -1 ){
                Color( 15 , 0 ) ;
                printf( "%d" , k ) ;
                k = k + 1 ;
            }else{
                if ( plat[i][j][item] == 0 ){
                     Color( 9 , 9 ) ;
                     printf( "%d" , plat[i][j][item] ) ;
                }else if ( plat[i][j][item] == 9 ){
                    Color( 7 , 7 ) ;
                    printf( "%d" , plat[i][j][item] ) ;
                }else if ( plat[i][j][item] == 8 ){
                    Color( 0 , 12 ) ;
                    printf( "%d" , plat[i][j][item] ) ;
                }else{
                    Color( 0 , 10 ) ;
                    printf( "%d" , plat[i][j][item] ) ;
                }
            }
        }printf("\n");
    }
}

void PlaceAleaCorvet( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int x = doRand( 0 , MAP_W - T_CORVET ) ;
    int y = doRand( 0 , MAP_H - T_CORVET ) ;
    int p = doRand( 0 , 1 ) ;
    int i = y ;
    int n = 0 ;
    if( ( p == 0 ) && ( ( y + T_CORVET - 1 ) < MAP_H ) ){
        for( i = y ; i < y + T_CORVET ; i++ ){
            if( plat [i][x][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n == T_CORVET ){
            i = y ;
            for ( i = y ; i < y + T_CORVET ; i++ ){
                plat [i][x][item] = ID_CORVET ;
            }
        }else{
            PlaceAleaCorvet( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }else if ( p == 1 && (x + T_CORVET - 1) < MAP_W ){
        for( i = x ; i < x + T_CORVET ; i++ ){
            if( plat [y][i][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n == T_CORVET ){
            i = x ;
            for ( i = x ; i < x + T_CORVET ; i++ ){
                plat [y][i][item] = ID_CORVET ;
            }
        }else{
            PlaceAleaCorvet( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }
}

void PlaceAleaDestroyer( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int x = doRand( 0 , MAP_W - T_DESTROYER ) ;
    int y = doRand( 0 , MAP_H - T_DESTROYER ) ;
    int p = doRand( 0 , 1 ) ;
    int i = y ;
    int n = 0 ;
    if( p == 0 && ( y + T_DESTROYER - 1 ) < MAP_H ){
        for( i = y ; i < y + T_DESTROYER ; i++ ){
            if( plat [i][x][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n == T_DESTROYER ){
            i = y ;
            for ( i = y ; i < y + T_DESTROYER ; i++ ){
                plat [i][x][item] = ID_DESTROYER ;
            }
        }else{
            PlaceAleaDestroyer( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }else if ( p == 1 && ( x + T_DESTROYER - 1 ) < MAP_W ){
        for( i = x ; i < x + T_DESTROYER ; i++ ){
            if(plat [y][i][item] == 0){
                n = n + 1 ;
            }
        }if ( n == T_DESTROYER ){
            i = x ;
            for ( i = x ; i < x + T_DESTROYER ; i++ ){
                plat [y][i][item] = ID_DESTROYER ;
            }
        }else{
            PlaceAleaDestroyer( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }
}

void PlaceAleaCroiseur( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int x = doRand( 0 , MAP_W - T_CROISEUR ) ;
    int y = doRand( 0 , MAP_H - T_CROISEUR ) ;
    int p = doRand( 0 , 1 ) ;
    int i = y ;
    int n = 0 ;
    if( p == 0 && ( y + T_CROISEUR - 1 ) < MAP_H ){
        for( i = y ; i < y + T_CROISEUR ; i++ ){
            if( plat [i][x][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n == T_CROISEUR ){
            i = y ;
            for ( i = y ; i < y + T_CROISEUR ; i++ ){
                plat [i][x][item] = ID_CROISEUR ;
            }
        }else{
            PlaceAleaCroiseur( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }else if ( p == 1 && ( x + T_CROISEUR - 1 ) < MAP_W ){
        for( i = x ; i < x + T_CROISEUR ; i++ ){
            if( plat [y][i][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n == T_CROISEUR ){
            i = x ;
            for ( i = x ; i < x + T_CROISEUR ; i++ ){
                plat [y][i][item] = ID_CROISEUR ;
            }
        }else{
            PlaceAleaCroiseur( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }
}

void PlaceAleaPortA( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int x = doRand( 0 , MAP_W - T_PORTA ) ;
    int y = doRand( 0 , MAP_H - T_PORTA ) ;
    int p = doRand( 0 , 1 ) ;
    int i = y ;
    int n = 0 ;
    if( p == 0 && ( ( y + T_PORTA - 1 ) < MAP_H ) ){
        for( i = y ; i < y + T_PORTA ; i++ ){
            if( plat[i][x][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n == T_PORTA ){
            i = y ;
            for ( i = y ; i < y + T_PORTA ; i++ ){
                plat [i][x][item] = ID_PORTA ;
            }
        }else{
            PlaceAleaPortA( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }else if ( p == 1 && (  x + T_PORTA - 1) < MAP_W ){
        for( i = x ; i < x + T_PORTA ; i++ ){
            if( plat [y][i][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n == T_PORTA ){
            i = x ;
            for ( i = x ; i < x + T_PORTA ; i++ ){
                plat [y][i][item] = ID_PORTA ;
            }
        }else{
            PlaceAleaPortA( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }
}
/* On aurait également pu créer une fonction PlaceAlea qui prendrait en plus les arguments
de taille et identifiant bateau au lieu de faire une fonction pour chaque bateau */

void PlaceCorvetJ( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int x , y , i ;
    int n = 0 ;
    char p ;
    printf( " Premières coordonnées du Croiseur en x ?  \n " ) ;
    scanf( "%d" , &x ) ;
    fflush( stdin ) ;
    printf( " Premières coordonnées du Croiseur en y ?  \n " ) ;
    scanf( "%d" , &y ) ;
    fflush( stdin ) ;
    printf( " Position verticale ou horizontales ? V / H  \n " ) ;
    scanf( "%c[VH]" , &p ) ;
    fflush( stdin ) ;
    if( p == 'V' && ( y + T_CORVET - 1 ) < MAP_H ){
        for( i = y ; i < y + T_CORVET ; i++ ){
            if( plat [i][x][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n = T_CORVET ){
            i = y ;
            for ( i = y ; i < y + T_CORVET ; i++ ){
                plat [i][x][item] = ID_CORVET ;
            }
        }else{
            PlaceCorvetJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }else if ( p == 'H' && ( x + T_CORVET - 1 ) < MAP_W ){
        for( i = x ; i < x + T_CORVET ; i++ ){
            if( plat [y][i][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n = T_CORVET ){
            i = x ;
            for ( i = x ; i < x + T_CORVET ; i++ ){
                plat [y][i][item] = ID_CORVET ;
            }
        }else{
            PlaceCorvetJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }
}

void PlaceDestroyerJ( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int x , y , i ;
    int n = 0 ;
    char p ;
    printf( " Premières coordonnées du Destroyer en x ?  \n " ) ;
    scanf( "%d" , &x ) ;
    fflush( stdin ) ;
    printf( " Premières coordonnées du Destroyer en y ?  \n " ) ;
    scanf( "%d" , &y ) ;
    fflush( stdin ) ;
    printf( " Position verticale ou horizontales ? V / H  \n " ) ;
    scanf( "%c[VH]" , &p ) ;
    fflush( stdin ) ;
    if( p == 'V' && ( y + T_DESTROYER - 1 ) < MAP_H ){
        for( i = y ; i < y + T_DESTROYER ; i++ ){
            if( plat [i][x][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n = T_DESTROYER ){
            i = y ;
            for ( i = y ; i < y + T_DESTROYER ; i++ ){
                plat [i][x][item] = ID_DESTROYER ;
            }
        }else{
            PlaceDestroyerJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }else if ( p == 'H' && ( x + T_DESTROYER - 1 ) < MAP_W ){
        for( i = x ; i < x + T_DESTROYER ; i++ ){
            if( plat [y][i][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n = T_DESTROYER ){
            i = x ;
            for ( i = x ; i < x + T_DESTROYER ; i++ ){
                plat [y][i][item] = ID_DESTROYER ;
            }
        }else{
            PlaceDestroyerJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }
}

void PlaceCroiseurJ( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int x , y , i ;
    int n = 0 ;
    char p ;
    printf( " Premières coordonnées du Croiseur en x ?  \n " ) ;
    scanf( "%d" , &x ) ;
    fflush( stdin ) ;
    printf( " Premières coordonnées du Croiseur en y ?  \n " ) ;
    scanf( "%d" , &y ) ;
    fflush( stdin ) ;
    printf( " Position verticale ou horizontales ? V / H  \n " ) ;
    scanf( "%c[VH]" , &p ) ;
    fflush( stdin ) ;
    if( p == 'V' && ( y + T_CROISEUR - 1 ) < MAP_H ){
        for( i = y ; i < ( y + T_CROISEUR ) ; i++ ){
            if( plat[i][x][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n = T_CROISEUR ){
            i = y ;
            for ( i = y ; i < y + T_CROISEUR ; i++ ){
                plat [i][x][item] = ID_CROISEUR ;
            }
        }else{
            PlaceCroiseurJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }else if ( ( p == 'H' ) && ( ( x + T_CROISEUR - 1 ) < MAP_W ) ){
        for( i = x ; i < x + T_CROISEUR ; i++ ){
            if( plat [y][i][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n = T_CROISEUR ){
            i = x ;
            for ( i = x ; i < x + T_CROISEUR ; i++ ){
                plat [y][i][item] = ID_DESTROYER ;
            }
        }else{
            PlaceCroiseurJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }
}

void PlacePortAJ( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int x , y , i ;
    int n = 0 ;
    char p ;
    printf( " Premières coordonnées du Port-avion en x ?  \n " ) ;
    scanf( "%d" , &x ) ;
    fflush( stdin ) ;
    printf( " Premières coordonnées du Port-avion en y ?  \n " ) ;
    scanf( "%d" , &y ) ;
    fflush( stdin ) ;
    printf( " Position verticale ou horizontales ? V / H  \n " ) ;
    scanf( "%c[VH]" , &p ) ;
    fflush( stdin ) ;
    if( p == 'V' && ( y + T_PORTA - 1 ) < MAP_H ){
        for( i = y ; i < y + T_PORTA ; i++ ){
            if( plat [i][x][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n = T_PORTA ){
            i = y ;
            for ( i = y ; i < y + T_PORTA ; i++ ){
                plat [i][x][item] = ID_PORTA ;
            }
        }else{
            PlacePortAJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }else if ( p == 'H' && ( x + T_PORTA - 1 ) < MAP_W ){
        for( i = x ; i < x + T_PORTA ; i++ ){
            if( plat [y][i][item] == 0 ){
                n = n + 1 ;
            }
        }if ( n = T_PORTA ){
            i = x ;
            for ( i = x ; i < x + T_PORTA ; i++ ){
                plat [y][i][item] = ID_PORTA ;
            }
        }else{
            PlacePortAJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        }
    }
}
// Même remarque que pour le placement aléatoire d'un bateau

void Menu( int * a ){
    printf( "Bataille navale \n \n " ) ;
    printf( "Mode de jeux : \n " ) ;
    printf( "   1 -> Joueur 1 VS Joueur 2 \n " ) ;
    printf( "   2 -> Joueur VS IA \n " ) ;
    printf( "   3 -> IA 1 VS IA 2 \n " ) ;
    printf( "   4 -> charger une partie \n " ) ;
    printf( "   5 -> quitter \n " ) ;
    printf( " La sauvegarde de la partie est automatique et uniquement s'il y a au moins un joueur dans la partie\n " ) ;
    scanf( "%d" , &*a ) ;
    fflush( stdin ) ;
}

char ColorOrNot( char * c ){
    printf( " Voulez-vous la version couleur ? O / N \n " ) ;
    scanf( "%c[ON]" , & * c ) ;
    fflush( stdin ) ;
}

void PlacementBateauxIA( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item ){
    int i = 0 ;
    for ( i = 0 ; i < NB_CORVET ; i++ ){
        PlaceAleaCorvet( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS], item) ;
        getchar() ;
        system( "cls" ) ;
    } i = 0 ;
    for ( i = 0 ; i < NB_DESTROYER ; i++ ){
        PlaceAleaDestroyer( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS], item) ;
        getchar() ;
        system( "cls" ) ;
    } i = 0 ;
    for ( i = 0 ; i < NB_CROISEUR ; i++ ){
        PlaceAleaCroiseur( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS], item) ;
        getchar() ;
        system( "cls" ) ;
    } i = 0 ;
    for ( i = 0 ; i < NB_PORTA ; i++ ){
        PlaceAleaPortA( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS], item) ;
        getchar() ;
        system( "cls" ) ;
    }
}

void PlacementBateauxJoueur( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item , char * c ){
    int i = 0 ;
    for ( i = 0 ; i < NB_CORVET ; i++ ){
        printf( " Placer un Corvette \n " ) ;
        PlaceCorvetJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        if ( *c == 'O' ){
            PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS], item ) ;
        }else{
            PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS], item ) ;
        }
        getchar() ;
        system( "cls" ) ;
    } i = 0 ;
    for ( i = 0 ; i < NB_DESTROYER ; i++ ){
        printf( " Placer un Destroyer \n " ) ;
        PlaceDestroyerJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        if ( *c == 'O' ){
            PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS], item ) ;
        }else{
            PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS], item ) ;
        }
        getchar() ;
        system( "cls" ) ;
    } i = 0 ;
    for ( i = 0 ; i < NB_CROISEUR ; i++ ){
        printf( " Placer un Croiseur \n " ) ;
        PlaceCroiseurJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        if ( *c == 'O' ){
            PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS], item ) ;
        }else{
            PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS], item ) ;
        }
        getchar() ;
        system( "cls" ) ;
    } i = 0 ;
    for ( i = 0 ; i < NB_PORTA ; i++ ){
        printf( " Placer un Porte-avion \n " ) ;
        PlacePortAJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        if ( *c == 'O' ){
            PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS], item ) ;
        }else{
            PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS], item ) ;
        }
        getchar() ;
        system( "cls" ) ;
    }
}

void InitJ1vsJ2( int plat[MAP_H][MAP_W][MAP_ITEMS] , char * c ){
    int J1[PLAYER_STATS] ;
    J1[0] = MAP_BAT1 ;
    J1[1] = MAP_J1 ;
    int J2[PLAYER_STATS] ;
    J2[0] = MAP_BAT2 ;
    J2[1] = MAP_J2 ;
    if ( * c == 'O' ){
        getchar() ;
        Color( 15 , 0 ) ;
        printf( " Joueur 1 , placer vos bateaux \n " ) ;
        getchar() ;
        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] ) ;
        getchar() ;
        system( "cls" ) ;
        PlacementBateauxJoueur( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] , * c ) ;
        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] ) ;
        getchar() ;
        system( "cls" ) ;
        getchar() ;
        Color( 15 , 0 ) ;
        printf( " Joueur 2 , placer vos bateaux \n " ) ;
        getchar() ;
        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , J2[0] ) ;
        getchar() ;
        system( "cls" ) ;
        PlacementBateauxJoueur( plat[MAP_H][MAP_W][MAP_ITEMS] , J2[0] , * c ) ;
        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , J2[0] ) ;
        getchar() ;
        system( "cls" ) ;
    }else{
        getchar() ;
        printf( " Joueur 1 , placer vos bateaux \n " ) ;
        getchar() ;
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] ) ;
        getchar() ;
        system( "cls" ) ;
        PlacementBateauxJoueur( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] , * c ) ;
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] ) ;
        getchar() ;
        system( "cls" ) ;
        getchar() ;
        printf( " Joueur 2 , placer vos bateaux \n " ) ;
        getchar() ;
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , J2[0] ) ;
        getchar() ;
        system( "cls" ) ;
        PlacementBateauxJoueur( plat[MAP_H][MAP_W][MAP_ITEMS] , J2[0] , * c ) ;
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , J2[0] ) ;
        getchar() ;
        system( "cls" ) ;
    }
}

void InitIA1vsIA2( int plat[MAP_H][MAP_W][MAP_ITEMS] ){
    int IA1[PLAYER_STATS] ;
    IA1[0] = MAP_BAT1 ;
    IA1[1] = MAP_J1 ;
    int IA2[PLAYER_STATS] ;
    IA2[0] = MAP_BAT2 ;
    IA2[1] = MAP_J2 ;
    PlacementBateauxIA( plat[MAP_H][MAP_W][MAP_ITEMS] , IA1[0] ) ;
    PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , IA1[0] ) ;
    getchar() ;
    system( "cls" ) ;
    getchar() ;
    PlacementBateauxIA( plat[MAP_H][MAP_W][MAP_ITEMS] , IA2[0] ) ;
    PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS], IA2[0] ) ;
    getchar() ;
    system( "cls" ) ;
    getchar() ;
}

void InitJ1vsIA2( int plat[MAP_H][MAP_W][MAP_ITEMS] , char * c ){
    int J1[PLAYER_STATS] ;
    J1[0] = MAP_BAT1 ;
    J1[1] = MAP_J1 ;
    int IA2[PLAYER_STATS] ;
    IA2[0] = MAP_BAT2 ;
    IA2[1] = MAP_J2 ;
    if ( *c == 'O' ){
        getchar() ;
        Color( 15 , 0 ) ;
        printf( " Joueur 1 , placer vos bateaux \n " ) ;
        getchar() ;
        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] ) ;
        getchar() ;
        system( "cls" ) ;
        PlacementBateauxJoueur( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] , * c ) ;
        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] ) ;
    }else{
        getchar() ;
        printf( " Joueur 1 , placer vos bateaux \n " ) ;
        getchar() ;
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] ) ;
        getchar() ;
        system( "cls" ) ;
        PlacementBateauxJoueur( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] , * c ) ;
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , J1[0] ) ;
    }getchar() ;
    system( "cls" ) ;
    getchar() ;
    PlacementBateauxIA( plat[MAP_H][MAP_W][MAP_ITEMS] , IA2[0] ) ;
    getchar() ;
    system( "cls" ) ;
    getchar() ;
}

void TireIA( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item , int * batrest ){            // Tire IA mode IA vs IA
    int a , b ;
    a = doRand( 0 , MAP_H - 1 ) ;
    b = doRand( 0 , MAP_W - 1 ) ;
    if ( plat[a][b][item] != 9 && plat[a][b][item] != 8 ){
        if ( plat[a][b][item+1] != 0 ){
            plat[a][b][item] = 8 ;
            plat[a][b][item + 1] = plat[a][b][item] ;
            * batrest -- ;
            printf( " Touché \n " ) ;
        }else{
            plat[a][b][item] = 9 ;
            printf( " Raté \n " ) ;
        }
    }else{
        TireIA( plat[MAP_H][MAP_W][MAP_ITEMS] , item , * batrest ) ;
    }
}

void TireIA2( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item , int * batrest ){
    int a , c , b , e , f ;
    a = doRand( 0 , 2 ) ;
    if ( a == 0 || a == 2 ){
        c = doRand( 0 , MAP_H - 1 ) ;
        b = doRand( 0 , MAP_W - 1 ) ;
        if ( plat[c][b][item ] != 9 && plat[c][b][item] != 8 ){
            if ( plat[c][b][item+1] != 0 ){
                plat[c][b][item] = 8 ;
                plat[c][b][item + 1] = plat[c][b][item] ;
                * batrest -- ;
                printf( " Touché \n " ) ;
           }else{
                plat[c][b][item] = 9 ;
                printf( " Raté \n " ) ;
           }
       }else{
            TireIA( plat[MAP_H][MAP_W][MAP_ITEMS] , item , * batrest ) ;
       }
    }else{
        c = 0 ;
        b = 0 ;
        for ( c = 0 ; c < MAP_H ; c++ ){
            for ( b = 0 ; b < MAP_W ; b++ ){
                if ( ( plat[c][b][item] != 0 ) && ( plat[c][b][item] != 8 ) ){
                    e = c ;
                    f = b ;
                }
            }
        }plat[e][f][item] = 8 ;
    plat[e][f][item + 1] = plat[c][b][item] ;
    printf( " Touché \n " ) ;
    }
}

void TireJ( int plat[MAP_H][MAP_W][MAP_ITEMS] , int item , int * batrest , char * c ){
    int a , b ;
    if ( c == '0' ){
        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
        Color( 15 , 0 ) ;
    }else{
        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , item ) ;
    }
    printf( " Sur quelle ligne voulez-vous tirer ? \n " ) ;
    scanf( "%d" , a ) ;
    fflush(stdin) ;
    printf( " Sur quelle colonne voulez-vous tirer ? \n " ) ;
    scanf( "%d" , a ) ;
    fflush(stdin) ;
    if ( plat[a][b][item] != 9 && plat[a][b][item] != 8 ){
        if ( plat[a][b][item+1] != 0 ){
            plat[a][b][item] = 8 ;
            plat[a][b][item + 1] = plat[a][b][item] ;
            * batrest -- ;
            printf( " Touché \n " ) ;
        }else{
            plat[a][b][item + 1] = 9 ;
            printf( " Raté \n " ) ;
        }
    }else{
        TireJ( plat[MAP_H][MAP_W][MAP_ITEMS] , item , * batrest , * c ) ;
    }
}

void BatailleSave( int map[MAP_H][MAP_W][MAP_ITEMS] , int * a , int * n , int * batrest1 , int * batrest2 , char * c ){
    FILE * fp ;
    fp = fopen ( " ./Sauvegarde.txt " , " w+ " ) ;
    int i , j , k ;
    for( i = 0 ; i < MAP_H ; i++ ){
        for( j = 0 ; j < MAP_W ; j++ ){
            for( k = 0 ; k < MAP_ITEMS ; k++ ){
                fprintf( fp , "%d" , (int)map[i][j][k] );
            }
        }
    }printf( fp , "%d\n%d\n%d\n%d\n%c" , * a , * n , * batrest1 , * batrest2 , * c ) ;
    fclose(fp);
}

void BatailleLoad( int map[MAP_H][MAP_W][MAP_ITEMS] ){
    FILE * fp ;
    int * a ;
    int * n ;
    int * batrest1 ;
    int * batrest2 ;
    int i , j , k ;
    int c ;
    fp = fopen( " ./file.txt " , " r " ) ;
    for( i = 0 ; i < MAP_H ; i++ ){
        for( j = 0 ; j < MAP_W ; j++ ){
            for( k = 0 ; k < MAP_ITEMS ; k++ ){
                c = fgetc(fp) ;
                map[i][j][k] = (int)c ;
            }
        }
    }* a = fgetc(fp) ;
    * n = fgetc(fp) ;
    * batrest1 = fgetc(fp) ;
    * batrest2 = fgetc(fp) ;
    fclose(fp);
}

void QuitterLaPartie( int plat[MAP_H][MAP_W][MAP_ITEMS] , int * a , int * n , int * batrest1 , int * batrest2 , char * c , char * q ){
    printf( " Voulez-vous quitter la partie ? O / N " ) ;
    scanf("%c[ON]", * q ) ;
    fflush(stdin) ;
    if ( * q == 'O' ){
        BatailleSave( plat[MAP_H][MAP_W][MAP_ITEMS] , * a , * n , * batrest1 , * batrest2 , * c ) ;
    }
}

void BatailleNavale(){
    int * a ;
    * a = 0 ;
    int * n ;
    int * batrest1 ;
    int * batrest2 ;
    char * c ;
    char * q ;
    int plat[MAP_H][MAP_W][MAP_ITEMS] = {0} ;
    while ( ( * a != 1 ) && ( * a != 2 ) && ( * a != 3 ) && ( * a != 4 ) && ( * a != 5 ) ){
        Menu( & a ) ;
    }
    switch( * a ){
        case 1 :
            * batrest1 = NB_CORVET * T_CORVET + NB_CROISEUR * T_CROISEUR + NB_DESTROYER * T_DESTROYER + NB_PORTA + T_PORTA ;
            * batrest2 = * batrest1 ;
            * n = ( MAP_H * MAP_W ) / 2 ;
            ColorOrNot( & c ) ;
            InitJ1vsJ2( plat[MAP_H][MAP_W][MAP_ITEMS] , & c ) ;
            while ( * n != 0 ){
                printf( " Au Joueur 1 de jouer \n " ) ;
                TireJ( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_BAT2 , & batrest1 , & c ) ;
                getchar() ;
                if ( * batrest1 == 0){
                    if ( * c == 'O' ){
                        Color( 15 , 0 ) ;
                        printf( " Le Joueur 1 a gagné \n " ) ;
                        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                        getchar() ;
                        Color( 15 , 0 ) ;
                        printf( " Le Joueur 2 a perdu \n " ) ;
                        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                    }else{
                        printf( " Le Joueur 1 a gagné \n " ) ;
                        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                        getchar() ;
                        printf( " Le Joueur 2 a perdu \n " ) ;
                        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                    }
                    break ;
                }QuitterLaPartie( plat[MAP_H][MAP_W][MAP_ITEMS] , & a , & n , & batrest1 , & batrest2 , & c , & q ) ;
                if ( * q == 'O' ){
                    break ;
                }getchar() ;
                system( "cls" ) ;
                getchar() ;
                printf( " Au Joueur 2 de jouer \n ") ;
                getchar() ;
                TireJ( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_BAT1 , & batrest2 , & c ) ;
                getchar() ;
                if ( * batrest1 == 0){
                    if ( * c == 'O' ){
                        Color( 15 , 0 ) ;
                        printf( " Le Joueur 1 a perdu \n " ) ;
                        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                        getchar() ;
                        Color( 15 , 0 ) ;
                        printf( " Le Joueur 2 a gagné \n " ) ;
                        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                    }else{
                        printf( " Le Joueur 1 a perdu \n " ) ;
                        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                        getchar() ;
                        printf( " Le Joueur 2 a gagné \n " ) ;
                        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                    }
                    break ;
                }QuitterLaPartie( plat[MAP_H][MAP_W][MAP_ITEMS] , & a , & n , & batrest1 , & batrest2 , & c , & q ) ;
                if ( * q == 'O' ){
                    break ;
                }getchar() ;
                system( "cls" ) ;
                * n -- ;
                getchar() ;
            }
        case 2 :
            * n = ( MAP_H * MAP_W ) / 2 ;
            * batrest1 = NB_CORVET * T_CORVET + NB_CROISEUR * T_CROISEUR + NB_DESTROYER * T_DESTROYER + NB_PORTA + T_PORTA ;
            * batrest2 = * batrest1 ;
            ColorOrNot( & c ) ;
            InitJ1vsIA2( plat[MAP_H][MAP_W][MAP_ITEMS] , & c ) ;
            while ( * n != 0 ){
                printf( " Au Joueur 1 de jouer \n " ) ;
                TireJ( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_BAT2 , & batrest1 , & c ) ;
                getchar() ;
                if ( * batrest1 == 0){
                    if ( * c == 'O' ){
                        Color( 15 , 0 ) ;
                        printf( " Le Joueur 1 a gagné \n " ) ;
                        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                        getchar() ;
                        Color( 15 , 0 ) ;
                        printf( " L'IA 2 a perdu \n " ) ;
                        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                    }else{
                        printf( " Le Joueur 1 a gagné \n " ) ;
                        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                        getchar() ;
                        printf( " L'IA 2 a perdu \n " ) ;
                        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                    }
                    break ;
                }QuitterLaPartie( plat[MAP_H][MAP_W][MAP_ITEMS] , & a , & n , & batrest1 , & batrest2 , & c , & q ) ;
                if ( * q == 'O' ){
                    break ;
                }getchar() ;
                system( "cls" ) ;
                getchar() ;
                printf( " A l'IA 2 de jouer \n ") ;
                getchar() ;
                TireIA2( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_BAT1 , & batrest2 ) ;
                getchar() ;
                if ( * batrest1 == 0){
                    if ( * c == 'O' ){
                        Color( 15 , 0 ) ;
                        printf( " Le Joueur 1 a perdu \n " ) ;
                        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                        getchar() ;
                        Color( 15 , 0 ) ;
                        printf( " L'IA 2 a gagné \n " ) ;
                        PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                    }else{
                        printf( " Le Joueur 1 a perdu \n " ) ;
                        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                        getchar() ;
                        printf( " L'IA 2 a gagné \n " ) ;
                        PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                    }
                    break ;
                }getchar() ;
                system( "cls" ) ;
                * n -- ;
                getchar() ;
            }
        case 3 :
            * n = ( MAP_H * MAP_W ) / 2 ;
            * batrest1 = NB_CORVET * T_CORVET + NB_CROISEUR * T_CROISEUR + NB_DESTROYER * T_DESTROYER + NB_PORTA + T_PORTA ;
            * batrest2 = * batrest1 ;
            InitIA1vsIA2( plat[MAP_H][MAP_W][MAP_ITEMS] ) ;
            while ( * n != 0 ){
                printf( " A l'IA 1 de jouer \n " ) ;
                TireIA2( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_BAT2 , & batrest1 ) ;
                getchar() ;
                if ( * batrest1 == 0){
                    printf( " L'IA 1 a gagné \n " ) ;
                    PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                    getchar() ;
                    printf( " L'IA 2 a perdu \n " ) ;
                    PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                    break ;
                }system("cls") ;
                getchar() ;
                printf( " A l'IA 2 de jouer \n ") ;
                getchar() ;
                TireIA( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_BAT1 , & batrest2 ) ;
                getchar() ;
                if ( * batrest1 == 0){
                    printf( " L' IA 2 a gagné \n " ) ;
                    PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                    getchar() ;
                    printf( " L' IA 1 a perdu \n " ) ;
                    PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                    break ;
                }system("cls") ;
                * n -- ;
                getchar() ;
            }
        case 4 :
            BatailleLoad( plat[MAP_H][MAP_W][MAP_ITEMS] ) ;
            switch( * a ){
                case 1:
                    while ( * n != 0 ){
                    printf( " Au Joueur 1 de jouer \n " ) ;
                    TireJ( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_BAT2 , & batrest1 , & c ) ;
                    getchar() ;
                    if ( * batrest1 == 0){
                        if ( * c == 'O' ){
                            Color( 15 , 0 ) ;
                            printf( " Le Joueur 1 a gagné \n " ) ;
                            PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                            getchar() ;
                            Color( 15 , 0 ) ;
                            printf( " Le Joueur 2 a perdu \n " ) ;
                            PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                        }else{
                            printf( " Le Joueur 1 a gagné \n " ) ;
                            PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                            getchar() ;
                            printf( " Le Joueur 2 a perdu \n " ) ;
                            PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                        }
                        break ;
                    }QuitterLaPartie( plat[MAP_H][MAP_W][MAP_ITEMS] , & a , & n , & batrest1 , & batrest2 , & c , & q ) ;
                    if ( * q == 'O' ){
                        break ;
                    }getchar() ;
                    system( "cls" ) ;
                    getchar() ;
                    printf( " Au Joueur 2 de jouer \n ") ;
                    getchar() ;
                    TireJ( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_BAT1 , & batrest2 , & c ) ;
                    getchar() ;
                    if ( * batrest1 == 0){
                        if ( * c == 'O' ){
                            Color( 15 , 0 ) ;
                            printf( " Le Joueur 1 a perdu \n " ) ;
                            PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                            getchar() ;
                            Color( 15 , 0 ) ;
                            printf( " Le Joueur 2 a gagné \n " ) ;
                            PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                        }else{
                            printf( " Le Joueur 1 a perdu \n " ) ;
                            PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                            getchar() ;
                            printf( " Le Joueur 2 a gagné \n " ) ;
                            PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                        }
                        break ;
                    }QuitterLaPartie( plat[MAP_H][MAP_W][MAP_ITEMS] , & a , & n , & batrest1 , & batrest2 , & c , & q ) ;
                    if ( * q == 'O' ){
                        break ;
                    }getchar() ;
                    system( "cls" ) ;
                    * n -- ;
                    getchar() ;
                }
                case 2 :
                    while ( * n != 0 ){
                        printf( " Au Joueur 1 de jouer \n " ) ;
                        TireJ( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_BAT2 , & batrest1 , & c ) ;
                        getchar() ;
                        if ( * batrest1 == 0){
                            if ( * c == 'O' ){
                                Color( 15 , 0 ) ;
                                printf( " Le Joueur 1 a gagné \n " ) ;
                                PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                                getchar() ;
                                Color( 15 , 0 ) ;
                                printf( " L'IA 2 a perdu \n " ) ;
                                PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                            }else{
                                printf( " Le Joueur 1 a gagné \n " ) ;
                                PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                                getchar() ;
                                printf( " L'IA 2 a perdu \n " ) ;
                                PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                            }
                            break ;
                        }QuitterLaPartie( plat[MAP_H][MAP_W][MAP_ITEMS] , & a , & n , & batrest1 , & batrest2 , & c , & q ) ;
                        if ( * q == 'O' ){
                            break ;
                        }getchar() ;
                        system( "cls" ) ;
                        getchar() ;
                        printf( " A l'IA 2 de jouer \n ") ;
                        getchar() ;
                        TireIA2( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_BAT1 , & batrest2 ) ;
                        getchar() ;
                        if ( * batrest1 == 0){
                            if ( * c == 'O' ){
                                Color( 15 , 0 ) ;
                                printf( " Le Joueur 1 a perdu \n " ) ;
                                PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                                getchar() ;
                                Color( 15 , 0 ) ;
                                printf( " L'IA 2 a gagné \n " ) ;
                                PrintTableauColor( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                            }else{
                                printf( " Le Joueur 1 a perdu \n " ) ;
                                PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J1 ) ;
                                getchar() ;
                                printf( " L'IA 2 a gagné \n " ) ;
                                PrintTableau( plat[MAP_H][MAP_W][MAP_ITEMS] , MAP_J2 ) ;
                            }
                            break ;
                        }getchar() ;
                        system( "cls" ) ;
                        * n -- ;
                        getchar() ;
                    }
        case 5 :
            break ;

    }
}
}


int main(){
    BatailleNavale() ;
}
