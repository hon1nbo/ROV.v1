

#include <WString.h>

#include <Ethernet.h>

// This code was modified from the Network Outlet code available from InventGeek to suit an ROV Program

// I modified this code because I used it as a basic tutorial for Arduino Ethernet coding

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address

byte ip[] = { 192, 168, 1, 110 }; // ip in lan

byte gateway[] = { 192, 168, 1, 1 }; // internet access via router

byte subnet[] = { 255, 255, 255, 0 }; //subnet mask

Server server(80); //server port

//int speakerPin = 13; // speaker connected to digital pin 9

//int ledPin = 1; // LED pin

int ballastfloodpin = 4;

int ballastdrainpin = 2;

int rightbilge = 3;

int leftbilge = 5;

int reversebilge = 7;

int forwardbilge = 9;

//int inputPin3 = 3; // choose the input pin (for a pushbutton)

int val = 0; // variable for reading the pin status

boolean LEDON = false; //LED status flag

String readString = String(30); //string for fetching data from address

void setup(){

	Ethernet.begin(mac, ip, gateway, subnet);
	// pinMode(ledPin, OUTPUT);
	// pinMode(inputPin3, INPUT); // declare pushbutton as input
	pinMode(ballastfloodpin, OUTPUT);
	pinMode(ballastdrainpin, OUTPUT);
	pinMode(rightbilge, OUTPUT);
	pinMode(leftbilge, OUTPUT);
	pinMode(reversebilge, OUTPUT);
	pinMode(forwardbilge, OUTPUT);
	digitalWrite(ballastfloodpin, LOW);
	digitalWrite(ballastdrainpin, LOW);
	digitalWrite(rightbilge, LOW);
	digitalWrite(leftbilge, LOW);
	digitalWrite(reversebilge, LOW);
	digitalWrite(forwardbilge, LOW);

	Serial.begin(9600);
	// pinMode(speakerPin, OUTPUT); // sets the speakerPin to be an output

}

void loop()  {

	Client client = server.available();

	if (client)  {

		while (client.connected()) {

			if (client.available()) {

				char c = client.read();

				if (readString.length() < 30)  {
					readString.append(c); //store characters to string
				}

				if (c == '\n') { 		//if HTTP request has ended
			
					// ledstatus(); //LED Status Sub
					//htmlcontent(); //LED Html Content Sub
					floodstatus();
					drainstatus();
					rightstatus();
					leftstatus();
					reversestatus();
					forwardstatus();

					// htmlcontent(); //LED Html Content Sub
					readString=""; //clearing string for next read

					client.stop(); //stopping client
					delay(100);
				}
			}
		}
	}
}

void htmlcontent(){

	Client client = server.available();

	client.println("HTTP/1.1 200 OK"); // now output HTML data starting with standart header

	client.println("Content-Type: text/html");

	client.println();

	client.print("<body>");

	// client.println("<form method=get name=LED><input type=checkbox name=L value=1>Activate Outlet<br><br><input type=submit value=submit></form>");	
	// client.println("<form method=get name=LED><input type=checkbox name=L value=1>Flood Ballast<br><br><input type=submit value=submit></form>");
	// client.println("<form method=get name=LED><input type=checkbox name=L value=2>Drain Ballast<br><br><input type=submit value=submit></form>");
	// client.println("<form method=get name=LED><input type=checkbox name=L value=3>Right Bilge<br><br><input type=submit value=submit></form>");
	// client.println("<form method=get name=LED><input type=checkbox name=L value=4>Left Bilge<br><br><input type=submit value=submit></form>");
	// client.println("<form method=get name=LED><input type=checkbox name=L value=5>Reverse Bilge<br><br><input type=submit value=submit></form>");
	// client.println("<form method=get name=LED><input type=checkbox name=F value=6>Forward Bilge<br><br><input type=submit value=submit></form>");
	
	client.println("<form method=get name=DIVE><input type=checkbox name=L value=1>DIVE!!!<br><br><input type=submit value=submit></form>");

	// client.println("<form method=get name=SURFACE><input type=checkbox name=L value=2>Surface<br><br><input type=submit value=submit></form>");
	// client.println("<form method=get name=RIGHT><input type=checkbox name=L value=3>Right Bilge<br><br><input type=submit value=submit></form>");
	// client.println("<form method=get name=LEFT><input type=checkbox name=L value=4>Left Bilge<br><br><input type=submit value=submit></form>");
	// client.println("<form method=get name=REVERSE><input type=checkbox name=L value=5>Reverse Bilge<br><input type=submit value=submit></form>");
	// client.println("<form method=get name=FORWARD><input type=checkbox name=F value=6>Forward Bilge<br><input type=submit value=submit></form>");
	// client.print("Outlet status: ");

	// if (LEDON)
		// client.println("ON");
	// else
		// client.println("OFF");
	
	client.println("<br ><br >");
	client.println("</body></html>");
}

void floodstatus(){

	if(readString.contains("L=1")) { 		//lets check if LED should be lighted
		digitalWrite(ballastfloodpin, HIGH); // set the LED on
		digitalWrite(ballastdrainpin, HIGH);
		//LEDON = true;
		// delay(1000);
		// digitalWrite(ballastfloodpin, LOW);
		Serial.print("DIVE");
	}

	else {
		//digitalWrite(ledPin, LOW); // set the LED OFF
		//LEDON = false;
	}
}

void drainstatus(){

	if(readString.contains("L=2")) {  			//lets check if LED should be lighted
		// digitalWrite(ballastdrainpin, HIGH); // set the LED on
		//LEDON = true;
		// delay(1000);
		// digitalWrite(ballastdrainpin, LOW);
		digitalWrite(ballastfloodpin, LOW);
		digitalWrite(ballastdrainpin, LOW);
		Serial.print("SURFACE");
	}

	else {
		// digitalWrite(ledPin, LOW); // set the LED OFF
		//LEDON = false;
	}
}

void rightstatus(){

	if(readString.contains("L=3")) { 	//lets check if LED should be lighted
		digitalWrite(rightbilge, HIGH); // set the LED on
		//LEDON = true;
		delay(6000);
		digitalWrite(rightbilge, LOW);
		Serial.print("RIGHT");
	}

	else {
		// digitalWrite(ledPin, LOW); // set the LED OFF
		// LEDON = false;
	}
}

void leftstatus(){

	if(readString.contains("L=4")) { 	//lets check if LED should be lighted
		digitalWrite(leftbilge, HIGH); // set the LED on
		// LEDON = true;
		delay(6000);
		digitalWrite(leftbilge, LOW);
		Serial.print("LEFT");
	}

	else {
		// digitalWrite(ledPin, LOW); // set the LED OFF
		// LEDON = false;
	}
}

void reversestatus(){

	if(readString.contains("L=5")) { 	//lets check if LED should be lighted
		digitalWrite(reversebilge, HIGH); // set the LED on
		//LEDON = true;
		delay(6000);
		digitalWrite(reversebilge, LOW);
		Serial.print("REVERSE");
	}

	else {
		// digitalWrite(ledPin, LOW); // set the LED OFF
		// LEDON = false;
	}
}

void forwardstatus(){

	if(readString.contains("L=6")) { 	//lets check if LED should be lighted

		digitalWrite(forwardbilge, HIGH); // set the LED on

		//LEDON = true;

		delay(6000);
		digitalWrite(forwardbilge, LOW);
		Serial.print("FORWARD");
	}

	else {
		// digitalWrite(ledPin, LOW); // set the LED OFF
		// LEDON = false;
	}
}
