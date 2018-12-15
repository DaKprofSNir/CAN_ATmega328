/*  TP Convertisseur Analogique vers Digital de l'ATmega328
 *  Acquisition d'un signal analogique
 *  1 mesure de la tension
 *  2 fonction de transfert 
 *  3 affichage
 */
// Permet de compacter des suites de Serial.Print
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; } 


uint16_t LireCAN(){
    // Initialiser les registres du C.A.N.
    ADMUX  =  0x40; // 01.. .... => reférence = 5.0V
                    // .... 0000 => analogPin = A0
                    // 0100 0000 => 0x40
                    
    ADCSRA =  0xC7; // 1... .... => Active le CAN
                    // .... .111 => Prediviseur = 128
                    // .1.. .... => Lancer la conversion analogique vers numérique	
                    // 1100 0111 => 0xC7
    
    // Attendre la fin de la conversion
    while( (ADCSRA&0x40) == 0x40 ); // x?xx xxxx le bit 6 reviendra à zéro quand terminé
	
    // récupérer le résultat
    return ADCL + (ADCH<<8); // 
}

void setup(){
    Serial.begin(9600);    
    // effacer la ligne suivante si on utilise pas la resistance interne de pullup
    pinMode(A0,INPUT_PULLUP); // utiliser le resistance de pullup
}

// fonction de transfert entre la tension et la grandeur mesuree
float f( float u ){
  // cet exemple calcule une resistance, resultat en homs
  return (35000.0 * u) / (5.0-u) ;
}

void loop() {
    delay(1000);
    int valeurCAN = LireCAN();
    Serial << "Valeur CAN = " << valeurCAN << "\n";

    float u = valeurCAN * 5.0 / 1023.0;
    Serial << "    Tension = " << u*1000 << " mV\n";

    Serial << " valeur mesuree = " << f(u) << " ???\n";
}


