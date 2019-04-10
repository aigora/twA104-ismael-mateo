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
	pinMode(5, INPUT); //+1 equipo A
	pinMode(6, INPUT); //-1 equipo A
	pinMode(7, INPUT); //+1 equipo B
	pinMode(8, INPUT); //-1 equipo B
	pinMode(9, INPUT); //Falta equipo A
	pinMode(10, INPUT); //Falta equipo B
	pinMode(11, OUTPUT);							 //Quitar despues
}

void loop() {

	//Asignaciones iniciales
	static float time = 0, inst0 = 0, inst1 = 0, tJuego;
	static boolean crono = false;
	static int ptEquipoA = 0, ptEquipoB = 0, flEquipoA = 0, flEquipoB = 0;
	
	//Tiempo
	if (digitalRead(3) == HIGH && crono == false) { //Pause crono

		crono = true;
		delay(DELAY);
	}
	if (digitalRead(3) == HIGH && crono == true) { //Play crono

		crono = false;
		delay(DELAY);
	}
  
	if (digitalRead(4) == HIGH) { //Reset crono

		//time = 0;
		//crono = false;					Esta desactivado porque al estar sin cable hace cosas no deseadas
	}

	tJuego = TCUARTO - time;
	inst0 = inst1;
	inst1 = millis() / 1000;
	if (crono == true) { //Crono (solo si activado)

		time += inst1 - inst0;
		digitalWrite(11, HIGH);								//Quitar despues
	}
	else
		digitalWrite(11, LOW);

	//Bocina
	if ((tJuego<0 && tJuego>-TBOCINA))
		digitalWrite(2, HIGH);
	else
		digitalWrite(2, LOW);


	//Puntos equipo A
	if (digitalRead(5) == HIGH)
		ptEquipoA++;
	if (digitalRead(6) == HIGH)
		ptEquipoA--;

	//Puntos equipo B
	if (digitalRead(7) == HIGH)
		ptEquipoB++;
	if (digitalRead(8) == HIGH)
		ptEquipoB--;

	//Faltas equipo A
	if (digitalRead(9) == HIGH)
		flEquipoA++;

	//Faltas equipo B
	if (digitalRead(10) == HIGH)
		flEquipoB++;

	//Cuarto

	//Display
}
