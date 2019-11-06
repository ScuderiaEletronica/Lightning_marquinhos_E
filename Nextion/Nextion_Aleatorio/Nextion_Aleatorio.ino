#include <doxygen.h>
#include <NexButton.h>
#include <NexCheckbox.h>
#include <NexConfig.h>
#include <NexCrop.h>
#include <NexDualStateButton.h>
#include <NexGauge.h>
#include <NexGpio.h>
#include <NexHardware.h>
#include <NexHotspot.h>
#include <NexNumber.h>
#include <NexObject.h>
#include <NexPage.h>
#include <NexPicture.h>
#include <NexProgressBar.h>
#include <NexRadio.h>
#include <NexRtc.h>
#include <NexScrolltext.h>
#include <NexSlider.h>
#include <NexText.h>
#include <NexTimer.h>
#include <Nextion.h>
#include <NexTouch.h>
#include <NexUpload.h>
#include <NexVariable.h>
#include <NexWaveform.h>

#define button 7
#define pot A0

NexText t0 = NexText(0, 2, "t0");
NexText t1 = NexText(0, 3, "t1");
NexText t2 = NexText(0, 4, "t2");
NexText t3 = NexText(0, 5, "t3");
NexText t4 = NexText(0, 6, "t4");
NexText t8 = NexText(0, 10, "t8");
NexPage page0 = NexPage(0, 0, "page0");
NexPage page1 = NexPage(1, 0, "page1");
NexPage page2 = NexPage(2, 0, "page2");

char  txt0[10],
      txt1[10],
      txt2[10],
      txt3[10],
      txt4[10],
      txt8[10];

int marcha=0,
    pot_value = 0,
    page=0;

boolean botaoAnt = false,
        botaoAtu = false;
        
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  nexInit();
  page0.show();
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  botaoAtu = digitalRead(button);
  if(botaoAtu && !botaoAnt){
    if(page % 2 == 0)
      page1.show();
    else
      page0.show();
  page++;
  }
  
  botaoAnt=botaoAtu;

  Write(page);

}

void Write(int page){
  pot_value = analogRead(pot);
  
  t0.setText(txt0);
  t1.setText(txt1);
  t2.setText(txt2);
  t3.setText(txt3);
  t4.setText(txt4);
  t8.setText(txt8);

  Alert(page,pot_value,500,t0);

  memset(txt0, 0, sizeof(txt0));
  itoa(pot_value, txt0, 10);

  Visor(random(1000),txt1);

  memset(txt2, 0, sizeof(txt2));
  itoa(random(1000), txt2, 10);

  memset(txt3, 0, sizeof(txt3));
  itoa(random(1000), txt3, 10);

  memset(txt4, 0, sizeof(txt4));
  itoa(random(1000), txt4, 10);

  memset(txt8, 0, sizeof(txt8));
  itoa(random(6), txt8, 10);
}

void Alert(int page, int val, int maximo, NexText t){
  if(val>=maximo){
    page2.show();
    t.Set_font_color_pco(2047);
  }
  else{
    if(page % 2 == 0)
      page1.show();
    else
      page0.show();
  }
}

void Visor(int val, char text[]){
  memset(text, 0, sizeof(text));
  itoa(val, text, 10);
}
