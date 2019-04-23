/*
	Name:       Marcador.ino
	Created:  09/04/2019 20:59:83
	Author:     MATEO-LENOVO\Mateo
*/

#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Wire.h>
#include <SPI.h>

#define TCUARTO 600 //s
#define TBOCINA 2 //s
#define DELAY 350 //ms

typedef struct {
	int puntosA, puntosB;
}partido;

void setup() {

	Serial.begin(9600);
	pinMode(2, OUTPUT); //Bocina auto
	pinMode(3, INPUT); //Play pause crono
	pinMode(4, INPUT); //Reset crono
	pinMode(11, INPUT); //Continuar al siguiente partido
	pinMode(12, INPUT); //Mostrar datos al final del partido
}

void loop() {

	//Asignaciones iniciales
	static float time = 0, instI = 0, instF = 0;
	static boolean crono = false, displayFl = true, dispPuntosFl = true, dispTimeFl = true, dispCuartoFl = true, faltasAFl = true, faltasBFl = true;
	static int puntosA = 0, puntosB = 0, tCuarto;
	static byte cuarto = 1, faltasA = 0, faltasB = 0;
	static Adafruit_SSD1306 display;

	if (displayFl == true) { //Inicio del display

		delay(100);
		display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
		display.clearDisplay();
		display.display();
		display.setTextSize(2);
		display.setTextColor(WHITE);
		display.setRotation(0);
		display.setTextWrap(false);
		display.dim(0);
		display.setCursor(10, 10);
		display.print("A");
		display.setCursor(110, 10);
		display.print("B");
		displayFl = false;
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
		dispTimeFl = true;
	}

	instI = instF;
	instF = millis() / 1000;
	tCuarto = TCUARTO - time;
	if (crono == true) { //Cuenta tiempo (si activado)

		time += instF - instI;
		dispTimeFl = true;
	}

	//Puntos equipo A
	if (analogRead(A0) > 340 && analogRead(A0) < 350) { //Puntos +1

		puntosA++;
		delay(DELAY);
		dispPuntosFl = true;
	}
	if (analogRead(A0) > 250 && analogRead(A0) < 260) { //Puntos -1

		puntosA--;
		delay(DELAY);
		dispPuntosFl = true;
	}
	if (puntosA < 0)
		puntosA = 0;

	//Puntos equipo B
	if (analogRead(A1) > 340 && analogRead(A1) < 350) { //Puntos +1

		puntosB++;
		delay(DELAY);
		dispPuntosFl = true;
	}
	if (analogRead(A1) > 250 && analogRead(A1) < 260) { //Puntos -1

		puntosB--;
		delay(DELAY);
		dispPuntosFl = true;
	}
	if(puntosB<0)
		puntosB=0;
    
	//Faltas equipo A
	if (analogRead(A0) > 510 && analogRead(A0) < 520) { //Faltas +1

		faltasA++;
		delay(DELAY);
		faltasAFl = true;
	}

	if (faltasAFl == true) { //LEDs faltas (tecnica charlieplexing)
		if (faltasA == 0) {
			pinMode(5, OUTPUT);
			Encender(5);
			pinMode(6, OUTPUT);
			Apagar(6);
			pinMode(7, INPUT);
			delay(DELAY);
			faltasAFl = false;
		}
		if (faltasA == 1) {
			pinMode(7, OUTPUT);
			Encender(7);
			pinMode(5, OUTPUT);
			Apagar(5);
			pinMode(6, INPUT);
			delay(DELAY);
			faltasAFl = false;
		}
		if (faltasA == 2) {
			pinMode(6, OUTPUT);
			Encender(6);
			pinMode(7, OUTPUT);
			Apagar(7);
			pinMode(5, INPUT);
			delay(DELAY);
			faltasAFl = false;
		}
		if (faltasA == 3) {
			pinMode(5, OUTPUT);
			Encender(5);
			pinMode(7, OUTPUT);
			Apagar(7);
			pinMode(6, INPUT);
			delay(DELAY);
			faltasAFl = false;
		}
		if (faltasA == 4) {
			pinMode(6, OUTPUT);
			Encender(6);
			pinMode(5, OUTPUT);
			Apagar(5);
			pinMode(7, INPUT);
			delay(DELAY);
			faltasAFl = false;
		}
		if (faltasA == 5) {
			pinMode(7, OUTPUT);
			Encender(7);
			pinMode(6, OUTPUT);
			Apagar(6);
			pinMode(5, INPUT);
			delay(DELAY);
			faltasAFl = false;
		}
	}
	if (faltasA == 6)
		faltasA = 0;

	//Faltas equipo B
	if (analogRead(A1) > 510 && analogRead(A1) < 520) { //Faltas +1

		faltasB++;
		delay(DELAY);
		faltasBFl = true;
	}

	if (faltasBFl == true) { //LEDs faltas (tecnica charlieplexing)
		if (faltasB == 0) {
			pinMode(8, OUTPUT);
			Encender(8);
			pinMode(9, OUTPUT);
			Apagar(9);
			pinMode(10, INPUT);
			delay(DELAY);
			faltasBFl = false;
		}
		if (faltasB == 1) {
			pinMode(10, OUTPUT);
			Encender(10);
			pinMode(8, OUTPUT);
			Apagar(8);
			pinMode(9, INPUT);
			delay(DELAY);
			faltasBFl = false;
		}
		if (faltasB == 2) {
			pinMode(9, OUTPUT);
			Encender(9);
			pinMode(10, OUTPUT);
			Apagar(10);
			pinMode(8, INPUT);
			delay(DELAY);
			faltasBFl = false;
		}
		if (faltasB == 3) {
			pinMode(8, OUTPUT);
			Encender(8);
			pinMode(10, OUTPUT);
			Apagar(10);
			pinMode(9, INPUT);
			delay(DELAY);
			faltasBFl = false;
		}
		if (faltasB == 4) {
			pinMode(9, OUTPUT);
			Encender(9);
			pinMode(8, OUTPUT);
			Apagar(8);
			pinMode(10, INPUT);
			delay(DELAY);
			faltasBFl = false;
		}
		if (faltasB == 5) {
			pinMode(10, OUTPUT);
			Encender(10);
			pinMode(9, OUTPUT);
			Apagar(9);
			pinMode(11, INPUT);
			delay(DELAY);
			faltasBFl = false;
		}
	}
	if (faltasB > 5)
		faltasB = 0;

	//Display
	if (dispTimeFl == true) { //Tiempo
		if (tCuarto == 600) {

			display.fillRect(35, 15, 70, 25, BLACK);
			display.setCursor(35, 25);
			display.print("10:00");
		}
		else {

			display.fillRect(35, 15, 70, 25, BLACK);
			display.setCursor(35, 25);
			display.setTextColor(WHITE);
			display.print("0");
			display.print((int)tCuarto / 60);
			display.print(":");
			if ((tCuarto % 60) < 10) {

				display.print("0");
				display.print((int)tCuarto % 60);
			}
			else {

				display.print((int)(tCuarto % 60));
			}
		}
		
		display.display();
		dispTimeFl = false;
	}

	if (dispCuartoFl == true) { //Cuarto

		display.fillRect(60, 40, 20, 25, BLACK);
		display.setCursor(60, 40);
		display.print(cuarto);
		display.display();
		dispCuartoFl = false;
	}

	if (dispPuntosFl == true){ //Puntos A y B

		display.fillRect(5, 45, 25, 25, BLACK);
		if (puntosA < 10) {
			display.setCursor(10, 45);
			display.print(puntosA);
		}
		else {
			if (puntosA < 100) {
				display.setCursor(5, 45);
				display.print(puntosA);
			}
			else {
				display.setCursor(0, 45);
				display.print(puntosA);
			}
		}

		display.fillRect(105, 45, 25, 25, BLACK);
		if (puntosB < 10) {
			display.setCursor(110, 45);
			display.print(puntosB);
		}
		else {
			if (puntosB < 100) {
				display.setCursor(105, 45);
				display.print(puntosB);
			}
			else {
				display.setCursor(100, 45);
				display.print(puntosB);
			}
		}
		display.display();
		dispPuntosFl = false;
	}

	//Final
	if (tCuarto == 0 && crono == true)
		FinCuarto(&crono, &faltasA, &faltasB, &time, &cuarto, &dispTimeFl, &faltasAFl, &faltasBFl, &dispCuartoFl);
	if (cuarto > 4)
		FinPartido(&cuarto, &puntosA, &puntosB, &dispPuntosFl, &dispCuartoFl, &display, &displayFl, &dispTimeFl);
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
void FinCuarto(boolean *crono, byte *faltasA, byte *faltasB, float *time, byte *cuarto, boolean *dispTimeFl, boolean *faltasAFl, boolean *faltasBFl, boolean *dispCuartoFl){

	*crono = false;
	Bocina();
	*faltasA = 0;
	*faltasB = 0;
	*time = 0;
	*cuarto = *cuarto + 1;
	*dispTimeFl = true;
	*faltasAFl = true;
	*faltasBFl = true;
  if(*cuarto < 5)
	  *dispCuartoFl = true;
}
void FinPartido(byte *cuarto, int *puntosA, int*puntosB, boolean *dispPuntosFl, boolean *dispCuartoFl, Adafruit_SSD1306 *display, boolean *displayFl, boolean *dispTimeFl) {

	static int cont = 0;
	cont++;
	Save(cont, *puntosA, *puntosB, display, displayFl, dispPuntosFl, dispTimeFl, dispCuartoFl);
	*cuarto = 1;
	*puntosA = 0;
	*puntosB = 0;
	*dispPuntosFl = true;
	*dispCuartoFl = true;
}
void Save(int cont, int puntosA, int puntosB, Adafruit_SSD1306 *display, boolean *displayFl, boolean *dispPuntosFl, boolean *dispTimeFl, boolean *dispCuartoFl) {

	//Guardar resultados
	partido *log, *aux;
	if (cont == 1)
		log = (partido*)malloc(sizeof(partido));
	else {
		aux = (partido*)malloc((cont - 1) * sizeof(partido));
		aux = log;
		log = (partido*)realloc(log, cont * sizeof(partido));
		log = aux;
		free(aux);
	}

	log[cont-1].puntosA = puntosA;
	log[cont-1].puntosB = puntosB;

	//Parar marcador hasta pulsar boton
	int i = 0;
	while (digitalRead(11) != HIGH) {
		//Mostrar resultados guardados por pantalla
		if (digitalRead(12) == HIGH) {
			(*display).clearDisplay();
			(*display).setCursor(15,20);
			(*display).print("Partido ");
			(*display).print(i+1);
			(*display).setCursor(35, 40);
			(*display).print(log[i].puntosA);
			(*display).print(" - ");
			(*display).print(log[i].puntosB);
			(*display).display();
			delay(DELAY);
			i++;
			if (i == cont)
				i = 0;
		}
	}

	//Flags para reiniciar display
	(*display).clearDisplay();
	*displayFl = true;
	*dispPuntosFl = true;
	*dispTimeFl = true;
	*dispCuartoFl = true;
}