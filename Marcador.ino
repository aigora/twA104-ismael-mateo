/*
    Name:       Marcador.ino
    Created:	09/04/2019 20:59:53
    Author:     MATEO-LENOVO\Mateo
*/

#define TCUARTO 5 //s
#define TBOCINA 2 //s

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
}

void loop() {
	//Asignaciones iniciales
	float time, inst0, inst1, tJuego;
	boolean crono;
	int ptEquipoA, ptEquipoB, flEquipoA, flEquipoB;
	if (millis() < 50) {
		time = 0;
		inst0 = 0;
		inst1 = 0;
		crono = false;
		ptEquipoA = 0;
		ptEquipoB = 0;
		flEquipoA = 0;
		flEquipoB = 0;
	}


	//Tiempo
	if (digitalRead(3) == LOW && crono == true) { //Pause crono
		crono == false;

	}
	if (digitalRead(3) == LOW && crono == false) { //Play crono
		crono == true;

	}
	if (digitalRead(4) == HIGH) //Reset crono
		time = 0;

	if (crono == true) { //Crono (solo si activado)

		inst0 = inst1;
		inst1 = millis() / 1000;
		time += inst1 - inst0;
		tJuego = TCUARTO - time;
	}


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

}
