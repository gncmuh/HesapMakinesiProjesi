#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(32,16,2);

const byte satir PROGMEM=4;
const byte sutun PROGMEM=4;

char tus_takimi[satir][sutun]={
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','x'},
  {'*','0','=','/'}
};

struct pinler{
  byte satir_pinleri[satir]={11,10,9,8};
  byte sutun_pinleri[sutun]={7,6,5,4};
  volatile const byte buton_pin_kesme[1]={2};
};
struct pinler pin;

struct sensor_deger {
  byte buton_deger;
  
};
struct sensor_deger sensor;

Keypad tus=Keypad(makeKeymap(tus_takimi),pin.satir_pinleri,pin.sutun_pinleri,satir,sutun);
bool ac=false;
bool kapi=false;bool kapi2=false;
char gelen_tus;
char birinci_hafiza[10];
char ikinci_hafiza[10];
char ekran_nesneleri[]={'+','-','*','/'};
byte sayac=3;
char islem;float sonuc;
void setup()
{
  Serial.begin(9600);
  if(!Serial)
  {
    while(!bool(0));
  }
  else
  {
    lcd.init();
    for(int i=0; i<1; i++)
      pinMode(pin.buton_pin_kesme[i],INPUT);
    attachInterrupt(0,hesap_makinesi_acma,CHANGE);
  }
}

void loop()
{
  ekran_yonetimi();
  delay(1);
 
  
}
void ilk_ekran() {
  
 if(!bool(0))
 {
   lcd.setCursor(0,0);lcd.print(F("["));
   lcd.setCursor(15,0);lcd.print(F("]"));
   lcd.setCursor(1,1);lcd.print(F("A=+ B=- C=* D=/"));
 }
}
void hesap_makinesi_acma() {
 
  if(!bool(0))
  {
    ac=!ac;
  }
  
}
void ekran_yonetimi() {
  
  if(!bool(0)) 
  {
    buradan:
    if(ac==true)
    {
      lcd.backlight();
      ilk_ekran();
      delay(1);
      kapi=!kapi;ac=!ac;
    } 
    if(kapi==true)
    {
      while(sayac<13)
      { 
        gelen_tus=tus.getKey();
        if(gelen_tus)
        {
          if(gelen_tus!='+' and gelen_tus!='-' and gelen_tus!='x' and gelen_tus!='/')
          {
            birinci_hafiza[sayac-3]=gelen_tus;
            lcd.setCursor(sayac,0);lcd.print(birinci_hafiza[sayac-3]);
            sayac++;
          }   
          if(gelen_tus=='*')
          {
            lcd.clear(); 
            kapi=!kapi;ac=true;
            sayac=3;
            goto buradan;
     
          }
          if(gelen_tus=='+' or gelen_tus=='-' or gelen_tus=='x' or gelen_tus=='/')
          {
            lcd.clear();
            ilk_ekran();
            kapi=!kapi;kapi2=!kapi2;sayac=3;
            islem=gelen_tus;
            goto buradan2;
          }  
          
        }
      }
    }
    
    buradan2:
    if(kapi2!=false)
    {
      do
      {
        gelen_tus=tus.getKey();
        if(gelen_tus)
        {
          if(gelen_tus!='+' and gelen_tus!='-' and gelen_tus!='x' and gelen_tus!='/')
          {
            ikinci_hafiza[sayac-3]=gelen_tus;
            lcd.setCursor(sayac,0);lcd.print(ikinci_hafiza[sayac-3]);
            sayac++;
          }
          if(gelen_tus=='*')
          {
            lcd.clear();
            kapi2=!kapi2;ac=true;
            sayac=3;
            goto buradan;
          }
          if(gelen_tus=='=')
          {
            lcd.clear();ilk_ekran();
            sayac=4;
            toplam(atoi(birinci_hafiza),atoi(ikinci_hafiza),islem);
          }
          
          
        }
        
      }while(sayac<13);
      
    }
   
  }
}
      

void toplam(float Sy1,float Sy2,char yapilan_islem) {
  
  if(!bool(0))
  {
    lcd.setCursor(sayac,0);
    if(yapilan_islem=='+')
    {
      sonuc=(Sy1+Sy2);
    }
    if(yapilan_islem=='-')
    {
      sonuc=(Sy1-Sy2);
    }
    if(yapilan_islem=='x')
    {
      sonuc=(Sy1*Sy2);
    }
    if(yapilan_islem=='/')
    {
      sonuc=(Sy1/Sy2);
    }
  }
  lcd.print(sonuc);
  
  
  
}





                 
                    
            
                  

                    
