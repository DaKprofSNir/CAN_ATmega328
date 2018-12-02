/*  TP Convertisseur Analogique vers Digital de l'ATmega328
 *  Acquisition d'un signal analigique
 *  Un capteur résistif (LDR ou NTC) est branchée entre A0 et GND
 */

uint16_t LireCAN(){
    // Initialiser les paramètres du C.A.N.
    ADMUX  =  0x40; // 01xx 0000 => reférence=5.0V xx analogPin=0
    ADCSRA =  0x87; // 1xxx x111 => Active le CAN xxxx Prediviseur = 128
    ADCSRA |= 0x40; // x1xx xxxx => Lancer la conversion analogique -> numérique
	
    // Attendre la fin de la conversion
    while( (ADCSRA&0x40) == 0x40 ); // x?xx xxxx bit 6 reviendra à zéro quand terminé
	
    // récupérer le résultat
    return ADCL + (ADCH<<8); // 
}

void setup() {
    pinMode(A0,INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
    delay(1000);
    Serial.print(" Valeur CAN = ");
    Serial.println( LireCAN() );
}


