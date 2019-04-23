//#include <Servo.h>

#define MIDA 10
#define SENSOR A0

char msend[MIDA];    //MENSAJE DE ENVIO
char mreciv[MIDA];   // MENSAJE DE RECEPCIÓN 
char codevM, codevE, codevS;    //CODI V
char codenn[2];
int  valor_sensor;
int  tiempo, pin_s, pin_e;
int i;

void msnread();
void ficatreu();

void setup() {
    codevM='0';  
    i=0;
    analogReference(DEFAULT);//tension interno de arduino 5v  (INTERNAL 1.1V)

    //set timer at 1 Hz
    noInterrupts();
         TCCR1A = 0;// set entire TCCR1A register to 0
         TCCR1B = 0;// same for TCCR1B
         TCNT1  = 0;//initialize counter value to 0
        
        // set compare match register for 1hz increments
        OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
        
        // turn on CTC mode
        TCCR1B |= (1 << WGM12);
        
        // Set CS12 and CS10 bits for 1024 prescaler
        TCCR1B |= (1 << CS12);
        TCCR1B |= (1 << CS10);  
        // enable timer compare interrupt
        TIMSK1 |= (1 << OCIE1A);
    interrupts();
       
    Serial.begin(9600);
   
}

void loop() {

 
    int valordig=0;
  

    msnread ();
    codenn[0] = mreciv[2];
    codenn[1] = mreciv[3];
    
    
    
    switch(mreciv[1]){
  
    //----------------------------------------CASE M---------------------------------//
         case 'M':
                
         tiempo= (mreciv[3]-48) * 10 + (mreciv[4]-48);
         
                                //---errors---// 
         if (mreciv[0] == 'A') {                        
           if ((mreciv[5] != 'Z') || (mreciv [1] =='A' || mreciv [2]=='A' || mreciv [3]=='A' || mreciv [4]== 'A'))
            {
            sprintf(msend,"AM1Z\n");
            
            }
            
           else if (codevM == mreciv[2]){  
            sprintf(msend,"AM2Z\n");
            Serial.println(msend);} 
                                //---ok---//                 
           else {
            sprintf(msend,"AM0Z\n");  
            Serial.println(msend);
            }
                     
         }//END IF MRECIV[0]
       
         codevM=mreciv[2];
         break;                       
         
         
   
    //----------------------------------------CASE S---------------------------------//      
         case 'S':

         pin_s= (mreciv[2]-48) * 10 + (mreciv[3]-48);
         
                                //---errors---//
         if (mreciv[0] == 'A' && codevM == '1') {                       
           if ((mreciv [5] != 'Z') || (mreciv [1] =='A' || mreciv [2]=='A' || mreciv [3]=='A' || mreciv [4]== 'A'))
            {
              ficatreu();
              sprintf(msend,"AS1Z\n");
  
            }//END IF
           else if ((pin_s > 13) || (mreciv[4] > '1'))
             {
              sprintf(msend,"AS2Z\n"); 
              Serial.println(msend);
             } //END ELSE IF
                            
            else 
             {
              sprintf(msend,"AS0Z\n");
             
              ficatreu();   
              Serial.println(msend);   
             } 
                    
         }
           memset( mreciv, 0, MIDA );
                           
         break;
         

    //----------------------------------------CASE E---------------------------------//
         case 'E':
         
          pin_e= (mreciv[2]-48) * 10 + (mreciv[3]-48);
                                //---errors---//
        if (mreciv[0] == 'A' && codevM == '1')
        {                        
          if ((mreciv [4] != 'Z') || (mreciv [1] =='A' || mreciv [2]=='A' || mreciv [3]=='A'))
          {
            ficatreu();
           sprintf(msend,"AE1%cZ\n",codevE);
          
          }
          else if (pin_e> 13)
          {
           ficatreu(); 
           sprintf(msend,"AE2%cZ\n",codevE);
           Serial.println(msend);
          } 
                      
         else 
          {
           ficatreu();
           sprintf(msend,"AE0%cZ\n",codevE);
           Serial.println(msend);
          }  
       } 
                           
         break;
         
 //----------------------------------------CASE C---------------------------------//
         case 'C':

                                //---errors---//
        if (mreciv[0] == 'A' && codevM=='1') {
          if ((mreciv [2] != 'Z') || (mreciv [1] =='A'))
          {
             sprintf(msend,"AC1%04dZ\n", 0);
          }//END IF
          else if (codevM == 0){
            sprintf(msend,"AC2%04dZ\n",0);
            Serial.println(msend);
          }  //END ELSE IF
           else {
             sprintf(msend,"AC0%04dZ\n",valor_sensor);
             Serial.println(msend);
          }  //END ELSE 
       }
       break;          
   
       
      }//END SWITCH
    
      memset( mreciv, 0, MIDA );
      memset( msend, 0, MIDA );
  

  
}//END LOOP




//----------------------------------------SUBFUNCIONS---------------------------------//

void msnread ()
{
  if (Serial.available())
  {
    memset( mreciv, 0, MIDA );
    Serial.readBytesUntil('\n',mreciv,MIDA);
  }
       
}//end msnread

void ficatreu ()
{ 
  int tmp;  //PIN ENTRADA / SORTIDA
  int ent;  //VALOR ENTRADA

  tmp = (codenn[0]-48) * 10 + (codenn[1]-48); //CONVERSIÓ DE ASCII A INT
  
  if (mreciv[1]== 'S')
  {
    
    pinMode(tmp,OUTPUT);
    codevS = mreciv[4];
    
    if (codevS == '0')
    {
      digitalWrite(tmp,LOW);
    } 
    else if (codevS == '1')
    { 
      digitalWrite(tmp,HIGH);
    }          
  }
             
  if (mreciv[1] == 'E')   
  {
    pinMode(tmp,INPUT);
    ent=digitalRead(tmp);
  }
     
  codevE = ent + 48;
 
}//END FICATREU



ISR(TIMER1_COMPA_vect)
  {
  
    if((i>tiempo) )
    {
  
          valor_sensor = analogRead(SENSOR);
       
          i=0;

    }//END IF
    i++;
  }//END ISR
  


  
