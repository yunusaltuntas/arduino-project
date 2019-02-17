#include <LiquidCrystal.h>
#include <DS1302.h>
#define doo  1000
#define re   1122
#define mi   1260
#define fa   1335
#define sol  1498
#define la   1681
#define si   1887
#define dom  2000
int melody[] =     {re,mi,fa,sol,fa,sol,sol,sol, fa, sol,sol,sol ,fa, mi, re,mi,fa,sol,fa,sol,sol,sol, fa, sol,sol,sol ,fa, mi,   re, mi ,fa,sol,mi,fa,re,mi,doo,doo,fa,mi,re,re,re, mi ,fa,sol,mi,fa,re,mi,doo,doo,fa,mi,re,re };
int notasuresi[] = {4,  4,  4,  4, 4,  4,4,  3 ,4,4,4,4,4,2,4,  4,  4,  4, 4,  4,4,  3 ,4,4,4,4,4,2       ,4,4,4,4,4,4,4,4,4,4,4,4,2,2,    4,4,4,4,4,4,4,4,4,4,4,4,2,2};// her notanin süresini array yaptim
int tempo = 1200;
DS1302 rtc(2, 3, 4);
LiquidCrystal lcd(10,9,8,7,6,5);
int saat=0;
int dakika=0;
int alarm=0;
int ay=1;
int gun=1;
int yil=2010;
Time t;
void setup() {
  Serial.begin(9600);
lcd.begin(16, 2);
  rtc.halt(false);
  rtc.writeProtect(false);
    rtc.setDOW(FRIDAY);       
  Serial.begin(9600);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
    while(1){                         ///burada dakaika ayarlanıyor
    lcd.setCursor(0, 0); 
    lcd.print("dakika ayarlayin");
        lcd.setCursor(3, 1); 
    lcd.print(dakika);
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(0, 1);
    lcd.print(saat);
    if(digitalRead(12)==HIGH){
    dakika=dakika+1;
    delay(500);
    if(dakika>59){                  ///burada dakika 60 dan buyuk olamıyacagı için 60 a geldiginde dönguyu tekrar 0 a getirir
      dakika=0;
      lcd.clear();
      }
    }
    if(digitalRead(11)==HIGH){      ///burada while döngüsünden çıkıyoruz
      delay(500);
      break;
      }
    }
    
    while(1){                       ///burada saati ayarlıyoruz
      lcd.setCursor(0, 0); 
    lcd.print("saati ayarlayin");   
       lcd.setCursor(3, 1); 
    lcd.print(dakika);
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(0, 1);
    lcd.print(saat);
      if(digitalRead(12)==HIGH){
      saat=saat+1;
      delay(500);
 
    if(saat>23){                ///burada saat 24 e geldiginde tekrar sıfıra getiriyoruz
      saat=0;
      lcd.clear();}}
    
    if(digitalRead(11)==HIGH){        ///burada while döngüsünden çıkıyoruz
      delay(500);
        lcd.clear();
      break;
      }
    }
    rtc.setTime(saat, dakika, 0);   ///burada biraz çnce kullanıcıdan aldıgımız saat ve dakikayı atıyorruz rtc module
    while(1){                   ///burada gunü ayarlıyoruz
        lcd.setCursor(0, 0); 
    lcd.print("gun ayarlayin");
        lcd.setCursor(0, 1);
    lcd.print(gun);
      lcd.setCursor(2, 1); 
    lcd.print(":");
    lcd.setCursor(3, 1);
    lcd.print(ay);
    lcd.setCursor(5, 1); 
    lcd.print(":");
    lcd.setCursor(6, 1);
    lcd.print(yil);
    if(digitalRead(12)==HIGH){
    gun=gun+1;
      if(gun>31){               ///burada gun 31 e ulaştıgında onu tekrar 1e çekiyoruz
    gun=1;
    lcd.clear();}
    delay(500); 

  }
if(digitalRead(11)==HIGH){        ///burada while döngüsünden çıkıyoruz
      delay(500);
      break;
      }}

    while(1){                   ///burada ayı ayarlıyoruz
    lcd.setCursor(0, 0); 
    lcd.print("ay ayarlayin");
    lcd.setCursor(0, 1);
    lcd.print(gun);
    lcd.setCursor(2, 1); 
    lcd.print(":");
    lcd.setCursor(3, 1);
    lcd.print(ay);
    lcd.setCursor(5, 1); 
    lcd.print(":");
    lcd.setCursor(6, 1);
    lcd.print(yil);
    if(digitalRead(12)==HIGH){
    ay=ay+1;
     if(ay>12){               ///burada ay 12 ye aştıgında ayı tekrar 1 ci ayaçeker
    ay=1; 
    lcd.clear();
  }
    delay(500); 
  }
if(digitalRead(11)==HIGH){        ///burada while döngüsünden çıkıyoruz
      delay(500);
      break;
      }}

  while(1){                     ///burada yılı ayarlıyoruz
        lcd.setCursor(0, 0); 
    lcd.print("yil ayarlayin");
        lcd.setCursor(0, 1);
    lcd.print(gun);
      lcd.setCursor(2, 1); 
    lcd.print(":");
    lcd.setCursor(3, 1);
    lcd.print(ay);
    lcd.setCursor(5, 1); 
    lcd.print(":");
    lcd.setCursor(6, 1);
    lcd.print(yil);
    if(digitalRead(12)==HIGH){
    yil=yil+1;
    delay(500); 

  }
if(digitalRead(11)==HIGH){        ///burada while döngüsünden çıkıyoruz
      delay(500);
      break;
      }}
rtc.setDate(gun,ay,yil);        ///ay yıl ve gün degişkenlerini atama işlemi gerçekleştiriyor rtc module
}

void loop() {
  saat=0;
  dakika=0;
  t = rtc.getTime();
  if(0!=t.hour|0!=t.min){
       lcd.setCursor(0, 0);     ///burada rtc modulden alınan saat ay yı gibi veriler lcd ye yazılır 
   lcd.print(t.date, DEC);
   lcd.print("/");
   lcd.print(rtc.getMonthStr());
   lcd.print("/");
   lcd.print(t.year, DEC);
  Serial.print("saat kısamı çalışıyor");
  lcd.setCursor(0,1);
  lcd.print(t.hour, DEC);
   lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print(t.min, DEC);
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(t.sec, DEC);

  if(alarm==1){                 ///alarmın durumu lcd ye yazılır
    lcd.setCursor(8,1);
    lcd.print(" acik");}
    else{
      lcd.setCursor(8,1);
      lcd.print(" kapali");
    }
 if(digitalRead(11)==HIGH){     /// kurulan alarmı çalmadan kapatma 
  alarm=0;
  }

    
 if(digitalRead(12)==HIGH){     ///burada alarm kurma sistemine giriliyor
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.println("alarm kurma sistemi");
  delay(1000);
  lcd.clear();
     while(1){                ///dakika buradav kurulur
    lcd.setCursor(0, 0); 
    lcd.print("dakika ayarlayin");
    lcd.setCursor(3, 1); 
    lcd.print(dakika);
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(0, 1);
    lcd.print(saat);
    if(digitalRead(12)==HIGH){
    dakika=dakika+1;
    delay(500);
    if(dakika>59){          ///burada dakika 60 oldugunda dakikayı sıfır yapıyor program
    dakika=0;
    lcd.clear();
      }
    }
    if(digitalRead(11)==HIGH){    ///while döngüsünde çıkma işlemi gerçekleşir
      delay(500);
      break;
      }
    }
    
    while(1){                     ///burada alarm saati ayarlanıyor
      lcd.setCursor(0, 0); 
    lcd.print("saati ayarlayin");
       lcd.setCursor(3, 1); 
    lcd.print(dakika);
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(0, 1);
    lcd.print(saat);
      if(digitalRead(12)==HIGH){
      saat=saat+1;
      delay(500);
 
    if(saat>23){                ///burada saaat 24 e ulaştıgında saati sıfıra tekrar getiriyoruz
      saat=0;
      lcd.clear();}}
    
    if(digitalRead(11)==HIGH){      ///while döngüsünde çıkma işlemi gerçekleşir
      delay(500);
        lcd.clear();
      break;
      }
    }
    alarm=1;
 }
  if(alarm==1&dakika==t.min){       ///alar saatini kontrol ediyor
    if(saat==t.hour){
    alarm=0;
  while(digitalRead(12)==LOW)
  {
    for (int Nota = 0; Nota <56; Nota++)                ///buradada alarm melodisi calınıyor
    {
      int sure = tempo/notasuresi[Nota];
     tone(13, melody[Nota],sure);// 8 numarali bacaktan notalarin frekanslarini nota uzunluklarina göre gönder
     delay(sure*1.2);// notalar arasinda biraz beklesin. Eger 1 ile çarparsaniz notalar birbirine bitisik olur
    if(digitalRead(12)!=LOW)
    break;
    }}}}}}
