/*  KSC16 Convertisseur Analogique vers Digital de l'ATmega328
 *  Lecture du capteur LDR5528
 *  La LDR est branchée entre A0 et GND
 *  Une résistance de 10 Kilo-Ohm est branchée entre A0 et Vcc
 */

int LireCAN(){
    // Initialiser les paramètres du C.A.N.
    ADMUX  =  0x40; // 01xx 0000 => reférence=5.0V xx analogPin=0
    ADCSRA =  0x87; // 1xxx x111 => Active le CAN xxxx Prediviseur = 128
    // Lancer la conversion analogique -> numérique
    ADCSRA |= 0x40; // x1xx xxxx 
    // Attendre la fin de la conversion
    while( (ADCSRA&0x40) == 0x40 ); // x?xx xxxx bit 6 reviendra à zéro qt terminé
    // récupérer le résultat
    byte lsb,msb;
    lsb = ADCL;
    msb = ADCH;
    return ((msb<<8) | lsb);
}

void setup() {
    pinMode(A0,INPUT);
    Serial.begin(9600);
    Serial.println("-- LECTURE C.A.N. --");
}

void loop() {
    delay(1000);
    Serial.print(" Valeur CAN = ");
    Serial.println( LireCAN() );
}


