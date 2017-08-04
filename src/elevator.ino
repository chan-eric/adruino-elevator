

#include <Bounce2.h>

struct floorpanel {
	bool up;
	bool down;
};

struct elevator {
  int state; //0 is stopped, 1 is up, -1 is down
  int currentfloor;
  bool input[5];
};

enum elevatorstate {
  UP = 1,
  DOWN = -1,
  HALT = 0
};

const int hallButtonPins[] = { 22, 24, 26, 28, 30, 32, 34, 36 };
const int elevButtonPins[] = { 38, 40, 44, 42, 46 };

const int ledfp[] = {23, 25, 27, 29, 31, 33, 35, 37};
const int ledelev[] = {47, 45, 43, 39, 41};

const int ledpinCount1 = 8;
const int ledpinCount2 = 5;

const int NUM_HALL = 8;
const int NUM_ELEV = 5;

// Bounce Stuff
Bounce debouncerHall1 = Bounce();
Bounce debouncerHall2 = Bounce();
Bounce debouncerHall3 = Bounce();
Bounce debouncerHall4 = Bounce();
Bounce debouncerHall5 = Bounce();
Bounce debouncerHall6 = Bounce();
Bounce debouncerHall7 = Bounce();
Bounce debouncerHall8 = Bounce();

Bounce debouncerElev1 = Bounce();
Bounce debouncerElev2 = Bounce();
Bounce debouncerElev3 = Bounce();
Bounce debouncerElev4 = Bounce();
Bounce debouncerElev5 = Bounce();

struct elevator e1;
struct floorpanel fp[5];

// the setup function runs once when you press reset or power the board
void setup() {
  e1.state = 0;
  e1.currentfloor = 0;
  e1.input[0] = false;
  e1.input[1] = false;
  e1.input[2] = false;
  e1.input[3] = false;
  e1.input[4] = false;
  
  for (int i = 0; i < ledpinCount1; i++) {
    pinMode( ledfp[i], OUTPUT);
  }
  
  for (int i = 0; i < ledpinCount2; i++) {
    pinMode( ledelev[i], OUTPUT);
  }
  
	Serial.begin(9600);
	setupHallButtons();
	setupElevButtons();

	// attach pins and set interval for debounce instances
	debouncerHall1.attach(hallButtonPins[0]);
	debouncerHall1.interval(5);
	debouncerHall2.attach(hallButtonPins[1]);
	debouncerHall2.interval(5);
	debouncerHall3.attach(hallButtonPins[2]);
	debouncerHall3.interval(5);
	debouncerHall4.attach(hallButtonPins[3]);
	debouncerHall4.interval(5);
	debouncerHall5.attach(hallButtonPins[4]);
	debouncerHall5.interval(5);
	debouncerHall6.attach(hallButtonPins[5]);
	debouncerHall6.interval(5);
	debouncerHall7.attach(hallButtonPins[6]);
	debouncerHall7.interval(5);
	debouncerHall8.attach(hallButtonPins[7]);
	debouncerHall8.interval(5);

	debouncerElev1.attach(elevButtonPins[0]);
	debouncerElev1.interval(5);
	debouncerElev2.attach(elevButtonPins[1]);
	debouncerElev2.interval(5);
	debouncerElev3.attach(elevButtonPins[2]);
	debouncerElev3.interval(5);
	debouncerElev4.attach(elevButtonPins[3]);
	debouncerElev4.interval(5);
	debouncerElev5.attach(elevButtonPins[4]);
	debouncerElev5.interval(5);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
	// update bounce instances
	debouncerHall1.update();
	debouncerHall2.update();
	debouncerHall3.update();
	debouncerHall4.update();
	debouncerHall5.update();
	debouncerHall6.update();
	debouncerHall7.update();
	debouncerHall8.update();

	debouncerElev1.update();
	debouncerElev2.update();
	debouncerElev3.update();
	debouncerElev4.update();
	debouncerElev5.update();

	int elev1 = debouncerElev1.fell();
	int elev2 = debouncerElev2.fell();
	int elev3 = debouncerElev3.fell();
	int elev4 = debouncerElev4.fell();
	int elev5 = debouncerElev5.fell();

	int hall1 = debouncerHall1.fell();
	int hall2 = debouncerHall2.fell();
	int hall3 = debouncerHall3.fell();
	int hall4 = debouncerHall4.fell();
	int hall5 = debouncerHall5.fell();
	int hall6 = debouncerHall6.fell();
	int hall7 = debouncerHall7.fell();
	int hall8 = debouncerHall8.fell();

	if (hall1 == HIGH)
	{
		Serial.println("Button Pressed on Ground");
		fp[0].up = true;
		digitalWrite(ledfp[0], HIGH);
	}
	else if (hall2 == HIGH)
	{
		Serial.println("Button Pressed First Down");
		fp[1].down = true;
		digitalWrite(ledfp[1], HIGH);
	}
	else if (hall3 == HIGH)
	{
		Serial.println("Button Pressed First Up");
		fp[1].up = true;
		digitalWrite(ledfp[2], HIGH);
	}
	else if (hall4 == HIGH)
	{
		Serial.println("Button Pressed Second Down");
		fp[2].down = true;
		digitalWrite(ledfp[3], HIGH);
	}
	else if (hall5 == HIGH)
	{
		Serial.println("Button Pressed Second Up");
		fp[2].up = true;
		digitalWrite(ledfp[4], HIGH);
	}
	else if (hall6 == HIGH)
	{
		Serial.println("Button Pressed Third Down");
		fp[3].down = true;
		digitalWrite(ledfp[5], HIGH);
	}
	else if (hall7 == HIGH)
	{
		Serial.println("Button Pressed Third Up");
		fp[3].up = true;
		digitalWrite(ledfp[6], HIGH);
	}
	else if (hall8 == HIGH)
	{
		Serial.println("Button Pressed Top");
		fp[4].down = true;
		digitalWrite(ledfp[7], HIGH);
	}
	else if (elev1 == HIGH)
	{
		Serial.println("Ground floor Selected");
		e1.input[0] = true;
		digitalWrite(ledelev[0], HIGH);
	}
	else if (elev2 == HIGH)
	{
		Serial.println("First floor Selected");
		e1.input[1] = true;
		digitalWrite(ledelev[1], HIGH);
	}
	else if (elev3 == HIGH)
	{
		Serial.println("Second floor Selected");
		e1.input[2] = true;
		digitalWrite(ledelev[2], HIGH);
	}
	else if (elev4 == HIGH)
	{
		Serial.println("Third floor Selected");
		e1.input[3] = true;
		digitalWrite(ledelev[3], HIGH);
	}
	else if (elev5 == HIGH)
	{
		Serial.println("Fourth floor Selected");
		e1.input[4] = true;
		//digitalWrite(41, HIGH);
		digitalWrite(ledelev[4], HIGH);
	}

	controlElevator();
}

void setupHallButtons() {
	for (int i = 0; i < NUM_HALL; i++)
		pinMode(hallButtonPins[i], INPUT_PULLUP);
}
void setupElevButtons() {
	for (int i = 0; i < NUM_ELEV; i++)
		pinMode(elevButtonPins[i], INPUT_PULLUP);
}

//keep in mind that this is inside the loop, it will keep doing this until there is no service request for fp or e1
void controlElevator() {
  
  	

	//if e1 panel requires service or fp requires service
	//then we do logics
	if (elevRequiresService(e1.input) || fpRequiresService(fp)) {
	  
	  Serial.print("  Current state: ");
		Serial.println(e1.state);
		
		Serial.print("  Current floor: ");
		Serial.println(e1.currentfloor );
	
		//first we need to change the elevator state and current floor
		if (e1.state == UP) {
			if (e1.currentfloor <4) {
				e1.currentfloor ++;
				waitOnElev(2000);
			}
			if (e1.currentfloor == 4) {
				e1.state = DOWN;
			}
			
		} else if (e1.state == DOWN) {			
			if (e1.currentfloor > 0) {
				e1.currentfloor --;
				waitOnElev(2000);
			}
			if (e1.currentfloor == 0) {
				e1.state = UP;
			}
			
		} else {
		  
		  Serial.println("Elevator current HALT");
		
			if (e1.currentfloor == 0) {
				e1.state = UP;
				e1.currentfloor ++;
				Serial.println("Elevator at ground floor");
			} else	if (e1.currentfloor == 4) {
				e1.state = DOWN;
				e1.currentfloor --;
				Serial.println("Elevator at top floor");
			} else if (e1.currentfloor == 1 || e1.currentfloor == 2 || e1.currentfloor == 3) {
			  if (e1.state == UP)
			    e1.currentfloor++;
			  else if (e1.state == DOWN)
			    e1.currentfloor--;
			  
			}
			waitOnElev(2000);

		}
		
    Serial.print("  Next state: ");
		Serial.println(e1.state);
		
		Serial.print("  Next floor: ");
		Serial.println(e1.currentfloor );
	
		//after we reach a certain floor, we need to turn off the signal for that floor on both fp and e1
		for (int i=0; i<5; i++) {
		  
		  //flip the inputs since we serviced the ground going up request already
			if (e1.currentfloor == i && e1.state == UP && i != 4) {
				fp[i].up = false;  
				e1.input[i] = false;
				digitalWrite(ledelev[i], LOW);
				turnOffFpLed(i);
				
				//need case for led fp
			}
			if (e1.currentfloor == i && e1.state == DOWN && i != 0) {
				fp[i].down = false;
				e1.input[i] = false;
				digitalWrite(ledelev[i], LOW);
				turnOffFpLed(i);
			}
		}

	} else {   //otherwise do nothing
	  //e1.state = HALT;
	}
}

void turnOffFpLed(int floor) {

  if (floor ==0 && e1.state==UP) digitalWrite(ledfp[0], LOW);
  if (floor ==1 && e1.state==DOWN) digitalWrite(ledfp[1], LOW);
  if (floor ==1 && e1.state==UP) digitalWrite(ledfp[2], LOW);
  if (floor == 2 && e1.state==DOWN) digitalWrite(ledfp[3], LOW);
  if (floor == 2 && e1.state==UP) digitalWrite(ledfp[4], LOW);
  if (floor == 3 && e1.state==DOWN) digitalWrite(ledfp[5], LOW);
  if (floor == 3 && e1.state==UP) digitalWrite(ledfp[6], LOW);
  if (floor == 4 && e1.state==DOWN) digitalWrite(ledfp[7], LOW);
}

bool elevRequiresService(bool array[]) {
	for (int i=0; i<8; i++) {
		if (array[i] == true) {
			return true;
		}
	}
	return false;
}

bool fpRequiresService(floorpanel fp[]){
	for (int i=0; i<5; i++) {
		if (fp[i].up == true || fp[i].down == true) {
			return true;
		}
	}
	return false;
}

void waitOnElev(unsigned int interval) {
    unsigned long previousMillis = millis(); // grab current time
    // check if "interval" time has passed (1000 milliseconds)
    while ((unsigned long)(millis() - previousMillis) < interval) {
      
		debouncerHall1.update();
    	debouncerHall2.update();
    	debouncerHall3.update();
    	debouncerHall4.update();
    	debouncerHall5.update();
    	debouncerHall6.update();
    	debouncerHall7.update();
    	debouncerHall8.update();
    
    	debouncerElev1.update();
    	debouncerElev2.update();
    	debouncerElev3.update();
    	debouncerElev4.update();
    	debouncerElev5.update();
    	
    	int elev1 = debouncerElev1.fell();
    	int elev2 = debouncerElev2.fell();
    	int elev3 = debouncerElev3.fell();
    	int elev4 = debouncerElev4.fell();
    	int elev5 = debouncerElev5.fell();
    
    	int hall1 = debouncerHall1.fell();
    	int hall2 = debouncerHall2.fell();
    	int hall3 = debouncerHall3.fell();
    	int hall4 = debouncerHall4.fell();
    	int hall5 = debouncerHall5.fell();
    	int hall6 = debouncerHall6.fell();
    	int hall7 = debouncerHall7.fell();
    	int hall8 = debouncerHall8.fell();
    
    	if (hall1 == HIGH)
    	{
    		Serial.println("Button Pressed on Ground");
    		fp[0].up = true;
    		digitalWrite(ledfp[0], HIGH);
    	}
    	else if (hall2 == HIGH)
    	{
    		Serial.println("Button Pressed First Down");
    		fp[1].down = true;
    		digitalWrite(ledfp[1], HIGH);
    	}
    	else if (hall3 == HIGH)
    	{
    		Serial.println("Button Pressed First Up");
    		fp[1].up = true;
    		digitalWrite(ledfp[2], HIGH);
    	}
    	else if (hall4 == HIGH)
    	{
    		Serial.println("Button Pressed Second Down");
    		fp[2].down = true;
    		digitalWrite(ledfp[3], HIGH);
    	}
    	else if (hall5 == HIGH)
    	{
    		Serial.println("Button Pressed Second Up");
    		fp[2].up = true;
    		digitalWrite(ledfp[4], HIGH);
    	}
    	else if (hall6 == HIGH)
    	{
    		Serial.println("Button Pressed Third Down");
    		fp[3].down = true;
    		digitalWrite(ledfp[5], HIGH);
    	}
    	else if (hall7 == HIGH)
    	{
    		Serial.println("Button Pressed Third Up");
    		fp[3].up = true;
    		digitalWrite(ledfp[6], HIGH);
    	}
    	else if (hall8 == HIGH)
    	{
    		Serial.println("Button Pressed Top");
    		fp[4].down = true;
    		digitalWrite(ledfp[7], HIGH);
    	}
    	else if (elev1 == HIGH)
    	{
    		Serial.println("Ground floor Selected");
    		e1.input[0] = true;
    		digitalWrite(ledelev[0], HIGH);
    	}
    	else if (elev2 == HIGH)
    	{
    		Serial.println("First floor Selected");
    		e1.input[1] = true;
    		digitalWrite(ledelev[1], HIGH);
    	}
    	else if (elev3 == HIGH)
    	{
    		Serial.println("Second floor Selected");
    		e1.input[2] = true;
    		digitalWrite(ledelev[2], HIGH);
    	}
    	else if (elev4 == HIGH)
    	{
    		Serial.println("Third floor Selected");
    		e1.input[3] = true;
    		digitalWrite(ledelev[3], HIGH);
    	}
    	else if (elev5 == HIGH)
    	{
    		Serial.println("Fourth floor Selected");
    		e1.input[4] = true;
    		//digitalWrite(41, HIGH);
    		digitalWrite(ledelev[4], HIGH);
    	}

    }
}

