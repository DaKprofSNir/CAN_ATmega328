/* ---- DaK dec 2018 ----------------------
 * 
 *  TP sur le C.A.N. de l'ATmega328
 *  
 *    Mesure de la resistance de pullup d'une entree analogique
 *  
 *  MONTAGE :
 *  placez une resistance connue entre GND et 
 *  l'entree Analogique a mesurer
 *  
 *  Modifiez les valeurs d'initialisation
 *  en fonction de la resistance utilisee (ligne 21)
 *  et de l'entree a tester (ligne 22)
 *
 *  Ouvrez le moniteur serie et reglez a 115200 baud
 * 
 -----------------------------------------*/

float const resistance_etalon = 10000; // 10Kohm
uint8_t  const entree = A0; // entree a tester

uint32_t resistance_interne, nb_mesures=0;


void setup(){
  pinMode(entree,INPUT_PULLUP); // utiliser la resistance interne de pullup
  Serial.begin(115200);
}
    
void loop(){
    uint16_t mesure_can = analogRead(entree);
    nb_mesures++;
    Serial.print("\n---------- Mesure numero ");
    Serial.print(nb_mesures);
    Serial.print("---------\n");
    Serial.print("  valeur CAN = "); Serial.println(mesure_can);
    
    Serial.print("  valeur de la resistance etalon = ");
    Serial.print(resistance_etalon); Serial.println(" Ohm");
    
    Serial.print("  tension aux bornes de la resistance etalon = ");
    float Uetalon = (5.0 / 1023.0 * mesure_can);
    Serial.print(Uetalon, 5); Serial.println(" Volts");
    
    Serial.print("  tension aux bornes de la resistance interne = ");
    float Uinterne = 5.0 - Uetalon;
    Serial.print(Uinterne, 5); Serial.println(" Volts");
    
    Serial.print("  courant qui traverse les deux resistances = ");
    float I = Uetalon / resistance_etalon;
    Serial.print( I*1000,5 ); Serial.println(" mA");
    
    Serial.print("  valeur de la resistance interne de pullup = ");
    float Rinterne = Uinterne / I;
    Serial.print( Rinterne, 2); Serial.println(" Ohm");
    
    Serial.print("  moyenne de la resistance interne de pullup = ");
    static float Rmoyenne = 0;
    Rmoyenne = Rmoyenne*(nb_mesures-1)/nb_mesures + Rinterne/nb_mesures;
    Serial.print( Rmoyenne, 2); Serial.println(" Ohm");

    delay(1500);

  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // clear screen 
}
    
