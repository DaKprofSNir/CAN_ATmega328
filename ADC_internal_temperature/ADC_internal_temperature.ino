/* ---- DaK dec 2018 ----------------------
 * 
 *  Mesure la température interne de l'ATmega
 *
 * ----------------------------------------*/

 
float getInternalTemp(void){
  ADMUX = 0xC8;  // Sélectionne le port analogique 8 + référence interne 1v1
  ADCSRA |= (1 << ADEN);       // Active le convertisseur analogique -> numérique
  ADCSRA |= (1 << ADSC);       // Lance une conversion analogique -> numérique
  while(ADCSRA & (1 << ADSC)); // Attend la fin de la conversion
  uint16_t raw = ADCL | (ADCH << 8); // Récupère le résultat de la conversion
  return (raw - 324.31 ) / 1.22;     // Calcul la température
}
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  float T = getInternalTemp();
  Serial.print("Temperature interne : ");
  Serial.print(T);
  Serial.print(" deg.\n");
  delay(1000);
}
