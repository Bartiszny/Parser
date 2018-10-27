#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>

using namespace std;

int main()
{

	fstream plik_wej; //plik wejsciowy
    fstream plik_wyj;//plik wyjsciowy
	
	cout<<"Podaj nazwe lub sciezk� do pliku: \n";
	char nazwa[40]; 								// tablica znak�w na nazw� lub scie�k�
	cin>>nazwa;										// wczytanie	
	plik_wej.open(nazwa,ios::in);					// otwarcie pliku do odczytu
    if( !plik_wej ) cout<<"\nNie mo�na otworzyc!";	// komunikat o b�edzie w otwarciu
    else
	{	
	
     plik_wyj.open( "Wynik.txt", ios::out );			// otwarcie pliku do zapisu
    	if( !plik_wyj ) cout<<"\nNie mo�na zapisac!"; 	// komunikat o b��dzie w otwarciu
		else{											

		// Poszukiwanie autora			 
			 char aut[]="\"author\"";				    // poszukiwany tekst 
    		 string dane;								// zmienna string na wczytane dane
    		
			 char *wynik;								// 	zmienna przechowuj�ca wynik funkcji strstr
    		 while(!plik_wej.eof())						// p�tla z wrunkiem do ko�ca pliku
				{
					getline(plik_wej,dane);				// pobranie linii danych do zmiennej dane
					wynik=strstr(dane.c_str(),aut);		// pszukuje �a�cucha "aut" w �a�cuchu "dane", string na c-string
					if(wynik!=NULL)						
						{
						
						short poz=dane.find("t=\"");		//szukanie pozycji pierwszego znaku �a�cucha	
						string podciag=dane.substr(poz+3);	// skr�cenie �a�cucha	
			
						cout<<"\nAutor: "<<podciag.substr(0,podciag.length()-2);	// wyswietlenie �a�cucha
						plik_wyj<<"Autor: "<<podciag.substr(0,podciag.length()-2);	// zapisanie do pliku wyj
						break;
						}
		    	}
		// Liczenie obrazk�w
			char img[]="<img";							 // poszukiwany tekst 
			short licz=0;								 // licznik
			while(!plik_wej.eof())						 	
				{
					getline(plik_wej,dane);
    				wynik=strstr(dane.c_str(),img);
					if(wynik!=NULL) licz+=1;			 // inkrementacja licznika
				}
			cout<<"\nLiczba ilustarcji: "<<licz;
			plik_wyj<<"\nLiczba ilustarcji: "<<licz;
			
		    
		plik_wej.clear();				//  
    	plik_wej.seekg(0, ios::beg);	// cofni�cie wewn�trznego znacznika pliku wej

  		
		// Liczenie tabel	(dzia�ania analogiczne)
		
				char tab[]="<table";
				short licz2=0;	
				while(!plik_wej.eof())
				{
				getline(plik_wej,dane);
    			wynik=strstr(dane.c_str(),tab);
				if(wynik!=NULL) licz2+=1;
				}
				cout<<"\nLiczba tabel: "<<licz2;
				plik_wyj<<"\nLiczba tabel: "<<licz2;
   				
				  
				
      	plik_wej.clear();
       	plik_wej.seekg(0, ios::beg);

	   	// Szukanie bibliografii	
			   char bibl[]="Bibliografia";				      
		
    		plik_wyj<<"\nBibliografia:\n";
			while(!plik_wej.eof())
				{
					getline(plik_wej,dane);
					wynik=strstr(dane.c_str(),bibl);
					if(wynik!=NULL)
						{
						 
						 char lista[]="<li>";
						 short licz=0;	
						 string podciag;
						 getline(plik_wej,dane); 
						 while(!plik_wej.eof() || dane.c_str()=="</ol>")
							{
						
							getline(plik_wej,dane);
							
							wynik=strstr(dane.c_str(),lista);
							
							if(wynik!=NULL) // wypisywanie bibliografii do pliku 
								{
									licz+=1;
									podciag=dane.substr(4,dane.length()-9);
									
									plik_wyj<<licz<<". "<<podciag<<endl;
																
								}	
							else if(dane.c_str()=="</ol>")
                            {
							cout<<"\nBrak listy lub blad";
							break;} 
						 	}cout<<"\nLiczba pozycji bibliografii: "<<licz<<endl ;	 // Wyswietlanie liczby bibliografii
				   
				   
				  		 }
					}
	   
		}plik_wyj.close();	// zamkni�cie pliku wyj
	}plik_wej.close();		// zamkniecie piku wej
	system("pause");
    return(0);

}
