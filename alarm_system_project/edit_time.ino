
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


int getTimeInput(char row, char column){  //row and column are used for setting where on lcd we are changing
  //gets input of 2 integers;
  
  //check for interuption
  }

void setHours(){
    
    char input;
    //checks format
    
    input = getTimeInput();
    if(input >= 24)
      input = 23;
    if(input<0)
      input = 0;    
}

void setMinutes(){

    char input;
    //checks format
    do{
        input = getTimeInput();
    }while(input>=0 && input < 60)


}

void setSeconds(){
    char input;
    //checks format
    do{
        input = getTimeInput();
    }while(input>=0 && input < 60)

  
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
        input = getTimeInput();
    }while(input>=0 && input < months[month])

    new_time += input; 

}

void setMonth(){
    char input;
    //checks format
    do{
        input = getTimeInput();
    }while(input>=1 && input < 13)

    //adds days of previous months of this year
    for(char i=0; i<input-1; i++)
        new_time += month[i];

}

void setYear(){
    char input;
    //checks format
    do{
        input = getTimeInput();
    }while(input>=0 && input < 100)

    //adds days of year
    new_time += input*DAYS_OF_YEAR;

}


void setDate(){
    
    setMonth();
    setDay();
    setYear();

}

void setDateTime(){
    setTime();
    setDate();
}
