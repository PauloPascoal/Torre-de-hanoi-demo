
#include <Servo.h>

#define GARRA                 3
#define HORIZONTAL            5
#define VERTICAL              6
#define BASE                  9
#define BASE_PADRAO           23
#define BRACOH_PADRAO         120
#define BRACOV_PADRAO         112

const int Alturas_LBH[] =   {140,132,125};       //Cordenadas das torres laterais de altura de baixo para cima do braço horizontal
const int Alturas_CBH[] =   {140,132,120};       //Cordenadas da torre central de altura de baixo pra cima do braço horizontal
const int Alturas_LBV[] =   {95,98,112};         //Cordenadas das torres laterais de altura de baixo para cima do braço vertical
const int Alturas_CBV[] =   {100,105,112};       //Cordenadas das torre central de altura de baixo para cima do braço vertical
const int Fechar_Garra  =   75;                  //Cordenadas do motor da garra do menor disco para o maior disco
const int Abrir_Garra   =   30;                  //Cordenada de abrir a garra
const int Girar_Base[]  =   {37,23,13};          //Cordenadas de rotação da base da torre da esquerda até a da direita
int       AlturaT[]     =   {2,0,0};             //Define a altura atual das torres   



Servo servoGarra, servoH, servoV, servoBase;

void setup(){
servoGarra.attach(GARRA);
servoH.attach(HORIZONTAL);
servoV.attach(VERTICAL);
servoBase.attach(BASE);                  //Define os pinos para cada motor


servoGarra.write(45);
delay(200);
servoH.write(120);
delay(200);
servoV.write(112);
delay(200);
servoBase.write(23);                     //Posição inicial
delay(200);                       
}

void baseInicial(){
  servoBase.write(BASE_PADRAO);
}
void bracoHInicial(){
  servoH.write(BRACOH_PADRAO);
}
void bracoVInicial(){
  servoV.write(BRACOV_PADRAO);
  
}

void abregarra(){
    servoGarra.write(Abrir_Garra);
    delay(10);
}

void movimentaBase(int Torre){
   for(int i = BASE_PADRAO; i < Girar_Base[Torre]; i++){
    servoBase.write(i);
    delay(10);
   }
  
}

void movimentaBH(int Torre){
  if (Torre == 0 or Torre == 2){                                                 //Verifica se é uma torre lateral ou a central
   for(int i = BRACOH_PADRAO; i < Alturas_LBH[AlturaT[Torre]]; i++){
    servoH.write(i);
    delay(10);
   }
  }
  else{
   for(int i = BRACOH_PADRAO; i < Alturas_CBH[AlturaT[Torre]]; i++){
    servoH.write(i);
    delay(10);
   }
  }
}

void movimentaBV(int Torre){
  if (Torre == 0 or Torre == 2){
   for(int i = BRACOV_PADRAO; i > Alturas_LBV[AlturaT[Torre]]; i--){
    servoH.write(i);
    delay(10);
   }
  }
  else{
   for(int i = BRACOV_PADRAO; i > Alturas_CBV[AlturaT[Torre]]; i--){
    servoH.write(i);
    delay(10);
   }  
  }
}

void Fechagarra(int Disco){
   for(int i = Abrir_Garra; Fechar_Garra; i++){
    servoH.write(i);
    delay(10);
   }
  
}
void movimente(int TorreI, int TorreF){
  baseInicial();
  delay(100);
  abregarra();
  delay(100);
  baseInicial();
  delay(100);
  bracoHInicial();
  delay(100);
  bracoVInicial();
  delay(200);                   //Garante que a posição seja a inicial
  movimentaBase(TorreI); 
  delay(200);  
  movimentaBH(TorreI);
  delay(200);
  movimentaBV(TorreI);
  delay(200);
  Fechagarra(0);                //Se movimenta em direção a torre certa e pega o disco
  delay(200);
}

void solucionar(int TorreE, int TorreM, int TorreD, int nDiscos){
 // TorreE = 0;
 // TorreM = 1;
 // TorreD = 2;
  
  if(nDiscos>0){
    movimente(TorreE, TorreD);
    solucionar(TorreD, TorreM, TorreE, nDiscos-1);
  }
}
void loop() {
}
