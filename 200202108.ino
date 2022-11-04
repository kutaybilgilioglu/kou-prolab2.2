#include<LiquidCrystal.h>
#include<EEPROM.h>
LiquidCrystal lcd(11, 12, 8, 9, 46, 48);
typedef struct Hizmet {
  byte HizmetId;
  char HizmetAd[10];
  byte KalanHizmet;
  byte HizmetFiyat;
  byte HizmetId_Adres;
  byte HizmetAd_Adres;
  byte KalanHizmet_Adres;
  byte HizmetFiyat_Adres;
};
Hizmet kopukleme, yikama, kurulama, cilalama;

byte _5TL_Adres = 0;
byte _10TL_Adres = 1;
byte _20TL_Adres = 2;
byte _50TL_Adres = 3;
byte _100TL_Adres = 4;
byte yatirilan_Banknot[5];
byte istenen_Hizmet[5];
byte reset;
int ucret;
byte para_Sikisma;
int para_Ustu;
byte banknot_Ustu[5];
byte _5TL_Adet, _10TL_Adet, _20TL_Adet, _50TL_Adet, _100TL_Adet;

int odeme = 0;
void setup() {
  Serial.begin(9600);
  pinMode(22, INPUT);
  pinMode(24, INPUT);
  pinMode(26, INPUT);
  pinMode(28, INPUT);
  pinMode(30, INPUT);
  pinMode(32, INPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  randomSeed(analogRead(A0));
  kopukleme.HizmetId_Adres = 5;
  kopukleme.HizmetAd_Adres = 7;
  kopukleme.KalanHizmet_Adres = 18;
  kopukleme.HizmetFiyat_Adres = 19;
  yikama.HizmetId_Adres = 20;
  yikama.HizmetAd_Adres = 21;
  yikama.KalanHizmet_Adres = 29;
  yikama.HizmetFiyat_Adres = 30;
  kurulama.HizmetId_Adres = 31;
  kurulama.HizmetAd_Adres = 32;
  kurulama.KalanHizmet_Adres = 42;
  kurulama.HizmetFiyat_Adres = 43;
  cilalama.HizmetId_Adres = 44;
  cilalama.HizmetAd_Adres = 45;
  cilalama.KalanHizmet_Adres = 55;
  cilalama.HizmetFiyat_Adres = 56;
  EEPROM.write(kopukleme.HizmetId_Adres, 1);
  EEPROM.put(kopukleme.HizmetAd_Adres, "kopukleme");
  EEPROM.write( kopukleme.KalanHizmet_Adres, 30);
  EEPROM.write(kopukleme.HizmetFiyat_Adres, 15);

  EEPROM.write(yikama.HizmetId_Adres, 2);
  EEPROM.put(yikama.HizmetAd_Adres, "yikama");
  EEPROM.write(yikama.KalanHizmet_Adres, 50);
  EEPROM.write(yikama.HizmetFiyat_Adres, 10);

  EEPROM.write(kurulama.HizmetId_Adres, 3);
  EEPROM.put(kurulama.HizmetAd_Adres, "kurulama");
  EEPROM.write(kurulama.KalanHizmet_Adres, 100);
  EEPROM.write(kurulama.HizmetFiyat_Adres, 5);

  EEPROM.write(cilalama.HizmetId_Adres, 4);
  EEPROM.put(cilalama.HizmetAd_Adres, "cilalama");
  EEPROM.write(cilalama.KalanHizmet_Adres, 20);
  EEPROM.write(cilalama.HizmetFiyat_Adres, 50);

  EEPROM.write(_5TL_Adres, 0);
  EEPROM.write(_10TL_Adres, 0);
  EEPROM.write(_20TL_Adres, 0);
  EEPROM.write(_50TL_Adres, 0);
  EEPROM.write(_100TL_Adres, 0);




  // LCD Başlangıç 
  lcd.begin(16, 2);




 

}

void loop() {
  while (1) {
    _5TL_Adet = EEPROM.read(_5TL_Adres);
    _10TL_Adet = EEPROM.read(_10TL_Adres);
    _20TL_Adet = EEPROM.read(_20TL_Adres);
    _50TL_Adet = EEPROM.read(_50TL_Adres);
    _100TL_Adet = EEPROM.read(_100TL_Adres);

    kopukleme.HizmetId = EEPROM.read(kopukleme.HizmetId_Adres);
    EEPROM.get(kopukleme.HizmetAd_Adres, kopukleme.HizmetAd);
    kopukleme.KalanHizmet = EEPROM.read(kopukleme.KalanHizmet_Adres);
    kopukleme.HizmetFiyat = EEPROM.read(kopukleme.HizmetFiyat_Adres);

    yikama.HizmetId = EEPROM.read(yikama.HizmetId_Adres);
    EEPROM.get(yikama.HizmetAd_Adres, yikama.HizmetAd);
    yikama.KalanHizmet = EEPROM.read(yikama.KalanHizmet_Adres);
    yikama.HizmetFiyat = EEPROM.read(yikama.HizmetFiyat_Adres);

    kurulama.HizmetId = EEPROM.read(kurulama.HizmetId_Adres);
    EEPROM.get(kurulama.HizmetAd_Adres, kurulama.HizmetAd);
    kurulama.KalanHizmet = EEPROM.read(kurulama.KalanHizmet_Adres);
    kurulama.HizmetFiyat = EEPROM.read(kurulama.HizmetFiyat_Adres);

    cilalama.HizmetId = EEPROM.read(cilalama.HizmetId_Adres);
    EEPROM.get(cilalama.HizmetAd_Adres, cilalama.HizmetAd);
    cilalama.KalanHizmet = EEPROM.read(cilalama.KalanHizmet_Adres);
    cilalama.HizmetFiyat = EEPROM.read(cilalama.HizmetFiyat_Adres);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    para_Ustu = 0;
    ucret = 0;
    odeme = 0;
    reset = 0;
    for (int i = 0; i < 5; i++) {
      yatirilan_Banknot[i] = 0;
      istenen_Hizmet[i] = 0;
      banknot_Ustu[i] = 0;
    }
    lcd.clear();
    
    lcd.home();
    lcd.print("Devam etmek icin");
    lcd.setCursor(0, 1);
    lcd.print("1.Butona Basiniz");
    lcd.home();
    while (digitalRead(22) == LOW) {

    }
    lcd.clear();
    lcd.print("Butonlar");
    lcd.setCursor(0, 1);
    lcd.print("sirasiyla");
    lcd.setCursor(0, 0);
    delay(2000);
    lcd.clear();
    lcd.print("5TL 10TL 20TL");
    lcd.setCursor(0, 1);
    lcd.print("50TL 100TL BITIS");

    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Para:");
    lcd.print(odeme);

    while (1) {
      if (digitalRead(22) == HIGH) {
        odeme = odeme + 5;
        yatirilan_Banknot[0]++;
        _5TL_Adet++;
        EEPROM.write(_5TL_Adres, _5TL_Adet);
        Serial.println(String("5 TL ") + String(EEPROM.read(_5TL_Adres)));
        lcd.clear();
        lcd.print(String("Para:") + String(odeme));
        delay(200);
      }
      if (digitalRead(24) == HIGH) {
        odeme = odeme + 10;
        yatirilan_Banknot[1]++;
        _10TL_Adet++;
        EEPROM.write(_10TL_Adres, _10TL_Adet);
        Serial.println(String("10 TL ") + String(EEPROM.read(_10TL_Adres)));
        lcd.clear();
        lcd.print(String("Para:") + String(odeme));
        delay(200);
      }
      if (digitalRead(26) == HIGH) {
        odeme = odeme + 20;
        yatirilan_Banknot[2]++;
        _20TL_Adet++;
        EEPROM.write(_20TL_Adres, _20TL_Adet);
        Serial.println(String("20 TL ") + String(EEPROM.read(_20TL_Adres)));
        lcd.clear();
        lcd.print(String("Para:") + String(odeme));
        delay(200);
      }
      if (digitalRead(28) == HIGH) {
        odeme = odeme + 50;
        yatirilan_Banknot[3]++;
        _50TL_Adet++;
        EEPROM.write(_50TL_Adres, _50TL_Adet);
        Serial.println(String("50 TL ") + String(EEPROM.read(_50TL_Adres)));
        lcd.clear();
        lcd.print(String("Para:") + String(odeme));

        delay(200);
      }
      if (digitalRead(30) == HIGH) {
        odeme = odeme + 100;
        yatirilan_Banknot[4]++;
        _100TL_Adet++;
        EEPROM.write(_100TL_Adres, _100TL_Adet);
        Serial.println(String("100 TL ") + String(EEPROM.read(_100TL_Adres)));
        lcd.clear();
        lcd.print(String("Para:") + String(odeme));
        delay(200);
      }
      if (digitalRead(32) == HIGH) {
        break;
      }
    }
    lcd.clear();
    lcd.print("yatirdiginiz");
    lcd.setCursor(0, 1);
    lcd.print(String("miktar:") + String(odeme));
    lcd.setCursor(0, 0);
    delay(4000);
    lcd.clear();
    lcd.print("Hizmet Kalan Bedel");
    delay(2500);
    lcd.scrollDisplayLeft();
    delay(600);
    lcd.scrollDisplayLeft();
    delay(1500);
    lcd.clear();

    lcd.print(String("kopuk ") + String(kopukleme.KalanHizmet) + String(" ") + String(kopukleme.HizmetFiyat));
    lcd.setCursor(0, 1);
    lcd.print(String("yika ") + String(yikama.KalanHizmet) + String(" ") + String(yikama.HizmetFiyat));
    lcd.home();
    delay(4000);
    lcd.clear();
    lcd.print(String("kuru ") + String(kurulama.KalanHizmet) + String(" ") + String(kurulama.HizmetFiyat));
    lcd.setCursor(0, 1);
    lcd.print(String("cila ") + String(cilalama.KalanHizmet) + String(" ") + String(cilalama.HizmetFiyat));
    lcd.home();
    delay(4000);
    lcd.clear();
    lcd.print("5.Buton 'Bitis'");
    lcd.setCursor(0, 1);
    lcd.print("6.Buton 'Reset'");
    lcd.home();
    delay(3000);
    lcd.clear();
    lcd.print(String("1kopuk ") + String(istenen_Hizmet[0]) + String(" 2yika ") + String(istenen_Hizmet[1]));
    lcd.setCursor(0, 1);
    lcd.print(String("3kuru ") + String(istenen_Hizmet[2]) + String(" 4cila ") + String(istenen_Hizmet[3]));
    lcd.home();//Kalan hizmet kontrolü yap
    while (1) {
      if (digitalRead(22) == HIGH) {
        istenen_Hizmet[0]++;
        if (kopukleme.KalanHizmet - istenen_Hizmet[0] < 0) {
          istenen_Hizmet[0]--;
          lcd.clear();
          lcd.print("Kopuk Hizmeti");
          lcd.setCursor(0, 1);
          lcd.print("Kalmamıstır");
          lcd.home();
          delay(3000);
          lcd.clear();
          lcd.print("Tekrar seciniz");
          lcd.home();
          delay(2000);
          lcd.clear();
          lcd.print(String("1kopuk ") + String(istenen_Hizmet[0]) + String(" 2yika ") + String(istenen_Hizmet[1]));
          lcd.setCursor(0, 1);
          lcd.print(String("3kuru ") + String(istenen_Hizmet[2]) + String(" 4cila ") + String(istenen_Hizmet[3]));
          lcd.home();
          continue;
        }
        else {
          kopukleme.KalanHizmet--;
          EEPROM.write(kopukleme.KalanHizmet_Adres, kopukleme.KalanHizmet);
          Serial.println(String("kopukleme ") + String(EEPROM.read(kopukleme.KalanHizmet_Adres)));
          ucret += 15;
          lcd.clear();
          lcd.print(String("1kopuk ") + String(istenen_Hizmet[0]) + String(" 2yika ") + String(istenen_Hizmet[1]));
          lcd.setCursor(0, 1);
          lcd.print(String("3kuru ") + String(istenen_Hizmet[2]) + String(" 4cila ") + String(istenen_Hizmet[3]));
          lcd.home();
          delay(200);
        }
      }
      if (digitalRead(24) == HIGH) {
        istenen_Hizmet[1]++;
        if (kopukleme.KalanHizmet - istenen_Hizmet[1] < 0) {
          istenen_Hizmet[1]--;
          lcd.clear();
          lcd.print("Yikama Hizmeti");
          lcd.setCursor(0, 1);
          lcd.print("Kalmamıstır");
          lcd.home();
          delay(3000);
          lcd.clear();
          lcd.print("Tekrar seciniz");
          lcd.home();
          delay(2000);
          lcd.clear();
          lcd.print(String("1kopuk ") + String(istenen_Hizmet[0]) + String(" 2yika ") + String(istenen_Hizmet[1]));
          lcd.setCursor(0, 1);
          lcd.print(String("3kuru ") + String(istenen_Hizmet[2]) + String(" 4cila ") + String(istenen_Hizmet[3]));
          lcd.home();
          continue;
        }
        else {
          yikama.KalanHizmet--;
          EEPROM.write(yikama.KalanHizmet_Adres, yikama.KalanHizmet);
          Serial.println(String("yikama ") + String(EEPROM.read(yikama.KalanHizmet_Adres)));
          ucret += 10;
          lcd.clear();
          lcd.print(String("1kopuk ") + String(istenen_Hizmet[0]) + String(" 2yika ") + String(istenen_Hizmet[1]));
          lcd.setCursor(0, 1);
          lcd.print(String("3kuru ") + String(istenen_Hizmet[2]) + String(" 4cila ") + String(istenen_Hizmet[3]));
          lcd.home();
          delay(200);
        }
      }
      if (digitalRead(26) == HIGH) {
        istenen_Hizmet[2]++;
        if (kopukleme.KalanHizmet - istenen_Hizmet[2] < 0) {
          istenen_Hizmet[2]--;
          lcd.clear();
          lcd.print("Kurulama Hizmeti");
          lcd.setCursor(0, 1);
          lcd.print("Kalmamıstır");
          lcd.home();
          delay(3000);
          lcd.clear();
          lcd.print("Tekrar seciniz");
          lcd.home();
          delay(2000);
          lcd.clear();
          lcd.print(String("1kopuk ") + String(istenen_Hizmet[0]) + String(" 2yika ") + String(istenen_Hizmet[1]));
          lcd.setCursor(0, 1);
          lcd.print(String("3kuru ") + String(istenen_Hizmet[2]) + String(" 4cila ") + String(istenen_Hizmet[3]));
          lcd.home();
          continue;
        }
        else {
          kurulama.KalanHizmet--;
          EEPROM.write(kurulama.KalanHizmet_Adres, kurulama.KalanHizmet);
          Serial.println(String("kurulama ") + String(EEPROM.read(kurulama.KalanHizmet_Adres)));
          ucret += 5;
          lcd.clear();
          lcd.print(String("1kopuk ") + String(istenen_Hizmet[0]) + String(" 2yika ") + String(istenen_Hizmet[1]));
          lcd.setCursor(0, 1);
          lcd.print(String("3kuru ") + String(istenen_Hizmet[2]) + String(" 4cila ") + String(istenen_Hizmet[3]));
          lcd.home();
          delay(200);
        }
      }
      if (digitalRead(28) == HIGH) {
        istenen_Hizmet[3]++;
        if (kopukleme.KalanHizmet - istenen_Hizmet[3] < 0) {
          istenen_Hizmet[3]--;
          lcd.clear();
          lcd.print("Cilalama Hizmeti");
          lcd.setCursor(0, 1);
          lcd.print("Kalmamıstır");
          lcd.home();
          delay(3000);
          lcd.clear();
          lcd.print("Tekrar seciniz");
          lcd.home();
          delay(2000);
          lcd.clear();
          lcd.print(String("1kopuk ") + String(istenen_Hizmet[0]) + String(" 2yika ") + String(istenen_Hizmet[1]));
          lcd.setCursor(0, 1);
          lcd.print(String("3kuru ") + String(istenen_Hizmet[2]) + String(" 4cila ") + String(istenen_Hizmet[3]));
          lcd.home();
          continue;
        }
        else {
          cilalama.KalanHizmet--;
          EEPROM.write(cilalama.KalanHizmet_Adres, cilalama.KalanHizmet);
          Serial.println(String("cilalama ") + String(EEPROM.read(cilalama.KalanHizmet_Adres)));
          ucret += 50;
          lcd.clear();
          lcd.print(String("1kopuk ") + String(istenen_Hizmet[0]) + String(" 2yika ") + String(istenen_Hizmet[1]));
          lcd.setCursor(0, 1);
          lcd.print(String("3kuru ") + String(istenen_Hizmet[2]) + String(" 4cila ") + String(istenen_Hizmet[3]));
          lcd.home();

          delay(200);
        }
      }
      if (digitalRead(30) == HIGH) {
        break;

      }
      if (digitalRead(32) == HIGH) {
        reset = 1;
        lcd.clear();
        lcd.print("Paraniz iade");
        lcd.setCursor(0, 1);
        lcd.print("ediliyor..");
        lcd.home();
        delay(3500);
        break;
      }
    }
    lcd.clear();

    para_Ustu = odeme - ucret;

    while (para_Ustu >= 100 && _100TL_Adet > 0) {
      para_Ustu -= 100;
      banknot_Ustu[4]++;
    }
    while (para_Ustu >= 50 && _50TL_Adet > 0) {
      para_Ustu -= 50;
      banknot_Ustu[3]++;
    }
    while (para_Ustu >= 20 && _20TL_Adet > 0) {
      para_Ustu -= 20;
      banknot_Ustu[2]++;
    }
    while (para_Ustu >= 10 && _10TL_Adet > 0) {
      para_Ustu -= 10;
      banknot_Ustu[1]++;
    }
    while (para_Ustu >= 5 && _5TL_Adet > 0) {
      para_Ustu -= 5;
      banknot_Ustu[0]++;
    }
    para_Sikisma = random(1, 50);
    if (odeme < ucret || para_Sikisma == 2 || reset == 1 || para_Ustu > 0) {
      digitalWrite(4, HIGH);
      if (odeme < ucret&&reset==0) {

        lcd.print("Yatirdiginiz");
        lcd.setCursor(0, 1);
        lcd.print("para yetersiz");
        delay(3000);
        lcd.clear();
        lcd.home();

      }
      else if (para_Sikisma == 2&&reset==0) {

        lcd.print("Paraniz sikisti :(");
        lcd.setCursor(0, 1);
        lcd.print("Iade yapiliyor");
        delay(7000);
        lcd.clear();
        lcd.home();

      }
      else if (para_Ustu > 0&&reset==0) {

        lcd.print("Kasada yeterli");
        lcd.setCursor(0, 1);
        lcd.print("para yoktur");
        lcd.home();
        delay(5000);
        lcd.clear();

      }
      lcd.print("Resetleniyor...");
      delay(3000);
      lcd.clear();
     EEPROM.write(kopukleme.KalanHizmet_Adres, (kopukleme.KalanHizmet + istenen_Hizmet[0]));
     EEPROM.write(yikama.KalanHizmet_Adres, (yikama.KalanHizmet + istenen_Hizmet[1]));
     EEPROM.write(kurulama.KalanHizmet_Adres, (kurulama.KalanHizmet + istenen_Hizmet[2]));
     EEPROM.write(cilalama.KalanHizmet_Adres, (cilalama.KalanHizmet + istenen_Hizmet[3]));
     EEPROM.write(_5TL_Adres, _5TL_Adet - yatirilan_Banknot[0] );
     EEPROM.write(_10TL_Adres, _10TL_Adet - yatirilan_Banknot[1] );
     EEPROM.write(_20TL_Adres, _20TL_Adet - yatirilan_Banknot[2]);
     EEPROM.write(_50TL_Adres, _50TL_Adet - yatirilan_Banknot[3]);
     EEPROM.write(_100TL_Adres, _100TL_Adet - yatirilan_Banknot[4]);
        Serial.println(String("5TL " )+String(EEPROM.read(_5TL_Adres)));
          Serial.println(String("10TL " )+String(EEPROM.read(_10TL_Adres)));
          Serial.println(String("20TL " )+String(EEPROM.read(_20TL_Adres)));
         Serial.println(String("50TL " )+String(EEPROM.read(_50TL_Adres)));
        Serial.println(String("100TL " )+String(EEPROM.read(_100TL_Adres)));
       Serial.println(String("kopukleme " )+String(EEPROM.read(kopukleme.KalanHizmet_Adres)));
       Serial.println(String("yikama " )+String(EEPROM.read(yikama.KalanHizmet_Adres)));
        Serial.println(String("kurulama " )+String(EEPROM.read(kurulama.KalanHizmet_Adres)));
         Serial.println(String("cilalama " )+String(EEPROM.read(cilalama.KalanHizmet_Adres)));
         
      continue;
    }





    digitalWrite(2, HIGH);
    lcd.print("Islem basarili");
    delay(4000);
    lcd.clear();
    lcd.print("Para Ustu");
    lcd.setCursor(0, 1);
    lcd.print("Veriliyor..");
    delay(3000);
    lcd.clear();
    lcd.print("Para Ustu:"),
              delay(2000);
    lcd.clear();
    lcd.print(String("5x") + String(banknot_Ustu[0]) + String(" 10x") + String(banknot_Ustu[1]) + String(" 20x") + String(banknot_Ustu[2])); //ekrana sığmıyor düzelt
    lcd.setCursor(0, 1);
    lcd.print(String("50x") + String(banknot_Ustu[3]) + String(" 100x") + String(banknot_Ustu[4]));
    lcd.home();
    EEPROM.write(kopukleme.KalanHizmet_Adres, (kopukleme.KalanHizmet - istenen_Hizmet[0]));
    EEPROM.write(yikama.KalanHizmet_Adres, (yikama.KalanHizmet - istenen_Hizmet[1]));
    EEPROM.write(kurulama.KalanHizmet_Adres, (kurulama.KalanHizmet - istenen_Hizmet[2]));
    EEPROM.write(cilalama.KalanHizmet_Adres, (cilalama.KalanHizmet - istenen_Hizmet[3]));

    EEPROM.write(_5TL_Adres, _5TL_Adet + (yatirilan_Banknot[0] - banknot_Ustu[0]));
    EEPROM.write(_10TL_Adres, _10TL_Adet + (yatirilan_Banknot[1] - banknot_Ustu[1]));
    EEPROM.write(_20TL_Adres, _20TL_Adet + (yatirilan_Banknot[2] - banknot_Ustu[2]));
    EEPROM.write(_50TL_Adres, _50TL_Adet + (yatirilan_Banknot[3] - banknot_Ustu[3]));
    EEPROM.write(_100TL_Adres, _100TL_Adet + (yatirilan_Banknot[4] - banknot_Ustu[4]));
    delay(6000);





  }
}
