

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.write("Hello world!\n");
//  usleep(1000);
}

