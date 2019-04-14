/*
	Name:       Marcador.ino
	Created:  09/04/2019 20:59:53
	Author:     MATEO-LENOVO\Mateo
*/

#define TCUARTO 600 //s
#define TBOCINA 2 //s
#define DELAY 350 //ms

void setup() {
	Serial.begin(9600);
	pinMode(2, OUTPUT); //Bocina auto
	pinMode(3, INPUT); //Play pause crono
	pinMode(4, INPUT); //Reset crono
}

void loop() {

	//Asignaciones iniciales
	static float time = 0, instI = 0, instF = 0, tCuarto;
	static boolean crono = false;
	static int puntosA = 0, puntosB = 0, faltasA = 0, faltasB = 0, cuarto = 0;
  if(millis()%1000==00){
	Serial.print((int)tCuarto/60);
  Serial.print(":");
  Serial.println(((float)tCuarto/60-(int)tCuarto/60)*60);
	Serial.print("FaltasA=");
  Serial.println(faltasA);
	Serial.print("PuntosA=");
  Serial.println(puntosA);
  Serial.print("FaltasB=");
  Serial.println(faltasB);
  Serial.print("PuntosB=");
  Serial.println(puntosB);
  }

	//Tiempo
	if (digitalRead(3) == HIGH && crono == false) { //Play time

		crono = true;
		delay(DELAY);
	}
	if (digitalRead(3) == HIGH && crono == true) { //Pause time

		crono = false;
		delay(DELAY);
	}

	if (digitalRead(4) == HIGH) { //Reset time

		time = 0;
		crono = false;
	}

	instI = instF;
	instF = millis() / 1000;
	tCuarto = TCUARTO - time;
	if (crono == true) {
		time += instF - instI;
	}

	//Puntos equipo A
	if (analogRead(A0) > 340 && analogRead(A0) < 350) {
		puntosA++;
		delay(DELAY);
	}
	if (analogRead(A0) > 250 && analogRead(A0) < 260) {
		puntosA--;
		delay(DELAY);
	}
  if(puntosA<0)
    puntosA=0;

	//Puntos equipo B
	/*if (analogRead(A1) > 340 && analogRead(A1) < 350) {
		puntosB++;
		delay(DELAY);
	}
	if (analogRead(A1) > 250 && analogRead(A1) < 260) {
		puntosB--;
		delay(DELAY);
	}
  if(puntosB<0)
    puntosB=0;*/
    
	//Faltas equipo A
	if (analogRead(A0) > 510 && analogRead(A0) < 520) {
		faltasA++;
		delay(DELAY);
	}
	/*if (faltasA == 0) {
		pinMode(11, OUTPUT);
		Encender(11);
		pinMode(12, OUTPUT);
		Apagar(12);
		pinMode(13, INPUT);
		delay(DELAY);
	}
	if (faltasA == 1) {
		pinMode(13, OUTPUT);
		Encender(13);
		pinMode(11, OUTPUT);
		Apagar(11);
		pinMode(12, INPUT);
		delay(DELAY);
	}
	if (faltasA == 2) {
		pinMode(12, OUTPUT);
		Encender(12);
		pinMode(13, OUTPUT);
		Apagar(13);
		pinMode(11, INPUT);
		delay(DELAY);
	}
	if (faltasA == 3) {
		pinMode(11, OUTPUT);
		Encender(11);
		pinMode(13, OUTPUT);
		Apagar(13);
		pinMode(12, INPUT);
		delay(DELAY);
	}
	if (faltasA == 4) {
		pinMode(12, OUTPUT);
		Encender(12);
		pinMode(11, OUTPUT);
		Apagar(11);
		pinMode(13, INPUT);
		delay(DELAY);
	}
	if (faltasA == 5) {
		pinMode(13, OUTPUT);
		Encender(13);
		pinMode(12, OUTPUT);
		Apagar(12);
		pinMode(11, INPUT);
		delay(DELAY);
	}*/
	if (faltasA == 6)
		faltasA = 0;

	//Faltas equipo B
	/*if (analogRead(A1) > 510 && analogRead(A1) < 520) {
		faltasB++;
		delay(DELAY);
	}

	if (faltasB == 0) {

	}
	if (faltasB == 1) {

	}
	if (faltasB == 2) {

	}
	if (faltasB == 3) {

	}
	if (faltasB == 4) {

	}
	if (faltasB == 5) {

	}
	if (faltasB > 5)
		faltasB = 0;*/

	//Cuarto
	if (tCuarto == 0)
		FinCuarto(&crono, &faltasA, &faltasB, &time, &cuarto);

	//Final
	if (cuarto > 4)
		FinPartido(&crono, &faltasA, &faltasB, &time, &cuarto, &puntosA, &puntosB);
	//Display
		/**/
}

//Funciones
void Bocina() {
	Encender(2);
	delay(1000 * TBOCINA);
	Apagar(2);
}
void Encender(int Pin) {
	digitalWrite(Pin, HIGH);
}
void Apagar(int Pin) {
	digitalWrite(Pin, LOW);
}
void FinCuarto(boolean *crono, int *faltasA, int *faltasB, float *time, int *cuarto){
		*crono = false;
		Bocina();
		*faltasA = 0;
		*faltasB = 0;
		*time = 0;
		*cuarto++;
}
void FinPartido(boolean *crono, int *faltasA, int *faltasB, float *time, int *cuarto, int *puntosA, int*puntosB) {
	*crono = false;
	Bocina();
	/*Fichero*/
	*puntosA = 0;
	*puntosB = 0;
	*faltasA = 0;
	*faltasB = 0;
	*time = 0;
}
