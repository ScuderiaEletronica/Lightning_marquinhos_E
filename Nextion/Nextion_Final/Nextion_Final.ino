#include <mcp_can.h>
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

#include "MCP(ECU).h"

#define button 7
#define PIN_CAN_INT 2                 // interrupt

//Texto no Nextion
NexText t0 = NexText(0, 11, "t0");
NexText t1 = NexText(0, 2, "t1");
NexText t2 = NexText(0, 10, "t2");
NexText t3 = NexText(0, 3, "t3");
NexText t4 = NexText(0, 4, "t4");
NexText t8 = NexText(0, 8, "t8");
NexText t9 = NexText(0, 12, "t9");
// Páginas do Nextion
NexPage page0 = NexPage(0, 0, "page0");
NexPage page1 = NexPage(1, 0, "page1");
NexPage page2 = NexPage(2, 0, "page2");

char  txt0[10],
      txt1[10],
      txt2[10],
      txt3[10],
      txt4[10],
      txt8[10],
      txt9[10];

int marcha=0,
    pot_value = 0,
    page=0,
    alert=0;

int variables[21];

boolean botaoAnt = false,
        botaoAtu = false;

//void Alert(int , int, int, NexText);

void setup() {
  // put your setup code here, to run once:
  CAN0.begin(CAN_500KBPS);
  Serial.begin(9600);
  Serial1.begin(9600);
  nexInit();
  page0.show();
  
  pinMode(A13, OUTPUT);
  digitalWrite(A13, 1);

  pinMode(A14, OUTPUT);
  digitalWrite(A14, 0);
  
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(PIN_CAN_INT)){
    Variables(variables);
  }
  Serial.print(variables[4]);

  // Botão para mudar de página
  botaoAtu = !digitalRead(button);
  if(botaoAtu && !botaoAnt){
    if(page % 2 == 0)
      page1.show();
    else
      page0.show();
    page++;
  }
  
  botaoAnt=botaoAtu;

  //Mudanças no Texto
  t0.setText(txt0);
  t1.setText(txt1);
  t2.setText(txt2);
  t3.setText(txt3);
  t4.setText(txt4);
  t8.setText(txt8);
  t9.setText(txt9);

  memset(txt0, 0, sizeof(txt0));
  itoa(variables[3], txt0, 10);
  Alert(page,variables[3],500,t0);

  memset(txt1, 0, sizeof(txt1));
  itoa(variables[4], txt1, 10);
  Alert(page,variables[4],500,t1);

  memset(txt2, 0, sizeof(txt2));
  itoa(variables[5], txt2, 10);
  Alert(page,variables[5],500,t2);

  memset(txt3, 0, sizeof(txt3));
  itoa(variables[1], txt3, 10);
  Alert(page,variables[1],500,t3);

  memset(txt4, 0, sizeof(txt4));
  itoa(variables[17], txt4, 10);
  Alert(page,variables[17],500,t4);

  memset(txt8, 0, sizeof(txt8));
  itoa(variables[15], txt8, 10);
  Alert(page,variables[15],7,t8);

  memset(txt9, 0, sizeof(txt9));
  itoa(variables[7], txt9, 10);
  Alert(page,variables[7],16,t9);
}

//Alerta
void Alert(int page, int val, int maximo, NexText t){
  if(val>=maximo){
    page2.show();
    t.Set_font_color_pco(2047);
    alert=1;
  }
  else{
    if(alert == 1){
      if(page % 2 == 0)
        page1.show();
      else
        page0.show();
      alert=0;
    }
  }
}
