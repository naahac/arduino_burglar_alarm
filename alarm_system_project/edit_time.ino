
//TODO:
// prestavljanje kazalca pri nastavljanju ure
// default ura = 0
// when cancel while editing set back to previous time
// if approved while editing (jump to next || finish and approve)

#define DEFAULT_TIME 4862
#define DEFAULT_DATE 2389
#define DAYS_OF_YEAR 365

int curent_time = DEFAULT_TIME;
int curent_date = DEFAULT_DATE;

int new_time;
int new_date;

char months[12] = {31,30,31,28,31,30,31,31,30,31,30,31};


char getIRInput(){
  Serial.println("Gimme input");
  while(true){
    if(irrecv.decode(&results)){
      int input_number = -1;
      switch(results.value){
        case IR_0:
          input_number = 0;
          break;  
        case IR_1:
          input_number = 1;
          break;  
        case IR_2:
          input_number = 2;
          break;   
        case IR_3:
          input_number = 3;
          break;  
        case IR_4:
          input_number = 4;
          break;  
        case IR_5:
          input_number = 5;
          break;  
        case IR_6:
          input_number = 6;
          break;  
        case IR_7:
          input_number = 7;
          break;  
        case IR_8:
          input_number = 8;
          break;  
        case IR_9:
          input_number = 9;
          break;  
        //check for interuption
      }
      if(input_number!=-1){
          //irrecv.resume();
          return input_number;
      }
    }
  }
}


char digitToChar(char num){
    
    //Serial.println(num+48);
    return num+48; // gets a ascii sign of a number  
}



void numberToCharArray(char* arr,char num) {
  arr[0] = digitToChar(num / 10);
  arr[1] = digitToChar(num % 10);
  arr[2] = '\0';
}

void printCharArray(char arr[],char row,char column){
  lcd.setCursor(row,column);
  lcd.print(arr);
}

char getTimeInput(char row, char column){  //row and column are used for setting where on lcd we are changing
  //gets input of 2 integers
  char input,num;
  
  num = getIRInput();
  lcd.setCursor(row,column);
  lcd.print(digitToChar(num));
  
  input = 10*num;
  Serial.println(input);
  num = getIRInput();
  lcd.setCursor(row,column+1);
  lcd.print(digitToChar(num));
  
  input +=num;

  Serial.println(input);
  return input;
}

void setHours(){
    
    char input;
    //checks format
    
    input = getTimeInput(0,0);
    if(input >= 24)
      input = 23;
    if(input<0)
      input = 0;

    char arr[3];
    numberToCharArray(arr, input);
    printCharArray(arr, 0, 0); 
}

void setMinutes(){

    char input;
    //checks format
    do{
        input = getTimeInput(3,0);
    }while(input>=0 && input < 60);

    char arr[3];
    numberToCharArray(arr, input);
    printCharArray(arr, 3, 0);
}

/*
void setSeconds(){
    char input;
    //checks format
    do{
        input = getTimeInput(5,0);
    }while(input>=0 && input < 60);

    char arr[3];
    numberToCharArray(arr, input);
    printCharArray(arr, 5, 0);
}
*/

void setTime(){

    setHours();
    setMinutes();
    //setSeconds();  
}

void setDay(char month){
    char input;
    //checks format
    do{
        input = getTimeInput(8,0);
    }while(input>=0 && input < months[month]);

    new_time += input; 

    char arr[3];
    numberToCharArray(arr, input);
    printCharArray(arr, 8, 0);
}

char setMonth(){
    char input;
    //checks format
    do{
        input = getTimeInput(11,0);
    }while(input>=1 && input < 13);

    //adds days of previous months of this year
    for(char i=0; i<input-1; i++)
        new_time += months[i];

    char arr[3];
    numberToCharArray(arr, input);
    printCharArray(arr, 11, 0);
    return input;
}

void setYear(){
    char input;
    //checks format
    do{
        input = getTimeInput(14,0);
    }while(input>=0 && input < 100);

    //adds days of year
    new_time += input*DAYS_OF_YEAR;

    char arr[3];
    numberToCharArray(arr, input);
    printCharArray(arr, 14, 0);
    
}


void setDate(){
    
    char month = setMonth();
    setDay(month);
    setYear();

}

void setDateTime(){
    setTime();
    setDate();
}

char getDay(){
    short days = curent_date % DAYS_OF_YEAR;
    char i = 0;
    for(; months[i] < days; i++){
        days -= months[i];
    }
    return days;
}

char getMonth(){
    short month_in_days = curent_date % DAYS_OF_YEAR;
    short tmp_month = 0;
    char i = 0;
    for(; tmp_month < month_in_days; i++){
        tmp_month += months[i];
    }
    return i;
}

char getYear(){
    return curent_date/DAYS_OF_YEAR;
}


void printTime(){
    char timeString[5];
    char time_hours[3],time_minutes[3],time_seconds[3];
    numberToCharArray(time_hours,(char)((int)curent_time / (60 * 60)));
    numberToCharArray(time_minutes, (curent_time / 60) % 60);
    //numberToCharArray(time_seconds,curent_time % 60);

    //sprintf(timeString, "%s/%s/%s",time_hours,time_minutes,time_seconds);
    sprintf(timeString, "%s:%s",time_hours,time_minutes);
    //Serial.println(timeString);
    printCharArray(timeString,0,0);
    //return timeString;
}

void printDate(){
    char dateString[8];
    char day[3],month[3],year[3];
    numberToCharArray(day,getDay());
    numberToCharArray(month, getMonth());
    numberToCharArray(year,getYear());

    sprintf(dateString, "%s/%s/%s",day,month,year);
    printCharArray(dateString,8,0);
    //return dateString;
}

void printDateTime(){
    printTime();
    lcd.setCursor(5,0);
    lcd.print(" - ");
    printDate();
}
