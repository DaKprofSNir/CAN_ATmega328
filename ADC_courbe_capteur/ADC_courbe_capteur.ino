/* ---- DaK dec 2018
 * 
 * Pour utiliser ce programme, ouvrez le traceur série
 * 
 * Le capteur analogique doit être connecté entre GND et A0
 * 
 * Si vous utilisez le buzzer actif, branchez-le entre GND et broche 11
 * 
 */

float moyenne = 0.0;
uint16_t valeurs[10]={0};
byte top=0;

void setup() {
    Serial.begin(9600);
    pinMode(11,OUTPUT);
    pinMode(A0,INPUT_PULLUP);
    for( byte i=0; i<=9; i++ ) valeurs[i]=analogRead(A0);;
}


void loop() {
    // ---- beep buzzer actif -----
    digitalWrite(11,HIGH); delay(5); digitalWrite(11,LOW); delay(500);

    // ---- mesure C.A.N. vers le tableau de valeurs
    valeurs[top]= analogRead(A0);
    Serial.print( valeurs[top] );
    top++; if(top>9) top=0;

    // ---- Calcul de la moyenne ----
    moyenne=0; for( byte i=0; i<=9; i++ ) moyenne+=valeurs[i];
    Serial.print("  ");
    Serial.println( moyenne/10 );
}
