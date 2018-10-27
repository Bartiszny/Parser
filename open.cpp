#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>

using namespace std;

int main()
{

	fstream plik_wej; //plik wejsciowy
    fstream plik_wyj;//plik wyjsciowy
	
	cout<<"Podaj nazwe lub sciezkê do pliku: \n";
	char nazwa[40]; 								// tablica znaków na nazwê lub scie¿kê
	cin>>nazwa;										// wczytanie	
	plik_wej.open(nazwa,ios::in);					// otwarcie pliku do odczytu
    if( !plik_wej ) cout<<"\nNie mo¿na otworzyc!";	// komunikat o b³edzie w otwarciu
    else
	{	
	
     plik_wyj.open( "Wynik.txt", ios::out );			// otwarcie pliku do zapisu
    	if( !plik_wyj ) cout<<"\nNie mo¿na zapisac!"; 	// komunikat o b³êdzie w otwarciu
		else{											

		// Poszukiwanie autora			 
			 char aut[]="\"author\"";				    // poszukiwany tekst 
    		 string dane;								// zmienna string na wczytane dane
    		
			 char *wynik;								// 	zmienna przechowuj¹ca wynik funkcji strstr
    		 while(!plik_wej.eof())						// pêtla z wrunkiem do koñca pliku
				{
					getline(plik_wej,dane);				// pobranie linii danych do zmiennej dane
					wynik=strstr(dane.c_str(),aut);		// pszukuje ³añcucha "aut" w ³añcuchu "dane", string na c-string
					if(wynik!=NULL)						
						{
						
						short poz=dane.find("t=\"");		//szukanie pozycji pierwszego znaku ³añcucha	
						string podciag=dane.substr(poz+3);	// skrócenie ³añcucha	
			
						cout<<"\nAutor: "<<podciag.substr(0,podciag.length()-2);	// wyswietlenie ³añcucha
						plik_wyj<<"Autor: "<<podciag.substr(0,podciag.length()-2);	// zapisanie do pliku wyj
						break;
						}
		    	}
		// Liczenie obrazków
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
    	plik_wej.seekg(0, ios::beg);	// cofniêcie wewnêtrznego znacznika pliku wej

  		
		// Liczenie tabel	(dzia³ania analogiczne)
		
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
	   
		}plik_wyj.close();	// zamkniêcie pliku wyj
	}plik_wej.close();		// zamkniecie piku wej
	system("pause");
    return(0);

}
