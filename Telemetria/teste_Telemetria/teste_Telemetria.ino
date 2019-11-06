int i=0;
String n;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  i++;
  if(i%2==0){
    Serial. print("Par:   ");
    Serial. print(i);
    Serial. print(" Impar: ");
    Serial. println(i+1);
    Serial. print(" Soma: ");
    Serial. println(i+1+i);
  }
  else{
    Serial. print("Impar: ");
    Serial. print(i);
    Serial. print(" Par:   ");
    Serial. println(i+1);
    Serial. print(" Soma: ");
    Serial. println(i+1+i);
  }
    
  delay(1000);
}
