// OctoWS2811 LED Library - https://www.pjrc.com/teensy/td_libs_OctoWS2811.html
#include <OctoWS2811.h>

// Configuration de l'adressage des DELs, Pour comprendre comment l'adressage fonctionne, consultez
// ceci: https://www.pjrc.com/teensy/td_libs_OctoWS2811.html#addr
const int DELS_PAR_SORTIE = 60;
const int NOMBRE_TOTAL_DELS = 300;

// Configuration de la vitesse de communication et de l'ordre de couleur des DELs. Pour comprendre 
// l'utilisation de l'opérateur | (OU inclusif bit à bit), consultez:
// https://www.arduino.cc/reference/en/language/structure/bitwise-operators/bitwiseor/
const int CONFIG_DELS = WS2811_GRB | WS2811_800kHz;

// Création d'une variable globale pour l'objet OctoWS2811. IL faut réserver 6 entiers (int) par
// DEL pour l'affichage et le calcul (voir doc pour détails).
DMAMEM int memoireAffichage[DELS_PAR_SORTIE * 6];
int memoireCalcul[DELS_PAR_SORTIE * 6];
OctoWS2811 dels(DELS_PAR_SORTIE, memoireAffichage, memoireCalcul, CONFIG_DELS);

void setup() {

  // Ouverture de la connexion série. On met 9600 mais le Teensy initie néanmoins une connexion
  // à la vitesse maximale (12 ou 480 MBits, voir https://www.pjrc.com/teensy/td_serial.html)
  Serial.begin(19600);

  // Envoi d'une confirmation de connexion
  Serial.println("Connexion établie1.");

  // Initialisation de la bibliothèque et mise à jour des DELs (elles seront initialement toutes 
  // fermées).
  dels.begin();
  dels.show();

}

void loop() {

  // Lecture des données entrantes sur le port série jusqu'à temps de tomber sur un \n ou jusqu'à
  // l'expiration du délai (timeout) de lecture (par défaut, une seconde).
  String chaine = Serial.readStringUntil('\n');

  // Vérification du marqueur de début. Si la chaîne commence par ">", on enlève le caractère et 
  // on continue. Sinon, on attend la prochaine chaîne.
  if (chaine.startsWith(">")) {
    chaine.remove(0, 1);
  } else {
    return;
  }

  // Extraction des valeurs R, V et B puis assignation de la couleur à la DEL correspondante.
  for (int i = 0; i < NOMBRE_TOTAL_DELS; i++) {

    // Extraction de la chaîne pour le rouge
    String r = chaine.substring(0, chaine.indexOf(','));
    chaine.remove(0, r.length() + 1);

    // Extraction de la chaîne pour le vert
    String v = chaine.substring(0, chaine.indexOf(','));
    chaine.remove(0, v.length() + 1);

    // Extraction de la chaîne pour le bleu
    String b = chaine.substring(0, chaine.indexOf(','));
    chaine.remove(0, b.length() + 1);

    // Assignation de la couleur à la DEL courante
    dels.setPixel(i, r.toInt(), v.toInt(), b.toInt());

  }

  // Mise à jour de toutes les DELs
  dels.show();

}
