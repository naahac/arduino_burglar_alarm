
//TODO:
// prestavljanje kazalca pri nastavljanju ure
// default ura = 0
// when cancel while editing set back to previous time
// if approved while editing (jump to next || finish and approve)

#define DEFAULT_TIME 0
#define DEFAULT_DATE 0
#define DAYS_OF_YEAR 365

int curent_time = DEFAULT_TIME;
int curent_date = DEFAULT_DATE;

int new_time;
int new_date;

char months[12] = {31,30,31,28,31,30,31,31,30,31,30,31};


char getIRInput(){
  while(true)
  if(irrecv.decode(&results)){
    switch(results.value){
      case IR_0:
        return 0;  
      case IR_1:
        return 1;  
      case IR_2:
        return 2;  
      case IR_3:
        return 3;  
      case IR_4:
        return 4;  
      case IR_5:
        return 5;  
      case IR_6:
        return 6;  
      case IR_7:
        return 7;  
      case IR_8:
        return 8;
      case IR_9:
        return 9;
      //check for interuption
    }    
  }
}


char digitToChar(char num){
    return num+48; // gets a ascii sign of a number  
}



char* numberToCharArray(char num){
  char arr[2];
  arr[0] = digitToChar(num/10);
  arr[1] = digitToChar(num%10);
  return arr;
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
  
  num = getIRInput();
  lcd.setCursor(row,column+1);
  lcd.print(digitToChar(num));
  
  input +=num;
  
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

    printCharArray(numberToCharArray(input),0,0);
}

void setMinutes(){

    char input;
    //checks format
    do{
        input = getTimeInput(3,0);
    }while(input>=0 && input < 60);

    printCharArray(numberToCharArray(input),3,0);

}

void setSeconds(){
    char input;
    //checks format
    do{
        input = getTimeInput(5,0);
    }while(input>=0 && input < 60);

    printCharArray(numberToCharArray(input),5,0);
}

void setTime(){

    setHours();
    setMinutes();
    setSeconds();  
}

void setDay(char month){
    char input;
    //checks format
    do{
        input = getTimeInput(9,0);
    }while(input>=0 && input < months[month]);

    new_time += input; 

    printCharArray(numberToCharArray(input),9,0);
}

char setMonth(){
    char input;
    //checks format
    do{
        input = getTimeInput(12,0);
    }while(input>=1 && input < 13);

    //adds days of previous months of this year
    for(char i=0; i<input-1; i++)
        new_time += months[i];

    printCharArray(numberToCharArray(input),12,0);
    return input;
}

void setYear(){
    char input;
    //checks format
    do{
        input = getTimeInput(15,0);
    }while(input>=0 && input < 100);

    //adds days of year
    new_time += input*DAYS_OF_YEAR;

    printCharArray(numberToCharArray(input),15,0);
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
    char timeString[8];
    sprintf(timeString, "%s//%s//%s",numberToCharArray(curent_time/60*60),numberToCharArray((curent_time/60)%60),numberToCharArray((curent_time%60)));
    printCharArray(timeString,0,0);
    //return timeString;
}

void printDate(){
    char dateString[8];
    sprintf(dateString, "%s//%s//%s",numberToCharArray(getDay()),numberToCharArray(getMonth()),numberToCharArray(getYear()));
    printCharArray(dateString,9,0);
    //return dateString;
}

void printDateTime(){
    printTime();
    lcd.setCursor(8,0);
    lcd.print("-");
    printDate();
}
