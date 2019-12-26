int boton1 = 2;
int boton2 = 10;
int led_r = 3;
int led_b = 11;
int led_1 = 4;
int led_2 = 5;
int led_3 = 6;
int led_4 = 7;
int led_5 = 9;

int gamestate = 0; // 0-> inicio, 1-> juego, 2-> gana rojo, 3-> gana azul

int ledEncendido = 0;
int duration = 1200;
unsigned long inicio, finalizado;

bool go = true;
bool go_Chrono = true;

bool rojo = true;
bool azul = false;

int click_ = 0; // 0-> nada, 1-> pulsado, 2-> click 
int click_2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  pinMode(led_r, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_5, OUTPUT);
}

void loop() {
  if(gamestate == 0){
    duration = 1200;
    rojo = true;
    azul = false;
    ledEncendido = 0;
    Encender();
    Click_1();
  }
  else if(gamestate == 1){
    EncenderCronometro();
    Movimiento();
    SetGo();
    Click_1();
    Click_2();
  }
  else if(gamestate == 2){
    RojoGana();
  }
  else if(gamestate == 3){
    AzulGana();
  }
}

void Encender(){
  if(ledEncendido == 1){
    digitalWrite(led_r, HIGH);
    digitalWrite(led_1, LOW);
  }
  else if(ledEncendido == 2){
    ComprobacionRojo();
    digitalWrite(led_1, HIGH);
    digitalWrite(led_r, LOW);
    digitalWrite(led_2, LOW);
  }
  else if(ledEncendido == 3){
    rojo = false;
    digitalWrite(led_2, HIGH);
    digitalWrite(led_1, LOW);
    digitalWrite(led_3, LOW);
  }
  else if(ledEncendido == 4){
    azul = false;
    digitalWrite(led_3, HIGH);
    digitalWrite(led_2, LOW);
    digitalWrite(led_4, LOW);
  }
  else if(ledEncendido == 5){
    digitalWrite(led_4, HIGH);
    digitalWrite(led_3, LOW);
    digitalWrite(led_5, LOW);
    
  }
  else if(ledEncendido == 6){
    ComprobacionAzul();
    digitalWrite(led_5, HIGH);
    digitalWrite(led_4, LOW);
    digitalWrite(led_b, LOW);
  }
  else if(ledEncendido == 7){
    digitalWrite(led_b, HIGH);
    digitalWrite(led_5, LOW);
  }
  else if(ledEncendido == 0){
    digitalWrite(led_r, LOW);
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    digitalWrite(led_4, LOW);
    digitalWrite(led_5, LOW);
    digitalWrite(led_b, LOW);
  }
}

void Movimiento(){
  if(go && millis() > finalizado){
      ledEncendido++;
      go_Chrono = true;
  }
  else if(!go && millis() > finalizado){
    ledEncendido--;
    go_Chrono = true;
  }
  Encender();
}

void SetGo(){
  if(ledEncendido <= 1){
    go = true;
  }
  else if(ledEncendido >= 7){
    go = false;
  }
}

void RojoGana(){
  digitalWrite(led_r, HIGH);
  digitalWrite(led_1, LOW);
  digitalWrite(led_2, LOW);
  digitalWrite(led_3, LOW);
  digitalWrite(led_4, LOW);
  digitalWrite(led_5, LOW);
  digitalWrite(led_b, LOW);

  delay(500);
  digitalWrite(led_r, LOW);
  delay(500);
  digitalWrite(led_r, HIGH);
  delay(500);
  gamestate = 0;
}

void AzulGana(){
  digitalWrite(led_b, HIGH);
  digitalWrite(led_1, LOW);
  digitalWrite(led_2, LOW);
  digitalWrite(led_3, LOW);
  digitalWrite(led_4, LOW);
  digitalWrite(led_5, LOW);
  digitalWrite(led_r, LOW);

  delay(500);
  digitalWrite(led_b, LOW);
  delay(500);
  digitalWrite(led_b, HIGH);
  delay(500);
  gamestate = 0;
}

void Click_1(){
  if(digitalRead(boton1) == LOW){
    click_ = 1;
  }
  else if(digitalRead(boton1) == HIGH && click_ == 1){
    click_ = 2;
  }
  else if(digitalRead(boton1) == HIGH && click_ != 1){
    click_ = 0;
  }
   //funcion al hacer click
  if(click_ == 2){
    if(gamestate == 0){
      gamestate = 1;
    }
    else if(gamestate == 1){
      Rojo();
    } 
  }
}

void Click_2(){
  if(digitalRead(boton2) == LOW){
    click_2 = 1;
  }
  else if(digitalRead(boton2) == HIGH && click_2 == 1){
    click_2 = 2;
  }
  else if(digitalRead(boton2) == HIGH && click_2 != 1){
    click_2 = 0;
  }
   //funcion al hacer click
  if(click_2 == 2){
    Azul();
  }
}


void Rojo(){
  if(ledEncendido == 1){
    Serial.println("BIEN!!");
    rojo = true;
    DisminuirTiempo();
  }
  else{
    gamestate = 3;
  }
}

void Azul(){
  if(ledEncendido == 7){
    Serial.println("BIEN!!");
     azul = true;
    DisminuirTiempo();
  }
  else{
    gamestate = 2;
  }
}


void EncenderCronometro(){
  if(go_Chrono){
    inicio = millis();
    finalizado = millis() + duration;
    go_Chrono = false;
  }
}

void DisminuirTiempo(){
  if(duration > 200){
    duration -= 200;
  }
  else if(duration <= 200 && duration > 100){
    duration -= 100;
  }
}

void ComprobacionRojo(){
   if(go){
    if(!rojo){
      gamestate = 3;
    }
   } 
}

void ComprobacionAzul(){
 if(!go){
    if(!azul){
      gamestate = 2;
    }
   }
}
