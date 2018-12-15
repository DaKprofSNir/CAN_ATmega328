/*  TP Convertisseur Analogique vers Digital de l'ATmega328
 *  Acquisition d'un signal analogique
 *  et calcul de la resistance du capteur
 *  connectez un capteur LDR ou NTC entre GND et A0
 */
 
// formule maqique qui permet de compacter des suites de Serial.Print
template<class T> inline Print &operator <<(Print &obj, T arg) {obj.print(arg);return obj;} 

#define RESISTANCE_PULLUP 35000 // resistance de pullup moyenne d'un arduino

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
    // Un capteur résistif (LDR ou NTC) est branchée entre A0 et GND
    pinMode(A0,INPUT_PULLUP); 
    // un buzzer est branché entre GND et 11
    pinMode(11,OUTPUT);
    Serial.begin(9600);
}

void loop(){
    delay(1000);
    int valeurCAN = LireCAN();
    Serial << "\nValeur CAN = " << valeurCAN << "\n";

    float u = valeurCAN * 5.0 / 1023.0;
    Serial << "    Tension = " << u << " V\n";

    float i = (5.0-u)/RESISTANCE_PULLUP; // est egale au courant dans la résistance de pullup
    Serial << "    Courant = " << i*1000 << " mA\n";
     
    float r = u/i; // resistance du capteur
    Serial << " resistance = " << r << " homs\n";

    // alarme sur detection d'un seuil
    float seuil = 1000.0; // ajustez cette valeur en fonction de votre experience
    if( r>=seuil ){
        // faire sonner le buzzer
        Serial << " Franchissement de seuil\n";
        digitalWrite(11,HIGH); delay(5); digitalWrite(11,LOW); delay(500); // beep   
    }
}


