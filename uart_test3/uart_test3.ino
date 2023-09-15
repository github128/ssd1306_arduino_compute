#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
extern uint8_t myfont1[];
void PlayWeatherAndDate();
void emo_tst(void);
int draw_color = 1;


void setup() {
  
  u8g2.begin();

  // initialize serial:
  Serial.begin(9600);



}



// i = 0 cmd ;
//i !=0 data
int i = 0;  //data receive all

int o_cmd = 0;

int data_k = 0;  //data count
int cmd_k = 0; //cmd count

int t = 0; //time_out

char data[200];
char cmd[20];

unsigned char COMPUTER_CONTROL = 0; //电脑接管
int CUR_X=0;
int CUR_Y = 12;//set curlsor

//draw string
void draw_string(const char *s) {
  // assign default color value
  int draw_color = 1;
  u8g2.setColorIndex(draw_color);
  u8g2.setFont(u8g2_font_8x13B_tf);
  u8g2.clearBuffer();
  u8g2.drawStr(CUR_X,CUR_Y, s);
  u8g2.sendBuffer();
  delay(1000);
}

void draw_img() {
  // assign default color value
  //旋转屏幕
  // u8g2.setDisplayRotation(U8G2_R3);
  int draw_color = 1;
  u8g2.setColorIndex(draw_color);
  u8g2.clearBuffer();
  u8g2.drawXBMP(20,20,10,80,data);
  u8g2.sendBuffer();
  delay(2000);
}


void loop() {

 
 if (COMPUTER_CONTROL == 0)
 {
 emo_tst();
 Serial.println("no serial data");
 }

 // 接收命令｛命令，数据｝
  // 传递数据
  while (Serial.available() > 0) {
    COMPUTER_CONTROL = 1;
    //接收数据
    if(i != 0)  //data input
    {
      data[data_k] = Serial.read();
      i = i -1;
      data_k = data_k +1; 

      cmd_k = 0;
      Serial.println(i);

    }
    //接收命令
    else  //cmd input
    {
      data_k = 0;
      cmd[cmd_k] = Serial.read();

      Serial.print(cmd);
      

      //Serial.println("i = 0"); -->接收命令的格式判断
      cmd_k = cmd_k +1;
       if (cmd[cmd_k-1] == '\n')  //ctrl + enter
       {
         cmd[cmd_k-1] = 0;
         Serial.println(cmd);
          draw_string(cmd);

          //接收协议 M开头  操作码OP 附加信息AD M结尾
          //OP = 0 命令 1 数据 
          //AD OP =1 数据长度
          if(cmd[0]== 'M' & cmd[cmd_k-2]=='M' )
          {
            //Serial.print("in xiyi");
            //传递命令
            if(cmd[1] == 'A')
            {
              COMPUTER_CONTROL = 1;
            }
            else if(cmd[1] = 'S')
            {
              CUR_X = 20;
              CUR_Y = 20;
            }


            if(cmd[1] == '0')
            {

            }
            // 传递数据 
            else if(cmd[1] == '1')
            {
              i = cmd[2];
              o_cmd = 1;
            }
            else if(cmd[1] == '2')  //data 数据绘图 
            {
              for(int m = 0;m<100;m++)
                data[m] = 0XFF;
              draw_img();
            }
            else if(cmd[1] == '5')  //show str
            {
              cmd[cmd_k-2] =0;
              draw_string(cmd);
            }
            else if(cmd[1] == '4') //play weather
            {
              Serial.print("is 4");
              PlayWeatherAndDate();
            }
            else if(cmd[1] =='3')  //play emo
            {
              emo_tst();
            }
            else 
            {
              Serial.print("no cmd");
            }
          }
          //command select
          if(strcmp(cmd,"weather")==0)  //4
          {
             Serial.println("play weather");
              PlayWeatherAndDate();
          }
          else if(strcmp(cmd,"emo") == 0)  //3
          {
            Serial.println("play emo");
            emo_tst();
          }
          //command end


        //command run start
         if(o_cmd != 0 )  //command operate  执行DATA_INPUT 数据接收完后的命令
         {
           Serial.print(data);
         }
         //command run end
        cmd_k = 0;
       Serial.print("*****end");
      }
      //传递错误处理

    }
    

   
  }
}



void emo_tst(void)
{
//emo 字体
int k = 0;
  for(int i = 0;i<66;i++)
  {
    k = k+1;
    u8g2.setColorIndex(draw_color);

  
    u8g2.clearBuffer();
  //u8g2.setFont(u8g2_font_8x13B_tf); 

  //u8g2.drawStr(0,10,num(k));
    u8g2.setFont(myfont1);

    u8g2.drawGlyph(34,60,65+k%66);
    //u8g2.drawGlyphX2(0,0,65+k%45);
    u8g2.sendBuffer();
    delay(100);
  }
}

void PlayWeatherAndDate()
{
  unsigned char r = 0;
  
  

  
  
  for(int i = 0;i<100;i ++)
  {
    r = r % 40;
  u8g2.setColorIndex(draw_color);
  u8g2.clearBuffer();
  //data
  u8g2.setFont(u8g2_font_8x13B_tf);
  u8g2.drawStr(40,60, "12月20日");

  u8g2.setFont(u8g2_font_open_iconic_weather_4x_t);
  u8g2.drawGlyph(65,40,65);

  u8g2.drawCircle(30,30,r );

  u8g2.sendBuffer();
  delay(10);
  r = r+1;
  }
  


}


