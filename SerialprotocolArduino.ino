//command serial protocol standarts [command:value]
String analyzer;
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
    analyzer += c;
  }

  if (  c == ']' ) {
    reading = false;
    parser(analyzer);
    analyzer = "";
  }

}

void parser(String analyzer) {
  analyzer.replace("[", "");
  analyzer.replace("]", "");
  int indexSeparator = analyzer.indexOf(':');
  int lastIndex = analyzer.length();

  String command = analyzer.substring(0, indexSeparator);
  String value = analyzer.substring(indexSeparator + 1, lastIndex);

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
