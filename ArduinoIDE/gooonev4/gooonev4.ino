#include <AccelStepper.h>

// Configuration pour les moteurs
#define dirPin1 7
#define stepPin1 27
#define motorInterfaceType1 1
AccelStepper stepper1(motorInterfaceType1, stepPin1, dirPin1);

#define dirPin2 6
#define stepPin2 26
#define motorInterfaceType2 1
AccelStepper stepper2(motorInterfaceType2, stepPin2, dirPin2);

#define dirPin3 5
#define stepPin3 25
#define motorInterfaceType3 1
AccelStepper stepper3(motorInterfaceType3, stepPin3, dirPin3);

#define dirPin4 4
#define stepPin4 24
#define motorInterfaceType4 1
AccelStepper stepper4(motorInterfaceType4, stepPin4, dirPin4);

#define dirPin5 3
#define stepPin5 23
#define motorInterfaceType5 1
AccelStepper stepper5(motorInterfaceType5, stepPin5, dirPin5);

int valeur = 0;        // Valeur reçue
int lastValeur = -1;   // Dernière valeur pour détecter un changement

void setup() {
  Serial.begin(19200);

  // Configuration des moteurs
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(1000);
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(1000);
  stepper3.setMaxSpeed(1000);
  stepper3.setAcceleration(1000);
  stepper4.setMaxSpeed(1000);
  stepper4.setAcceleration(1000);
  stepper5.setMaxSpeed(1000);
  stepper5.setAcceleration(1000);

  Serial.println("Ready to receive commands!");
}

void loop() {
  // Vérifier si une commande a été reçue
  if (Serial.available() > 0) {
    int receivedValue = Serial.parseInt();
    if (receivedValue != 0 || Serial.peek() == '\n') {
      valeur = receivedValue;
      Serial.print("Valeur reçue : ");
      Serial.println(valeur);
    }
  }

  // Si la valeur a changé, arrêter les moteurs, faire une pause, et changer de pattern
  if (valeur != lastValeur) {
    stopMotors();
    delay(1000); // Pause d'une seconde
    lastValeur = valeur;
  }

  // Exécuter le pattern actuel
  handleMotors();
}

void handleMotors() {
  switch (valeur) {
    case 1:
      stopMotors(); // Arrête les moteurs si "1" est envoyé
      break;
    case 2:
      pattern1();
      break;
    case 3:
      pattern2();
      break;
    case 4:
      pattern3();
      break;
    case 5:
      pattern4();
      break;
    case 6:
      pattern5();
      break;
    case 7:
      pattern6();
      break;
  }
}

// Pattern 1 : Mouvement synchronisé avec pauses
void pattern1() {
  stepper1.moveTo(1500);
  stepper2.moveTo(1500);
  stepper3.moveTo(1500);
  stepper4.moveTo(1500);
  stepper5.moveTo(1500);
  runMotors();

  delay(750);

  stepper1.moveTo(0);
  stepper2.moveTo(0);
  stepper3.moveTo(0);
  stepper4.moveTo(0);
  stepper5.moveTo(0);
  runMotors();

  delay(750);
}

// Pattern 2 : Mouvements opposés
void pattern2() {
  stepper1.moveTo(1500);
  stepper2.moveTo(-1500);
  stepper3.moveTo(1500);
  stepper4.moveTo(-1500);
  stepper5.moveTo(1500);
  runMotors();

  delay(1000);

  stepper1.moveTo(-1500);
  stepper2.moveTo(1500);
  stepper3.moveTo(-1500);
  stepper4.moveTo(1500);
  stepper5.moveTo(-1500);
  runMotors();

  delay(1000);
}

// Pattern 3 : Mouvement en alternance pairs et impaires
void pattern3() {
  stepper2.moveTo(1500);
  stepper4.moveTo(1500);
  runMotors();
  delay(500);

  stepper1.moveTo(-1500);
  stepper3.moveTo(-1500);
  stepper5.moveTo(-1500);
  runMotors();
  delay(1000);

  stepper1.moveTo(0);
  stepper2.moveTo(0);
  stepper3.moveTo(0);
  stepper4.moveTo(0);
  stepper5.moveTo(0);
  runMotors();
}

// Pattern 4 : Mouvement du centre désynchronisé
void pattern4() {
  stepper1.moveTo(1500);
  stepper2.moveTo(1500);
  stepper4.moveTo(-1500);
  stepper5.moveTo(-1500);
  runMotors();

  stepper3.moveTo(1500);
  runMotor(stepper3);
  delay(750);

  stepper1.moveTo(0);
  stepper2.moveTo(0);
  stepper3.moveTo(0);
  stepper4.moveTo(0);
  stepper5.moveTo(0);
  runMotors();
}

// Pattern 5 : Mouvement des extrémités allant vers le centre
void pattern5() {
  stepper1.moveTo(1500);
  stepper5.moveTo(-1500);
  runMotors();
  delay(500);

  stepper2.moveTo(1500);
  stepper4.moveTo(-1500);
  runMotors();
  delay(500);

  stepper3.moveTo(1500);
  runMotor(stepper3);
  delay(750);

  stepper1.moveTo(0);
  stepper2.moveTo(0);
  stepper3.moveTo(0);
  stepper4.moveTo(0);
  stepper5.moveTo(0);
  runMotors();
}

// Pattern 6 : Mouvement en alternance
void pattern6() {
  stepper1.moveTo(500);
  runMotor(stepper1);

  stepper1.moveTo(1000);
  stepper2.moveTo(500);
  runMotors();

  stepper1.moveTo(1500);
  stepper2.moveTo(1000);
  stepper3.moveTo(500);
  runMotors();

  stepper1.moveTo(2000);
  stepper2.moveTo(1500);
  stepper3.moveTo(1000);
  stepper4.moveTo(500);
  runMotors();


  stepper1.moveTo(2500);
  stepper2.moveTo(2000);
  stepper3.moveTo(1500);
  stepper4.moveTo(1000);
  stepper5.moveTo(500);
  runMotors();
  delay(750);

  stepper1.moveTo(0);
  stepper2.moveTo(0);
  stepper3.moveTo(0);
  stepper4.moveTo(0);
  stepper5.moveTo(0);
  runMotors();
}

// Fonction pour exécuter les moteurs jusqu'à ce qu'ils atteignent leurs positions
void runMotors() {
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0 ||
         stepper3.distanceToGo() != 0 || stepper4.distanceToGo() != 0 ||
         stepper5.distanceToGo() != 0) {
    if (valeur != lastValeur) return; // Sortir si une nouvelle commande est reçue
    stepper1.run();
    stepper2.run();
    stepper3.run();
    stepper4.run();
    stepper5.run();
  }
}

// Fonction pour exécuter un seul moteur jusqu'à ce qu'il atteigne sa position
void runMotor(AccelStepper &stepper) {
  while (stepper.distanceToGo() != 0) {
    if (valeur != lastValeur) return; // Sortir si une nouvelle commande est reçue
    stepper.run();
  }
}

// Fonction pour arrêter les moteurs
void stopMotors() {
  stepper1.stop();
  stepper2.stop();
  stepper3.stop();
  stepper4.stop();
  stepper5.stop();
  Serial.println("Moteurs arrêtés.");
}
