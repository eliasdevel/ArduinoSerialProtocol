//command serial protocol standarts [command:value]
String analiser;
boolean reading = false;

void setup()
{
  //set the mode for the ports
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  protocol();
}

//analit Serial for start and end listening protocol
void protocol() {
  char c = Serial.read();

  if ( c == '[' ) {
    reading = true;
  }

  if (reading && c != -1) {
    analiser += c;
  }

  if (  c == ']' ) {
    reading = false;
    parser(analiser);
    analiser = "";
  }

}

void parser(String analiser) {
  analiser.replace("[", "");
  analiser.replace("]", "");
  int indexSeparator = analiser.indexOf(':');
  int lastIndex = analiser.length();

  String command = analiser.substring(0, indexSeparator);
  String value = analiser.substring(indexSeparator + 1, lastIndex);

  caller(command, value);
}

void caller(String command, String value) {
  if (command == "on") putOn(value.toInt());
  if (command == "off") putOff(value.toInt());
}

void putOn(int port) {
  digitalWrite(port, HIGH);
}
void putOff(int port) {
  digitalWrite(port, LOW);
}
