/* ---- DaK dec 2018
 * 
 *  TP sur le C.A.N. de l'ATmega328
 *  
 *  Connectez un buzzer actif. Broche + dur 11 et broche - sur GND
 *  
 *  Connectez un capteur analogique entre les broches GND et A0
 *  
 *  Affichez le moniteur serie ou le traceur serie
 *  
 */

void setup(){
  pinMode(11,OUTPUT);
  pinMode(A0,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop(){
    digitalWrite(11,HIGH); delay(5); digitalWrite(11,LOW); delay(500); // beep
    Serial.println( analogRead(A0) ); // lecture C.A.N. et affichage
}
