//============================鏅哄畤绉戞妧===========================銆�
/*鍓嶈繘  鎸変笅鍙戝嚭 ONA  鏉惧紑ONF
  鍚庨��锛氭寜涓嬪彂鍑� ONB  鏉惧紑ONF
  宸﹁浆锛氭寜涓嬪彂鍑� ONC  鏉惧紑ONF
  鍙宠浆锛氭寜涓嬪彂鍑� OND  鏉惧紑ONF
  鍋滄锛氭寜涓嬪彂鍑� ONE  鏉惧紑ONF
  
  钃濈墮绋嬪簭鍔熻兘鏄寜涓嬪搴旂殑鎸夐敭鎵ц鎿嶏紝鏉惧紑鎸夐敭灏卞仠姝�
*/
char getstr; 
int Left_motor_go=8;     //宸︾數鏈哄墠杩�(IN1)
int Left_motor_back=9;     //宸︾數鏈哄悗閫�(IN2)
int Right_motor_go=10;    // 鍙崇數鏈哄墠杩�(IN3)
int Right_motor_back=11;    // 鍙崇數鏈哄悗閫�(IN4)
byte index = 0;
byte variable[40];


int Echo = A1;  // Echo鍥炲０鑴�(P2.0)
int Trig =A0;  //  Trig 瑙﹀彂鑴�(P2.1)
int Distance = 0;

int servopin=2;//璁剧疆鑸垫満椹卞姩鑴氬埌鏁板瓧鍙�2
int myangle;//瀹氫箟瑙掑害鍙橀噺
int pulsewidth;//瀹氫箟鑴夊鍙橀噺
int val;

void setup()
{
  //鍒濆鍖栫數鏈洪┍鍔↖O涓鸿緭鍑烘柟寮�
   Serial.begin(9600);
  pinMode(Left_motor_go,OUTPUT); // PIN 8 (鏃燩WM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
  pinMode(servopin,OUTPUT);//璁惧畾鑸垫満鎺ュ彛涓鸿緭鍑烘帴鍙�
  delay(1000);
}
void run()     // 鍓嶈繘
{
   digitalWrite(Right_motor_go,HIGH);  // 鍙崇數鏈哄墠杩�
   digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,255);//PWM姣斾緥0~255璋冮�燂紝宸﹀彸杞樊寮傜暐澧炲噺
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);  // 宸︾數鏈哄墠杩�
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);//PWM姣斾緥0~255璋冮�燂紝宸﹀彸杞樊寮傜暐澧炲噺
  analogWrite(Left_motor_back,255);
  //delay(time * 100);   //鎵ц鏃堕棿锛屽彲浠ヨ皟鏁� 
}

void brake()         //鍒硅溅锛屽仠杞�
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  //delay(time * 100);//鎵ц鏃堕棿锛屽彲浠ヨ皟鏁�  
}

void left()         //宸﹁浆(宸﹁疆涓嶅姩锛屽彸杞墠杩�)
{
  digitalWrite(Right_motor_go,HIGH);	// 鍙崇數鏈哄墠杩�
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,150); 
  analogWrite(Right_motor_back,0);//PWM姣斾緥0~255璋冮��
  digitalWrite(Left_motor_go,LOW);   //宸﹁疆鍚庨��
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);//PWM姣斾緥0~255璋冮��
  //delay(time * 100);	//鎵ц鏃堕棿锛屽彲浠ヨ皟鏁� 
}

void spin_left()         //宸﹁浆(宸﹁疆鍚庨��锛屽彸杞墠杩�)
{
  digitalWrite(Right_motor_go,HIGH);	// 鍙崇數鏈哄墠杩�
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,150); 
  analogWrite(Right_motor_back,0);//PWM姣斾緥0~255璋冮��
  digitalWrite(Left_motor_go,HIGH);   //宸﹁疆鍚庨��
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,150); 
  analogWrite(Left_motor_back,0);//PWM姣斾緥0~255璋冮��
  //delay(time * 100);	//鎵ц鏃堕棿锛屽彲浠ヨ皟鏁� 
}

void right()        //鍙宠浆(鍙宠疆涓嶅姩锛屽乏杞墠杩�)
{
  digitalWrite(Right_motor_go,LOW);   //鍙崇數鏈哄悗閫�
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);//PWM姣斾緥0~255璋冮��
  digitalWrite(Left_motor_go,LOW);//宸︾數鏈哄墠杩�
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,150);//PWM姣斾緥0~255璋冮��
 // delay(time * 100);	//鎵ц鏃堕棿锛屽彲浠ヨ皟鏁� 
}

void spin_right()        //鍙宠浆(鍙宠疆鍚庨��锛屽乏杞墠杩�)
{
  digitalWrite(Right_motor_go,LOW);   //鍙崇數鏈哄悗閫�
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,150);//PWM姣斾緥0~255璋冮��
  digitalWrite(Left_motor_go,LOW);//宸︾數鏈哄墠杩�
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,150);//PWM姣斾緥0~255璋冮��
  //delay(time * 100);	//鎵ц鏃堕棿锛屽彲浠ヨ皟鏁�
}

void back()          //鍚庨��
{
  digitalWrite(Right_motor_go,LOW);  //鍙宠疆鍚庨��
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,250);//PWM姣斾緥0~255璋冮��
  digitalWrite(Left_motor_go,HIGH);  //宸﹁疆鍚庨��
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,250);
  analogWrite(Left_motor_back,0);//PWM姣斾緥0~255璋冮��
  //delay(time * 100);     //鎵ц鏃堕棿锛屽彲浠ヨ皟鏁�    
}

void servopulse(int servopin,int myangle)/*瀹氫箟涓�涓剦鍐插嚱鏁帮紝鐢ㄦ潵妯℃嫙鏂瑰紡浜х敓PWM鍊艰埖鏈虹殑鑼冨洿鏄�0.5MS鍒�2.5MS 1.5MS 鍗犵┖姣旀槸灞呬腑鍛ㄦ湡鏄�20MS*/ 
{
  pulsewidth=(myangle*11)+500;//灏嗚搴﹁浆鍖栦负500-2480 鐨勮剦瀹藉�� 杩欓噷鐨刴yangle灏辨槸0-180搴�  鎵�浠�180*11+50=2480  11鏄负浜嗘崲鎴�90搴︾殑鏃跺�欏熀鏈氨鏄�1.5MS
  digitalWrite(servopin,HIGH);//灏嗚埖鏈烘帴鍙ｇ數骞崇疆楂�  90*11+50=1490uS  灏辨槸1.5ms
  //analogWrite(servopin,-50);
  delayMicroseconds(pulsewidth);//寤舵椂鑴夊鍊肩殑寰鏁�  杩欓噷璋冪敤鐨勬槸寰寤舵椂鍑芥暟
  digitalWrite(servopin,LOW);//灏嗚埖鏈烘帴鍙ｇ數骞崇疆浣�
    //analogWrite(servopin,0);
 // delay(20-pulsewidth/1000);//寤舵椂鍛ㄦ湡鍐呭墿浣欐椂闂�  杩欓噷璋冪敤鐨勬槸ms寤舵椂鍑芥暟
  delay(40-(pulsewidth*0.001));//寤舵椂鍛ㄦ湡鍐呭墿浣欐椂闂�  杩欓噷璋冪敤鐨勬槸ms寤舵椂鍑芥暟
}

void Distance_test()   // 閲忓嚭鍓嶆柟璺濈 
{
  digitalWrite(Trig, LOW);   // 缁欒Е鍙戣剼浣庣數骞�2渭s
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // 缁欒Е鍙戣剼楂樼數骞�10渭s锛岃繖閲岃嚦灏戞槸10渭s
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // 鎸佺画缁欒Е鍙戣剼浣庣數
  float Fdistance = pulseIn(Echo, HIGH);  // 璇诲彇楂樼數骞虫椂闂�(鍗曚綅锛氬井绉�)
  Fdistance= Fdistance/58;       //涓轰粈涔堥櫎浠�58绛変簬鍘樼背锛�  Y绫�=锛圶绉�*344锛�/2
  // X绉�=锛� 2*Y绫筹級/344 ==銆媂绉�=0.0058*Y绫� ==銆嬪帢绫�=寰/58
  Serial.print("Distance:");      //杈撳嚭璺濈锛堝崟浣嶏細鍘樼背锛�
  Serial.println(Fdistance);         //鏄剧ず璺濈
  Distance = Fdistance;
}

void loop() {
  while (Serial.available() > 0) {
    byte b = Serial.read();
    variable[index++] = b;
    Serial.println(b);
xunhuan:
    if((variable[0] != 0x00 || variable[0] != 0x01 || variable[0] != 0x02) && index >= 3 ){
          for(int i=0; i < index;  i++)
          {
            variable[i] = variable[i+1];
           }
            index--;
            goto xunhuan;
      }
  if (index >= 2) {
    //Serial.println(variable[1],HEX);
    
    //Serial.println(variable[1]);
    if(variable[0]==0x00 && variable[1]==0x01){
      run();
      //Serial.print(0x00,HEX); 
      //Serial.print(0x00,HEX);
    }
    else if(variable[0]==0x00 && variable[1]==0x02){
      back();
      //Serial.print(0x00,HEX); 
      //Serial.print(0x01,HEX);
    }
    else if(variable[0]==0x00 && variable[1]==0x03){
      right();
      //Serial.print(0x00,HEX); 
      //Serial.print(0x02,HEX);
    }
    else if(variable[0]==0x00 && variable[1]==0x04){
      left();
      //Serial.print(0x00,HEX); 
      //Serial.print(0x03,HEX);
    }
    else if(variable[0]==0x00 && variable[1]==0x05){
      brake();
      //Serial.print(0x00,HEX); 
      //Serial.print(0x04,HEX);
    }
    
    else if(variable[0]==0x01 && variable[1]==0x01){
      Distance_test();
      Serial.print(0x01,HEX); 
      Serial.print(Distance,HEX);
    }
    
    else if(variable[0]==50){
      byte temp=variable[1];
      int ten=temp/16;
      int sing=temp%16;
      int total=ten*16+sing-48;
      Serial.println(total);
      for(int i=0; i<5; i++){
        servopulse(servopin,total*15);
      }
    }
    index = 0;
    }
  }
}


